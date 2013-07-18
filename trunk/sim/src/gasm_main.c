/* 
 * 
 * _GASM_MAIN_C_
 * 
 * GOBLIN SIMPLE ASSEMBLER MAIN SOURCE FILE 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"

/* -------------------------------------------------- FUNCTION_PROTOTYPES */
extern int	gsim_opcodes_init( struct gsim_t *sim );
extern int	gsim_reg_init( struct gsim_t *sim );

/* -------------------------------------------------- GASM_PRINT_HELP */
/* 
 * GASM_PRINT_HELP
 * 
 */
static void gasm_print_help( char **argv )
{
	printf( "=====================================================\n" );
	printf( "                 --> GASM <--\n" );
	printf( "=====================================================\n" );
	printf( "usage : %s%s\n", argv[0], " -aoh" );
	printf( "=====================================================\n" );
	printf( " -a asm_file.s                 : assembly file\n" );
	printf( " -o output.o                   : output file\n" );
	printf( " -h                            : print this help\n" );
	printf( "=====================================================\n" );

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
	char *afile		= NULL;
	char *ofile		= NULL;
	struct gsim_t *sim	= NULL;
	/* ---- */

#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_ENTRY();
#endif

	/*
	 * allocate the sim data
	 */
	sim = gsim_malloc( sizeof( struct gsim_t ) );
	if( sim == NULL ){ 
		GSIM_PRINT_ERROR( "GASM_ERROR: Cannot allocate memory for sim" );
		return -1;
	}


	/* 
	 * Parse the command line args
	 */
	while(( ret = getopt( argc, argv, "a:o:h" )) != -1 )
	{
		switch( ret )
		{	
			case 'a': 
				afile = gsim_malloc( (strlen( optarg ) * sizeof( char )) );
				if( afile == NULL) { 
					GSIM_PRINT_ERROR( "GASM_ERROR: Cannot allocate memory for afile" );
					gsim_free( ofile );
					gsim_free( sim );
					return -1;
				}

				sprintf( afile, "%s", optarg );

				break;
			case 'o':
				ofile = gsim_malloc( (strlen( optarg ) * sizeof( char )) );
				if( ofile == NULL) { 
					GSIM_PRINT_ERROR( "GASM_ERROR: Cannot allocate memory for ofile" );
					gsim_free( afile );
					gsim_free( sim );
					return -1;
				}

				sprintf( ofile, "%s", optarg );

				break;
			case 'h': 
				gasm_print_help( argv );
				gsim_free( sim );
				return 0;
				break;
			case '?':
			default:
				printf( "%s%s%s\n", "Unknown Option: see ", argv[0], " -h" );
				gasm_print_help( argv );
				return -1;	
				break;
		}
	}	

	/* 
	 * sanity check the args
	 */
	if( afile == NULL ){ 
		GSIM_PRINT_ERROR( "GASM_ERROR: No ASM file specified" );
		gsim_free( ofile );
		gsim_free( sim );
		return -1;
	}

	if( ofile == NULL ){
		/* build the output file name */
		ofile = gsim_malloc( (strlen( afile ) + 2) * sizeof( char ) );
		sprintf( ofile, "%s%s", afile, ".o" );
	}

	/*
	 * init the sim structures
	 */
	gsim_opcodes_init( sim );
	gsim_reg_init( sim );

	/* 
	 * run the assembler
	 */

	/* 
	 * free the sim 
	 */
	gsim_free( afile );
	gsim_free( ofile );
	gsim_free( sim );

#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;	
}


/* EOF */
