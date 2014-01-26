/* 
 * _MEMSIM_VALIDATE_RQST_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM VALIDATE RQST FUNCTIONS
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ MEMSIM_VALIDATE_RQST */
/* 
 * MEMSIM_VALIDATE_RQST
 * 
 */
extern int memsim_validate_rqst( memsim_rqst_t rqst ){

	switch( rqst )
	{
		case MEMSIM_RD8:
		case MEMSIM_WR8:
		case MEMSIM_FENCE:
			return MEMSIM_OK;
			break;
		case MEMSIM_UNK:
		default:
			return MEMSIM_ERROR;
	}
}

/* EOF */
