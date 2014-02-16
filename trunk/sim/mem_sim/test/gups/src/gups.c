/* 
 * _GUPS_C_ 
 * 
 * MEMSIM UNBINNED GUPS TEST
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mem_sim.h"

/* ------------------------------------------- FUNCTION PROTOTYPES */
extern int execute_test( struct memsim_t *msim, uint64_t *gconst, uint32_t num_threads, long num_req );

/* ------------------------------------------- MAIN */
int main( int argc, char **argv )
{
	/* vars */
	struct memsim_t msim;
	memsim_alg_t 	alg	= MEMSIM_SIMPLE;
	memsim_iface_t iface	= MEMSIM_HMC;
	int ret			= 0;
	uint32_t simd		= 0x01;
	uint32_t task_groups	= 0x01;
	uint32_t task_procs	= 0x01;
	uint32_t tasks		= 0x01;
	uint32_t tg_c		= 0x00;
	uint32_t tp_c		= 0x00;
	uint32_t t_c		= 0x00;	
	uint32_t t_s		= 0x00;
	uint64_t i		= 0x00;
	uint32_t g_slots	= 0x00;
	uint32_t s_slots	= 0x00;
	uint32_t a_slots	= 0x00;
	uint32_t ga_slots	= 0x00;
	uint32_t level		= 0x00;
	uint32_t num_links	= 0x00;
	uint32_t num_lanes	= 0x00;
	uint32_t num_threads	= 0;	/* number of threads for parallelization */
	float gbps		= 0.;
	long num_req		= 0;	/* number of iters in the triad loop */
	uint64_t options	= 0x00ll;
	uint64_t *gconst	= NULL;
	FILE *ofile		= NULL;
	/* ---- */

	/* 
	 * parse the args
	 * 
	 */
	while(( ret = getopt( argc, argv, "A:I:g:p:t:G:S:M:L:l:n:a:P:s:T:R:s:h" )) != -1 ){
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
			case 'T':
				num_threads	= (uint32_t)(atoi(optarg));
				break;
			case 'R':
				num_req		= (long)(atol(optarg));
				break;
			case 's':
				simd		= (uint32_t)(atoi(optarg));
				break;
			case 'h':
				printf( "Usage: %s%s", argv[0], " -AIgptGSMLlnaPTRs\n" );
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
				printf( "\t-T <num_threads>\n" );
				printf( "\t-R <num_req>\n" );
				printf( "\t-s <simd_elems>\n" );
				return 0;
				break;
			case '?':
			default:
				printf( "Unknown option : %s%s", argv[0], " -AIgptGSMLlnaPTRs\n" );
				return -1;
				break;
		}
	}

	/* 
	 * quick sanity check 
	 * 
	 */
	if( num_threads <= 0 ){ 
		printf( "ERROR : MUST USE AT LEAST 1 THREAD\n" );
		printf( "  num_threads = %d\n", num_threads );
		return -1;
	}else if( num_req <= 0 ){
		printf( "ERROR : MUST USE AT LEAST 1 REQUEST\n" );
		printf( "  num_req = %ld", num_req );
		return -1;
	}

	/* 
	 * adjust num_threads
	 * we do this to account for the number of SIMD pipes
 	 * 
 	 */
	if( simd > 1 ){ 
		num_threads *= simd;
	}

	/* 
	 * init the gconst field 
	 *
	 */
	gconst	= malloc( sizeof( uint64_t ) * num_threads );
	if( gconst == NULL ){ 
		printf( "ERROR : COULD NOT ALLOCATE MEMORY FOR GCONST\n" );
		return -1;
	}

	for( i=0; i<(uint64_t)(num_threads); i++ ){ 

		gconst[i]	= 0x00ll;
		gconst[i]	|= (((uint64_t)(tg_c) << 40) & GSIM_REG_GCONST_TG);
		gconst[i]	|= (((uint64_t)(tp_c) << 48) & GSIM_REG_GCONST_TP);
		gconst[i]	|= (((uint64_t)(t_c)  << 56) & GSIM_REG_GCONST_TC);

		t_s++;
		
		if( t_s == simd ){
			t_s = 0;
			t_c++;

			if( t_c == tasks ){ 
				t_c = 0;
				tp_c++;		

				if( tp_c == task_procs ){ 
					tp_c = 0;
					tg_c++;
				
					if( tg_c == task_groups ){ 
						if( i<(uint64_t)(num_threads-2) ){ 
							printf( "ERROR : TOO MANY THREADS OR NOT ENOUGH HARDWARE\n" );
							free( gconst );
							return -1;
						} /* if num_threads-2 */ 
					} /* if tg_c */
				} /* if_tp_c */
			} /* if t_c */
		}/* if t_s */	
	}/* for */

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
		free( gconst );
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
		free( gconst );
		return -1;
	}*/

	/* 
	 * open the output file 
	 * 
	 */
	ofile = fopen( "gups.out", "w" );

	if( ofile == NULL ){ 
		printf( "FAILED TO OPEN OUTPUT FILE\n" );
		memsim_free( &msim );
		free( gconst );
		return -1;
	}	

	if( memsim_trace_handle( &msim, ofile ) != MEMSIM_OK ){ 
		printf( "FAILED TO INIT THE TRACE FILE\n" );
		memsim_free( &msim );
		free( gconst );
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
		free( gconst );
		return -1;
	}


	/* 
	 * everything is initialized ready to begin our run
	 * 
 	 */
	execute_test( &msim, gconst, num_threads, num_req );

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

	free( gconst );

	return 0;
}
/* EOF */
