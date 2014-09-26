//==- RISCVTargetMachine.h - Define TargetMachine for RISCV ---*- C++ -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the RISCV specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//


#ifndef RISCVTARGETMACHINE_H
#define RISCVTARGETMACHINE_H

#include "RISCVFrameLowering.h"
#include "RISCVISelLowering.h"
#include "RISCVInstrInfo.h"
#include "RISCVRegisterInfo.h"
#include "RISCVSubtarget.h"
#include "RISCVSelectionDAGInfo.h"
#if 0
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetFrameLowering.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetSelectionDAGInfo.h"
#endif
#include "llvm/ADT/OwningPtr.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class RISCVTargetMachine : public LLVMTargetMachine {
  RISCVSubtarget        *Subtarget;
  RISCVSubtarget	DefaultSubtarget;
  const DataLayout        DL;
  RISCVInstrInfo        InstrInfo;
  RISCVTargetLowering   TLInfo;
  RISCVSelectionDAGInfo  TSInfo;
  RISCVFrameLowering    FrameLowering;

public:
 RISCVTargetMachine(const Target &T, StringRef TT,
                                     StringRef CPU, StringRef FS,
                                     const TargetOptions &Options,
                                     Reloc::Model RM, CodeModel::Model CM,
                                     CodeGenOpt::Level OL);
  // Override TargetMachine.
  const TargetFrameLowering *getFrameLowering() const override {
    return &FrameLowering;
  }
  const RISCVInstrInfo *getInstrInfo() const override {
    return &InstrInfo;
  }
  const RISCVSubtarget *getSubtargetImpl() const override {
    if (Subtarget)
      return Subtarget;
    return &DefaultSubtarget;
  }
  const DataLayout *getDataLayout() const override {
    return &DL;
  }
  const RISCVRegisterInfo *getRegisterInfo() const override {
    return &InstrInfo.getRegisterInfo();
  }
  const RISCVTargetLowering *getTargetLowering() const override {
    return &TLInfo;
  }
  const RISCVSelectionDAGInfo *getSelectionDAGInfo() const
    override {
    return &TSInfo;
  }

  // Override LLVMTargetMachine
  virtual TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
};

} // end namespace llvm

#endif
