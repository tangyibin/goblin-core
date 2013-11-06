/* 
 * _STREAM_C_ 
 * 
 * HMCSIM STREAM TEST DRIVER 
 * 
 * Attempts to initialize a HMC instantiation
 * and execute a stream test
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "hmc_sim.h"


/* ----------------------------------------------------- FUNCTION PROTOTYPES */
extern int getshiftamount( 	uint32_t num_links, 
				uint32_t capacity, 
				uint32_t bsize, 
				uint32_t *shiftamt );


/* ----------------------------------------------------- MAIN */
/* 
 * MAIN 
 * 
 */
extern int main( int argc, char **argv )
{
	/* vars */
	int ret			= 0;
	uint32_t num_devs	= 0;
	uint32_t num_links	= 0;
	uint32_t num_vaults	= 0;
	uint32_t queue_depth	= 0;
	uint32_t num_banks	= 0;
	uint32_t num_drams	= 0;
	uint32_t capacity	= 0;
	uint32_t xbar_depth	= 0;		
	uint32_t num_threads	= 2;
	uint32_t bsize		= 128;
	uint32_t simd		= 1;
	uint32_t shiftamt	= 0;
	long num_req		= 0;
	uint64_t *addr_a	= NULL;
	uint64_t *addr_b	= NULL;
	uint64_t *addr_c	= NULL;
	struct hmcsim_t hmc;
	/* ---- */

	while(( ret = getopt( argc, argv, "b:c:d:hl:m:n:q:s:v:x:N:T:" )) != -1 )
	{
		switch( ret )
		{
			case 'b': 
				num_banks = (uint32_t)(atoi(optarg));
				break;
			case 'c':
				capacity = (uint32_t)(atoi(optarg));
				break;
			case 'd': 
				num_drams = (uint32_t)(atoi(optarg));
				break;
			case 'h': 
				printf( "%s%s%s\n", "usage : ", argv[0], " -bcdhlnqvx" );
				printf( " -b <num_banks>\n" );
				printf( " -c <capacity>\n" );
				printf( " -d <num_drams>\n" );
				printf( " -h ...print help\n" );
				printf( " -l <num_links>\n" );
				printf( " -m <block_size>\n" );
				printf( " -n <num_devs>\n" );
				printf( " -q <queue_depth>\n" );
				printf( " -s <simd_width>\n" );
				printf( " -v <num_vaults>\n" );
				printf( " -x <xbar_depth>\n" );
				printf( " -N <num_requests>\n" );
				printf( " -T <num_threads>\n" );
				return 0;
				break;
			case 'l':
				num_links = (uint32_t)(atoi(optarg));
				break;
			case 'm': 
				bsize = (uint32_t)(atoi(optarg));
				break;
			case 'n':
				num_devs = (uint32_t)(atoi(optarg));
				break;
			case 'q':
				queue_depth = (uint32_t)(atoi(optarg));
				break;
			case 's':
				simd	= (uint32_t)(atoi(optarg));
				break;
			case 'v': 
				num_vaults = (uint32_t)(atoi(optarg));
				break;
			case 'x': 
				xbar_depth = (uint32_t)(atoi(optarg));
				break;
			case 'N':
				num_req	= (long)(atol(optarg));
				break;
			case 'T':
				num_threads = (uint32_t)(atoi(optarg));
				break;
			case '?':
			default:
				printf( "%s%s%s\n", "Unknown option: see ", argv[0], " -bcdhlmnqsvxNT" );
				return -1;
				break;
		}
	}


	/* 
	 * allocate memory 
	 * 
	 */
	addr_a = malloc( sizeof( uint64_t ) * num_req );
	if( addr_a == NULL ){ 
		printf( "FAILED TO ALLOCATE MEMORY FOR ADDR_A\n" );
		return -1;
	}
	addr_b = malloc( sizeof( uint64_t ) * num_req );
	if( addr_b == NULL ){ 
		printf( "FAILED TO ALLOCATE MEMORY FOR ADDR_B\n" );
		free( addr_a );
		return -1;
	}

	addr_c = malloc( sizeof( uint64_t ) * num_req );
	if( addr_c == NULL ){ 
		printf( "FAILED TO ALLOCATE MEMORY FOR ADDR_C\n" );
		free( addr_a );
		free( addr_b );
		return -1;
	}

	/* 
	 * get the shift amount based upon
	 * the max block size, device size and link count
 	 * 
	 */
	if( getshiftamount( num_links, capacity, bsize, &shiftamt ) != 0 ){ 
		printf( "FAILED TO RETRIEVE SHIFT AMOUNT\n" );
		hmcsim_free( &hmc );
		free( addr_a );
		free( addr_b );
		free( addr_c );
	}


	/* 
	 * setup the addressing structure 
	 * decide where to start the respective arrays
	 * 
 	 */

	/* 
	 * init the library 
	 * 
	 */

	ret = hmcsim_init(	&hmc, 
				num_devs, 
				num_links, 
				num_vaults, 
				queue_depth, 
				num_banks, 
				num_drams, 
				capacity, 
				xbar_depth );
	if( ret != 0 ){ 
		printf( "FAILED TO INIT HMCSIM\n" );	
		return -1;
	}else {
		printf( "SUCCESS : INITALIZED HMCSIM\n" );
	}

	/* 
	 * setup the device topology
	 * 
	 */
	if( num_devs > 1 ){ 
		/* 
		 * MULTIPLE DEVICES
		 *
		 */
	}else{
		/* 
		 * SINGLE DEVICE
		 *
		 */
	}	

	/* 
	 * init the max request block size 
 	 * 
	 */
	ret = hmcsim_util_set_all_max_blocksize( &hmc, bsize );

	if( ret != 0 ){ 
		printf( "FAILED TO INIT MAX BLOCKSIZE\n" );
		hmcsim_free( &hmc );
		return -1;
	}else {
		printf( "SUCCESS : INITIALIZED MAX BLOCK SIZE\n" );
	}


	/* 
	 * execute the test
	 * 
	 */
	
	/* 
	 * free the library data
	 * 
	 */	
	ret = hmcsim_free( &hmc );
	
	if( ret != 0 ){ 
		printf( "FAILED TO FREE HMCSIM\n" );
		return -1;
	}else {
		printf( "SUCCESS : FREE'D HMCSIM\n" );
	}
	
	return ret;
}

/* EOF */
