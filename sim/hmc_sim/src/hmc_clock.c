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


/* ----------------------------------------------------- HMCSIM_CLOCK_PROCESS_RQST_QUEUE */
/* 
 * HMCSIM_CLOCK_PROCESS_RQST_QUEUE
 * 
 */
static int hmcsim_clock_process_rqst_queue( 	struct hmcsim_t *hmc, 
						uint32_t dev, 
						uint32_t link )
{
	/* vars */
	uint32_t i	= 0;
	uint32_t success= 0;
	uint32_t len	= 0;
	uint8_t	cub	= 0;
	uint8_t plink	= 0;
	uint64_t header	= 0x00ll;
	uint64_t tail	= 0x00ll;
	/* ---- */

	/* 
	 * walk the queue and process all the valid
	 * slots
	 * 
	 */

	for( i=0; i<hmc->xbar_depth; i++ ){
		
		if( hmc->devs[dev].xbar[link].xbar_rqst[i].valid == HMC_RQST_VALID ){ 
			
			/* 
			 * process me
			 * 
			 */			

			/* 
			 * Step 1: Get the header
			 * 
			 */
			header = hmc->devs[dev].xbar[link].xbar_rqst[i].packet[0];

			/* 
			 * Step 2: Get the CUB.  
			 *
			 */
			cub = (uint8_t)( header & 0x3F );	

			/* Step 3: If it is equal to `dev`
			 *         then we have a local request.
			 * 	   Otherwise, its a request to forward to
			 * 	   an adjacent device.
			 */
		
			/* 
			 * Stage 4: Get the packet length
			 * 
			 */
			len = (uint32_t)( (header & 0x780) >> 7);
			len *= 2;

			/* 
			 * Stage 5: Get the packet tail
			 * 
			 */		
			tail = hmc->devs[dev].xbar[link].xbar_rqst[i].packet[len-1];


			/* 
			 * Stage 6: Get the link
			 * 
			 */
			plink = (uint8_t)( (tail & 0x7000000) >> 24 );

			if( cub == (uint8_t)(dev) ){
				/* 
				 * local request
				 *
				 */
			}else{

				/* 
				 * forward request to remote device
				 *
				 */

			}

			if( success == 1 ){ 
			
				/* 
				 * clear the packet 
				 * 
				 */
				hmc->devs[dev].xbar[link].xbar_rqst[i].valid = HMC_RQST_INVALID;
				memset( hmc->devs[dev].xbar[link].xbar_rqst[i].packet, 0, sizeof( uint64_t ) * HMC_MAX_UQ_PACKET ); 
			}

		}

		success = 0;
	}		

	return 0;
}


/* ----------------------------------------------------- HMCSIM_CLOCK_CHILD_XBAR */
/* 
 * HMCSIM_CLOCK_CHILD_XBAR
 * 
 */
static int hmcsim_clock_child_xbar( struct hmcsim_t *hmc )
{
	/* vars */
	uint32_t i	= 0;
	uint32_t j	= 0;
	uint32_t host_l	= 0;
	/* ---- */

	/* 
	 * walk each device and interpret the links
	 * if you find a HOST link, no dice. 
	 * otherwise, process the xbar queues
	 * 
	 */
	for( i=0; i<hmc->num_devs; i++ ){ 
		
		/* 
		 * walk the links
	 	 * 
	 	 */
		
		for( j=0; j<hmc->num_links; j++ ){ 
			
			if( hmc->devs[i].links[j].type == HMC_LINK_HOST_DEV ){ 
				host_l++;
			}

		}

		/* 
		 * if no host links found, process the queues
	 	 *
		 */
		if( host_l == 0 ) {

			/* 
			 * walk the xbar queues and process the 
			 * incoming packets
			 *
			 */
			for( j=0; j<hmc->num_links; j++ ){ 

				hmcsim_clock_process_rqst_queue( hmc, i, j );

			}		
		}

		/* 
		 * reset the host links
		 *
		 */
		host_l	= 0;
	}

	return 0;
}


/* ----------------------------------------------------- HMCSIM_CLOCK_ROOT_XBAR */
/* 
 * HMCSIM_CLOCK_ROOT_XBAR
 * 
 */
static int hmcsim_clock_root_xbar( struct hmcsim_t *hmc )
{
	return 0;
}


/* ----------------------------------------------------- HMCSIM_CLOCK */
/* 
 * HMCSIM_CLOCK
 * 
 */
extern int	hmcsim_clock( struct hmcsim_t *hmc )
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

	/* 
	 * Walk all the devices one by one
	 * 
	 * Stage 1: Walk all the child devices and drain
	 * 	    their xbars
	 * 
	 * Stage 2: Start with the root device(s) and drain
	 * 	    the xbar of any messages
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

	/* 
	 * Stage 1: Drain the child devices
	 * 
	 */
	if( hmcsim_clock_child_xbar( hmc ) != 0 ){
		return -1;
	}

	/* 
	 * Stage 2: Drain the root devices
	 * 
	 */
	if( hmcsim_clock_root_xbar( hmc ) != 0 ){
		return -1;
	}

	/* 
	 * Stage 6: update the clock value
	 * 
	 */
	hmc->clk++;

	return 0;
}

/* EOF */
