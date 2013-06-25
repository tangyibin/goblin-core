/* 
 * 
 * _GSIM_OPCODES_C_ 
 * 
 * GOBLIN-SIM OPCODES INIT 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "goblin_sim.h"


/* -------------------------------------------------- GSIM_OPCODES_INIT */
/* 
 * GSIM_OPCODES_INIT
 * 
 */
static int gsim_opcodes_init( struct gsim_t *sim )
{
	/* 
	 * check the sim structure 
	 *
	 */
	if( sim == NULL ){ 
		/* nothing to do, return */
		return -1;
	}

	/* 
	 * zero the opcode tables
	 * 	
	 */
	memset( sim->opcodes.valid, 0, sizeof( uint32_t ) * 256 );
	memset( sim->opcodes.format, 0, sizeof( uint32_t ) * 256 );
	memset( sim->opcodes.name, 0, sizeof( char ) * (256*64) );

	/* 
	 * populate the opcode table 
	 * 
	 */
	
	/* -- NOP */	
	sim->opcodes.valid[0x00]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x00]	= GSIM_OPCODE_NOREG;
	sprintf( sim->opcodes.name[0x00], "%s", "nop" );

	/* -- MOV */
	sim->opcodes.valid[0x01]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x01]	= GSIM_OPCODE_RART | GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x01], "%s", "mov" );

	/* -- LD.UB */
	sim->opcodes.valid[0x02]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x02]	= GSIM_OPCODE_RARBRT | GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x02], "%s", "ld.ub" );
		
	/* -- LD.UW */
	sim->opcodes.valid[0x03]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x03]	= GSIM_OPCODE_RARBRT | GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x03], "%s", "ld.uw" );
	
	/* -- LD.UD */
	sim->opcodes.valid[0x04]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x04]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x04], "%s", "ld.ud" );
	
	/* -- LD.UQ */
	sim->opcodes.valid[0x05]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x05]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x05], "%s", "ld.uq" );
	
	/* -- LD.SB */
	sim->opcodes.valid[0x06]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x06]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x06], "%s", "ld.sb" );
	
	/* -- LD.SW */
	sim->opcodes.valid[0x07]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x07]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x07], "%s", "ld.sw" );
	
	/* -- LD.SD */
	sim->opcodes.valid[0x08]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x08]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x08], "%s", "ld.sd" );
	
	/* -- ST.UB */
	sim->opcodes.valid[0x09]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x09]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x09], "%s", "st.ub" );
	

	/* -- ST.UW */
	sim->opcodes.valid[0x0A]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x0A]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x0A], "%s", "st.uw" );
	
	/* -- ST.UD */
	sim->opcodes.valid[0x0B]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x0B]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x0B], "%s", "st.ud" );
	
	/* -- ST.UQ */
	sim->opcodes.valid[0x0C]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x0C]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x0C], "%s", "st.uq" );
	
	/* -- ST.SB */
	sim->opcodes.valid[0x0D]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x0D]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x0D], "%s", "st.sb" );
	
	/* -- ST.SW */
	sim->opcodes.valid[0x0E]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x0E]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x0E], "%s", "st.sw" );
	
	/* -- ST.SD */
	sim->opcodes.valid[0x0F]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x0F]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x0F], "%s", "st.sd" );
	
	/* -- LDI.SQ */
	sim->opcodes.valid[0x10]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x10]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x10], "%s", "ldi.sq" );
	
	/* -- LDI.UQ */
	sim->opcodes.valid[0x11]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x11]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x11], "%s", "ldi.uq" );
	
	/* -- LD.FS */
	sim->opcodes.valid[0x12]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x12]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x12], "%s", "ld.fs" );
	
	/* -- LD.FD */
	sim->opcodes.valid[0x13]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x13]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x13], "%s", "ld.fd" );
	
	/* -- ST.FS */
	sim->opcodes.valid[0x14]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x14]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x14], "%s", "st.fs" );
	
	/* -- ST.FD */
	sim->opcodes.valid[0x15]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x15]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x15], "%s", "st.fd" );

	/* -- 0x16 */	
	sim->opcodes.valid[0x16]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x16], "%s", "INVALID" );

	/* -- 0x17 */	
	sim->opcodes.valid[0x17]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x17], "%s", "INVALID" );

	/* -- 0x18 */	
	sim->opcodes.valid[0x18]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x18], "%s", "INVALID" );

	/* -- 0x19 */	
	sim->opcodes.valid[0x19]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x19], "%s", "INVALID" );

	/* -- LD.GA */
	sim->opcodes.valid[0x1A]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x1A]	= GSIM_OPCODE_RARBRT;
	sprintf( sim->opcodes.name[0x1A], "%s", "ld.ga" );

	/* -- ST.GA */
	sim->opcodes.valid[0x1B]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x1B]	= GSIM_OPCODE_RARBRT;
	sprintf( sim->opcodes.name[0x1B], "%s", "st.ga" );

	/* -- 0x1C */
	sim->opcodes.valid[0x1C]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x1C], "%s", "INVALID" );

	/* -- 0x1D */
	sim->opcodes.valid[0x1D]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x1D], "%s", "INVALID" );

	/* -- 0x1E */
	sim->opcodes.valid[0x1E]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x1E], "%s", "INVALID" );

	/* -- FENCE */
	sim->opcodes.valid[0x1F]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x1F]	= GSIM_OPCODE_NOREG;
	sprintf( sim->opcodes.name[0x1F], "%s", "fence" );
	
	/* -- AND */
	sim->opcodes.valid[0x20]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x20]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x20], "%s", "and" );

	/* -- ANDC */
	sim->opcodes.valid[0x21]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x21]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x21], "%s", "andc" );

	/* -- OR */
	sim->opcodes.valid[0x22]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x22]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x22], "%s", "or" );

	/* -- ORC */
	sim->opcodes.valid[0x23]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x23]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x23], "%s", "orc" );

	/* -- NAND */
	sim->opcodes.valid[0x24]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x24]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x24], "%s", "nand" );

	/* -- NOR */
	sim->opcodes.valid[0x25]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x25]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x25], "%s", "nor" );

	/* -- XOR */
	sim->opcodes.valid[0x26]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x26]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x26], "%s", "xor" );

	/* -- XNOR */
	sim->opcodes.valid[0x27]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x27]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x27], "%s", "xnor" );

	/* -- 0x28 */
	sim->opcodes.valid[0x28]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x28], "%s", "INVALID" );

	/* -- 0x29 */
	sim->opcodes.valid[0x29]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x29], "%s", "INVALID" );

	/* -- 0x2A */
	sim->opcodes.valid[0x2A]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x2A], "%s", "INVALID" );

	/* -- 0x2B */
	sim->opcodes.valid[0x2B]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x2B], "%s", "INVALID" );

	/* -- 0x2C */
	sim->opcodes.valid[0x2C]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x2C], "%s", "INVALID" );

	/* -- 0x2D */
	sim->opcodes.valid[0x2D]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x2D], "%s", "INVALID" );

	/* -- 0x2E */
	sim->opcodes.valid[0x2E]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x2E], "%s", "INVALID" );

	/* -- 0x2F */	
	sim->opcodes.valid[0x2F]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x2F], "%s", "INVALID" );

	/* -- ADD.SQ */
	sim->opcodes.valid[0x30]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x30]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x30], "%s", "add.sq" );
	
	/* -- ADD.UQ */
	sim->opcodes.valid[0x31]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x31]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x31], "%s", "add.uq" );
	
	/* -- SUB.SQ */
	sim->opcodes.valid[0x32]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x32]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x32], "%s", "sub.sq" );
	
	/* -- SUB.UQ */
	sim->opcodes.valid[0x33]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x33]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x33], "%s", "sub.uq" );
	
	/* -- MUL.SQ */
	sim->opcodes.valid[0x34]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x34]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x34], "%s", "mul.sq" );

	/* -- MUL.UQ */
	sim->opcodes.valid[0x35]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x35]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x35], "%s", "mul.uq" );

	/* -- DIV.SQ */
	sim->opcodes.valid[0x36]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x36]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x36], "%s", "div.sq" );

	/* -- DIV.UQ */
	sim->opcodes.valid[0x37]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x37]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x37], "%s", "div.uq" );

	/* -- ABS.SQ */
	sim->opcodes.valid[0x38]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x38]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x38], "%s", "abs.sq" );

	/* -- NEG.SQ */
	sim->opcodes.valid[0x39]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x39]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x39], "%s", "neg.sq" );

	/* -- SHFL.SQ */
	sim->opcodes.valid[0x3A]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x3A]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x3A], "%s", "shfl.sq" );

	/* -- SHFL.UQ */
	sim->opcodes.valid[0x3B]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x3B]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x3B], "%s", "shfl.uq" );

	/* -- SHFR.SQ */
	sim->opcodes.valid[0x3C]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x3C]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x3C], "%s", "shfr.sq" );

	/* -- SHFR.UQ */
	sim->opcodes.valid[0x3D]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x3D]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x3D], "%s", "shfr.uq" );

	/* -- CMP.SQ */
	sim->opcodes.valid[0x3E]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x3E]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x3E], "%s", "cmp.sq" );

	/* -- CMP.UQ */
	sim->opcodes.valid[0x3F]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x3F]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x3F], "%s", "cmp.uq" );

	/* -- ADD.FS */
	sim->opcodes.valid[0x40]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x40]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x40], "%s", "add.fs" );

	/* -- ADD.FD */
	sim->opcodes.valid[0x41]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x41]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x41], "%s", "ADD.FD" );

	/* -- SUB.FS */
	sim->opcodes.valid[0x42]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x42]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x42], "%s", "sub.fs" );

	/* -- SUB.FD */
	sim->opcodes.valid[0x43]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x43]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x43], "%s", "sub.fd" );

	/* -- MUL.FS */
	sim->opcodes.valid[0x44]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x44]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x44], "%s", "mul.fs" );

	/* -- MUL.FD */
	sim->opcodes.valid[0x45]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x45]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x45], "%s", "mul.fd" );

	/* -- DIV.FS */
	sim->opcodes.valid[0x46]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x46]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x46], "%s", "div.fs" );

	/* -- DIV.FD */
	sim->opcodes.valid[0x47]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x47]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x47], "%s", "div.fd" );

	/* -- ABS.FS */
	sim->opcodes.valid[0x48]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x48]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x48], "%s", "abs.fs" );

	/* -- ABS.FD */
	sim->opcodes.valid[0x49]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x49]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x49], "%s", "abs.fd" );

	/* -- NEG.FS */
	sim->opcodes.valid[0x4A]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x4A]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x4A], "%s", "neg.fs" );

	/* -- NEG.FD */
	sim->opcodes.valid[0x4B]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x4B]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x4B], "%s", "neg.fd" );

	/* -- 0x4C */	
	sim->opcodes.valid[0x4C]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x4C], "%s", "INVALID" );

	/* -- 0x4D */	
	sim->opcodes.valid[0x4D]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x4D], "%s", "INVALID" );

	/* -- CMP.FS */
	sim->opcodes.valid[0x4E]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x4E]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x4E], "%s", "cmp.fs" );

	/* -- CMP.FD */
	sim->opcodes.valid[0x4F]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x4F]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x4F], "%s", "cmp.fd" );

	/* -- CVT.FD.FS */
	sim->opcodes.valid[0x50]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x50]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x50], "%s", "cvt.fd.fs" );

	/* -- CVT.FD.SQ */
	sim->opcodes.valid[0x51]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x51]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x51], "%s", "cvt.fd.sq" );

	/* -- CVT.FD.UQ */
	sim->opcodes.valid[0x52]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x52]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x52], "%s", "cvt.fd.uq" );

	/* -- CVT.FS.FD */
	sim->opcodes.valid[0x53]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x53]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x53], "%s", "cvt.fs.fd" );

	/* -- CVT.FS.SQ */
	sim->opcodes.valid[0x54]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x54]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x54], "%s", "cvt.fs.sq" );

	/* -- CVT.FS.UQ */
	sim->opcodes.valid[0x55]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x55]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x55], "%s", "cvt.fs.uq" );

	/* -- CVT.SQ.FS */
	sim->opcodes.valid[0x56]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x56]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x56], "%s", "cvt.sq.fs" );

	/* -- CVT.SQ.FD */
	sim->opcodes.valid[0x57]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x57]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x57], "%s", "cvt.sq.fd" );

	/* -- CVT.SQ.UQ */
	sim->opcodes.valid[0x58]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x58]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x58], "%s", "cvt.sq.uq" );

	/* -- CVT.UQ.SQ */
	sim->opcodes.valid[0x59]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x59]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x59], "%s", "cvt.uq.sq" );

	/* -- CVT.UQ.FS */
	sim->opcodes.valid[0x5A]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x5A]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x5A], "%s", "cvt.uq.fs" );

	/* -- CVT.UQ.FD */
	sim->opcodes.valid[0x5B]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x5B]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x5B], "%s", "cvt.uq.fd" );

	/* -- 0x5C */
	sim->opcodes.valid[0x5C]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x5C], "%s", "INVALID" );

	/* -- 0x5D */
	sim->opcodes.valid[0x5D]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x5D], "%s", "INVALID" );

	/* -- 0x5E */
	sim->opcodes.valid[0x5E]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x5E], "%s", "INVALID" );

	/* -- 0x5F */
	sim->opcodes.valid[0x5F]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x5F], "%s", "INVALID" );

	/* -- AMO.ADD.SD */
	sim->opcodes.valid[0x60]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x60]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x60], "%s", "amo.add.sd" );

	/* -- AMO.ADD.SQ */
	sim->opcodes.valid[0x61]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x61]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x61], "%s", "amo.add.sq" );

	/* -- AMO.SUB.SD */
	sim->opcodes.valid[0x62]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x62]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x62], "%s", "amo.sub.sd" );

	/* -- AMO.SUB.SQ */
	sim->opcodes.valid[0x63]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x63]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x63], "%s", "amo.sub.sq" );

	/* -- AMO.EXCH.SD */
	sim->opcodes.valid[0x64]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x64]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x64], "%s", "amo.exch.sd" );

	/* -- AMO.EXCH.SQ */
	sim->opcodes.valid[0x65]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x65]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x65], "%s", "amo.exch.sq" );

	/* -- AMO.MIN.SD */
	sim->opcodes.valid[0x66]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x66]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x66], "%s", "amo.min.sd" );

	/* -- AMO.MIN.SQ */
	sim->opcodes.valid[0x67]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x67]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x67], "%s", "amo.min.sq" );

	/* -- AMO.MAX.SD */
	sim->opcodes.valid[0x68]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x68]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x68], "%s", "amo.max.sd" );

	/* -- AMO.MAX.SQ */
	sim->opcodes.valid[0x69]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x69]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x69], "%s", "amo.max.sq" );

	/* -- AMO.INC.SD */
	sim->opcodes.valid[0x6A]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x6A]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x6A], "%s", "amo.inc.sd" );

	/* -- AMO.INC.SQ */
	sim->opcodes.valid[0x6B]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x6B]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x6B], "%s", "amo.inc.sq" );

	/* -- AMO.DEC.SD */
	sim->opcodes.valid[0x6C]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x6C]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x6C], "%s", "amo.dec.sd" );

	/* -- AMO.DEC.SQ */
	sim->opcodes.valid[0x6D]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x6D]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x6D], "%s", "amo.dec.sq" );

	/* -- AMO.CAS.SD */
	sim->opcodes.valid[0x6E]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x6E]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x6E], "%s", "amo.cas.sd" );

	/* -- AMO.CAS.SQ */
	sim->opcodes.valid[0x6F]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x6F]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x6F], "%s", "amo.cas.sq" );

	/* -- AMO.AND.SD */
	sim->opcodes.valid[0x70]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x70]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x70], "%s", "amo.and.sd" );

	/* -- AMO.AND.SQ */
	sim->opcodes.valid[0x71]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x71]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x71], "%s", "amo.and.sq" );

	/* -- AMO.OR.SD */	
	sim->opcodes.valid[0x72]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x72]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x72], "%s", "amo.or.sd" );

	/* -- AMO.OR.SQ */
	sim->opcodes.valid[0x73]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x73]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x73], "%s", "amo.or.sq" );

	/* -- AMO.XOR.SD */
	sim->opcodes.valid[0x74]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x74]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x74], "%s", "amo.xor.sd" );

	/* -- AMO.XOR.SQ */
	sim->opcodes.valid[0x75]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x75]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x75], "%s", "amo.xor.sq" );

	/* -- 0x76 */
	sim->opcodes.valid[0x76]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x76], "%s", "INVALID" );

	/* -- 0x77 */
	sim->opcodes.valid[0x77]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x77], "%s", "INVALID" );

	/* -- 0x78 */
	sim->opcodes.valid[0x78]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x78], "%s", "INVALID" );

	/* -- 0x79 */
	sim->opcodes.valid[0x79]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x79], "%s", "INVALID" );

	/* -- 0x7A */
	sim->opcodes.valid[0x7A]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x7A], "%s", "INVALID" );

	/* -- 0x7B */
	sim->opcodes.valid[0x7B]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x7B], "%s", "INVALID" );

	/* -- 0x7C */
	sim->opcodes.valid[0x7C]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x7C], "%s", "INVALID" );

	/* -- 0x7D */
	sim->opcodes.valid[0x7D]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x7D], "%s", "INVALID" );

	/* -- 0x7E */
	sim->opcodes.valid[0x7E]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x7E], "%s", "INVALID" );

	/* -- 0x7F */
	sim->opcodes.valid[0x7F]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x7F], "%s", "INVALID" );

	/* -- MIN.SQ */
	sim->opcodes.valid[0x80]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x80]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x80], "%s", "min.sq" );

	/* -- MIN.UQ */
	sim->opcodes.valid[0x81]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x81]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x81], "%s", "min.uq" );

	/* -- MAX.SQ */
	sim->opcodes.valid[0x82]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x82]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x82], "%s", "max.sq" );

	/* -- MAX.UQ */	
	sim->opcodes.valid[0x83]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x83]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x83], "%s", "max.uq" );

	/* -- 0x84 */
	sim->opcodes.valid[0x84]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x84], "%s", "INVALID" );

	/* -- 0x85 */
	sim->opcodes.valid[0x85]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x85], "%s", "INVALID" );

	/* -- 0x86 */
	sim->opcodes.valid[0x86]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x86], "%s", "INVALID" );

	/* -- 0x87 */
	sim->opcodes.valid[0x87]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x87], "%s", "INVALID" );

	/* -- 0x88 */
	sim->opcodes.valid[0x88]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x88], "%s", "INVALID" );

	/* -- 0x89 */
	sim->opcodes.valid[0x89]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x89], "%s", "INVALID" );

	/* -- 0x8A */
	sim->opcodes.valid[0x8A]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x8A], "%s", "INVALID" );

	/* -- 0x8B */
	sim->opcodes.valid[0x8B]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x8B], "%s", "INVALID" );

	/* -- 0x8C */
	sim->opcodes.valid[0x8C]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x8C], "%s", "INVALID" );

	/* -- 0x8D */
	sim->opcodes.valid[0x8D]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x8D], "%s", "INVALID" );

	/* -- 0x8E */
	sim->opcodes.valid[0x8E]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x8E], "%s", "INVALID" );

	/* -- 0x8F */	
	sim->opcodes.valid[0x8F]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x8F], "%s", "INVALID" );

	/* -- MIN.FS */
	sim->opcodes.valid[0x90]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x90]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x90], "%s", "min.fs" );

	/* -- MIN.FD */
	sim->opcodes.valid[0x91]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x91]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x91], "%s", "min.fd" );

	/* -- MAX.FS */
	sim->opcodes.valid[0x92]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x92]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x92], "%s", "max.fs" );

	/* -- MAX.FD */
	sim->opcodes.valid[0x93]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0x93]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0x93], "%s", "max.fd" );

	/* -- 0x94 */
	sim->opcodes.valid[0x94]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x94], "%s", "INVALID" );

	/* -- 0x95 */
	sim->opcodes.valid[0x95]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x95], "%s", "INVALID" );

	/* -- 0x96 */
	sim->opcodes.valid[0x96]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x96], "%s", "INVALID" );

	/* -- 0x97 */
	sim->opcodes.valid[0x97]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x97], "%s", "INVALID" );

	/* -- 0x98 */
	sim->opcodes.valid[0x98]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x98], "%s", "INVALID" );

	/* -- 0x99 */
	sim->opcodes.valid[0x99]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x99], "%s", "INVALID" );

	/* -- 0x9A */
	sim->opcodes.valid[0x9A]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x9A], "%s", "INVALID" );

	/* -- 0x9B */
	sim->opcodes.valid[0x9B]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x9B], "%s", "INVALID" );

	/* -- 0x9C */
	sim->opcodes.valid[0x9C]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x9C], "%s", "INVALID" );

	/* -- 0x9D */
	sim->opcodes.valid[0x9D]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x9D], "%s", "INVALID" );

	/* -- 0x9E */
	sim->opcodes.valid[0x9E]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x9E], "%s", "INVALID" );

	/* -- 0x9F */
	sim->opcodes.valid[0x9F]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0x9F], "%s", "INVALID" );

	/* -- SEL CC3.NE */	
	sim->opcodes.valid[0xA0]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xA0]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0xA0], "%s", "sel" );

	/* -- SEL CC3.EQ */
	sim->opcodes.valid[0xA1]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xA1]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0xA1], "%s", "sel" );

	/* -- SEL CC3.GT */
	sim->opcodes.valid[0xA2]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xA2]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0xA2], "%s", "sel" );

	/* -- SEL CC3.LT */
	sim->opcodes.valid[0xA3]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xA3]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0xA3], "%s", "sel" );

	/* -- SEL CC3.GTE */
	sim->opcodes.valid[0xA4]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xA4]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0xA4], "%s", "sel" );

	/* -- SEL CC3.LTE */
	sim->opcodes.valid[0xA5]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xA5]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0xA5], "%s", "sel" );

	/* -- 0xA6 */
	sim->opcodes.valid[0xA6]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xA6], "%s", "INVALID" );

	/* -- 0xA7 */
	sim->opcodes.valid[0xA7]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xA7], "%s", "INVALID" );

	/* -- 0xA8 */
	sim->opcodes.valid[0xA8]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xA8], "%s", "INVALID" );

	/* -- 0xA9 */
	sim->opcodes.valid[0xA9]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xA9], "%s", "INVALID" );

	/* -- 0xAA */
	sim->opcodes.valid[0xAA]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xAA], "%s", "INVALID" );

	/* -- 0xAB */
	sim->opcodes.valid[0xAB]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xAB], "%s", "INVALID" );

	/* -- 0xAC */
	sim->opcodes.valid[0xAC]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xAC], "%s", "INVALID" );

	/* -- 0xAD */
	sim->opcodes.valid[0xAD]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xAD], "%s", "INVALID" );

	/* -- 0xAE */
	sim->opcodes.valid[0xAE]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xAE], "%s", "INVALID" );

	/* -- 0xAF */
	sim->opcodes.valid[0xAF]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xAF], "%s", "INVALID" );

	/* -- RTN */
	sim->opcodes.valid[0xB0]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xB0]	= GSIM_OPCODE_NOREG;
	sprintf( sim->opcodes.name[0xB0], "%s", "rtn" );

	/* -- RTN */
	sim->opcodes.valid[0xB1]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xB1]	= GSIM_OPCODE_RT;
	sprintf( sim->opcodes.name[0xB1], "%s", "rtn" );

	/* -- 0xB2 */
	sim->opcodes.valid[0xB2]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xB2], "%s", "INVALID" );

	/* -- 0xB3 */
	sim->opcodes.valid[0xB3]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xB3], "%s", "INVALID" );

	/* -- 0xB4 */
	sim->opcodes.valid[0xB4]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xB4], "%s", "INVALID" );

	/* -- 0xB5 */
	sim->opcodes.valid[0xB5]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xB5], "%s", "INVALID" );

	/* -- 0xB6 */
	sim->opcodes.valid[0xB6]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xB6], "%s", "INVALID" );

	/* -- 0xB7 */
	sim->opcodes.valid[0xB7]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xB7], "%s", "INVALID" );

	/* -- 0xB8 */
	sim->opcodes.valid[0xB8]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xB8], "%s", "INVALID" );

	/* -- 0xB9 */
	sim->opcodes.valid[0xB9]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xB9], "%s", "INVALID" );

	/* -- BR */
	sim->opcodes.valid[0xBA]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xBA]	= GSIM_OPCODE_RT;
	sprintf( sim->opcodes.name[0xBA], "%s", "br" );

	/* -- BR */
	sim->opcodes.valid[0xBB]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xBB]	= GSIM_OPCODE_RARBRT;
	sprintf( sim->opcodes.name[0xBB], "%s", "br" );

	/* -- 0xBC */
	sim->opcodes.valid[0xBC]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xBC], "%s", "INVALID" );

	/* -- 0xBD */
	sim->opcodes.valid[0xBD]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xBD], "%s", "INVALID" );

	/* -- 0xBE */
	sim->opcodes.valid[0xBE]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xBE], "%s", "INVALID" );

	/* -- 0xBF */
	sim->opcodes.valid[0xBF]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xBF], "%s", "INVALID" );

	/* -- BRA */
	sim->opcodes.valid[0xC0]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xC0]	= GSIM_OPCODE_RT;
	sprintf( sim->opcodes.name[0xC0], "%s", "bra" );

	/* -- BRA */
	sim->opcodes.valid[0xC1]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xC1]	= GSIM_OPCODE_RARBRT;
	sprintf( sim->opcodes.name[0xC1], "%s", "bra" );

	/* -- 0xC2 */
	sim->opcodes.valid[0xC2]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xC2], "%s", "INVALID" );

	/* -- 0xC3 */
	sim->opcodes.valid[0xC3]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xC3], "%s", "INVALID" );

	/* -- 0xC4 */
	sim->opcodes.valid[0xC4]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xC4], "%s", "INVALID" );

	/* -- 0xC5 */
	sim->opcodes.valid[0xC5]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xC5], "%s", "INVALID" );

	/* -- 0xC6 */
	sim->opcodes.valid[0xC6]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xC6], "%s", "INVALID" );

	/* -- 0xC7 */
	sim->opcodes.valid[0xC7]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xC7], "%s", "INVALID" );

	/* -- 0xC8 */
	sim->opcodes.valid[0xC8]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xC8], "%s", "INVALID" );

	/* -- 0xC9 */
	sim->opcodes.valid[0xC9]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xC9], "%s", "INVALID" );

	/* -- CALL */
	sim->opcodes.valid[0xCA]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xCA]	= GSIM_OPCODE_RT;
	sprintf( sim->opcodes.name[0xCA], "%s", "call" );

	/* -- CALL */
	sim->opcodes.valid[0xCB]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xCB]	= GSIM_OPCODE_RARBRT;
	sprintf( sim->opcodes.name[0xCB], "%s", "call" );

	/* -- 0xCC */
	sim->opcodes.valid[0xCC]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xCC], "%s", "INVALID" );

	/* -- 0xCD */
	sim->opcodes.valid[0xCD]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xCD], "%s", "INVALID" );

	/* -- 0xCE */
	sim->opcodes.valid[0xCE]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xCE], "%s", "INVALID" );

	/* -- 0xCF */
	sim->opcodes.valid[0xCF]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xCF], "%s", "INVALID" );

	/* -- CALLA */
	sim->opcodes.valid[0xD0]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xD0]	= GSIM_OPCODE_RT;
	sprintf( sim->opcodes.name[0xD0], "%s", "calla" );

	/* -- CALLA */
	sim->opcodes.valid[0xD1]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xD1]	= GSIM_OPCODE_RART;
	sprintf( sim->opcodes.name[0xD1], "%s", "calla" );

	/* -- 0xD2 */
	sim->opcodes.valid[0xD2]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xD2], "%s", "INVALID" );

	/* -- 0xD3 */
	sim->opcodes.valid[0xD3]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xD3], "%s", "INVALID" );

	/* -- 0xD4 */
	sim->opcodes.valid[0xD4]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xD4], "%s", "INVALID" );

	/* -- 0xD5 */
	sim->opcodes.valid[0xD5]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xD5], "%s", "INVALID" );

	/* -- 0xD6 */
	sim->opcodes.valid[0xD6]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xD6], "%s", "INVALID" );

	/* -- 0xD7 */
	sim->opcodes.valid[0xD7]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xD7], "%s", "INVALID" );

	/* -- 0xD8 */
	sim->opcodes.valid[0xD8]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xD8], "%s", "INVALID" );

	/* -- 0xD9 */
	sim->opcodes.valid[0xD9]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xD9], "%s", "INVALID" );

	/* -- SYSTEM */
	sim->opcodes.valid[0xDA]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xDA]	= GSIM_OPCODE_RA;
	sprintf( sim->opcodes.name[0xDA], "%s", "system" );

	/* -- 0xDB */
	sim->opcodes.valid[0xDB]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xDB], "%s", "INVALID" );

	/* -- 0xDC */
	sim->opcodes.valid[0xDC]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xDC], "%s", "INVALID" );

	/* -- 0xDD */
	sim->opcodes.valid[0xDD]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xDD], "%s", "INVALID" );

	/* -- 0xDE */
	sim->opcodes.valid[0xDE]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xDE], "%s", "INVALID" );

	/* -- 0xDF */
	sim->opcodes.valid[0xDF]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xDF], "%s", "INVALID" );

	/* -- POPCNT */
	sim->opcodes.valid[0xE0]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xE0]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0xE0], "%s", "popcnt" );

	/* -- ADDC */
	sim->opcodes.valid[0xE1]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xE1]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0xE1], "%s", "addc" );

	/* -- 0xE2 */
	sim->opcodes.valid[0xE2]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xE2], "%s", "INVALID" );

	/* -- SUBB */
	sim->opcodes.valid[0xE3]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xE3]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0xE3], "%s", "subb" );

	/* -- 0xE4 */
	sim->opcodes.valid[0xE4]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xE4], "%s", "INVALID" );

	/* -- MULU */
	sim->opcodes.valid[0xE5]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xE5]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0xE5], "%s", "mulu" );

	/* -- 0xE6 */
	sim->opcodes.valid[0xE6]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xE6], "%s", "INVALID" );

	/* -- 0xE7 */
	sim->opcodes.valid[0xE7]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xE7], "%s", "INVALID" );

	/* -- 0xE8 */
	sim->opcodes.valid[0xE8]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xE8], "%s", "INVALID" );

	/* -- 0xE9 */
	sim->opcodes.valid[0xE9]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xE9], "%s", "INVALID" );

	/* -- LZC */
	sim->opcodes.valid[0xEA]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xEA]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0xEA], "%s", "lzc" );

	/* -- TZC */
	sim->opcodes.valid[0xEB]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xEB]	= GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0xEB], "%s", "addc" );

	/* -- BSEL */
	sim->opcodes.valid[0xEC]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xEC]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0xEC], "%s", "addc" );

	/* -- 0xED */
	sim->opcodes.valid[0xED]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xED], "%s", "INVALID" );

	/* -- 0xEE */
	sim->opcodes.valid[0xEE]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xEE], "%s", "INVALID" );

	/* -- 0xEF */
	sim->opcodes.valid[0xEF]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xEF], "%s", "INVALID" );

	/* -- 0xF0 */
	sim->opcodes.valid[0xF0]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xF0], "%s", "INVALID" );

	/* -- GETC */
	sim->opcodes.valid[0xF1]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xF1]	= GSIM_OPCODE_RT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0xEF1], "%s", "getc" );

	/* -- SETC */
	sim->opcodes.valid[0xF2]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xF2]	= GSIM_OPCODE_RA|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0xF2], "%s", "setc" );

	/* -- GETB */
	sim->opcodes.valid[0xF3]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xF3]	= GSIM_OPCODE_RT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0xF3], "%s", "getb" );

	/* -- SETB */
	sim->opcodes.valid[0xF4]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xF4]	= GSIM_OPCODE_RA|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0xF4], "%s", "setb" );

	/* -- 0xF5 */
	sim->opcodes.valid[0xF5]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xF5], "%s", "INVALID" );

	/* -- 0xF6 */
	sim->opcodes.valid[0xF6]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xF6], "%s", "INVALID" );

	/* -- 0xF7 */
	sim->opcodes.valid[0xF7]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xF7], "%s", "INVALID" );

	/* -- 0xF8 */
	sim->opcodes.valid[0xF8]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xF8], "%s", "INVALID" );

	/* -- 0xF9 */
	sim->opcodes.valid[0xF9]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xF9], "%s", "INVALID" );

	/* -- DSHFL */
	sim->opcodes.valid[0xFA]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xFA]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0xFA], "%s", "dshfl" );

	/* -- 0xFB */
	sim->opcodes.valid[0xFB]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xFB], "%s", "INVALID" );

	/* -- 0xFC */
	sim->opcodes.valid[0xFC]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xFC], "%s", "INVALID" );

	/* -- DSHFR */
	sim->opcodes.valid[0xFD]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xFD]	= GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0xFD], "%s", "dshfr" );

	/* -- 0xFE */
	sim->opcodes.valid[0xFE]	= GSIM_OPCODE_INVALID;
	sprintf( sim->opcodes.name[0xFE], "%s", "INVALID" );

	/* -- LFSHV */
	sim->opcodes.valid[0xFF]	= GSIM_OPCODE_VALID;
	sim->opcodes.format[0xFF]	= GSIM_OPCODE_RA|GSIM_OPCODE_VECTOR;
	sprintf( sim->opcodes.name[0xFF], "%s", "ldshv" );


	return 0;
}

/* EOF */
