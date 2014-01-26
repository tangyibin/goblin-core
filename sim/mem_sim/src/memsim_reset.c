/* 
 * _MEMSIM_RESET_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM RESET FUNCTIONS
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ MEMSIM_RESET */
/* 
 * MEMSIM_RESET
 * 
 */
extern int memsim_reset( struct memsim_t *msim )
{
	/* vars */
	uint64_t total	= 0x00ll;
	uint64_t i	= 0x00ll;
	/* ---- */

	/* 
	 * sanity check 
	 *
	 */
	if( msim == NULL ){ 
		return MEMSIM_ERROR;
	}

	total	= (uint64_t)(msim->task_groups)*(uint64_t)(msim->g_slots);
	total	+= (uint64_t)(msim->s_slots);

	if( (msim->opt & MEMSIM_AMO) > 0 ){ 
		total += (uint64_t)(msim->a_slots);
	}

	if( (msim->opt & MEMSIM_GA) > 0 ){ 
		total += (uint64_t)(msim->ga_slots);
	}

	for( i=0; i<total; i++ ){ 
		msim->__ptr_entry[i].buf[0]	= 0x00ll;
		msim->__ptr_entry[i].buf[1]	= 0x00ll;
		msim->__ptr_entry[i].buf[2]	= 0x00ll;
		msim->__ptr_entry[i].buf[3]	= 0x00ll;
		msim->__ptr_entry[i].gconst	= 0x00ll;
		msim->__ptr_entry[i].valid	= 0x00;
		msim->__ptr_entry[i].rqst	= MEMSIM_UNK;
	}

	return MEMSIM_OK;
}

/* EOF */
