/* 
 * 
 * _GSIM_MAIN_C_ 
 * 
 * GOBLIN-SIM MAIN SIMULATION FILE 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


/* -------------------------------------------------- FUNCTION PROTOTYPES */
extern int	gsim_opcodes_init( struct gsim_t *sim );
extern int	gsim_reg_init( struct gsim_t *sim );


/* -------------------------------------------------- GSIM_FREE_SIM */
/* 
 * GSIM_FREE_SIM
 * 
 */
static void gsim_free_sim( struct gsim_t *sim )
{
	if( sim == NULL ){ 
		/* nothing to do, return */
		return ;
	}

	/* 
 	 * free all the intermediate objects
	 *
	 */
	gsim_free( sim->config_file );
	gsim_free( sim->log_file );
	gsim_free( sim->inst_file );
	gsim_free( sim->trace_file );

	if( sim != NULL ) { 
		free( sim );
		sim = NULL;
	}

	return ;
}

/* -------------------------------------------------- GSIM_INIT_SIM */
/* 
 * GSIM_INIT_SIM
 * 
 */
static int gsim_init_sim( struct gsim_t *sim )
{
	/* 
	 * set the default sim attributes
	 * 
	 */
	sim->options	= GSIM_OPT_DEFAULT;

	/* 
	 * zero the pointers 
	 * 
	 */
	sim->config_file	= NULL;
	sim->log_file		= NULL;
	sim->inst_file		= NULL;
	sim->trace_file		= NULL;

	/* 
	 * setup the opcodes table
	 * 
	 */
	if( gsim_opcodes_init( sim ) != 0 ){ 
		GSIM_PRINT_ERROR( "GSIM_ERROR: Failed to initialize the opcode table" );
		return -1;
	}

	/* 
	 * setup the registers table
	 * 
	 */
	if( gsim_reg_init( sim ) != 0 ){ 
		GSIM_PRINT_ERROR( "GSIM_ERROR: Failed to initialize the register table" );
		return -1;
	}


	/* 
	 * put the system in reset
	 * 
	 */

	return 0;
}

/* -------------------------------------------------- GSIM_PRINT_HELP */
/* 
 * GSIM_PRINT_HELP 
 * 
 */
static void gsim_print_help( char **argv )
{
	printf( "================================================================\n" );
	printf( " GSIM VERSION %d.%d\n", GSIM_MAJOR_VERSION, GSIM_MINOR_VERSION );
	printf( "================================================================\n" );
	printf( " usage : %s -cCfhILtTvV\n", argv[0] );
	printf( " Options:\n" );
	printf( " -c                             : enable C++ cycle accurate sim\n" );
	printf( " -C /path/to/config.cfg         : simualtion config file\n" );
	printf( " -f                             : enable functional sim\n" );
	printf( " -h                             : print this help menu\n" );
	printf( " -I /path/to/inst.instr         : simulation instruction file\n" );
	printf( " -L /path/to/sim.log            : simulation log file\n" );
	printf( " -t                             : enable tracing\n" );
	printf( " -T /path/to/tracefile          : simulation trace file\n" );
	printf( " -v                             : enable verilog simulation\n" );
	printf( " -V /path/to/object.o           : dissasemble and validate object\n" );
	printf( "================================================================\n" );
	printf( " Note:\n" );
	printf( " Functional simulation is the default [-f]\n" );
	printf( "================================================================\n" );

	return ;
}

/* -------------------------------------------------- MAIN */
/* 
 * MAIN 
 * 
 */
int main( int argc, char **argv )
{
	/* vars */
	int ret			= 0;
	struct gsim_t	*sim	= NULL;
	/* ---- */


#ifdef GSIM_DEBUG
	GSIM_PRINT_MSG( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
	GSIM_PRINT_MSG( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
	GSIM_PRINT_MSG( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
	GSIM_PRINT_MSG( "!!WARNING!!  RUNNING IN DEBUG MODE!" );
	GSIM_PRINT_MSG( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
	GSIM_PRINT_MSG( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
	GSIM_PRINT_MSG( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
#endif


	/* 
	 * allocate the simulation data
	 */
	sim = malloc( sizeof( struct gsim_t ) );
	if( sim == NULL ){ 
		GSIM_PRINT_ERROR( "GSIM_ERROR: Cannot allocate memoy for sim" );
		return -1;
	}

	if( gsim_init_sim( sim ) != 0 ){ 
		GSIM_PRINT_ERROR( "GSIM_ERROR: Failed to initialize simualtion data" );
		goto gsim_cleanup;
		return -1;
	}

	/*
	 * Parse the command line args
	 */
	while(( ret = getopt( argc, argv, "cC:fhI:L:tT:vV:" )) != -1 )
	{
		switch ( ret )
		{
			case 'c': 
				/* enable c++ cycle accurate simulation */
				break;
			case 'C': 
				/* config file */
				sim->config_file = gsim_malloc( (size_t)(sizeof( char ) * strlen( optarg )) );

				if( sim->config_file == NULL ) {
					GSIM_PRINT_ERROR( "GSIM_ERROR: Cannot allocate memory for config_file" );
				}
				snprintf( sim->config_file, strlen( optarg )+1, "%s", optarg );
				break;
			case 'f': 
				/* enable functional simulation
				 * not cycle accurate 
				 */
				break;
			case 'h': 
				/* print help */
				gsim_print_help( argv );
				return 0;
				break;
			case 'I': 
				/* instruction file */
				sim->inst_file = gsim_malloc( (size_t)(sizeof( char ) * strlen( optarg )) );

				if( sim->inst_file == NULL ) {
					GSIM_PRINT_ERROR( "GSIM_ERROR: Cannot allocate memory for inst_file" );
				}
				snprintf( sim->inst_file, strlen( optarg )+1, "%s", optarg );
				break;
			case 'L':
				/* log file */
				sim->log_file = gsim_malloc( (size_t)(sizeof( char ) * strlen( optarg )) );

				if( sim->log_file == NULL ) {
					GSIM_PRINT_ERROR( "GSIM_ERROR: Cannot allocate memory for log_file" );
				}
				snprintf( sim->log_file, strlen( optarg )+1, "%s", optarg );
				break;
			case 't': 
				/* enable tracing */
				break;
			case 'T': 
				/* set the trace file : default = gsim.trace */
				sim->trace_file = gsim_malloc( (size_t)(sizeof( char ) * strlen( optarg )) );

				if( sim->trace_file == NULL ) {
					GSIM_PRINT_ERROR( "GSIM_ERROR: Cannot allocate memory for trace_file" );
				}
				snprintf( sim->trace_file, strlen( optarg )+1, "%s", optarg );
				break;
			case 'v': 
				/* enable verilog simulation */
				break;
			case 'V': 
				/* validate the target object file, but do not execute */
				break;
			case '?':
			default:
				printf( "%s%s%s\n", "Unknown Option: see ", argv[0], " -h" );
				gsim_print_help( argv );
				return -1;
				break;
		}
	}

	/* 
	 * sanity check the options 
	 * 
 	 */

	/* 
	 * run the simulation
	 * 
	 */


gsim_cleanup:
	/* 
	 * done running the sim; free the memory
	 * 
	 */
	gsim_free_sim( sim );

	return 0;
}


/* EOF */
