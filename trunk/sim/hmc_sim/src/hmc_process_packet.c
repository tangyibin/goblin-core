/* 
 * _HMC_PROCESS_PACKET_C_
 * 
 * HYBRID MEMORY CUBE SIMULATION LIBRARY 
 * 
 * HMC PACKET PROCESSORS FOR MEM OPS
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hmc_sim.h"

/* ----------------------------------------------------- FUNCTION PROTOTYPES */
extern int	hmcsim_trace( struct hmcsim_t *hmc, char *str );




/* ----------------------------------------------------- HMCSIM_PROCESS_RQST */
/* 
 * HMCSIM_PROCESS_RQST
 * 
 */
extern int	hmcsim_process_rqst( 	struct hmcsim_t *hmc, 
					uint32_t dev, 
					uint32_t quad, 
					uint32_t vault, 
					uint32_t slot )
{
	if( hmc == NULL ){ 
		return -1;
	}



	return 0;
}

/* EOF */
