/* 
 * _MEMSIM_FIND_SLOT_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM FIND_SLOT 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ MEMSIM_FIND_SLOT */
/* 
 * MEMSIM_FIND_SLOT
 * 
 */
extern int memsim_find_slot( struct memsim_slot_t *slot, uint32_t *rtn ) 
{

	/* vars */
	uint32_t i	= 0;
	/* ---- */

	/* 
	 * sanity check 
	 * 
	 */
	if( slot == NULL ){ 
		return MEMSIM_ERROR;
	}else if( rtn == NULL ){ 
		return MEMSIM_ERROR;
	}

	/* 
	 * find the first empty entry 
 	 * 
 	 */
	for( i=0; i<slot->num_slots; i++ ){ 
		if( slot->entry[i].valid == 0 ){ 
			/* found a candidate */
			*rtn = i;
			return MEMSIM_OK;
		}
	}

	return MEMSIM_STALL;
}

/* EOF */
