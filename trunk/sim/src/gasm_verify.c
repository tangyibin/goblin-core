/* 
 * 
 * _GASM_VERIFY_C_ 
 * 
 * GASM ASM VERIFICATION
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


#define G_8BIT	0x000000FF
#define G_6BIT	0x0000003F

/* -------------------------------------------------- GASM_VALIDATE */
/* 
 * GASM_VALIDATE
 * 
 */
static int gasm_validate( struct gsim_t *sim, uint64_t *inst, uint64_t n )
{
	/* vars */
	uint32_t l_r0		= 0;
	uint32_t l_r1		= 0;
	uint32_t l_r2		= 0;
	uint32_t l_opc		= 0;
	uint32_t l_ctr		= 0;
	uint32_t l_ctr_vec	= 0;
	uint32_t l_ctr_v0	= 0;
	uint32_t l_ctr_v1	= 0;
	uint32_t l_ctr_brk	= 0;
	uint32_t l_ctr_imm8	= 0;
	uint32_t l_ctr_imm4	= 0;
	int32_t l_imm4		= 0;
	int64_t l_imm8		= 0;
	uint32_t u_r0		= 0;
	uint32_t u_r1		= 0;
	uint32_t u_r2		= 0;
	uint32_t u_opc		= 0;
	uint32_t u_ctr		= 0;
	uint32_t u_ctr_vec	= 0;
	uint32_t u_ctr_v0	= 0;
	uint32_t u_ctr_v1	= 0;
	uint32_t u_ctr_brk	= 0;
	uint32_t u_ctr_imm8	= 0;
	uint32_t u_ctr_imm4	= 0;
	int32_t u_imm4		= 0;
	int64_t u_imm8		= 0;
	/* ---- */

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

	if( gsim_disass(	inst, 
				&l_r0, 
				&l_r1, 
				&l_r2, 
				&l_opc, 
				&l_ctr, 
				&l_ctr_vec,
				&l_ctr_v0, 
				&l_ctr_v1, 
				&l_ctr_brk, 
				&l_ctr_imm8, 
				&l_ctr_imm4, 
				&l_imm4, 
				&l_imm8,
				&u_r0, 
				&u_r1, 
				&u_r2, 
				&u_opc, 
				&u_ctr, 
				&u_ctr_vec,
				&u_ctr_v0, 
				&u_ctr_v1, 
				&u_ctr_brk, 
				&u_ctr_imm8, 
				&u_ctr_imm4, 
				&u_imm4, 
				&u_imm8 ) != 0 ){
		/* 
		 * disass failed
		 */
		return -1;

	}
	
	/* -- validate the lower instruction */
	if( gsim_inst_validate(	sim, 
				l_r0, 
				l_r1, 
				l_r2, 
				l_opc, 
				l_ctr, 
				l_ctr_vec, 
				l_ctr_v0, 
				l_ctr_v1, 
				l_ctr_brk, 
				l_ctr_imm4, 
				l_ctr_imm8, 
				l_imm4, 
				l_imm8 ) != 0 )
	{
		/* 
		 * validation failed
		 */

		return -1;
	}

	/* -- validate the upper instruction */
	if( gsim_inst_validate(	sim, 
				u_r0, 
				u_r1, 
				u_r2, 
				u_opc, 
				u_ctr, 
				u_ctr_vec, 
				u_ctr_v0, 
				u_ctr_v1, 
				u_ctr_brk, 
				u_ctr_imm4, 
				u_ctr_imm8, 
				u_imm4, 
				u_imm8 ) != 0 )
	{
		/* 
		 * validation failed
		 */

		return -1;
	}


#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif

	return 0;
}

/* -------------------------------------------------- GASM_VERIFY */
/* 
 * GASM_VERIFY
 * 
 */
extern int gasm_verify( struct gsim_t *sim, uint64_t *inter, uint64_t nread )
{
	/* vars */
	uint64_t i	= 0;
	int tmp		= 0;
	int rtn		= 0;
	/* ---- */

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

	/* 
	 * walk the instructions and verify each
	 */
	for( i=0; i<nread; i++ ){ 
	
		/* 
	 	 * validate this instruction 
		 */
		tmp = gasm_validate( sim, &(inter[i]), i );

		if( tmp == -1 ){ 
			/* 
			 * failed
			 */
			rtn = -1;

		}else if( tmp == 1 ){ 
			/* 
			 * next quad word is an immediate 
			 * bump the counter to skip over it
			 */
			i++;
		}
	}	


#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return rtn;	
}


/* EOF */
