/* 
 * _MEMSIM_SET_CACHE_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM SET CACHE 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ MEMSIM_SET_CACHE */
/* 
 * MEMSIM_SET_CACHE
 * 
 */
extern int memsim_set_cache(	struct memsim_t *msim, 
				uint32_t unit, 
				uint8_t ways, 
				uint32_t sets,
				uint32_t size )
{
	/* vars */
	struct memsim_cache_t *ptr	= NULL;
	/* ---- */

	/* 
	 * sanity check 
	 *
	 */
	if( msim == NULL ){ 
		return MEMSIM_ERROR;
	}

	if( (unit == 0 ) || (unit > 3) ){ 
		return -1;
	}

	ptr	= malloc( sizeof( struct memsim_cache_t ) *
				(ways * sets) );
	if( ptr == NULL ){ 
		return -1;
	}

	if( unit == 1 ){ 
		msim->l1_cache_sets 	= sets;
		msim->l1_cache_ways	= ways;
		msim->l1_cache_size	= size;
		msim->l1		= ptr;
	}else if( unit == 2 ){ 
		msim->l2_cache_sets 	= sets;
		msim->l2_cache_ways	= ways;
		msim->l2_cache_size	= size;
		msim->l2		= ptr;
	}else if( unit == 3 ){ 
		msim->l3_cache_sets 	= sets;
		msim->l3_cache_ways	= ways;
		msim->l3_cache_size	= size;
		msim->l3		= ptr;
	}

	return MEMSIM_OK;
}

/* EOF */
