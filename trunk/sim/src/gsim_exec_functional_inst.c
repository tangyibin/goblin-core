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

/* -------------------------------------------------- FUNCTION PROTOTYPES */
extern int gsim_stov( uint32_t scalar, uint32_t *vec );

/* -------------------------------------------------- MACROS & UNIONS */
union reg_u{ 
	uint8_t		u_ub;	/* unsigned byte */
	uint16_t	u_uw;	/* unsigned word */
	uint32_t	u_ud;	/* unsigned double */
	uint64_t	u_uq;	/* unsigned quad */
	int8_t		u_sb;	/* signed byte */
	int16_t		u_sw;	/* signed word */
	int32_t		u_sd;	/* signed double */
	int64_t		u_sq;	/* signed quad */
	float 		u_fs;	/* float single */
	double		u_fd;	/* float double */
};


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
	uint32_t 	rA_idx	= 0x00;
	uint32_t	rB_idx	= 0x00;
	uint32_t	rT_idx	= 0x00;
	union reg_u	r0;
	union reg_u	r1;
	union reg_u	r2;
	union reg_u	v0e0;
	union reg_u	v0e1;
	union reg_u	v0e2;
	union reg_u	v0e3;
	union reg_u	v1e0;
	union reg_u	v1e1;
	union reg_u	v1e2;
	union reg_u	v1e3;
	union reg_u	v2e0;
	union reg_u	v2e1;
	union reg_u	v2e2;
	union reg_u	v2e3;
	/* ---- */

	/*
	 * init the reg values
	 * 
	 */
	r0.u_uq		= 0x00ll;
	r1.u_uq		= 0x00ll;
	r2.u_uq		= 0x00ll;
	v0e0.u_uq	= 0x00ll;
	v0e1.u_uq	= 0x00ll;
	v0e2.u_uq	= 0x00ll;
	v0e3.u_uq	= 0x00ll;
	v1e0.u_uq	= 0x00ll;
	v1e1.u_uq	= 0x00ll;
	v1e2.u_uq	= 0x00ll;
	v1e3.u_uq	= 0x00ll;
	v2e0.u_uq	= 0x00ll;
	v2e1.u_uq	= 0x00ll;
	v2e2.u_uq	= 0x00ll;
	v2e3.u_uq	= 0x00ll;

	/*
	 * decode the register values
	 * 
	 */
	if( l_ctr_vec == 0 ){

		/* operating in scalar mode */
		rA_idx	= l_r0;
		rB_idx	= l_r1;
		rT_idx	= l_r2;
		r0.u_uq	= task->reg[rA_idx];
		r1.u_uq	= task->reg[rB_idx];
		r2.u_uq	= task->reg[rT_idx];

	}else{ 
		/* operating in vector mode */
		if( l_ctr_v0 != 0 ){ 
			gsim_stov( l_r0, &rA_idx );
			v0e0.u_uq	= task->reg[rA_idx];
			v0e1.u_uq	= task->reg[rA_idx+1];
			v0e2.u_uq	= task->reg[rA_idx+2];
			v0e3.u_uq	= task->reg[rA_idx+3];
		}else{ 
			rA_idx	= l_r0;
			r0.u_uq	= task->reg[rA_idx];
		}

		if( l_ctr_v1 != 0 ){ 
			gsim_stov( l_r1, &rA_idx );
			v1e0.u_uq	= task->reg[rB_idx];
			v1e1.u_uq	= task->reg[rB_idx+1];
			v1e2.u_uq	= task->reg[rB_idx+2];
			v1e3.u_uq	= task->reg[rB_idx+3];
		}else{
			rB_idx	= l_r0;
			r1.u_uq	= task->reg[rB_idx];
		}

		gsim_stov( l_r2, &rT_idx );
		v2e0.u_uq	= task->reg[rT_idx];
		v2e1.u_uq	= task->reg[rT_idx+1];
		v2e2.u_uq	= task->reg[rT_idx+2];
		v2e3.u_uq	= task->reg[rT_idx+3];

	}

	/* 
	 * walk the instruction table and find the necessary insruction 
	 * 
	 */
	switch( l_opc )
	{
		case 0x00: 
			/* nop */
					
			break;
		case 0x01:
			/* mov */
			if( l_ctr_vec == 0 ){
				/* scalar */
				r2.u_uq	= r0.u_uq;	
				task->reg[rT_idx] = r2.u_uq;
			}else{
				/* vector */
				v2e0.u_uq	= v0e0.u_uq;
				v2e1.u_uq	= v0e1.u_uq;
				v2e2.u_uq	= v0e1.u_uq;
				v2e3.u_uq	= v0e3.u_uq;
				task->reg[rT_idx]   = v2e0.u_uq;
				task->reg[rT_idx+1] = v2e1.u_uq;
				task->reg[rT_idx+2] = v2e2.u_uq;
				task->reg[rT_idx+3] = v2e3.u_uq;
			}
			
			break; 
		case 0x02: 
			/* ld.ub */
			
			break;
		case 0x03: 
			/* ld.uw */
			
			break;
		case 0x04: 
			/* ld.ud */
			
			break;
		case 0x05: 
			/* ld.sq */
			
			break;
		case 0x06: 
			/* ld.sb */
			
			break;
		case 0x07: 
			/* ld.sw */
			
			break;
		case 0x08: 
			/* ld.sd */
			
			break;
		case 0x09: 
			/* st.ub */
			
			break;
		case 0x0A: 
			/* st.uw */
			
			break;
		case 0x0B: 
			/* st.ud */
			
			break;
		case 0x0C: 
			/* st.uq */
			
			break;	
		case 0x0D: 
			/* st.sb */
			
			break;
		case 0x0E: 
			/* st.sw */
			
			break;
		case 0x0F: 
			/* st.sd */
			
			break;
		case 0x10: 
			/* ldi.sq */
			
			break;
		case 0x11: 
			/* ldi.uq */
			
			break;
		case 0x12: 
			/* ld.fs */
			
			break;
		case 0x13: 
			/* ld.fd */
			
			break;
		case 0x14: 
			/* st.fs */
			
			break;
		case 0x15: 
			/* st.fd */
			
			break;
		case 0x1A: 
			/* ld.ga */
			
			break;
		case 0x1B:
			/* st.ga */
			
			break;
		case 0x1F: 
			/* fence */
			/* -- this must be handled special */	
			break;
		case 0x20: 
			/* and */
			if( l_ctr_vec == 0 ){
				/* scalar */
				r2.u_uq	= (r0.u_uq & r1.u_uq);	
				task->reg[rT_idx] = r2.u_uq;
			}else{
				/* vector */
			}	
			break;
		case 0x21:
			/* andc */
			
			break;
		case 0x22: 
			/* or */
			
			break;
		case 0x23:
			/* orc */
			
			break;
		case 0x24: 
			/* nand */
			
			break;
		case 0x25: 
			/* nor */
			
			break;
		case 0x26: 
			/* xor */
			if( l_ctr_vec == 0 ){
				/* scalar */
				r2.u_uq	= (r0.u_uq ^ r1.u_uq);	
				task->reg[rT_idx] = r2.u_uq;
			}else{
				/* vector */
			}	
			
			break;
		case 0x27: 
			/* xnor */
			
			break;
		case 0x2A: 	
			/* fence.ga */
			
			break;
		case 0x30: 
			/* add.sq */
			if( l_ctr_vec == 0 ){
				/* scalar */
				r2.u_sq	= (r0.u_sq + r1.u_sq);	
				task->reg[rT_idx] = r2.u_uq;
			}else{
				/* vector */
			}	
			
			break;
		case 0x31: 
			/* add.uq */
			if( l_ctr_vec == 0 ){
				/* scalar */
				r2.u_uq	= (r0.u_uq + r1.u_uq);	
				task->reg[rT_idx] = r2.u_uq;
			}else{
				/* vector */
			}	
			
			break;
		case 0x32: 
			/* sub.sq */
			if( l_ctr_vec == 0 ){
				/* scalar */
				r2.u_sq	= (r0.u_sq - r1.u_sq);	
				task->reg[rT_idx] = r2.u_uq;
			}else{
				/* vector */
			}	
			
			break;
		case 0x33: 
			/* sub.uq */
			if( l_ctr_vec == 0 ){
				/* scalar */
				r2.u_uq	= (r0.u_uq - r1.u_uq);	
				task->reg[rT_idx] = r2.u_uq;
			}else{
				/* vector */
			}	
			
			break;
		case 0x34: 
			/* mul.sq */
			if( l_ctr_vec == 0 ){
				/* scalar */
				r2.u_sq	= (r0.u_sq * r1.u_sq);	
				task->reg[rT_idx] = r2.u_uq;
			}else{
				/* vector */
			}	
			
			break;
		case 0x35: 
			/* mul.uq */
			if( l_ctr_vec == 0 ){
				/* scalar */
				r2.u_uq	= (r0.u_uq * r1.u_uq);	
				task->reg[rT_idx] = r2.u_uq;
			}else{
				/* vector */
			}	
			
			break;
		case 0x36: 
			/* div.sq */
			if( l_ctr_vec == 0 ){
				/* scalar */
				r2.u_sq	= (r0.u_sq / r1.u_sq);	
				task->reg[rT_idx] = r2.u_uq;
			}else{
				/* vector */
			}	
			
			break;
		case 0x37: 
			/* div.uq */
			if( l_ctr_vec == 0 ){
				/* scalar */
				r2.u_uq	= (r0.u_uq / r1.u_uq);	
				task->reg[rT_idx] = r2.u_uq;
			}else{
				/* vector */
			}	
			
			break;
		case 0x38: 
			/* abs.sq */
			
			break;
		case 0x39: 
			/* neg.sq */
			
			break;
		case 0x3A: 
			/* shfl.sq */
			
			break;
		case 0x3B: 
			/* shfl.uq */
			
			break;
		case 0x3C: 
			/* shfr.sq */
			
			break;
		case 0x3D: 
			/* shfr.uq */
			
			break;
		case 0x3E: 
			/* cmp.sq */
			
			break;
		case 0x3F: 
			/* cmp.uq */
			
			break;
		case 0x40: 
			/* add.fs */
			
			break;
		case 0x41: 
			/* add.fd */
			
			break;
		case 0x42: 
			/* sub.fs */
			
			break;
		case 0x43: 
			/* sub.fd */
			
			break;
		case 0x44: 
			/* mul.fs */
			
			break;
		case 0x45: 
			/* mul.fd */
			
			break;
		case 0x46: 
			/* div.fs */
			
			break;
		case 0x47: 
			/* div.fd */
			
			break;
		case 0x48: 
			/* abs.fs */
			
			break;
		case 0x49: 
			/* abs.fd */
			
			break;
		case 0x4A: 
			/* neg.fs */
			
			break;
		case 0x4B: 
			/* neg.fd */
			
			break;
		case 0x4E: 
			/* cmp.fs */ 
			
			break;
		case 0x4F:
			/* cmd.fd */
			
			break;
		case 0x50: 
			/* cvt.fd.fs */
			
			break;
		case 0x51: 
			/* cvt.fd.sq */
			
			break;
		case 0x52: 
			/* cvt.fd.uq */
			
			break;
		case 0x53: 
			/* cvt.fs.fd */
			
			break;
		case 0x54: 
			/* cvt.fs.sq */
			
			break;
		case 0x55: 
			/* cvt.fs.sq */
			
			break;
		case 0x56: 
			/* cvt.sq.fs */
			
			break;
		case 0x57: 
			/* cvt.sq.fd */
			
			break;
		case 0x58: 
			/* cvt.sq.uq */
			
			break;
		case 0x59: 
			/* cvt.uq.sq */
			
			break;
		case 0x5A: 
			/* cvt.uq.fs */
			
			break;
		case 0x5B:
			/* cvt.uq.fd */
			
			break;
		case 0x60: 
			/* amo.add.sd */
			
			break;
		case 0x61: 
			/* amo.add.sq */
			
			break;
		case 0x62: 
			/* amod.sub.sd */
			
			break;
		case 0x63: 
			/* amo.sub.sq */
			
			break;
		case 0x64: 
			/* amo.exch.sd */
			
			break;
		case 0x65: 
			/* amo.exch.sq */
			
			break;
		case 0x66: 
			/* amo.min.sd */
			
			break;
		case 0x67: 
			/* amo.min.sq */
			
			break;
		case 0x68: 
			/* amo.max.sd */
			
			break;
		case 0x69: 
			/* amo.max.sq */
			
			break;
		case 0x6A: 
			/* amo.inc.sd */
			
			break;
		case 0x6B:
			/* amo.inc.sq */
			
			break;
		case 0x6C:
			/* amo.dec.sd */
			
			break;
		case 0x6D: 
			/* amo.dec.sq */
			
			break;
		case 0x6E: 
			/* amo.cas.sd */
			
			break;
		case 0x6F: 
			/* amo.cas.sq */
			
			break;
		case 0x70: 
			/* amo.and.sd */
			
			break;
		case 0x71: 
			/* amo.and.sq */
			
			break;
		case 0x72: 
			/* amo.or.sd */
			
			break;
		case 0x73: 
			/* amo.or.sq */
			
			break;
		case 0x74: 
			/* amo.xor.sd */
			
			break;
		case 0x75: 
			/* amo.xor.sq */
			
			break;
		case 0x80: 
			/* min.sq */
			
			break;
		case 0x81: 
			/* min.uq */
			
			break;
		case 0x82: 
			/* max.sq */
			
			break;
		case 0x83: 
			/* max.uq */
			
			break;
		case 0x90: 
			/* min.fs */
			
			break;
		case 0x91: 
			/* min.fd */
			
			break;
		case 0x92: 
			/* max.fs */
			
			break;
		case 0x93: 
			/* max.fd */
			
			break;
		case 0xA0: 
			/* sel.cc3.ne */
			
			break;
		case 0xA1: 
			/* sel.cc3.eq */
			
			break;
		case 0xA2: 
			/* sel.cc3.gt */
			
			break;
		case 0xA3: 
			/* sel.cc3.lt */
			
			break;
		case 0xA4: 
			/* sel.cc3.gte */
			
			break;
		case 0xA5: 
			/* sel.cc3.lte */
			
			break;
		case 0xB0: 
			/* rtn */
			
			break;
		case 0xB1: 
			/* rtna */
			
			break;
		case 0xBA: 
			/* br */
			
			break;
		case 0xBB: 
			/* brc */
			
			break;
		case 0xC0: 
			/* bra */
			
			break;
		case 0xC1: 
			/* brac */
			
			break;
		case 0xCA: 
			/* call */
			
			break;
		case 0xCB: 
			/* callc */
			
			break;
		case 0XD0: 
			/* calla */
			
			break;
		case 0xD1: 
			/* callac */
			
			break;
		case 0xDA: 
			/* system */
			
			break;
		case 0xDB: 
			/* spawn */
			
			break;
		case 0xDC: 
			/* join */
			
			break;
		case 0xDD: 
			/* iwait */
			
			break;
		case 0xDE: 
			/* peg */
			
			break;
		case 0xDF: 
			/* future */
			
			break;
		case 0xE0: 
			/* popcnt */
			
			break;
		case 0xE1: 
			/* addc */
			
			break;
		case 0xE3: 
			/* subb */
			
			break;
		case 0xE5: 
			/* mulu */
			
			break;
		case 0xEA: 
			/* lzc */
			
			break;
		case 0xEB: 
			/* tzc */
			
			break;
		case 0xEC: 
			/* bsel */
			
			break;
		case 0xF1: 
			/* getc */
			
			break;
		case 0xF2: 
			/* setc */
			
			break;
		case 0xF3: 
			/* getb */
			
			break;
		case 0xF4: 
			/* setb */
			
			break;
		case 0xFA: 
			/* dshfl */
			
			break;
		case 0xFD: 
			/* dshfr */
			
			break;
		case 0xFF: 
			/* ldshv */
			
			break;
		default : 
			/* set an exception */
			break;
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
