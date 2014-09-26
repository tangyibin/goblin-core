//===-- RISCVSelectionDAGInfo.h - RISCV SelectionDAG Info ---------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the RISCV subclass for TargetSelectionDAGInfo.
//
//===----------------------------------------------------------------------===//

#ifndef RISCVSELECTIONDAGINFO_H
#define RISCVSELECTIONDAGINFO_H

#include "llvm/Target/TargetSelectionDAGInfo.h"

namespace llvm {

class RISCVTargetMachine;

class RISCVSelectionDAGInfo : public TargetSelectionDAGInfo {
public:
  explicit RISCVSelectionDAGInfo(const DataLayout &DL);
  ~RISCVSelectionDAGInfo();
};

}

#endif
