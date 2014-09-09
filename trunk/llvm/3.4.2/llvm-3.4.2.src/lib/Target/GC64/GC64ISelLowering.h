//===-- GC64ISelLowering.h - GC64 DAG Lowering Interface ------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the interfaces that GC64 uses to lower LLVM code into a
// selection DAG.
//
//===----------------------------------------------------------------------===//

#ifndef GC64ISELLOWERING_H
#define GC64ISELLOWERING_H

#include "GC64.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/Target/TargetLowering.h"

namespace llvm {

// Forward delcarations
class GC64Subtarget;
class GC64TargetMachine;

namespace GC64ISD {
enum NodeType {
  // Start the numbering where the builtin ops and target ops leave off.
  FIRST_NUMBER = ISD::BUILTIN_OP_END,
  RET_FLAG,
  // This loads the symbol (e.g. global address) into a register.
  LOAD_SYM,
  // This loads a 32-bit immediate into a register.
  MOVEi32,
  CALL,
};
}

//===--------------------------------------------------------------------===//
// TargetLowering Implementation
//===--------------------------------------------------------------------===//
class GC64TargetLowering : public TargetLowering {
public:
  explicit GC64TargetLowering(GC64TargetMachine &TM);

  /// LowerOperation - Provide custom lowering hooks for some operations.
  virtual SDValue LowerOperation(SDValue Op, SelectionDAG &DAG) const;

  /// getTargetNodeName - This method returns the name of a target specific
  //  DAG node.
  virtual const char *getTargetNodeName(unsigned Opcode) const;

private:
  const GC64TargetMachine &TM;
  const GC64Subtarget &Subtarget;

  SDValue LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv,
                               bool isVarArg,
                               const SmallVectorImpl<ISD::InputArg> &Ins,
                               SDLoc dl, SelectionDAG &DAG,
                               SmallVectorImpl<SDValue> &InVals) const override;

  SDValue LowerCall(TargetLowering::CallLoweringInfo &CLI,
                    SmallVectorImpl<SDValue> &InVals) const override;

  SDValue LowerReturn(SDValue Chain, CallingConv::ID CallConv, bool isVarArg,
                      const SmallVectorImpl<ISD::OutputArg> &Outs,
                      const SmallVectorImpl<SDValue> &OutVals, SDLoc dl,
                      SelectionDAG &DAG) const override;

  SDValue LowerCallResult(SDValue Chain, SDValue InGlue,
                          CallingConv::ID CallConv, bool isVarArg,
                          const SmallVectorImpl<ISD::InputArg> &Ins, SDLoc dl,
                          SelectionDAG &DAG,
                          SmallVectorImpl<SDValue> &InVals) const;

  bool CanLowerReturn(CallingConv::ID CallConv, MachineFunction &MF,
                      bool isVarArg,
                      const SmallVectorImpl<ISD::OutputArg> &ArgsFlags,
                      LLVMContext &Context) const;

  // LowerGlobalAddress - Emit a constant load to the global address.
  SDValue LowerGlobalAddress(SDValue Op, SelectionDAG &DAG) const;
};
}

#endif // GC64ISELLOWERING_H

