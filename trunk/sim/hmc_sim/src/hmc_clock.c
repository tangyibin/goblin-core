/* 
 * _HMC_CLOCK_C_
 * 
 * HYBRID MEMORY CUBE SIMULATION LIBRARY 
 * 
 * CLOCK FUNCTIONS
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hmc_sim.h"


/* ----------------------------------------------------- HMCSIM_CLOCK */
/* 
 * HMCSIM_CLOCK
 * 
 */
extern int	hmcsim_clock( struct hmcsim_t *hmc )
{
	/* vars */
	uint32_t i	= 0;
	/* ---- */

	/* 
	 * sanity check 
	 * 
 	 */
	if( hmc == NULL ){ 
		return -1;
	}

	/* 
	 * Walk all the devices one by one
	 * 
	 * Stage 1: Start with the root device and drain
	 * 	    the xbar of any messages
	 * 
	 * Stage 2: Walk all the child devices and drain
	 * 	    their xbars as well
	 *
	 * Stage 3: Walk each device's vault queues and
	 *          look for bank conflicts
	 * 
	 * Stage 4: Walk each device's vault queues and 
	 * 	    perform the respective operations
	 * 
	 * Stage 5: Register any necessary responses with
	 * 	    the xbar
	 * 
	 * Stage 6: Update the internal clock value
	 * 
	 */

	/* -- Stage 1: walk each device and drain the xbar's of msg's */
	for( i=0; i<hmc->num_devs; i++ ){
	}


	/* 
	 * update the clock value
	 * 
	 */
	hmc->clk++;

	return 0;
}

/* EOF */
