/* 
 * 
 * _GSIM_DISASS_C_ 
 * 
 * GOBLIN-SIM BUILT-IN DISASSEMBLER
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


#define G_8BIT	0x00000000
#define	G_6BIT	0x00000000
#define G_32BIT	0xFFFFFFFF
#define	G_BIT0	0x00000001
#define G_BIT1	0x00000002
#define G_BIT2	0x00000004
#define G_BIT3	0x00000008
#define G_BIT4	0x00000010
#define G_BIT5	0x00000020

/* -------------------------------------------------- GSIM_DISASS_UPPER */
/* 
 * GSIM_DISASS_UPPER
 * 
 */
static int gsim_disass_upper(	uint64_t *inst,  
				uint32_t *r0, 
				uint32_t *r1, 
				uint32_t *r2, 
				uint32_t *opc, 
				uint32_t *ctr,
				uint32_t *ctr_vec,
				uint32_t *ctr_v0, 
				uint32_t *ctr_v1, 
				uint32_t *ctr_brk, 
				uint32_t *ctr_imm8, 
				uint32_t *ctr_imm4, 
				int32_t  *imm4, 
				uint64_t *imm8 )
{
	/* vars */
	uint32_t itmp	= (uint32_t)(*inst >> 32);
	uint64_t *ptr	= NULL;
	/* ---- */

#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_ENTRY();
#endif

	/* -- instruction fields */
	*r0		= ( itmp & G_6BIT );
	*r1		= ( (itmp >> 6) & G_6BIT );
	*r2		= ( (itmp >> 12) & G_6BIT );
	*opc		= ( (itmp >> 18) & G_8BIT );
	*ctr		= ( (itmp >> 26) & G_6BIT );

	/* -- control bits */
	*ctr_vec	= ( *ctr & G_BIT0 );
	*ctr_v0		= ( *ctr & G_BIT1 );
	*ctr_v1		= ( *ctr & G_BIT2 );
	*ctr_brk	= ( *ctr & G_BIT3 );
	*ctr_imm4	= ( *ctr & G_BIT4 );
	*ctr_imm8	= ( *ctr & G_BIT5 );

	/* -- check for immediate values */
	if( *ctr_imm4 > 0 ){
		/* 4 byte immediate */
		ptr = (inst+0x08);
		*imm4 = (int32_t)(*ptr >> 32);	
	}

	if( *ctr_imm8 > 0 ){ 
		/* 8 byte immediate */
		ptr = (inst+0x08);
		*imm8 = *ptr;	
	}

#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;
}

/* -------------------------------------------------- GSIM_DISASS_LOWER */
/* 
 * GSIM_DISASS_LOWER
 * 
 */
static int gsim_disass_lower(	uint64_t *inst,  
				uint32_t *r0, 
				uint32_t *r1, 
				uint32_t *r2, 
				uint32_t *opc, 
				uint32_t *ctr,
				uint32_t *ctr_vec,
				uint32_t *ctr_v0, 
				uint32_t *ctr_v1, 
				uint32_t *ctr_brk, 
				uint32_t *ctr_imm8, 
				uint32_t *ctr_imm4, 
				int32_t  *imm4, 
				uint64_t *imm8 )
{
	/* vars */
	uint32_t itmp	= (uint32_t)(*inst & G_32BIT);
	uint64_t *ptr	= NULL;
	/* ---- */

#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_ENTRY();
#endif

	/* -- instruction fields */
	*r0		= ( itmp & G_6BIT );
	*r1		= ( (itmp >> 6) & G_6BIT );
	*r2		= ( (itmp >> 12) & G_6BIT );
	*opc		= ( (itmp >> 18) & G_8BIT );
	*ctr		= ( (itmp >> 26) & G_6BIT );

	/* -- control bits */
	*ctr_vec	= ( *ctr & G_BIT0 );
	*ctr_v0		= ( *ctr & G_BIT1 );
	*ctr_v1		= ( *ctr & G_BIT2 );
	*ctr_brk	= ( *ctr & G_BIT3 );
	*ctr_imm4	= ( *ctr & G_BIT4 );
	*ctr_imm8	= ( *ctr & G_BIT5 );

	/* -- check for immediate values */
	if( *ctr_imm4 > 0 ){
		/* 4 byte immediate */
		ptr = (inst+0x08);
		*imm4 = (int32_t)(*ptr & G_32BIT);	
	}

	if( *ctr_imm8 > 0 ){ 
		/* 8 byte immediate */
		ptr = (inst+0x08);
		*imm8 = *ptr;	
	}

#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;
}

/* -------------------------------------------------- GSIM_DISASS */
/* 
 * GSIM_DISASS
 * 
 */
extern int gsim_disass(	uint64_t *inst,  
			uint32_t *l_r0, 
			uint32_t *l_r1, 
			uint32_t *l_r2, 
			uint32_t *l_opc, 
			uint32_t *l_ctr,
			uint32_t *l_ctr_vec,
			uint32_t *l_ctr_v0, 
			uint32_t *l_ctr_v1, 
			uint32_t *l_ctr_brk, 
			uint32_t *l_ctr_imm8, 
			uint32_t *l_ctr_imm4, 
			int32_t  *l_imm4, 
			uint64_t *l_imm8, 
			uint32_t *u_r0, 
			uint32_t *u_r1, 
			uint32_t *u_r2, 
			uint32_t *u_opc, 
			uint32_t *u_ctr,
			uint32_t *u_ctr_vec,
			uint32_t *u_ctr_v0, 
			uint32_t *u_ctr_v1, 
			uint32_t *u_ctr_brk, 
			uint32_t *u_ctr_imm8, 
			uint32_t *u_ctr_imm4, 
			int32_t  *u_imm4, 
			uint64_t *u_imm8 )
{
#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_ENTRY();
#endif

	gsim_disass_lower(	inst, 
				l_r0, 
				l_r1, 
				l_r2, 
				l_opc, 
				l_ctr, 
				l_ctr_vec, 
				l_ctr_v0, 
				l_ctr_v1, 
				l_ctr_brk,
				l_ctr_imm8, 
				l_ctr_imm4, 
				l_imm4, 
				l_imm8 );


	gsim_disass_upper(	inst, 
				u_r0, 
				u_r1, 
				u_r2, 
				u_opc, 
				u_ctr, 
				u_ctr_vec, 
				u_ctr_v0, 
				u_ctr_v1, 
				u_ctr_brk,
				u_ctr_imm8, 
				u_ctr_imm4, 
				u_imm4, 
				u_imm8 );

#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;	
}


/* EOF */
