//===-- GC64.h - Top-level interface for GC64 representation --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// GC64 back-end.
//
//===----------------------------------------------------------------------===//

#ifndef TARGET_GC64_H
#define TARGET_GC64_H

#include "MCTargetDesc/GC64MCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class TargetMachine;
class GC64TargetMachine;

FunctionPass *createGC64ISelDag(GC64TargetMachine &TM,
                               CodeGenOpt::Level OptLevel);
} // end namespace llvm;

#endif
