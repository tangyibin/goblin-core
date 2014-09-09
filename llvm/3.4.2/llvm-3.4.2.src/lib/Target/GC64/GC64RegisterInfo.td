//===- GC64RegisterInfo.td - GC64 Register defs ----------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//  This file contains declarations that describe the GC64 register file
//
//===----------------------------------------------------------------------===//


//-- GC64 top-level register class   
//-- We have banks of 64 registers each
class GC64Reg<bits<16> Enc, string n> : Register<n> {
	let HWEncoding = Enc;
	let Namespace = "GC64";
}

//===----------------------------------------------------------------------===//
//  GC64 Registers
//===----------------------------------------------------------------------===//
let Namespace = "GC64" in {

	//-- General Purpose Registers
	def R0	: GC64Reg<0,	"r0">,	DwarfRegNum<[0]>;
	def R1	: GC64Reg<1,	"r1">,	DwarfRegNum<[1]>;
	def R2	: GC64Reg<2,	"r2">,	DwarfRegNum<[2]>;
	def R3	: GC64Reg<3,	"r3">,	DwarfRegNum<[3]>;
	def R4	: GC64Reg<4,	"r4">,	DwarfRegNum<[4]>;
	def R5	: GC64Reg<5,	"r5">,	DwarfRegNum<[5]>;
	def R6	: GC64Reg<6,	"r6">,	DwarfRegNum<[6]>;
	def R7	: GC64Reg<7,	"r7">,	DwarfRegNum<[7]>;
	def R8	: GC64Reg<8,	"r8">,	DwarfRegNum<[8]>;
	def R9	: GC64Reg<9,	"r9">,	DwarfRegNum<[9]>;
	def R10	: GC64Reg<10,	"r10">,	DwarfRegNum<[10]>;
	def R11	: GC64Reg<11,	"r11">,	DwarfRegNum<[11]>;
	def R12	: GC64Reg<12,	"r12">,	DwarfRegNum<[12]>;
	def R13	: GC64Reg<13,	"r13">,	DwarfRegNum<[13]>;
	def R14	: GC64Reg<14,	"r14">,	DwarfRegNum<[14]>;
	def R15	: GC64Reg<15,	"r15">,	DwarfRegNum<[15]>;
	def R16	: GC64Reg<16,	"r16">,	DwarfRegNum<[16]>;
	def R17	: GC64Reg<17,	"r17">,	DwarfRegNum<[17]>;
	def R18	: GC64Reg<18,	"r18">,	DwarfRegNum<[18]>;
	def R19	: GC64Reg<19,	"r19">,	DwarfRegNum<[19]>;
	def R20	: GC64Reg<20,	"r20">,	DwarfRegNum<[20]>;
	def R21	: GC64Reg<21,	"r21">,	DwarfRegNum<[21]>;
	def R22	: GC64Reg<22,	"r22">,	DwarfRegNum<[22]>;
	def R23	: GC64Reg<23,	"r23">,	DwarfRegNum<[23]>;
	def R24	: GC64Reg<24,	"r24">,	DwarfRegNum<[24]>;
	def R25	: GC64Reg<25,	"r25">,	DwarfRegNum<[25]>;
	def R26	: GC64Reg<26,	"r26">,	DwarfRegNum<[26]>;
	def R27	: GC64Reg<27,	"r27">,	DwarfRegNum<[27]>;
	def R28	: GC64Reg<28,	"r28">,	DwarfRegNum<[28]>;
	def R29	: GC64Reg<29,	"r29">,	DwarfRegNum<[29]>;
	def R30	: GC64Reg<30,	"r30">,	DwarfRegNum<[30]>;
	def R31	: GC64Reg<31,	"r31">,	DwarfRegNum<[31]>;

	//-- Control Registers	
	def SP	: GC64Reg<32,	"sp">,	DwarfRegNum<[32]>;
	def FP	: GC64Reg<33,	"fp">,	DwarfRegNum<[33]>;
	def PIC	: GC64Reg<34,	"pic">,	DwarfRegNum<[34]>;
	def UP	: GC64Reg<35,	"up">,	DwarfRegNum<[35]>;
	def RP	: GC64Reg<36,	"rp">,	DwarfRegNum<[36]>;

	//-- Condition Code Registers
	def CC0	: GC64Reg<37,	"cc0">,	DwarfRegNum<[37]>;
	def CC1	: GC64Reg<38,	"cc1">,	DwarfRegNum<[38]>;
	def CC2	: GC64Reg<39,	"cc2">,	DwarfRegNum<[39]>;
	def CC3	: GC64Reg<40,	"cc3">,	DwarfRegNum<[40]>;

	//-- Tasking Registers
	def TQ	: GC64Reg<41,	"tq">,	DwarfRegNum<[41]>;
	def TID	: GC64Reg<47,	"tid">,	DwarfRegNum<[47]>;

	//-- Vector Control Registers
	def VL	: GC64Reg<42,	"vl">,	DwarfRegNum<[42]>;
	def VS	: GC64Reg<43,	"vs">,	DwarfRegNum<[43]>;

	//-- Mode Registers	
	def GMODE	: GC64Reg<44,	"gmode">,	DwarfRegNum<[44]>;
	def PMASK	: GC64Reg<45,	"pmask">,	DwarfRegNum<[45]>;
	def PREAD	: GC64Reg<46,	"pread">,	DwarfRegNum<[46]>;

	//-- IP
	def IP	: GC64Reg<46,	"ip">,	DwarfRegNum<[48]>;

	//-- Security Key
	def GKEY	: GC64Reg<51,	"gkey">,	DwarfRegNum<[51]>;

	//-- Read-Only Registers
	def GEXC	: GC64Reg<52,	"gexc">,	DwarfRegNum<[52]>;
	def ZERO	: GC64Reg<53,	"zero">,	DwarfRegNum<[53]>;
	def IMM32	: GC64Reg<54,	"imm32">,	DwarfRegNum<[54]>;
	def IMM64	: GC64Reg<55,	"imm64">,	DwarfRegNum<[55]>;
	def GCONST	: GC64Reg<56,	"gconst">,	DwarfRegNum<[56]>;

	//-- Read-Only: Combinatorial Registers
	def EQ	: GC64Reg<57,	"eq">,	DwarfRegNum<[57]>;
	def GT	: GC64Reg<58,	"gt">,	DwarfRegNum<[58]>;
	def GTE	: GC64Reg<59,	"gte">,	DwarfRegNum<[59]>;
	def LT	: GC64Reg<60,	"lt">,	DwarfRegNum<[60]>;
	def LTE : GC64Reg<61,	"lte">,	DwarfRegNum<[61]>;
	def NE	: GC64Reg<62,	"ne">,	DwarfRegNum<[62]>;
	
	//-- Read-Only Perf Counters 
	def PVAL	: GC64Reg<63,	"pval">,	DwarfRegNum<[63]>;
	
}


//===----------------------------------------------------------------------===//
//  GC64 Register Classes
//===----------------------------------------------------------------------===//

//-- General Purpose Registers
def GRRegs : RegisterClass<"GC64", [i64], 64, 
	(add R0, R1, R2, R3, R4, R5, R6, R7, R8, R9,
	R11, R12, R13, R14, R15, R16, R17, R18, R19, 
	R20, R21, R22, R23, R24, R25, R26, R27, R28, 
	R29, R30, R31, SP, FP, PIC, UP, RP, CC0, CC1,
	CC2, CC3, TQ, VL, VS, GMODE, PMASK, PREAD, TID, 
	IP, GKEY, GEXC, ZERO, IMM32, IMM64, GCONST, EQ,
	GT, GTE, LT, LTE, NE, PVAL)>;

//def R64	: RegisterClass<"GC64", [i64], 64, 
//		(sequence "R%u", 0, 31)> {
//}


//-- EOF: GC64RegisterInfo.td 
