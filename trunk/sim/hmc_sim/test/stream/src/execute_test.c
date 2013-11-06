/* 
 * _EXECUTE_TEST_C_
 * 
 * HMCSIM STREAM_TRIAD EXECUTION FUNCTIONS 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "hmc_sim.h"


/* ------------------------------------------------- ZERO_PACKET */
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

/* ------------------------------------------------- EXECUTE_TEST */
/* 
 * EXECUTE_TEST
 * 
 * Executes a Stream Triad : 
 * 
 * a[j] = b[j] + scalar * c[j];
 * where, 0 <= j < num_req
 * 
 */
extern int execute_test(	struct hmcsim_t *hmc, 
				uint64_t *addr_a, 
				uint64_t *addr_b, 
				uint64_t *addr_c, 
				uint32_t *req, 
				long num_req, 
				uint32_t num_threads )
{
	return 0;
}


/* EOF */
