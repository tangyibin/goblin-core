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
extern int	hmcsim_trace_bank_conflict( 	struct hmcsim_t *hmc, 
						uint32_t dev, 
						uint32_t quad, 
						uint32_t vault, 
						uint32_t bank, 
						uint64_t addr1, 
						uint64_t addr2 );




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
	/* vars */
	/* ---- */

	/* 
	 * sanity check 
	 *
	 */
	if( hmc == NULL ){ 
		return -1;
	}

	if( addr == NULL ){ 
		return -1;
	}

	return 0;
}

/* EOF */
