//===-- RISCVMCObjectWriter.cpp - RISCV ELF writer --------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/RISCVMCTargetDesc.h"
#include "MCTargetDesc/RISCVMCFixups.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCValue.h"

using namespace llvm;

namespace {
class RISCVObjectWriter : public MCELFObjectTargetWriter {
public:
  RISCVObjectWriter(uint8_t OSABI);

  virtual ~RISCVObjectWriter();

protected:
  // Override MCELFObjectTargetWriter.
#if 0
  unsigned GetRelocType(const MCValue &Target, const MCFixup &Fixup,
                                bool IsPCRel, bool IsRelocWithSymbol,
                                int64_t Addend) const override;
#endif
  unsigned GetRelocType(const MCValue &Target, const MCFixup &Fixup,
                          bool IsPCRel) const override;
#if 0
  //-- DEPRECATED
  const MCSymbol *ExplicitRelSym(const MCAssembler &Asm,
                                         const MCValue &Target,
                                         const MCFragment &F,
                                         const MCFixup &Fixup,
                                         bool IsPCRel) const override;
#endif
   bool needsRelocateWithSymbol(const MCSymbolData &SD,
                                 unsigned Type) const override;
};
} // end anonymouse namespace

RISCVObjectWriter::RISCVObjectWriter(uint8_t OSABI)
  : MCELFObjectTargetWriter(/*Is64Bit=*/true, OSABI, ELF::EM_S390,
                            /*HasRelocationAddend=*/ true) {}

RISCVObjectWriter::~RISCVObjectWriter() {
}

// Return the relocation type for an absolute value of MCFixupKind Kind.
static unsigned getAbsoluteReloc(unsigned Kind) {
  switch (Kind) {
  case FK_Data_1: return ELF::R_390_8;
  case FK_Data_2: return ELF::R_390_16;
  case FK_Data_4: return ELF::R_390_32;
  case FK_Data_8: return ELF::R_390_64;
  }
  llvm_unreachable("Unsupported absolute address");
}

//TODO: fix relocation types
// Return the relocation type for a PC-relative value of MCFixupKind Kind.
static unsigned getPCRelReloc(unsigned Kind) {
  switch (Kind) {
  case FK_Data_2:                return ELF::R_390_PC16;
  case FK_Data_4:                return ELF::R_390_PC32;
  case FK_Data_8:                return ELF::R_390_PC64;
  case RISCV::FK_390_PC16DBL:  return ELF::R_390_PC16DBL;
  case RISCV::FK_390_PC32DBL:  return ELF::R_390_PC32DBL;
  case RISCV::FK_390_PLT16DBL: return ELF::R_390_PLT16DBL;
  case RISCV::FK_390_PLT32DBL: return ELF::R_390_PLT32DBL;
  case RISCV::FK_390_PLT64DBL: return ELF::R_390_PLT64;
  }
  llvm_unreachable("Unsupported PC-relative address");
}

// Return the R_390_TLS_LE* relocation type for MCFixupKind Kind.
static unsigned getTLSLEReloc(unsigned Kind) {
  switch (Kind) {
  case FK_Data_4: return ELF::R_390_TLS_LE32;
  case FK_Data_8: return ELF::R_390_TLS_LE64;
  }
  llvm_unreachable("Unsupported absolute address");
}

// Return the PLT relocation counterpart of MCFixupKind Kind.
static unsigned getPLTReloc(unsigned Kind) {
  switch (Kind) {
  case RISCV::FK_390_PC16DBL: return ELF::R_390_PLT16DBL;
  case RISCV::FK_390_PC32DBL: return ELF::R_390_PLT32DBL;
  }
  llvm_unreachable("Unsupported absolute address");
}

#if 0
unsigned RISCVObjectWriter::GetRelocType(const MCValue &Target,
                                           const MCFixup &Fixup,
                                           bool IsPCRel,
                                           bool IsRelocWithSymbol,
                                           int64_t Addend) const {
#endif
unsigned RISCVObjectWriter::GetRelocType(const MCValue &Target,
                                           const MCFixup &Fixup,
                                           bool IsPCRel) const {
  MCSymbolRefExpr::VariantKind Modifier = (Target.isAbsolute() ?
                                           MCSymbolRefExpr::VK_None :
                                           Target.getSymA()->getKind());
  unsigned Kind = Fixup.getKind();
  switch (Modifier) {
  case MCSymbolRefExpr::VK_None:
    if (IsPCRel)
      return getPCRelReloc(Kind);
    return getAbsoluteReloc(Kind);

  case MCSymbolRefExpr::VK_NTPOFF:
    assert(!IsPCRel && "NTPOFF shouldn't be PC-relative");
    return getTLSLEReloc(Kind);

  case MCSymbolRefExpr::VK_GOT:
    if (IsPCRel && Kind == RISCV::FK_390_PC32DBL)
      return ELF::R_390_GOTENT;
    llvm_unreachable("Only PC-relative GOT accesses are supported for now");

  case MCSymbolRefExpr::VK_PLT:
    assert(IsPCRel && "@PLT shouldt be PC-relative");
    return getPLTReloc(Kind);

  default:
    llvm_unreachable("Modifier not supported");
  }
}

#if 0
//-- DEPRECATED 
const MCSymbol *RISCVObjectWriter::ExplicitRelSym(const MCAssembler &Asm,
                                                    const MCValue &Target,
                                                    const MCFragment &F,
                                                    const MCFixup &Fixup,
                                                    bool IsPCRel) const {
  // The addend in a PC-relative R_390_* relocation is always applied to
  // the PC-relative part of the address.  If some kind of indirection
  // is applied to the symbol first, we can't use an addend there too.
  if (!Target.isAbsolute() &&
      Target.getSymA()->getKind() != MCSymbolRefExpr::VK_None &&
      IsPCRel)
    return &Target.getSymA()->getSymbol().AliasedSymbol();
  return NULL;
}
#endif


bool
RISCVObjectWriter::needsRelocateWithSymbol(const MCSymbolData &SD,
                                             unsigned Type) const {
  // FIXME: This is extremelly conservative. This really needs to use a
  // whitelist with a clear explanation for why each realocation needs to
  // point to the symbol, not to the section.

  // John Leidel : 
  // We need to add the necessary enums to Support/ELF.h for RISCV
  // This includes the necessary 32, 64 and 128 reloc data
  // for dynamically and statically linked objects
  switch (Type) {
  default:
    return true;
  }
}

MCObjectWriter *llvm::createRISCVObjectWriter(raw_ostream &OS,
                                                uint8_t OSABI) {
  MCELFObjectTargetWriter *MOTW = new RISCVObjectWriter(OSABI);
  return createELFObjectWriter(MOTW, OS, /*IsLittleEndian=*/false);
}
