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


/* ------------------------------------------------ MEMSIM_CLOCK */
/* 
 * MEMSIM_CLOCK
 * 
 */
extern int memsim_clock( struct memsim_t *msim )
{
	/* vars */
	/* ---- */

	/* 
	 * sanity check 
	 *
	 */
	if( msim == NULL ){ 
		return MEMSIM_ERROR;
	}


	return MEMSIM_OK;
}

/* EOF */
