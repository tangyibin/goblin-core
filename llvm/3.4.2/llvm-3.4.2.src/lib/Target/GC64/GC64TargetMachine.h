//=== GC64TargetMachine.h - Define TargetMachine for GC64 -*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the GC64 specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_AARCH64TARGETMACHINE_H
#define LLVM_AARCH64TARGETMACHINE_H

#include "GC64FrameLowering.h"
#include "GC64ISelLowering.h"
#include "GC64InstrInfo.h"
#include "GC64SelectionDAGInfo.h"
#include "GC64Subtarget.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class GC64TargetMachine : public LLVMTargetMachine {
  GC64Subtarget          Subtarget;
  GC64InstrInfo          InstrInfo;
  const DataLayout          DL;
  GC64TargetLowering     TLInfo;
  GC64SelectionDAGInfo   TSInfo;
  GC64FrameLowering      FrameLowering;

public:
  GC64TargetMachine(const Target &T, StringRef TT, StringRef CPU,
                       StringRef FS, const TargetOptions &Options,
                       Reloc::Model RM, CodeModel::Model CM,
                       CodeGenOpt::Level OL);

  const GC64InstrInfo *getInstrInfo() const {
    return &InstrInfo;
  }

  const GC64FrameLowering *getFrameLowering() const {
    return &FrameLowering;
  }

  const GC64TargetLowering *getTargetLowering() const {
    return &TLInfo;
  }

  const GC64SelectionDAGInfo *getSelectionDAGInfo() const {
    return &TSInfo;
  }

  const GC64Subtarget *getSubtargetImpl() const { return &Subtarget; }

  const DataLayout *getDataLayout() const { return &DL; }

  const TargetRegisterInfo *getRegisterInfo() const {
    return &InstrInfo.getRegisterInfo();
  }
  TargetPassConfig *createPassConfig(PassManagerBase &PM);
};

}

#endif
