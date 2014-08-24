##===- lib/Target/GC64/Makefile -------------------------*- Makefile -*-===##
#
#                     The LLVM Compiler Infrastructure
#
# This file is distributed under the University of Illinois Open Source
# License. See LICENSE.TXT for details.
#
##===----------------------------------------------------------------------===##

LEVEL = ../../..
LIBRARYNAME = LLVMGC64CodeGen
TARGET = GC64 

# Make sure that tblgen is run, first thing.
BUILT_SOURCES = GC64GenAsmMatcher.inc \
   GC64GenAsmWriter.inc \
   GC64GenCallingConv.inc \
   GC64GenDAGISel.inc \
   GC64GenDisassemblerTables.inc \
   GC64GenInstrInfo.inc \
   GC64GenMCCodeEmitter.inc \
   GC64GenMCPseudoLowering.inc \
   GC64GenRegisterInfo.inc \
   GC64GenSubtargetInfo.inc

DIRS = InstPrinter AsmParser Disassembler TargetInfo MCTargetDesc Utils

include $(LEVEL)/Makefile.common


