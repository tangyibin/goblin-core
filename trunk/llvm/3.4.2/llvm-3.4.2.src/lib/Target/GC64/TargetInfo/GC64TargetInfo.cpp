//===-- GC64TargetInfo.cpp - GC64 Target Implementation -------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the key registration step for the architecture.
//
//===----------------------------------------------------------------------===//

#include "GC64.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

Target llvm::TheGC64Target;

extern "C" void LLVMInitializeGC64TargetInfo() {
    RegisterTarget<Triple::gc64, /*HasJIT=*/true>
    X(TheGC64Target, "gc64", "GC64 (GoblinCore-64 target)");
}
