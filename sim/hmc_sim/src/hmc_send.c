/* 
 * _HMC_SEND_C_
 * 
 * HYBRID MEMORY CUBE SIMULATION LIBRARY 
 * 
 * MEMORY SEND FUNCTIONS
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hmc_sim.h"


/* ----------------------------------------------------- HMCSIM_SEND */
/* 
 * HMCSIM_SEND
 * 
 */
extern int	hmcsim_send( struct hmcsim_t *hmc, uint64_t *packet )
{
	/* vars */
	uint64_t header = 0x00ll;
	uint64_t tail 	= 0x00ll;
	uint32_t len	= 0;
	uint32_t t_len	= 0;
	uint32_t target	= hmc->xbar_depth+1;	/* -- out of bounds to check for stalls */
	uint32_t i	= 0;
	uint8_t link	= 0;
	uint8_t cub	= 0;
	/* ---- */

	if( hmc == NULL ){ 
		return -1;
	}

	if( packet == NULL ){ 
		return -1;
	}

	/* 
	 * pull the packet header
	 * we need to know the packet length and the packet destination
	 *
	 */
	header = packet[0];

	/* 
	 * pull the packet length and grab the tail
	 * 
	 */
	len = (uint32_t)( (header & 0x780) >> 7 );
	t_len = len * 2;
	
	tail = packet[t_len-1];	

	/* 
	 * grab the cub 
	 * 
	 */
	cub = (uint8_t)( header & 0x3F );

	/* 
	 * grab the link id 
	 *
	 */
	link = (uint8_t)( (tail & 0x7000000 ) >> 24 );


	/* 
	 * validate the cub:link 
	 * 
	 */
	if( hmc->devs[cub].links[link].type != HMC_LINK_HOST_DEV ){
		/* 
		 * NOT A HOST LINK!!
	 	 * 
	 	 */

		return -1;
	}

	/* 
	 * Now that we have the locality details
	 * of the packet request destination, 
	 * go out and walk the respective link
	 * xbar queues and try to push the request
	 * into the first empty queue slot.
	 * 
	 * NOTE: this will likely need to be changed
	 *       if we ever support proper ordering
	 * 	 constraints on the devsice
	 * 
	 */	

	for( i=hmc->xbar_depth-1; i>=0; i-- ){
		if( hmc->devs[cub].xbar[link].xbar_rqst[i].valid == HMC_RQST_INVALID ){
			target = i;
		} 
	}		

	if( target == (hmc->xbar_depth+1) ) {
		/* 
		 * stall the request
		 * 
		 */
		return HMC_STALL;	
	}

	/* else, push the packet into the designate queue slot */
	hmc->devs[cub].xbar[link].xbar_rqst[target].valid = HMC_RQST_VALID;	
	memset( hmc->devs[cub].xbar[link].xbar_rqst[target].packet, 0, sizeof( uint64_t ) * HMC_MAX_UQ_PACKET );	
	for( i=0; i<t_len; i++ ) { 
		hmc->devs[cub].xbar[link].xbar_rqst[target].packet[i] = packet[i];
	}

	return 0;
}

/* EOF */
