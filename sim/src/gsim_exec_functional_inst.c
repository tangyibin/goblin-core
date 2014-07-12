/* 
 * 
 * _GSIM_EXEC_FUNCTIONAL_INST_C_
 * 
 * GOBLIN-SIM FUNCTIONAL SIMULATION EXECUTION: INDIVIDUAL INSTRUCTIONS
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


/* -------------------------------------------------- GSIM_EXEC_FUNCTIONAL_INST */
/* 
 * GSIM_EXEC_FUNCTIONAL_INST
 * 
 */
extern int gsim_exec_functional_inst( 	struct gsim_t *sim, 
					struct gsim_task_unit_t *task, 
					uint32_t l_r0,
					uint32_t l_r1,
					uint32_t l_r2,
					uint32_t l_opc,
					uint32_t l_ctr,
					uint32_t l_ctr_vec,
					uint32_t l_ctr_v0,
					uint32_t l_ctr_v1,
					uint32_t l_ctr_brk,
					uint32_t l_ctr_imm8,
					uint32_t l_ctr_imm4,
					int32_t  l_imm4,
					int64_t  l_imm8 )
{
#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

	/* vars */
	int found	= 0;
	/* ---- */

	/* 
	 * walk the instruction table and find the necessary insruction 
	 * 
	 */
	switch( l_opc )
	{
		case 0x00: 
			/* nop */
			found = 1;
			break;
		case 0x01:
			/* mov */
			found = 1;
			break; 
		case 0x02: 
			/* ld.ub */
			found = 1;
			break;
		case 0x03: 
			/* ld.uw */
			found = 1;
			break;
		case 0x04: 
			/* ld.ud */
			found = 1;
			break;
		case 0x05: 
			/* ld.sq */
			found = 1;
			break;
		case 0x06: 
			/* ld.sb */
			found = 1;
			break;
		case 0x07: 
			/* ld.sw */
			found = 1;
			break;
		case 0x08: 
			/* ld.sd */
			found = 1;
			break;
		case 0x09: 
			/* st.ub */
			found = 1;
			break;
		case 0x0A: 
			/* st.uw */
			found = 1;
			break;
		case 0x0B: 
			/* st.ud */
			found = 1;
			break;
		case 0x0C: 
			/* st.uq */
			found = 1;
			break;	
		case 0x0D: 
			/* st.sb */
			found = 1;
			break;
		case 0x0E: 
			/* st.sw */
			found = 1;
			break;
		case 0x0F: 
			/* st.sd */
			found = 1;
			break;
		case 0x10: 
			/* ldi.sq */
			found = 1;
			break;
		case 0x11: 
			/* ldi.uq */
			found = 1;
			break;
		case 0x12: 
			/* ld.fs */
			found = 1;
			break;
		case 0x13: 
			/* ld.fd */
			found = 1;
			break;
		case 0x14: 
			/* st.fs */
			found = 1;
			break;
		case 0x15: 
			/* st.fd */
			found = 1;
			break;
		case 0x1A: 
			/* ld.ga */
			found = 1;
			break;
		case 0x1B:
			/* st.ga */
			found = 1;
			break;
		case 0x1F: 
			/* fence */
			found = 1;
			break;
		case 0x20: 
			/* and */
			found = 1;
			break;
		case 0x21:
			/* andc */
			found = 1;
			break;
		case 0x22: 
			/* or */
			found = 1;
			break;
		case 0x23:
			/* orc */
			found = 1;
			break;
		case 0x24: 
			/* nand */
			found = 1;
			break;
		case 0x25: 
			/* nor */
			found = 1;
			break;
		case 0x26: 
			/* xor */
			found = 1;
			break;
		case 0x27: 
			/* xnor */
			found = 1;
			break;
		case 0x2A: 	
			/* fence.ga */
			found = 1;
			break;
		case 0x30: 
			/* add.sq */
			found = 1;
			break;
		case 0x31: 
			/* add.uq */
			found = 1;
			break;
		case 0x32: 
			/* sub.sq */
			found = 1;
			break;
		case 0x33: 
			/* sub.uq */
			found = 1;
			break;
		case 0x34: 
			/* mul.sq */
			found = 1;
			break;
		case 0x35: 
			/* mul.uq */
			found = 1;
			break;
		case 0x36: 
			/* div.sq */
			found = 1;
			break;
		case 0x37: 
			/* div.uq */
			found = 1;
			break;
		case 0x38: 
			/* abs.sq */
			found = 1;
			break;
		case 0x39: 
			/* neg.sq */
			found = 1;
			break;
		case 0x3A: 
			/* shfl.sq */
			found = 1;
			break;
		case 0x3B: 
			/* shfl.uq */
			found = 1;
			break;
		case 0x3C: 
			/* shfr.sq */
			found = 1;
			break;
		case 0x3D: 
			/* shfr.uq */
			found = 1;
			break;
		case 0x3E: 
			/* cmp.sq */
			found = 1;
			break;
		case 0x3F: 
			/* cmp.uq */
			found = 1;
			break;
		case 0x40: 
			/* add.fs */
			found = 1;
			break;
		case 0x41: 
			/* add.fd */
			found = 1;
			break;
		case 0x42: 
			/* sub.fs */
			found = 1;
			break;
		case 0x43: 
			/* sub.fd */
			found = 1;
			break;
		case 0x44: 
			/* mul.fs */
			found = 1;
			break;
		case 0x45: 
			/* mul.fd */
			found = 1;
			break;
		case 0x46: 
			/* div.fs */
			found = 1;
			break;
		case 0x47: 
			/* div.fd */
			found = 1;
			break;
		case 0x48: 
			/* abs.fs */
			found = 1;
			break;
		case 0x49: 
			/* abs.fd */
			found = 1;
			break;
		case 0x4A: 
			/* neg.fs */
			found = 1;
			break;
		case 0x4B: 
			/* neg.fd */
			found = 1;
			break;
		case 0x4E: 
			/* cmp.fs */ 
			found = 1;
			break;
		case 0x4F:
			/* cmd.fd */
			found = 1;
			break;
		case 0x50: 
			found = 1;
			break;
		case 0x51: 
			found = 1;
			break;
		case 0x52: 
			found = 1;
			break;
		case 0x53: 
			found = 1;
			break;
		case 0x54: 
			found = 1;
			break;
		case 0x55: 
			found = 1;
			break;
		case 0x56: 
			found = 1;
			break;
		case 0x57: 
			found = 1;
			break;
		case 0x58: 
			found = 1;
			break;
		case 0x59: 
			found = 1;
			break;
		case 0x5A: 
			found = 1;
			break;
		case 0x5B:
			found = 1;
			break;
		case 0x60: 
			found = 1;
			break;
		case 0x61: 
			found = 1;
			break;
		case 0x62: 
			found = 1;
			break;
		case 0x63: 
			found = 1;
			break;
		case 0x64: 
			found = 1;
			break;
		case 0x65: 
			found = 1;
			break;
		case 0x66: 
			found = 1;
			break;
		case 0x67: 
			found = 1;
			break;
		case 0x68: 
			found = 1;
			break;
		case 0x69: 
			found = 1;
			break;
		case 0x6A: 
			found = 1;
			break;
		case 0x6B: 
			found = 1;
			break;
		case 0x6C:
			found = 1;
			break;
		case 0x6D: 
			found = 1;
			break;
		case 0x6E: 
			found = 1;
			break;
		case 0x6F: 
			found = 1;
			break;
		case 0x70: 
			found = 1;
			break;
		case 0x71: 
			found = 1;
			break;
		case 0x72: 
			found = 1;
			break;
		case 0x73: 
			found = 1;
			break;
		case 0x74: 
			found = 1;
			break;
		case 0x75: 
			found = 1;
			break;
		case 0x80: 
			found = 1;
			break;
		case 0x81: 
			found = 1;
			break;
		case 0x82: 
			found = 1;
			break;
		case 0x83: 
			found = 1;
			break;
		case 0x90: 
			found = 1;
			break;
		case 0x91: 
			found = 1;
			break;
		case 0x92: 
			found = 1;
			break;
		case 0x93: 
			found = 1;
			break;
		case 0xA0: 
			found = 1;
			break;
		case 0xA1: 
			found = 1;
			break;
		case 0xA2: 
			found = 1;
			break;
		case 0xA3: 
			found = 1;
			break;
		case 0xA4: 
			found = 1;
			break;
		case 0xA5: 
			found = 1;
			break;
		case 0xB0: 
			found = 1;
			break;
		case 0xB1: 
			found = 1;
			break;
		case 0xBA: 
			found = 1;
			break;
		case 0xBB: 
			found = 1;
			break;
		case 0xC0: 
			found = 1;
			break;
		case 0xC1: 
			found = 1;
			break;
		case 0xCA: 
			found = 1;
			break;
		case 0xCB: 
			found = 1;
			break;
		case 0XD0: 
			found = 1;
			break;
		case 0xD1: 
			found = 1;
			break;
		case 0xDA: 
			found = 1;
			break;
		case 0xDB: 
			found = 1;
			break;
		case 0xDC: 
			found = 1;
			break;
		case 0xDD: 
			found = 1;
			break;
		case 0xDE: 
			found = 1;
			break;
		case 0xDF: 
			found = 1;
			break;
		case 0xE0: 
			found = 1;
			break;
		case 0xE1: 
			found = 1;
			break;
		case 0xE3: 
			found = 1;
			break;
		case 0xE5: 
			found = 1;
			break;
		case 0xEA: 
			found = 1;
			break;
		case 0xEB: 
			found = 1;
			break;
		case 0xEC: 
			found = 1;
			break;
		case 0xF1: 
			found = 1;
			break;
		case 0xF2: 
			found = 1;
			break;
		case 0xF3: 
			found = 1;
			break;
		case 0xF4: 
			found = 1;
			break;
		case 0xFA: 
			found = 1;
			break;
		case 0xFD: 
			found = 1;
			break;
		case 0xFF: 
			found = 1;
			break;
		default : 
			found = 0;
			break;
	}

	if( found != 1 ){ 
		/* 
	 	 * print a error trace 
		 * 
		 */

		/* 
		 * set an exception 
		 *
		 */
	}


	/* 
	 * if required, push the IP 
	 * 
	 */

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif

	return 0;
}

/* EOF */
