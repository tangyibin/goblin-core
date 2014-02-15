/* 
 * _MEMSIM_CLOCK_CACHE_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM CLOCK CACHE BACKEND
 * 
 * IMPLEMENTS A 4-WAY SET ASSOCIATIVE I-CACHE MODEL
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ FUNCTION PROTOTYPES */
extern int memsim_tid_push( struct memsim_t *msim, uint32_t tid );
extern int memsim_tick_count( struct memsim_entry_t *ent, uint64_t *ticks );
extern int memsim_trace_memop( struct memsim_t *msim, struct memsim_entry_t *ent );
extern int memsim_trace_membus( struct memsim_t *msim, struct memsim_entry_t *ent );
extern int memsim_clear_entry( struct memsim_entry_t *ent );
extern int memsim_bubble_slot( struct memsim_slot_t *slot, uint32_t *rtn );
extern int memsim_cp_entry( struct memsim_entry_t *src, struct memsim_entry_t *dest );

/* ------------------------------------------------ MEMSIM_CLOCK_CACHE_PROCESS_SOCKET */
static int memsim_clock_cache_process_socket( struct memsim_t *msim ){ 
	return MEMSIM_OK;
}

/* ------------------------------------------------ MEMSIM_CLOCK_CACHE_PROCESS_AMO */
static int memsim_clock_cache_process_amo( struct memsim_t *msim ){ 
	return MEMSIM_OK;
}

/* ------------------------------------------------ MEMSIM_CLOCK_CACHE_PROCESS_GLOBAL */
static int memsim_clock_cache_process_global( struct memsim_t *msim ){
	return MEMSIM_OK;
}

/* ------------------------------------------------ MEMSIM_CLOCK_CACHE_PROCESS_TASKGROUP */
static int memsim_clock_cache_process_taskgroup( struct memsim_t *msim, uint32_t gr ){ 
	return MEMSIM_OK;
}

/* ------------------------------------------------ MEMSIM_CLOCK_CACHE */
/* 
 * MEMSIM_CLOCK_CACHE
 * 
 * This backend implementation implements a cache coherency
 * mechanism using a 4-way set associated cache model 
 * 
 */
extern int memsim_clock_cache( struct memsim_t *msim )
{
	/* vars */
	uint32_t i	= 0;
	/* ---- */

	/* 
	 * process the queues 
 	 * 
	 */
	/* -- socket queue */
	if( memsim_clock_cache_process_socket( msim ) != 0 ){ 
		return MEMSIM_ERROR;
	}

	/* -- amo queue */
	if( (msim->opt & MEMSIM_AMO) > 0 ){ 
		if( memsim_clock_cache_process_amo( msim ) != 0 ){ 
			return MEMSIM_ERROR;
		}
	} 

	/* -- global queue */
	if( (msim->opt & MEMSIM_GA) > 0 ){ 
		if( memsim_clock_cache_process_global( msim ) != 0 ){ 
			return MEMSIM_ERROR;
		}
	}

	/* 
	 * process each of the local task group queues
	 * 
 	 */
	for( i=0; i<msim->task_groups; i++ ){ 
		if( memsim_clock_cache_process_taskgroup( msim, i ) != 0 ){ 
			return MEMSIM_ERROR;
		}
	}

	return MEMSIM_OK;
}

/* EOF */
