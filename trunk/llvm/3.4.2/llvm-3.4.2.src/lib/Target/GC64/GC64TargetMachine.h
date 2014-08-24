//===-- GC64TargetMachine.h - Define TargetMachine for GC64 ---*- C++ -*-===//
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

#ifndef GC64TARGETMACHINE_H
#define GC64TARGETMACHINE_H

#include "GC64FrameLowering.h"
#include "GC64ISelLowering.h"
#include "GC64InstrInfo.h"
#include "GC64JITInfo.h"
#include "GC64SelectionDAGInfo.h"
#include "GC64Subtarget.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetFrameLowering.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class GC64TargetMachine : public LLVMTargetMachine {
  GC64Subtarget Subtarget;
  const DataLayout DL;       // Calculates type size & alignment
  GC64InstrInfo InstrInfo;
  GC64TargetLowering TLInfo;
  GC64SelectionDAGInfo TSInfo;
  GC64FrameLowering FrameLowering;
  GC64JITInfo JITInfo;
public:
  GC64TargetMachine(const Target &T, StringRef TT,
                     StringRef CPU, StringRef FS, const TargetOptions &Options,
                     Reloc::Model RM, CodeModel::Model CM,
                     CodeGenOpt::Level OL, bool is64bit);

  virtual const GC64InstrInfo *getInstrInfo() const { return &InstrInfo; }
  virtual const TargetFrameLowering  *getFrameLowering() const {
    return &FrameLowering;
  }
  virtual const GC64Subtarget   *getSubtargetImpl() const{ return &Subtarget; }
  virtual const GC64RegisterInfo *getRegisterInfo() const {
    return &InstrInfo.getRegisterInfo();
  }
  virtual const GC64TargetLowering* getTargetLowering() const {
    return &TLInfo;
  }
  virtual const GC64SelectionDAGInfo* getSelectionDAGInfo() const {
    return &TSInfo;
  }
  virtual GC64JITInfo *getJITInfo() {
    return &JITInfo;
  }
  virtual const DataLayout       *getDataLayout() const { return &DL; }

  // Pass Pipeline Configuration
  virtual TargetPassConfig *createPassConfig(PassManagerBase &PM);
  virtual bool addCodeEmitter(PassManagerBase &PM, JITCodeEmitter &JCE);
};

} // end namespace llvm

#endif /* define GC64TARGETMACHINE_H */

