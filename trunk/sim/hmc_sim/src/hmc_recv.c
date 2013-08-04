/* 
 * _HMC_RECV_C_
 * 
 * HYBRID MEMORY CUBE SIMULATION LIBRARY 
 * 
 * MEMORY RECV FUNCTIONS
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hmc_sim.h"


/* ----------------------------------------------------- HMCSIM_RECV */
/* 
 * HMCSIM_RECV
 * 
 */
extern int	hmcsim_recv( struct hmcsim_t *hmc )
{
	if( hmc == NULL ){ 
		return -1;
	}

	return 0;
}

/* EOF */
