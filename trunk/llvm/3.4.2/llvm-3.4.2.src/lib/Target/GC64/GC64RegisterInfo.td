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

//-- GC64 General Purpose Register Def
class GC64GPRReg<bits<16> Enc, string n> : GC64Reg<Enc, n>;

//===----------------------------------------------------------------------===//
//  GC64 Registers
//===----------------------------------------------------------------------===//
let Namespace = "GC64" in {

	//-- General Purpose Registers
	def R0	: GC64GPRReg<0,	"r0">,	DwarfRegNum<[0]>;
	def R1	: GC64GPRReg<1,	"r1">,	DwarfRegNum<[1]>;
	def R2	: GC64GPRReg<2,	"r2">,	DwarfRegNum<[2]>;
	def R3	: GC64GPRReg<3,	"r3">,	DwarfRegNum<[3]>;
	def R4	: GC64GPRReg<4,	"r4">,	DwarfRegNum<[4]>;
	def R5	: GC64GPRReg<5,	"r5">,	DwarfRegNum<[5]>;
	def R6	: GC64GPRReg<6,	"r6">,	DwarfRegNum<[6]>;
	def R7	: GC64GPRReg<7,	"r7">,	DwarfRegNum<[7]>;
	def R8	: GC64GPRReg<8,	"r8">,	DwarfRegNum<[8]>;
	def R9	: GC64GPRReg<9,	"r9">,	DwarfRegNum<[9]>;
	def R10	: GC64GPRReg<10,	"r10">,	DwarfRegNum<[10]>;
	def R11	: GC64GPRReg<11,	"r11">,	DwarfRegNum<[11]>;
	def R12	: GC64GPRReg<12,	"r12">,	DwarfRegNum<[12]>;
	def R13	: GC64GPRReg<13,	"r13">,	DwarfRegNum<[13]>;
	def R14	: GC64GPRReg<14,	"r14">,	DwarfRegNum<[14]>;
	def R15	: GC64GPRReg<15,	"r15">,	DwarfRegNum<[15]>;
	def R16	: GC64GPRReg<16,	"r16">,	DwarfRegNum<[16]>;
	def R17	: GC64GPRReg<17,	"r17">,	DwarfRegNum<[17]>;
	def R18	: GC64GPRReg<18,	"r18">,	DwarfRegNum<[18]>;
	def R19	: GC64GPRReg<19,	"r19">,	DwarfRegNum<[19]>;
	def R20	: GC64GPRReg<20,	"r20">,	DwarfRegNum<[20]>;
	def R21	: GC64GPRReg<21,	"r21">,	DwarfRegNum<[21]>;
	def R22	: GC64GPRReg<22,	"r22">,	DwarfRegNum<[22]>;
	def R23	: GC64GPRReg<23,	"r23">,	DwarfRegNum<[23]>;
	def R24	: GC64GPRReg<24,	"r24">,	DwarfRegNum<[24]>;
	def R25	: GC64GPRReg<25,	"r25">,	DwarfRegNum<[25]>;
	def R26	: GC64GPRReg<26,	"r26">,	DwarfRegNum<[26]>;
	def R27	: GC64GPRReg<27,	"r27">,	DwarfRegNum<[27]>;
	def R28	: GC64GPRReg<28,	"r28">,	DwarfRegNum<[28]>;
	def R29	: GC64GPRReg<29,	"r29">,	DwarfRegNum<[29]>;
	def R30	: GC64GPRReg<30,	"r30">,	DwarfRegNum<[30]>;
	def R31	: GC64GPRReg<31,	"r31">,	DwarfRegNum<[31]>;

	//-- Control Registers	
	def SP	: GC64GPRReg<32,	"sp">,	DwarfRegNum<[32]>;
	def FP	: GC64GPRReg<33,	"fp">,	DwarfRegNum<[33]>;
	def PIC	: GC64GPRReg<34,	"pic">,	DwarfRegNum<[34]>;
	def UP	: GC64GPRReg<35,	"up">,	DwarfRegNum<[35]>;
	def RP	: GC64GPRReg<36,	"rp">,	DwarfRegNum<[36]>;

	//-- Condition Code Registers
	def CC0	: GC64GPRReg<37,	"cc0">,	DwarfRegNum<[37]>;
	def CC1	: GC64GPRReg<38,	"cc1">,	DwarfRegNum<[38]>;
	def CC2	: GC64GPRReg<39,	"cc2">,	DwarfRegNum<[39]>;
	def CC3	: GC64GPRReg<40,	"cc3">,	DwarfRegNum<[40]>;

	//-- Tasking Registers
	def TQ	: GC64GPRReg<41,	"tq">,	DwarfRegNum<[41]>;
	def TID	: GC64GPRReg<47,	"tid">,	DwarfRegNum<[47]>;

	//-- Vector Control Registers
	def VL	: GC64GPRReg<42,	"vl">,	DwarfRegNum<[42]>;
	def VS	: GC64GPRReg<43,	"vs">,	DwarfRegNum<[43]>;

	//-- Mode Registers	
	def GMODE	: GC64GPRReg<44,	"gmode">,	DwarfRegNum<[44]>;
	def PMASK	: GC64GPRReg<45,	"pmask">,	DwarfRegNum<[45]>;
	def PREAD	: GC64GPRReg<46,	"pread">,	DwarfRegNum<[46]>;

	//-- IP
	def IP	: GC64GPRReg<46,	"ip">,	DwarfRegNum<[48]>;

	//-- Security Key
	def GKEY	: GC64GPRReg<51,	"gkey">,	DwarfRegNum<[51]>;

	//-- Read-Only Registers
	def GEXC	: GC64GPRReg<52,	"gexc">,	DwarfRegNum<[52]>;
	def ZERO	: GC64GPRReg<53,	"zero">,	DwarfRegNum<[53]>;
	def IMM32	: GC64GPRReg<54,	"imm32">,	DwarfRegNum<[54]>;
	def IMM64	: GC64GPRReg<55,	"imm64">,	DwarfRegNum<[55]>;
	def GCONST	: GC64GPRReg<56,	"gconst">,	DwarfRegNum<[56]>;

	//-- Read-Only: Combinatorial Registers
	def EQ	: GC64GPRReg<57,	"eq">,	DwarfRegNum<[57]>;
	def GT	: GC64GPRReg<58,	"gt">,	DwarfRegNum<[58]>;
	def GTE	: GC64GPRReg<59,	"gte">,	DwarfRegNum<[59]>;
	def LT	: GC64GPRReg<60,	"lt">,	DwarfRegNum<[60]>;
	def LTE : GC64GPRReg<61,	"lte">,	DwarfRegNum<[61]>;
	def NE	: GC64GPRReg<62,	"ne">,	DwarfRegNum<[62]>;
	
	//-- Read-Only Perf Counters 
	def PVAL	: GC64GPRReg<63,	"pval">,	DwarfRegNum<[63]>;
	
}


//===----------------------------------------------------------------------===//
//  GC64 Register Classes
//===----------------------------------------------------------------------===//

//-- General Purpose Registers
def R64	: RegisterClass<"GC64", [i64], 64, 
		(sequence "R%u", 0, 31)> {
}

//-- Control Registers
def CTR64 : RegisterClass<"GC64", [i64], 64, 
		(add 	
		//-- STACK POINTER
		SP,
		
		//-- FRAME POINTER
		FP,
	
		//-- POSITION INDEPENDENT POINTER	
		PIC,

		//-- UPLEVEL FRAME POINTER
		UP,

		//-- RETURN POINTER
		RP)>;

//-- Condition Code Registers
def CCODE : RegisterClass<"GC64", [i64], 64, 
		(sequence "CC%u", 0, 3)>{
}

//-- Tasking Registers
def TASK64 : RegisterClass<"GC64", [i64], 64, 
		(add
		//-- TASK QUEUE POINTER
		TQ, 
		
		//-- TASK ID
		TID)>;	

//-- Constants: Read-Only
def CONST64 : RegisterClass<"GC64", [i64], 64, 
		(add
		//-- CONTROL 
		ZERO, IMM32, IMM64, 

		//-- COMBINATORIAL 
		EQ, GT, GTE, LT, LTE, NE)>;

//-- EOF: GC64RegisterInfo.td 
