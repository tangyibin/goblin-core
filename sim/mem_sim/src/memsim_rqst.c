/* 
 * _MEMSIM_RQST_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM RQST FUNCTIONS
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ MEMSIM_RQST */
/* 
 * MEMSIM_RQST
 * 
 */
extern int memsim_rqst(	struct memsim_t *msim, 
			uint64_t gconst, 
			memsim_rqst_t rqst, 
			uint64_t *addr, 
			uint64_t *payload )
{
	/* vars */
	/* ---- */

	/* 
	 * sanity check 
	 *
	 */
	if( msim == NULL ){ 
		return MEMSIM_ERROR;
	}

	return MEMSIM_OK;
}

/* EOF */
