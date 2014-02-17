/* 
 * _MEMSIM_HW_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM HW FUNCTIONS
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ MEMSIM_SET_HW */
/* 
 * MEMSIM_SET_HW
 * 
 */
extern int memsim_set_hw( struct memsim_t *msim, 
				uint32_t num_links, 
				uint32_t num_lanes, 
				float gbps )
{
	/* 
	 * sanity check 
	 *
	 */
	if( msim == NULL ){ 
		return MEMSIM_ERROR;
	}

	/* TODO : SANITY CHECK THE LINKS */

	if( (num_links != 4 ) && ( num_links != 8 )){ 
		return MEMSIM_ERROR;
	}

	if( (num_lanes != 8) && (num_lanes != 16) ){ 
		return MEMSIM_ERROR;
	}

	if( (gbps != (float)(10.)) && 
		(gbps != (float)(12.5)) && 
		(gbps != (float)(15.)) ){ 
		return MEMSIM_ERROR;
	}

	msim->hw.num_links	= num_links;
	msim->hw.num_lanes	= num_lanes;
	msim->hw.gbps		= gbps;
	msim->hw.payps		= (uint64_t)( (((float)(num_lanes) * gbps * MEMSIM_GIGABIT )
					/(float)(8))/8 ) 
					* (uint64_t)(num_links);

	return MEMSIM_OK;
}

/* EOF */
