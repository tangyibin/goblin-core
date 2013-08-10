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


/* ----------------------------------------------------- FUNCTION PROTOTYPES */
extern int hmcsim_trace( struct hmcsim_t *hmc, char *str );

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
	uint32_t j	= 0;
	uint32_t found	= 0;
	uint32_t success= 0;
	uint32_t len	= 0;
	uint32_t t_link	= 0;
	uint32_t t_slot	= 0;
	uint32_t t_quad = 0;
	uint32_t t_vault= hmc->queue_depth+1;
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
				
				/* 
				 * 7a: Retrieve the vault id
				 * 
				 */
				/* TODO: RETRIEVE THE VAULT FROM THE ADDRESS */
				t_vault = 0;

				/* 
				 * 8a: Retrieve the quad id
				 * 
				 */
				t_quad = plink % hmc->num_quads;
					
				
				/* 
				 * 9a: Search the vault queue for valid slot
				 *     Search bottom-up
				 * 
				 */
				t_slot = hmc->queue_depth+1;

				for( j=hmc->queue_depth-1; j>=0; j-- ){
					if( hmc->devs[dev].quads[t_quad].vaults[t_vault].rqst_queue[j].valid == HMC_RQST_INVALID ){
						t_slot = j;	
					}
				}

				if( t_slot == hmc->queue_depth+1 ){ 
					/* STALL */
				}else {

					/*
					 * push it into the designated queue slot
					 * 
					 */
					hmc->devs[dev].quads[t_quad].vaults[t_vault].rqst_queue[t_slot].valid = HMC_RQST_VALID;
					for( j=0; j<HMC_MAX_UQ_PACKET; j++ ){ 
						hmc->devs[dev].quads[t_quad].vaults[t_vault].rqst_queue[t_slot].packet[j] = 
							hmc->devs[dev].xbar[link].xbar_rqst[i].packet[j];
					}

				}

			}else{

				/* 
				 * forward request to remote device
				 *
				 */

				/* 
				 * Stage 7b: Decide whether cub is accessible
				 * 
				 */
				found = 0;
	
				while( (found != 1) && (j<hmc->num_links) ){ 
					
					if( hmc->devs[dev].links[j].dest_cub == cub ){ 
						found = 1;
						t_link = j;
					}

					j++;
				}

				if( found == 0 ){ 
					/* 
					 * oh snap! can't route to that CUB
					 *
					 */
					/* -- TODO, RETURN AN ERROR */
				}else{ 
					/* 
					 * 8b: routing is good, look for an empty slot
					 * in the target xbar link queue
					 *
					 */
					t_slot = hmc->xbar_depth+1;
					for( j=hmc->xbar_depth-1; j>= 0; j-- ){
	
						/* 
						 * walk the queue from the bottom
						 * up
						 */			
						if( hmc->devs[cub].xbar[t_link].xbar_rqst[j].valid == 
							HMC_RQST_INVALID ) {
							t_slot = j;
						}
					}

					/* 
				 	 * 9b: If available, insert into remote xbar slot 
					 * 
					 */
					if( t_slot == hmc->xbar_depth+1 ){
						/* 
						 * STALL!
						 *
						 */
						success = 0;
					}else {
						/* 
						 * put the new link in the link field
						 *  
						 */
						 hmc->devs[dev].xbar[link].xbar_rqst[i].packet[len-1] |= 
										((uint64_t)(plink)<<24);

						/* 
						 * transfer the packet to the target slot
						 * 
						 */
						hmc->devs[cub].xbar[t_link].xbar_rqst[t_slot].valid = 
							HMC_RQST_VALID;	
						for( j=0; j<HMC_MAX_UQ_PACKET; j++ ){ 
							hmc->devs[cub].xbar[t_link].xbar_rqst[t_slot].packet[j] = 
							hmc->devs[dev].xbar[link].xbar_rqst[i].packet[j];
						}	

						/* 
						 * signal success
						 *
						 */
						success = 1;
					}
				}
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
