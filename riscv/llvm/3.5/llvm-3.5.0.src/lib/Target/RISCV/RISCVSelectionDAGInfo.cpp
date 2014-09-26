//===-- RISCVSelectionDAGInfo.cpp - RISCV SelectionDAG Info -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the RISCVSelectionDAGInfo class.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "riscv-selectiondag-info"
#include "RISCVTargetMachine.h"
using namespace llvm;

RISCVSelectionDAGInfo::RISCVSelectionDAGInfo(const DataLayout &DL)
    : TargetSelectionDAGInfo(&DL) {}

RISCVSelectionDAGInfo::~RISCVSelectionDAGInfo() {
}
