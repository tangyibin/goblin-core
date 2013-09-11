/* 
 * _HMC_BANK_CONFLICT_C_
 * 
 * HYBRID MEMORY CUBE SIMULATION LIBRARY 
 * 
 * HMC BANK CONFLICT MODEL
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hmc_sim.h"

/* ----------------------------------------------------- FUNCTION PROTOTYPES */
extern int	hmcsim_trace( struct hmcsim_t *hmc, char *str );




/* ----------------------------------------------------- HMCSIM_PROCESS_BANK_CONFLICTS */
/* 
 * HMCSIM_PROCESS_BANK_CONFLICTS
 * 
 */
extern int	hmcsim_process_bank_conflicts( struct hmcsim_t *hmc, 
						uint32_t dev, 
						uint32_t quad, 
						uint32_t vault, 
						uint64_t *addr )
{
	if( hmc == NULL ){ 
		return -1;
	}

	if( addr == NULL ){ 
		return -1;
	}

	return 0;
}

/* EOF */
