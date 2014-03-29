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
#include <inttypes.h>
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
	/* vars */
	float bw	= 0.;
	/* ---- */

	/* 
	 * sanity check 
	 *
	 */
	if( msim == NULL ){ 
		return MEMSIM_ERROR;
	}

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

	bw      = ((float)(msim->hw.num_lanes * 2 * msim->hw.num_links) * msim->hw.gbps)/(float)(8.0);

        /* 64-bit payloads per second */
        bw      /= (float)(8.0);
        msim->hw.payps          = (uint64_t)(bw);

	return MEMSIM_OK;
}

/* EOF */
