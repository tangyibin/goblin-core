//===- GC64CallingConv.td - Calling Conventions for GC64 -*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// This describes the calling conventions for GC64 architecture.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// GC64 Return Value Calling Convention
//===----------------------------------------------------------------------===//
def RetCC_GC64 : CallingConv<[
  // i64 are returned in registers R0, R1, R2, R3
  CCIfType<[i64], CCAssignToReg<[R0, R1, R2, R3]>>,

  // Integer values get stored in stack slots that are 8 bytes in
  // size and 8-byte aligned.
  CCIfType<[i64], CCAssignToStack<8, 8>>
]>;

//===----------------------------------------------------------------------===//
// GC64 Argument Calling Conventions
//===----------------------------------------------------------------------===//
def CC_GC64 : CallingConv<[
  // Promote i8/i16/i32 arguments to i64.
  CCIfType<[i8, i16, i32], CCPromoteToType<i64>>,

  // The first 4 integer arguments are passed in integer registers.
  CCIfType<[i64], CCAssignToReg<[R0, R1, R2, R3]>>,

  // Integer values get stored in stack slots that are 8 bytes in
  // size and 8-byte aligned.
  CCIfType<[i64], CCAssignToStack<8, 8>>
]>;

def CC_Save : CalleeSavedRegs<(add R4, R5, R6, R7, R8, R9)>;
