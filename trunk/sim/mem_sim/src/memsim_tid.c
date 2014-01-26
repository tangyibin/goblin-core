/* 
 * _MEMSIM_TID_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM TID FUNCTIONS
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ MEMSIM_TID_PUSH */
/* 
 * MEMSIM_TID_PUSH
 * 
 */
extern int memsim_tid_push( struct memsim_t *msim, uint32_t tid )
{
	/* 
	 * sanity check
	 * 
	 */
	if( msim == NULL ){ 
		return MEMSIM_ERROR;
	}

	if( tid >= msim->num_tids ){ 
		return MEMSIM_ERROR;
	}

	/* clear the tid */
	msim->tids[tid].gconst	= 0x00ll;
	msim->tids[tid].valid	= 0;

	return MEMSIM_OK;
}

/* ------------------------------------------------ MEMSIM_TID_POP */
/* 
 * MEMSIM_TID_POP
 * 
 */
extern int memsim_tid_pop( struct memsim_t *msim, uint32_t *tid )
{
	/* vars */
	uint32_t i	= 0;
	/* ---- */

	/* 
	 * sanity check 
	 *
	 */
	if( msim == NULL ){ 
		return MEMSIM_ERROR;
	}

	/* search bottom up */
	for( i=0; i<msim->num_tids; i++ ){ 
		if( msim->tids[i].valid == 0 ){ 
			*tid = 1;
			return MEMSIM_OK;
		}
	}

	return MEMSIM_ERROR;
}

/* EOF */
