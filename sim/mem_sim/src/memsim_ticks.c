/* 
 * _MEMSIM_TICKS_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM TICKS FUNCTIONS
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ MEMSIM_TICK_COUNT */
/* 
 * MEMSIM_TICK_COUNT
 * 
 */
extern int memsim_tick_count(	struct memsim_entry_t *ent, uint64_t *ticks )
{
	/* 
	 * sanity check 
	 *
	 */
	if( ent == NULL ){ 
		return MEMSIM_ERROR;
	}else if( ticks == NULL ){ 
		return MEMSIM_ERROR;
	}

	switch( ent->rqst )
	{
		case MEMSIM_RD4:
			*ticks	= 1;
			break;
		case MEMSIM_WR4:
			*ticks	= 1;
			break;
		case MEMSIM_RD8:
			*ticks	= 1;
			break;
		case MEMSIM_WR8:
			*ticks	= 1;
			break;
		case MEMSIM_FENCE:
			*ticks	= 1;
			break;
		case MEMSIM_UNK:
			*ticks	= 1;
			break;
		case MEMSIM_HMC_RD16:
		case MEMSIM_HMC_RD32:
		case MEMSIM_HMC_RD48:
		case MEMSIM_HMC_RD64:
		case MEMSIM_HMC_RD80:
		case MEMSIM_HMC_RD96:
		case MEMSIM_HMC_RD112:
		case MEMSIM_HMC_RD128:
			*ticks	= 2;
			break;
		case MEMSIM_HMC_WR16:
			*ticks	= 4;
			break;
		case MEMSIM_HMC_WR32:
			*ticks	= 6;
			break;
		case MEMSIM_HMC_WR48:
			*ticks	= 8;
			break;
		case MEMSIM_HMC_WR64:
			*ticks	= 10;
			break;
		case MEMSIM_HMC_WR80:
			*ticks	= 12;
			break;
		case MEMSIM_HMC_WR96:
			*ticks	= 14;
			break;
		case MEMSIM_HMC_WR112:
			*ticks	= 16;
			break;
		case MEMSIM_HMC_WR128:
			*ticks	= 18;
			break;
		default:
			return MEMSIM_ERROR;	
			break;
	}	

	return MEMSIM_OK;
}

/* EOF */
