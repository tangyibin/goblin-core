/* 
 * _MEMSIM_CLOCK_SIMPLE_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM CLOCK SIMPLE BACKEND
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ MEMSIM_CLOCK_SIMPLE_PROCESS_SOCKET */
static int memsim_clock_simple_process_socket( struct memsim_t *msim ){
	return MEMSIM_OK;
}

/* ------------------------------------------------ MEMSIM_CLOCK_SIMPLE_PROCESS_AMO */
static int memsim_clock_simple_process_amo( struct memsim_t *msim ){
	return MEMSIM_OK;
}

/* ------------------------------------------------ MEMSIM_CLOCK_SIMPLE_PROCESS_GLOBAL */
static int memsim_clock_simple_process_global( struct memsim_t *msim ){
	return MEMSIM_OK;
}

/* ------------------------------------------------ MEMSIM_CLOCK_SIMPLE_PROCESS_TASKGROUP */
static int memsim_clock_simple_process_taskgroup( struct memsim_t *msim, uint32_t group ){
	return MEMSIM_OK;
}

/* ------------------------------------------------ MEMSIM_CLOCK_SIMPLE */
/* 
 * MEMSIM_CLOCK_SIMPLE
 * 
 * 
 * This backend implementation does nothing but pass
 * the slot entries between queues. It does not request coalescing 
 * whatsoever.  
 * 
 */
extern int memsim_clock_simple( struct memsim_t *msim )
{
	/* vars */
	uint32_t i	= 0;
	/* ---- */

	/* 
	 * process the socket queues 
	 * 
	 */
	/* -- socket queue */
	if( memsim_clock_simple_process_socket( msim ) != 0 ){ 
		return MEMSIM_ERROR;
	}

	/* -- amo queue */
	if( memsim_clock_simple_process_amo( msim ) != 0 ){ 
		return MEMSIM_ERROR;
	}

	/* -- global queue */
	if( memsim_clock_simple_process_global( msim ) != 0 ){ 
		return MEMSIM_ERROR;
	}

	/* 
	 * process each of the local task group queues
	 * 
 	 */
	for( i=0; i<msim->task_groups; i++ ){ 
		if( memsim_clock_simple_process_taskgroup( msim, i ) != 0 ){ 
			return MEMSIM_ERROR;
		}
	}

	return MEMSIM_OK;
}

/* EOF */
