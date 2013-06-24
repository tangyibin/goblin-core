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
#include "goblin_sim.h"


/* -------------------------------------------------- GSIM_PRINT_USAGE */
/* 
 * GSIM_PRINT_USAGE 
 * 
 */
static void gsim_print_usage( char **argv )
{
	printf( "================================================================" );
	printf( "%s%s", argv[0], " " );
	printf( "================================================================" );
	printf( "================================================================" );


	return ;
}

/* -------------------------------------------------- GSIM_PRINT_HELP */
/* 
 * GSIM_PRINT_HELP 
 * 
 */
static void gsim_print_help( char **argv )
{
	printf( "================================================================" );
	printf( " GSIM VERSION %d.%d\n", GSIM_MAJOR_VERSION, GSIM_MINOR_VERSION );
	printf( "================================================================" );
	printf( " usage : %s -ChILtT\n", argv[0] );
	printf( " Options:\n" );
	printf( " -C /path/to/config.cfg         : simualtion config file\n" );
	printf( " -h                             : print this help menu\n" );
	printf( " -I /path/to/inst.instr         : simulation instruction file\n" );
	printf( " -L /path/to/sim.log            : simulation log file\n" );
	printf( " -t                             : enable tracing\n" );
	printf( " -T /path/to/tracefile          : simulation trace file\n" );
	printf( " -V /path/to/object.o           : dissasemble and validate object\n" );
	printf( "================================================================" );


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

	/*
	 * Parse the command line args
	 */
	while(( ret = getopt( argc, argv, "C:hI:L:tT:V:" )) != -1 )
	{
		switch ( ret )
		{
			case 'C': 
				/* config file */
				break;
			case 'h': 
				/* print help */
				gsim_print_help( argv );
				return 0;
				break;
			case 'I': 
				/* instruction file */
				break;
			case 'L':
				/* log file */
				break;
			case 't': 
				/* enable tracing */
				break;
			case 'T': 
				/* set the trace file : default = gsim.trace */
				break;
			case 'V': 
				/* validate the target object file, but do not execute */
				break;
			case '?':
			default:
				printf( "%s%s%s\n", "Unknown Option: see ", argv[0], " -h" );
				gsim_print_usage( argv );
				return -1;
				break;
		}
	}

	return 0;
}


/* EOF */
