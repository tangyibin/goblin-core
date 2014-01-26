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
		case MEMSIM_RD4:
		case MEMSIM_WR4:
		case MEMSIM_RD8:
		case MEMSIM_WR8:
		case MEMSIM_HMC_RD16:
		case MEMSIM_HMC_RD32:
		case MEMSIM_HMC_RD48:
		case MEMSIM_HMC_RD64:
		case MEMSIM_HMC_RD80:
		case MEMSIM_HMC_RD96:
		case MEMSIM_HMC_RD112:
		case MEMSIM_HMC_RD128:
		case MEMSIM_HMC_WR16:
		case MEMSIM_HMC_WR32:
		case MEMSIM_HMC_WR48:
		case MEMSIM_HMC_WR64:
		case MEMSIM_HMC_WR80:
		case MEMSIM_HMC_WR96:
		case MEMSIM_HMC_WR112:
		case MEMSIM_HMC_WR128:
		case MEMSIM_FENCE:
			return MEMSIM_OK;
			break;
		case MEMSIM_UNK:
		default:
			return MEMSIM_ERROR;
	}
}

/* EOF */
