/* 
 * _MEMSIM_CACHE_UTILS_C_
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM CACHE BACKEND UTILITY FUNCTIONS
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"

/* ------------------------------------------------ MEMSIM_CACHE_CLEAR_LINE */
/* 
 * MEMSIM_CACHE_CLEAR_LINE
 * 
 */
extern int memsim_cache_clear_line( struct memsim_line_t *line )
{
	line->valid	= 0;
	line->tag	= 0x00;
	line->clock	= 0x00ll;
	line->data[0]	= 0x00ll;
	line->data[1]	= 0x00ll;
	line->data[2]	= 0x00ll;
	line->data[3]	= 0x00ll;
	line->data[4]	= 0x00ll;
	line->data[5]	= 0x00ll;
	line->data[6]	= 0x00ll;
	line->data[7]	= 0x00ll;

	return 0;
}

/* ------------------------------------------------ MEMSIM_CACHE_ENTRY_CLOCK */
/* 
 * MEMSIM_CACHE_ENTRY_CLOCK
 * 
 */
extern int memsim_cache_entry_clock( struct memsim_t *msim )
{
	/* vars */
	uint32_t	i = 0;
	/* ---- */

	/* 
	 * L1 Cache 
	 *
	 */	
	if( msim->l1 != NULL ){ 
		for( i=0; i<msim->l1_cache_size; i++ ){
			if( msim->l1->cache[i].valid == 1 ){ 
				msim->l1->cache[i].clock++;
			}
		}
	}


	/* 
	 * L2 Cache 
	 *
	 */	
	if( msim->l2 != NULL ){ 
		for( i=0; i<msim->l2_cache_size; i++ ){
			if( msim->l2->cache[i].valid == 1 ){ 
				msim->l2->cache[i].clock++;
			}
		}
	}

	/* 
	 * L3 Cache 
	 *
	 */	
	if( msim->l3 != NULL ){ 
		for( i=0; i<msim->l3_cache_size; i++ ){
			if( msim->l3->cache[i].valid == 1 ){ 
				msim->l3->cache[i].clock++;
			}
		}
	}



	return 0;
}

/* EOF */
