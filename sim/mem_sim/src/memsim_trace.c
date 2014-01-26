/* 
 * _MEMSIM_TRACE_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM TRACE 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ MEMSIM_TRACE_LEVEL */
/* 
 * MEMSIM_TRACE_LEVEL
 * 
 */
extern int memsim_trace_level(	struct memsim_t *msim, 
				uint32_t level )
{
	if( msim == NULL ){ 
		return MEMSIM_ERROR;
	}

	msim->tracelevel = level;	

	return MEMSIM_OK;
}

/* ------------------------------------------------ MEMSIM_TRACE_HANDLE */
/* 
 * MEMSIM_TRACE_HANDLE
 * 
 */
extern int memsim_trace_handle(	struct memsim_t *msim, 
				FILE *tfile )
{
	/* 
	 * sanity check 
	 *
	 */
	if( msim == NULL ){ 
		return MEMSIM_ERROR;
	}

	if( tfile == NULL ){ 
		return MEMSIM_ERROR;
	}

	msim->tfile	= tfile;

	return MEMSIM_OK;
}

/* EOF */
