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
static void gsim_print_help()
{
	printf( "================================================================" );
	printf( " GSIM VERSION %d.%d\n", GSIM_MAJOR_VERSION, GSIM_MINOR_VERSION );
	printf( "================================================================" );
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
	while(( ret = getopt( argc, argv, "Ch:I:L:tT:" )) != -1 )
	{
		switch ( ret )
		{
			case 'C': 
				/* config file */
				break;
			case 'h': 
				/* print help */
				gsim_print_help();
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
