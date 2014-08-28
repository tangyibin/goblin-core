//===- GC64.td - Describe the GC64 Target Machine -------*- tblgen -*-==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This is the top level entry point for the GC64 target.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// GC64 Subtarget features.
//

def FeatureFPGC64 : SubtargetFeature<"fp-gc64", "HasFPGC64", "true",
  "Enable GC64 FP">;

def FeatureGC64SIMD : SubtargetFeature<"simd", "HasSIMD", "true",
  "Enable Advanced SIMD instructions", [FeatureFPGC64]>;

//===----------------------------------------------------------------------===//
// GC64 Processors
//

include "GC64Schedule.td"

def : Processor<"generic", GenericItineraries, [FeatureFPGC64]>;

//===----------------------------------------------------------------------===//
// Register File Description
//===----------------------------------------------------------------------===//

include "GC64RegisterInfo.td"

include "GC64CallingConv.td"

//===----------------------------------------------------------------------===//
// Instruction Descriptions
//===----------------------------------------------------------------------===//

include "GC64InstrInfo.td"

def GC64InstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// Assembly printer
//===----------------------------------------------------------------------===//

def GC64InstPrinter : AsmWriter {
  string AsmWriterClassName = "InstPrinter";
  bit isMCAsmWriter = 1;
}

//===----------------------------------------------------------------------===//
// Declare the target which we are implementing
//===----------------------------------------------------------------------===//

def GC64 : Target {
  let InstructionSet = GC64InstrInfo;
  let AssemblyWriters = [GC64InstPrinter];
}
