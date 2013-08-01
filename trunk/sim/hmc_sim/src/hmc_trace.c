/* 
 * _HMC_TRACE_C_
 * 
 * HYBRID MEMORY CUBE SIMULATION LIBRARY 
 * 
 * HMC TRACE CONFIGURATION/EXEC FUNCTIONS
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hmc_sim.h"


/* ----------------------------------------------------- HMCSIM_TRACE_LEVEL */
/* 
 * HMCSIM_TRACE_LEVEL
 * 
 */
extern int	hmcsim_trace_level( struct hmcsim_t *hmc, uint32_t level )
{
	if( hmc == NULL ){ 
		return -1;
	}

	hmc->tracelevel	= level;

	return 0;
}

/* ----------------------------------------------------- HMCSIM_TRACE_HANDLE */
/* 
 * HMCSIM_TRACE_HANDLE
 * 
 */
extern int	hmcsim_trace_handle( struct hmcsim_t *hmc, FILE *tfile )
{
	if( hmc == NULL ){ 
		return -1;
	}

	if( tfile == NULL ){
		return -1;
	}

	hmc->tfile = tfile;	

	return 0;
}

/* EOF */
