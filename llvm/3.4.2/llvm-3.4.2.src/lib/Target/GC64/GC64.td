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
// Descriptions 
//===----------------------------------------------------------------------===//

include "GC64RegisterInfo.td"
include "GC64IntrInfo.td"
include "GC64CallingConv.td"

//===----------------------------------------------------------------------===//
// GC64 processors supported 
//===----------------------------------------------------------------------===//
class Proc<string Name, list<SubtargetFeature> Features>
    : Processor<Name, NoItineraries, Features>;

def : Proc<"generic", []>;

//===----------------------------------------------------------------------===//
// Declare the target we are implementing  
//===----------------------------------------------------------------------===//
def GC64 : Target {
  let InstructionSet = GC64InstrInfo;
}

//===----------------------------------------------------------------------===//
// GC64 Subtarget features.
//

//def FeatureFPGC64 : SubtargetFeature<"fp-gc64", "HasFPGC64", "true",
//  "Enable GC64 FP">;

//def FeatureGC64SIMD : SubtargetFeature<"simd", "HasSIMD", "true",
//  "Enable Advanced SIMD instructions", [FeatureFPGC64]>;

//===----------------------------------------------------------------------===//
// EOF: GC64.td 
//===----------------------------------------------------------------------===//

