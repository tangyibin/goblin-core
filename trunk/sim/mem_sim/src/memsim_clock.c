/* 
 * _MEMSIM_CLOCK_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM CLOCK 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ FUNCTION_PROTOTYPES */
extern int memsim_clock_simple( struct memsim_t *msim );
extern int memsim_clock_cache( struct memsim_t *msim );
extern int memsim_clock_exp( struct memsim_t *msim );

/* ------------------------------------------------ MEMSIM_CLOCK */
/* 
 * MEMSIM_CLOCK
 * 
 */
extern int memsim_clock( struct memsim_t *msim )
{
	int rtn	= 0;

	/* 
	 * sanity check 
	 *
	 */
	if( msim == NULL ){ 
		return MEMSIM_ERROR;
	}

	/* 
	 * Here we decide which algorithm to 
 	 * execute. For each algorithm type, 
	 * we must provide a backend 
	 * implementation.  
	 *
	 */
	switch( msim->alg )
	{
		case MEMSIM_SIMPLE:

			rtn	= memsim_clock_simple(msim);

			/* 
			 * nudge the clock 
		 	 *
			 */
			msim->clock ++;

			break;
		case MEMSIM_CACHE:

			rtn	= memsim_clock_cache(msim);

			/* 
			 * nudge the clock 
		 	 *
			 */
			msim->clock ++;

			break;
		case MEMSIM_EXP:

			rtn	= memsim_clock_exp(msim);

			/* 
			 * nudge the clock 
		 	 *
			 */
			msim->clock ++;

			break;
		default:
			rtn = MEMSIM_ERROR;
			break;
	}

	return rtn;
}

/* EOF */
