/* 
 * _MEMSIM_EMPTY_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM EMPTY FUNCTIONS
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ MEMSIM_IS_EMPTY */
/* 
 * MEMSIM_IS_EMPTY
 * 
 */
extern int memsim_is_empty( struct memsim_t *msim )
{
	/* vars */
	uint32_t i		= 0;
	uint32_t j		= 0;
	/* ---- */

	/* 
	 * sanity check 
	 *
	 */
	if( msim == NULL ){ 
		return MEMSIM_ERROR;
	}

	/* 
	 * global 
	 *
	 */
	if( (msim->opt & MEMSIM_GA ) > 0 ){
		for( j=0; j<msim->ga_slots; j++ ){ 
			if( msim->global->entry[j].valid == 1 ){ 
				return MEMSIM_NEMPTY;
			}
		}
	}

	/* 
	 * amo 
	 * 
 	 */
	if( (msim->opt & MEMSIM_AMO ) > 0 ){
		for( j=0; j<msim->a_slots; j++ ){ 
			if( msim->amo->entry[j].valid == 1 ){ 
				return MEMSIM_NEMPTY;
			}
		}
	}

	/* 
	 * socket
	 * 
 	 */
	for( j=0; j<msim->s_slots; j++ ){ 
		if( msim->socket->entry[j].valid == 1 ){ 
			return MEMSIM_NEMPTY;
		}
	}

	/* 
	 * task groups
	 * 
 	 */	
	for( i=0; i<msim->task_groups; i++ ){ 
		for( j=0; j<msim->g_slots; j++ ){ 
			if( msim->group[i].entry[j].valid == 1 ){ 
				return MEMSIM_NEMPTY;	
			}
		}
	}

	return MEMSIM_OK;
}

/* EOF */
