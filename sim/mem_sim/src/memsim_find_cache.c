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
	return MEMSIM_CACHE_STALL;
}

/* EOF */
