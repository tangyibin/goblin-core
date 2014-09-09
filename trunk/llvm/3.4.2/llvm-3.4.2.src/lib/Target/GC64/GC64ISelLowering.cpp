//===-- GC64ISelLowering.cpp - GC64 DAG Lowering Implementation ---------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the GC64TargetLowering class.
//
//===----------------------------------------------------------------------===//

#include "GC64ISelLowering.h"
#include "GC64.h"
#include "GC64MachineFunctionInfo.h"
#include "GC64Subtarget.h"
#include "GC64TargetMachine.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineJumpTableInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/ValueTypes.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalAlias.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
#include <algorithm>

using namespace llvm;

const char *GC64TargetLowering::getTargetNodeName(unsigned Opcode) const {
  switch (Opcode) {
  default:
    return NULL;
  case GC64ISD::RET_FLAG: return "RetFlag";
  case GC64ISD::LOAD_SYM: return "LOAD_SYM";
  case GC64ISD::MOVEi32: return "MOVEi32";
  case GC64ISD::CALL:     return "CALL";
  }
}

GC64TargetLowering::GC64TargetLowering(GC64TargetMachine &GC64TM)
    : TargetLowering(GC64TM, new TargetLoweringObjectFileELF()), TM(GC64TM),
      Subtarget(*GC64TM.getSubtargetImpl()) {
  // Set up the register classes.
  addRegisterClass(MVT::i32, &GC64::GRRegsRegClass);

  // Compute derived properties from the register classes
  computeRegisterProperties();

  setStackPointerRegisterToSaveRestore(GC64::SP);

  setSchedulingPreference(Sched::Source);

  // Nodes that require custom lowering
  setOperationAction(ISD::GlobalAddress, MVT::i32, Custom);
}

SDValue GC64TargetLowering::LowerOperation(SDValue Op, SelectionDAG &DAG) const {
  switch (Op.getOpcode()) {
  default:
    llvm_unreachable("Unimplemented operand");
  case ISD::GlobalAddress:
    return LowerGlobalAddress(Op, DAG);
  }
}

SDValue GC64TargetLowering::LowerGlobalAddress(SDValue Op, SelectionDAG& DAG) const
{
  EVT VT = Op.getValueType();
  GlobalAddressSDNode *GlobalAddr = cast<GlobalAddressSDNode>(Op.getNode());
  SDValue TargetAddr =
      DAG.getTargetGlobalAddress(GlobalAddr->getGlobal(), Op, MVT::i32);
  return DAG.getNode(GC64ISD::LOAD_SYM, Op, VT, TargetAddr);
}

//===----------------------------------------------------------------------===//
//                      Calling Convention Implementation
//===----------------------------------------------------------------------===//

#include "GC64GenCallingConv.inc"

//===----------------------------------------------------------------------===//
//                  Call Calling Convention Implementation
//===----------------------------------------------------------------------===//

/// GC64 call implementation
SDValue GC64TargetLowering::LowerCall(TargetLowering::CallLoweringInfo &CLI,
                                     SmallVectorImpl<SDValue> &InVals) const {
  SelectionDAG &DAG = CLI.DAG;
  SDLoc &dl = CLI.DL;
  SmallVectorImpl<ISD::OutputArg> &Outs = CLI.Outs;
  SmallVectorImpl<SDValue> &OutVals = CLI.OutVals;
  SmallVectorImpl<ISD::InputArg> &Ins = CLI.Ins;
  SDValue Chain = CLI.Chain;
  SDValue Callee = CLI.Callee;
  bool &isTailCall = CLI.IsTailCall;
  CallingConv::ID CallConv = CLI.CallConv;
  bool isVarArg = CLI.IsVarArg;

  if (isVarArg || isTailCall)
    llvm_unreachable("Unimplemented");

  // Analyze operands of the call, assigning locations to each operand.
  SmallVector<CCValAssign, 16> ArgLocs;
  CCState CCInfo(CallConv, isVarArg, DAG.getMachineFunction(), DAG.getTarget(),
                 ArgLocs, *DAG.getContext());
  CCInfo.AnalyzeCallOperands(Outs, CC_GC64);

  // Get the size of the outgoing arguments stack space requirement.
  const unsigned NumBytes = CCInfo.getNextStackOffset();

  Chain =
      DAG.getCALLSEQ_START(Chain, DAG.getIntPtrConstant(NumBytes, true), dl);

  SmallVector<std::pair<unsigned, SDValue>, 8> RegsToPass;
  SmallVector<SDValue, 8> MemOpChains;

  // Walk the register/memloc assignments, inserting copies/loads.
  for (unsigned i = 0, realArgIdx = 0, e = ArgLocs.size(); i != e;
       ++i, ++realArgIdx) {
    CCValAssign &VA = ArgLocs[i];
    SDValue Arg = OutVals[realArgIdx];

    // We only handle fully promoted arguments.
    assert(VA.getLocInfo() == CCValAssign::Full && "Unhandled loc info");

    if (!VA.isRegLoc()) {
      llvm_unreachable("Only passing paramters via registers");
    }

    RegsToPass.push_back(std::make_pair(VA.getLocReg(), Arg));
  }

  // Build a sequence of copy-to-reg nodes chained together with token chain
  // and flag operands which copy the outgoing args into the appropriate regs.
  SDValue InFlag;

  for (unsigned i = 0, e = RegsToPass.size(); i != e; ++i) {
    Chain = DAG.getCopyToReg(Chain, dl, RegsToPass[i].first,
                             RegsToPass[i].second, InFlag);
    InFlag = Chain.getValue(1);
  }

  // We only support calling global addresses.
  GlobalAddressSDNode *G = dyn_cast<GlobalAddressSDNode>(Callee);
  assert(G && "We only support the calling of global addresses");

  Callee = DAG.getGlobalAddress(G->getGlobal(), dl, getPointerTy(), 0);

  std::vector<SDValue> Ops;
  Ops.push_back(Chain);
  Ops.push_back(Callee);

  // Add argument registers to the end of the list so that they are known live
  // into the call.
  for (unsigned i = 0, e = RegsToPass.size(); i != e; ++i)
    Ops.push_back(DAG.getRegister(RegsToPass[i].first,
                                  RegsToPass[i].second.getValueType()));

  // Add a register mask operand representing the call-preserved registers.
  const uint32_t *Mask;
  const TargetRegisterInfo *TRI = getTargetMachine().getRegisterInfo();
  const GC64RegisterInfo *LRI = static_cast<const GC64RegisterInfo *>(TRI);
  Mask = LRI->getCallPreservedMask(CallConv);

  assert(Mask && "Missing call preserved mask for calling convention");
  Ops.push_back(DAG.getRegisterMask(Mask));

  if (InFlag.getNode())
    Ops.push_back(InFlag);

  SDVTList NodeTys = DAG.getVTList(MVT::Other, MVT::Glue);

  // Returns a chain and a flag for retval copy to use.
  Chain = DAG.getNode(GC64ISD::CALL, dl, NodeTys, &Ops[0], Ops.size());
  InFlag = Chain.getValue(1);

  Chain = DAG.getCALLSEQ_END(Chain, DAG.getIntPtrConstant(NumBytes, true),
                             DAG.getIntPtrConstant(0, true), InFlag, dl);
  if (!Ins.empty())
    InFlag = Chain.getValue(1);

  // Handle result values, copying them out of physregs into vregs that we
  // return.
  return LowerCallResult(Chain, InFlag, CallConv, isVarArg, Ins, dl, DAG,
                         InVals);
}

SDValue GC64TargetLowering::LowerCallResult(
    SDValue Chain, SDValue InGlue, CallingConv::ID CallConv, bool isVarArg,
    const SmallVectorImpl<ISD::InputArg> &Ins, SDLoc dl, SelectionDAG &DAG,
    SmallVectorImpl<SDValue> &InVals) const {
  assert(!isVarArg && "Unsupported");

  // Assign locations to each value returned by this call.
  SmallVector<CCValAssign, 16> RVLocs;
  CCState CCInfo(CallConv, isVarArg, DAG.getMachineFunction(),
                 getTargetMachine(), RVLocs, *DAG.getContext());

  CCInfo.AnalyzeCallResult(Ins, RetCC_GC64);

  // Copy all of the result registers out of their specified physreg.
  for (unsigned i = 0; i != RVLocs.size(); ++i) {
    Chain = DAG.getCopyFromReg(Chain, dl, RVLocs[i].getLocReg(),
                               RVLocs[i].getValVT(), InGlue).getValue(1);
    InGlue = Chain.getValue(2);
    InVals.push_back(Chain.getValue(0));
  }

  return Chain;
}

//===----------------------------------------------------------------------===//
//             Formal Arguments Calling Convention Implementation
//===----------------------------------------------------------------------===//

/// GC64 formal arguments implementation
SDValue GC64TargetLowering::LowerFormalArguments(
    SDValue Chain, CallingConv::ID CallConv, bool isVarArg,
    const SmallVectorImpl<ISD::InputArg> &Ins, SDLoc dl, SelectionDAG &DAG,
    SmallVectorImpl<SDValue> &InVals) const {
  MachineFunction &MF = DAG.getMachineFunction();
  MachineRegisterInfo &RegInfo = MF.getRegInfo();

  assert(!isVarArg && "VarArg not supported");

  // Assign locations to all of the incoming arguments.
  SmallVector<CCValAssign, 16> ArgLocs;
  CCState CCInfo(CallConv, isVarArg, DAG.getMachineFunction(),
                 getTargetMachine(), ArgLocs, *DAG.getContext());

  CCInfo.AnalyzeFormalArguments(Ins, CC_GC64);

  for (unsigned i = 0, e = ArgLocs.size(); i != e; ++i) {
    CCValAssign &VA = ArgLocs[i];
    SDValue ArgIn;

    assert(VA.isRegLoc() && "Can only pass arguments as registers");

    // Arguments passed in registers
    EVT RegVT = VA.getLocVT();
    switch (RegVT.getSimpleVT().SimpleTy) {
    default:
      llvm_unreachable("Unhandled type for register");
    case MVT::i32: {
      unsigned VReg = RegInfo.createVirtualRegister(&GC64::GRRegsRegClass);
      RegInfo.addLiveIn(VA.getLocReg(), VReg);
      ArgIn = DAG.getCopyFromReg(Chain, dl, VReg, RegVT);
      break;
    }
    }

    InVals.push_back(ArgIn);
  }

  return Chain;
}

//===----------------------------------------------------------------------===//
//               Return Value Calling Convention Implementation
//===----------------------------------------------------------------------===//

bool GC64TargetLowering::CanLowerReturn(
    CallingConv::ID CallConv, MachineFunction &MF, bool isVarArg,
    const SmallVectorImpl<ISD::OutputArg> &Outs, LLVMContext &Context) const {
  SmallVector<CCValAssign, 16> RVLocs;
  CCState CCInfo(CallConv, isVarArg, MF, getTargetMachine(), RVLocs, Context);
  if (!CCInfo.CheckReturn(Outs, RetCC_GC64))
    return false;
  if (CCInfo.getNextStackOffset() != 0 && isVarArg)
    return false;
  return true;
}

SDValue
GC64TargetLowering::LowerReturn(SDValue Chain, CallingConv::ID CallConv,
                               bool isVarArg,
                               const SmallVectorImpl<ISD::OutputArg> &Outs,
                               const SmallVectorImpl<SDValue> &OutVals,
                               SDLoc dl, SelectionDAG &DAG) const {
  if (isVarArg)
    report_fatal_error("VarArg not supported");

  // CCValAssign - represent the assignment of
  // the return value to a location
  SmallVector<CCValAssign, 16> RVLocs;

  // CCState - Info about the registers and stack slot.
  CCState CCInfo(CallConv, isVarArg, DAG.getMachineFunction(),
                 getTargetMachine(), RVLocs, *DAG.getContext());

  CCInfo.AnalyzeReturn(Outs, RetCC_GC64);

  SDValue Flag;
  SmallVector<SDValue, 4> RetOps(1, Chain);

  // Copy the result values into the output registers.
  for (unsigned i = 0; i != RVLocs.size(); ++i) {
    CCValAssign &VA = RVLocs[i];
    assert(VA.isRegLoc() && "Can only return in registers!");

    Chain = DAG.getCopyToReg(Chain, dl, VA.getLocReg(), OutVals[i], Flag);

    Flag = Chain.getValue(1);
    RetOps.push_back(DAG.getRegister(VA.getLocReg(), VA.getLocVT()));
  }

  RetOps[0] = Chain; // Update chain.

  // Add the flag if we have it.
  if (Flag.getNode())
    RetOps.push_back(Flag);

  return DAG.getNode(GC64ISD::RET_FLAG, dl, MVT::Other, &RetOps[0],
                     RetOps.size());
}
