/* 
 * _EXECUTE_TEST_C_ 
 * 
 * HMCSIM PHYSRAND TEST EXECUTION FUNCTIONS
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "hmc_sim.h"


/* ---------------------------------------------------- ZERO_PACKET */
/* 
 * ZERO_PACKET 
 * 
 */
static void zero_packet( uint64_t *packet )
{
	uint64_t i = 0x00ll;

	/* 
	 * zero the packet
	 * 
	 */
	for( i=0; i<HMC_MAX_UQ_PACKET; i++ ){
		packet[i] = 0x00ll;
	} 


	return ;
}

/* ---------------------------------------------------- EXECUTE_TEST */
/* 
 * EXECUTE TEST
 * 
 */
extern int execute_test(	struct hmcsim_t *hmc, 
				uint64_t *addr, 
				uint32_t *req, 
				long num_req )
{
	/* vars */
	uint32_t z		= 0x00;
	long iter		= 0x00l;
	uint64_t head		= 0x00ll;
	uint64_t tail		= 0x00ll;
	uint64_t payload[2]	= {0x00ll,0x00ll};
	uint64_t packet[HMC_MAX_UQ_PACKET];
	uint8_t	cub		= 0;
	uint16_t tag		= 0;
	uint8_t link		= 0;
	int ret			= HMC_OK;
	FILE *ofile		= NULL;
	/* ---- */


	/* 
	 * Setup the tracing mechanisms
	 * 
	 */
	ofile = fopen( "physrand.out", "w" );	
	if( ofile == NULL ){ 
		printf( "FAILED : COULD NOT OPEN OUTPUT FILE physrand.out\n" );
		return -1;
	}

	hmcsim_trace_handle( hmc, ofile );
	hmcsim_trace_level( hmc, (HMC_TRACE_BANK|
				HMC_TRACE_QUEUE|
				HMC_TRACE_CMD|
				HMC_TRACE_STALL|
				HMC_TRACE_LATENCY) );

	/* 
	 * zero the packet
	 * 
	 */
	zero_packet( &(packet[0]) );

	/* 
	 * Attempt to execute all the requests
	 * Push requests into the device
	 * until we get a stall signal 
 	 */ 
	while( iter < num_req ){ 

		/* 
	 	 * attempt to push a request in 
		 * as long as we don't stall
		 *
	 	 */		
		while( (ret != HMC_STALL) && (ret != HMC_ERROR) ){

			/* 
			 * try to push another request 
			 * 
			 * Step 1: Build the Request
			 * 
			 */		
			if( req[(int)iter] == 1 ){
				/* 
			 	 * read request
				 *
				 */
				hmcsim_build_memrequest( hmc, 
							cub, 
							addr[iter], 
							tag, 
							RD16, 
							link, 
							&(payload[0]), 
							&head, 
							&tail );
				/* 
				 * read packets have: 
				 * head + 
				 * tail
				 * 
				 */
				packet[0] = head;
				packet[1] = tail;
			}else {
				/* 
				 * write request
				 *
				 */
				hmcsim_build_memrequest( hmc, 
							cub, 
							addr[iter], 
							tag, 
							WR16, 
							link, 
							&(payload[0]), 
							&head, 
							&tail );
				/* 
				 * write packets have: 
				 * head + 
				 * data + 
				 * data + 
				 * tail
				 * 
				 */
				packet[0] = head;
				packet[1] = 0x00ll;
				packet[2] = 0x00ll;
				packet[3] = tail;
			}
			
			/* 
			 * Step 2: Send it 
			 *
			 */
			ret = hmcsim_send( hmc, &(packet[0]) );

			/* 
			 * zero the packet 
			 * 
			 */
			zero_packet( &(packet[0]) );

			/* 
			 * update the counts
			 *
			 */
			iter++;

			tag++;
			if( tag == (UINT8_MAX-1) ){
				tag = 0;
			}	

			link++;
			if( link == hmc->num_links ){
				/* -- TODO : look at the number of connected links
				 * to the host processor
				 */
				link = 0;
			}

			/* DONE SENDING REQUESTS */
		}

		/* 
		 * reset the return code for receives
		 * 
		 */
		ret = HMC_OK;

		/* 
		 * We hit a stall or an error
		 * 
		 * Try to drain the responses off all the links
		 * 
		 */
		for( z=0; z<hmc->num_links; z++ ){

			/* 
			 * try link 'z' 
			 * pull responses until you get a stall signal 
			 * 
	 		 */
			while( (ret != HMC_STALL) && (ret != HMC_ERROR) ){

				ret = hmcsim_recv(hmc,cub,z,&(packet[0]) );

				/* 
				 * zero the packet 
				 * 
				 */
				zero_packet( &(packet[0]) );

			}
		}

		/* 
		 * reset the return code
		 * 
		 */
		ret = HMC_OK;
	

		/* 
	 	 * done with sending/receiving packets
		 * update the clock 
		 */
		hmcsim_clock( hmc );

	}

	fclose( ofile );
	ofile = NULL;

	return 0;
}

/* EOF */
