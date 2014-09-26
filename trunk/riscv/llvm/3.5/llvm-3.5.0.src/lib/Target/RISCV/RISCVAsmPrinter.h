//===-- RISCVAsmPrinter.h - RISCV LLVM assembly printer ----*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef RISCVASMPRINTER_H
#define RISCVASMPRINTER_H

#include "RISCVTargetMachine.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class MCStreamer;
class MachineBasicBlock;
class MachineInstr;
class Module;
class raw_ostream;

class LLVM_LIBRARY_VISIBILITY RISCVAsmPrinter : public AsmPrinter {
private:
  const RISCVSubtarget *Subtarget;

public:
  RISCVAsmPrinter(TargetMachine &TM, MCStreamer &Streamer)
    : AsmPrinter(TM, Streamer) {
    Subtarget = &TM.getSubtarget<RISCVSubtarget>();
  }

  // Override AsmPrinter.
  virtual const char *getPassName() const override {
    return "RISCV Assembly Printer";
  }
  void EmitInstruction(const MachineInstr *MI) override;
  //virtual void EmitMachineConstantPoolValue(MachineConstantPoolValue *MCPV)
  void EmitMachineConstantPoolValue(MachineConstantPoolValue *MCPV)
    override;
  void printOperand(const MachineInstr *MI, int opNum, raw_ostream &O);
  //virtual bool PrintAsmOperand(const MachineInstr *MI, unsigned OpNo,
  bool PrintAsmOperand(const MachineInstr *MI, unsigned OpNo,
                               unsigned AsmVariant, const char *ExtraCode,
                               raw_ostream &OS) override;
  //virtual bool PrintAsmMemoryOperand(const MachineInstr *MI, unsigned OpNo,
  bool PrintAsmMemoryOperand(const MachineInstr *MI, unsigned OpNo,
                                     unsigned AsmVariant,
                                     const char *ExtraCode,
                                     raw_ostream &OS) override;
  void printMemOperand(const MachineInstr *MI, int opNum, raw_ostream &OS);
  //virtual void EmitEndOfAsmFile(Module &M) override;
  void EmitEndOfAsmFile(Module &M) override;
};
} // end namespace llvm

#endif
