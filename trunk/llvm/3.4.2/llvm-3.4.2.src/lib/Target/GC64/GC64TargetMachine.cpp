//===-- GC64TargetMachine.cpp - Define TargetMachine for GC64 -------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the implementation of the GC64TargetMachine
// methods. Principally just setting up the passes needed to generate correct
// code on this architecture.
//
//===----------------------------------------------------------------------===//

#include "GC64.h"
#include "GC64TargetMachine.h"
#include "MCTargetDesc/GC64MCTargetDesc.h"
#include "llvm/PassManager.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

extern "C" void LLVMInitializeGC64Target() {
  RegisterTargetMachine<GC64TargetMachine> X(TheGC64Target);
}

GC64TargetMachine::GC64TargetMachine(const Target &T, StringRef TT,
                                           StringRef CPU, StringRef FS,
                                           const TargetOptions &Options,
                                           Reloc::Model RM, CodeModel::Model CM,
                                           CodeGenOpt::Level OL)
  : LLVMTargetMachine(T, TT, CPU, FS, Options, RM, CM, OL),
    Subtarget(TT, CPU, FS),
    InstrInfo(Subtarget),
    DL("e-p:64:64-i64:64:64-f128:128:128-v64:64:64"),
    TLInfo(*this),
    TSInfo(*this),
    FrameLowering(Subtarget) {
  initAsmInfo();
}

namespace {
/// GC64 Code Generator Pass Configuration Options.
class GC64PassConfig : public TargetPassConfig {
public:
  GC64PassConfig(GC64TargetMachine *TM, PassManagerBase &PM)
    : TargetPassConfig(TM, PM) {}

  GC64TargetMachine &getGC64TargetMachine() const {
    return getTM<GC64TargetMachine>();
  }

  const GC64Subtarget &getGC64Subtarget() const {
    return *getGC64TargetMachine().getSubtargetImpl();
  }

  virtual bool addInstSelector();
  virtual bool addPreEmitPass();
};
} // namespace

TargetPassConfig *GC64TargetMachine::createPassConfig(PassManagerBase &PM) {
  return new GC64PassConfig(this, PM);
}

bool GC64PassConfig::addPreEmitPass() {
  addPass(&UnpackMachineBundlesID);
  addPass(createGC64BranchFixupPass());
  return true;
}

bool GC64PassConfig::addInstSelector() {
  addPass(createGC64ISelDAG(getGC64TargetMachine(), getOptLevel()));

  // For ELF, cleanup any local-dynamic TLS accesses.
  if (getGC64Subtarget().isTargetELF() && getOptLevel() != CodeGenOpt::None)
    addPass(createGC64CleanupLocalDynamicTLSPass());

  return false;
}
