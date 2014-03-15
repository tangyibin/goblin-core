/* 
 * _MEMSIM_FIND_CACHE_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM CACHELINE SEARCH FUNCTIONS FUNCTIONS
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"

/* ------------------------------------------------ LOCAL MACROS */
#define	MEMSIM_CACHE_HIT	0
#define	MEMSIM_CACHE_FILL_L1	1
#define	MEMSIM_CACHE_FILL_L2	2
#define	MEMSIM_CACHE_FILL_L3	3
#define	MEMSIM_CACHE_STALL	-1

/* ------------------------------------------------ MEMSIM_FIND_CACHE */
/* 
 * MEMSIM_FIND_CACHE
 * 
 */
extern int memsim_find_cache( 	struct memsim_t *msim, 
				struct memsim_entry_t *ent, 
				uint8_t *way, 
				uint32_t *set )
{
	/* vars */
	/* ---- */

	/* 
	 * we want to walk down the caching chain
	 * from the closest level to the processor
	 * down and look for a free slot or a line
	 * to eject.
	 *
	 */ 

	/* 
	 * L1 Cache
	 * 
	 */
	if( msim->l1 != NULL ){ 
	}


	/* 
	 * L2 Cache
	 * 
	 */
	if( msim->l2 != NULL ){ 
	}


	/* 
	 * L3 Cache
	 * 
	 */
	if( msim->l3 != NULL ){ 
	}


	/* 
	 * we have nothing left, 
	 * time to stall 
	 * 
	 */

	return MEMSIM_CACHE_STALL;
}

/* EOF */
