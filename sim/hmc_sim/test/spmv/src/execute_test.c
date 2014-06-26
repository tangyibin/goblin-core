/* 
 * _EXECUTE_TEST_C_ 
 * 
 * HMC-SIM SPMV TEST EXECUTION FUNCTIONS
 * FOR THE FINITE STATE MACHINE 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "spmv.h"
#include "hmc_sim.h"


/* ------------------------------------------ ZERO_PACKET */
/* 
 * ZERO_PACKET 
 * 
 */
static void zero_packet( uint64_t *packet )
{
	uint64_t i	= 0x00ll;

	/* 
	 * zero the packet 
	 * 
 	 */
	for( i=0; i<HMC_MAX_UQ_PACKET; i++ ){ 
		packet[i] = 0x00ll;
	}

	return ;
}

/* ------------------------------------------ EXECUTE_TEST */
/* 
 * executes a sparse matrix vector multiply 
 * using a compressed sparse row format 
 * 
 */
extern int execute_test( struct hmcsim_t *hmc, 
			struct csr_t *mat, 
			uint32_t num_threads, 
			uint32_t simd )
{
	/* vars */
	/* ---- */

	return 0;
}

/* EOF */
