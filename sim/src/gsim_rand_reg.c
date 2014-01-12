/* 
 * 
 * _GSIM_RAND_REG_C_ 
 * 
 * GOBLIN-SIM RANDOM REGISTER GENERATORS
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


/* -------------------------------------------------- GSIM_RAND_REG_CTRL */
/* 
 * GSIM_RAND_REG_CTRL
 * 
 */
extern uint32_t gsim_rand_reg_ctrl()
{
	/* vars */
	uint32_t tmp	= 0;
	/* ---- */

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

	tmp = (uint32_t)(rand() % 32);

	tmp += 31;

	if( (tmp==0x31) || (tmp==0x32) ){ 
		tmp = 0x33;
	}
	if( (tmp==0x2A) || (tmp==0x2B) ){ 
		tmp = 0x29;
	}


#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return tmp;	
}


/* -------------------------------------------------- GSIM_RAND_REG_CTRL_RO */
/* 
 * GSIM_RAND_REG_CTRL_RO
 * 
 */
extern uint32_t gsim_rand_ctrl_ro()
{
	/* vars */
	uint32_t tmp	= 0;
	/* ---- */

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

	tmp = (uint32_t)(rand() % 13);

	tmp += 0x33;

	if( tmp > 0x3F ) { tmp--; }

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return tmp;	
}

/* -------------------------------------------------- GSIM_RAND_REG_CTRL_RW */
/* 
 * GSIM_RAND_REG_CTRL_RW
 * 
 */
extern uint32_t gsim_rand_reg_ctrl_rw()
{
	/* vars */
	uint32_t tmp	= 0;
	/* ---- */

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

	tmp = (uint32_t)(rand() % 0x30);
	if( (tmp==0x2A) || (tmp==0x2B) ){ 
		tmp = 0x29;
	}

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return tmp;	
}

/* -------------------------------------------------- GSIM_RAND_REG_V */
/* 
 * GSIM_RAND_REG_V
 * 
 */
extern uint32_t gsim_rand_reg_v()
{
	/* vars */
	uint32_t tmp	= 0;
	/* ---- */

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

	tmp = (uint32_t)(rand() % 7);

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return tmp;	
}

/* -------------------------------------------------- GSIM_RAND_REG_R */
/* 
 * GSIM_RAND_REG_R
 * 
 */
extern uint32_t gsim_rand_reg_r()
{
	/* vars */
	uint32_t tmp	= 0;
	/* ---- */

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

	tmp = (uint32_t)(rand() % 31);

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return tmp;	
}


/* EOF */
