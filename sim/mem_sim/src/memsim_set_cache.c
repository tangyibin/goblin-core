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


/* ------------------------------------------------ MEMSIM_INIT_CACHE */
/* 
 * MEMSIM_INIT_CACHE
 * 
 */
static int memsim_init_cache( struct memsim_t *msim, 
				struct memsim_cache_t *level, 
				uint8_t ways, 
				uint32_t sets ) {

	/* vars */
	uint32_t i	= 0;
	/* ---- */

	if( msim == NULL ){ 
		return MEMSIM_ERROR;
	}

	if( level == NULL ){ 
		return MEMSIM_ERROR;
	}

	level->ways	= ways;
	level->sets	= sets;

	/* init each line */
	for( i=0; i<((uint32_t)(ways)*sets); i++ ){ 
		level->cache->valid	= 0x0;
		level->cache->tag	= 0x00;
		level->cache->clock	= 0x00ll;
		level->cache->data[0]	= 0x00ll;	
		level->cache->data[1]	= 0x00ll;	
		level->cache->data[2]	= 0x00ll;	
		level->cache->data[3]	= 0x00ll;	
		level->cache->data[4]	= 0x00ll;	
		level->cache->data[5]	= 0x00ll;	
		level->cache->data[6]	= 0x00ll;	
		level->cache->data[7]	= 0x00ll;	
	}	

	return 0;
}

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
	struct memsim_line_t *lines	= NULL;
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

	ptr	= malloc( sizeof( struct memsim_cache_t ) );
	if( ptr == NULL ){ 
		return -1;
	}


	lines 	= malloc( sizeof( struct memsim_line_t ) * (ways*sets));
	if( lines == NULL ){ 
		return -1;
	}

	ptr->cache = lines;

	memsim_init_cache( msim, ptr, ways, sets );

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
