/* 
 * _SIMPLE_C_ 
 * 
 * MEMSIM SIMPLE TEST
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mem_sim.h"

/* ------------------------------------------- MAIN */
int main( int argc, char **argv )
{
	/* vars */
	struct memsim_t msim;
	memsim_alg_t 	alg	= MEMSIM_SIMPLE;
	memsim_iface_t iface	= MEMSIM_HMC;
	int ret			= 0;
	uint32_t task_groups	= 0x00;
	uint32_t task_procs	= 0x00;
	uint32_t tasks		= 0x00;
	uint32_t g_slots	= 0x00;
	uint32_t s_slots	= 0x00;
	uint32_t a_slots	= 0x00;
	uint32_t ga_slots	= 0x00;
	uint32_t level		= 0x00;
	uint32_t num_links	= 0x00;
	uint32_t num_lanes	= 0x00;
	float gbps		= 0.;
	uint64_t options	= 0x00ll;
	uint64_t gconst		= 0x00ll;
	FILE *ofile		= NULL;
	/* ---- */

	/* 
	 * parse the args
	 * 
	 */
	while(( ret = getopt( argc, argv, "A:I:g:p:t:G:S:M:L:l:n:a:P:h" )) != -1 ){
		switch( ret )
		{
			case 'A':
				if( strstr( optarg, "MEMSIM_SIMPLE" ) != NULL ){ 
					alg = MEMSIM_SIMPLE;
				}else if( strstr( optarg, "MEMSIM_CACHE" ) != NULL ){ 
					alg = MEMSIM_CACHE;
				}else if( strstr( optarg, "MEMSIM_EXP" ) != NULL ){ 
					alg = MEMSIM_EXP;
				}else{ 
					printf( "ERROR : UNRECOGNIZED ALGORITHM : %s\n", optarg );
					return -1;
				}
				break;
			case 'I':
				if( strstr( optarg, "MEMSIM_HMC" ) != NULL ){ 
					iface = MEMSIM_HMC;
				}else if( strstr( optarg, "MEMSIM_BASIC" ) != NULL ){
					iface = MEMSIM_HMC;
				}else{
					printf( "ERROR : UNRECOGNIZED INTERFACE : %s\n", optarg );
					return -1;
				}
				break;
			case 'g':
				task_groups	= (uint32_t)(atoi(optarg));
				break;
			case 'p':
				task_procs	= (uint32_t)(atoi(optarg));
				break;
			case 't':
				tasks		= (uint32_t)(atoi(optarg));
				break;
			case 'G':
				g_slots		= (uint32_t)(atoi(optarg));
				break;
			case 'S':
				s_slots		= (uint32_t)(atoi(optarg));
				break;
			case 'M':
				a_slots		= (uint32_t)(atoi(optarg));
				break;
			case 'L':
				ga_slots	= (uint32_t)(atoi(optarg));
				break;
			case 'l':
				level 		= (uint32_t)(atoi(optarg));
				break;
			case 'n':
				num_links	= (uint32_t)(atoi(optarg));
				break;
			case 'a':
				num_lanes	= (uint32_t)(atoi(optarg));
				break;
			case 'P':
				gbps		= (float)(atof(optarg));
				break;
			case 'h':
				printf( "Usage: %s%s", argv[0], " -AIgptGSMLlnaP\n" );
				printf( "\t-A <MEMSIM_SIMPLE|MEMSIM_CACHE|MEMSIM_EXP>\n" );
				printf( "\t-I <MEMSIM_BASIC|MEMSIM_HMC>\n" );
				printf( "\t-g <task_groups>\n" );
				printf( "\t-p <task_procs>\n" );
				printf( "\t-t <tasks>\n" );
				printf( "\t-G <task_group_slots>\n" );
				printf( "\t-S <socket_slots>\n" );
				printf( "\t-M <amo_slots>\n" );
				printf( "\t-L <global_address_slots>\n" );
				printf( "\t-l <trace_level>\n" );
				printf( "\t-n <num_links>\n" );
				printf( "\t-a <num_lanes>\n" );
				printf( "\t-P <gbps>\n" );
				break;
			case '?':
			default:
				printf( "Unknown option : %s%s", argv[0], " -AIgptGSMLlnaP\n" );
				return -1;
				break;
		}
	}

	/* 
	 * determine the appropriate options
	 * 
	 */
	if( a_slots > 0 ){ 
		options |= MEMSIM_AMO;
	}
	if( ga_slots > 0 ){ 
		options |= MEMSIM_GA;
	}

	/* 
	 * init memsim 
	 * 
 	 */
	if( memsim_init( &msim, 
			iface, 
			alg, 
			task_groups, 
			task_procs, 
			tasks,
			g_slots, 
			s_slots, 
			a_slots, 
			ga_slots, 
			options ) != MEMSIM_OK ){ 
		printf( "FAILED TO INIT MEMSIM\n" );
		return -1;
	}

	/* 
	 * set the hardware details
 	 * 
	 */
	/*
	if( memsim_set_hw( &msim, 
			num_links, 
			num_lanes, 
			gbps ) != MEMSIM_OK ){
		printf( "FAILED TO SET MEMSIM HARDWARE DETAILS\n" );
		memsim_free( &msim );
		return -1;
	}*/

	/* 
	 * open the output file 
	 * 
	 */
	ofile = fopen( "simple.out", "w" );

	if( ofile == NULL ){ 
		printf( "FAILED TO OPEN OUTPUT FILE\n" );
		memsim_free( &msim );
		return -1;
	}	

	if( memsim_trace_handle( &msim, ofile ) != MEMSIM_OK ){ 
		printf( "FAILED TO INIT THE TRACE FILE\n" );
		memsim_free( &msim );
		return -1;
	}

	/* 
	 * set the trace level 
	 * 
 	 */
	if( memsim_trace_level( &msim, level ) != MEMSIM_OK ){ 
		printf( "FAILED TO SET THE TRACE LEVEL\n" );
		memsim_free( &msim );
		fclose( ofile );
		return -1;
	}


	/* 
	 * everything is initialized, send some requests
	 * 
 	 */
	ret	= memsim_rqst(	&msim, 
				gconst, 
				MEMSIM_RD8, 
				(uint64_t)(0x00), 
				(uint64_t)(0x00), 
				(uint64_t)(0x00) );
	if( ret == MEMSIM_STALL ){ 
		printf( "STALLED!\n" );
	}

	ret	= memsim_rqst(	&msim, 
				gconst, 
				MEMSIM_RD8, 
				(uint64_t)(0x08), 
				(uint64_t)(0x00), 
				(uint64_t)(0x00) );
	if( ret == MEMSIM_STALL ){ 
		printf( "STALLED!\n" );
	}

	ret	= memsim_rqst(	&msim, 
				gconst, 
				MEMSIM_WR8, 
				(uint64_t)(0x10), 
				(uint64_t)(0x0F), 
				(uint64_t)(0x00) );
	if( ret == MEMSIM_STALL ){ 
		printf( "STALLED!\n" );
	}

	/* 
	 * clock the sim until requests are complete
	 * 
	 */
	while( memsim_is_empty( &msim ) == MEMSIM_NEMPTY ){ 
		memsim_clock( &msim );
	}

	/* 
	 * close the output file 
	 * 
	 */
	fflush( ofile );
	fclose( ofile );
	ofile = NULL;

	/* 
	 * free memsim 
	 * 
 	 */
	memsim_free( &msim );

	return 0;
}
/* EOF */
