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

	return 0;
}

/* EOF */
