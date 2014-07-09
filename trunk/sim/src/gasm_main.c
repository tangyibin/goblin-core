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
#include <sys/types.h>	/* -- stat */
#include <sys/stat.h>	/* -- stat */

#include "goblin_sim.h"

/* -------------------------------------------------- FUNCTION_PROTOTYPES */
extern int	gsim_opcodes_init( struct gsim_t *sim );
extern int	gsim_reg_init( struct gsim_t *sim );
extern uint64_t gasm_row_walker( char *afile );
extern uint64_t gasm_parser( char *afile, uint64_t *inter, uint64_t nrows, int *error );
extern int	gasm_verify( struct gsim_t *sim, uint64_t *inter, uint64_t nread );
extern int	gasm_write_object( char *ofile, uint64_t *inter, uint64_t nread );




/* -------------------------------------------------- GASM_EXEC */
/* 
 * GASM_EXEC
 * 
 */
static int gasm_exec( struct gsim_t *sim, char *afile, char *ofile )
{
	/* vars */
	uint64_t nrows	= 0x00ll;
	uint64_t nread	= 0x00ll;
	int error	= 0;
	uint64_t *inter	= NULL;
	/* ---- */

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif
	/* 
	 * Stage1: Resolve the Number of Rows Required
	 */
	nrows	= gasm_row_walker( afile );
	if( nrows == 0x00ll ){ 
		GSIM_PRINT_ERROR( "GASM_ERROR : No Instructions Found" );
		return -1;
	}
#ifdef GSIM_TRACE
	GSIM_PRINT_U8_MSG( "FOUND THE FOLLOWING NUMBER OF ROWS", nrows );
#endif

	inter	= gsim_malloc( sizeof( uint64_t ) * nrows );
	if( inter == NULL ){ 
		GSIM_PRINT_ERROR( "GASM_ERROR : Could not allocate intermediate format buf" );
		return -1;
	}

	/* 
	 * Stage2: Parse Into Row Format 
	 */
	nread = gasm_parser( afile, inter, nrows, &error );
	if( nread == 0x00ll ){ 
		GSIM_PRINT_ERROR( "GASM_ERROR : No Instructions Read" );
		gsim_free( inter );
		return -1;
	}else if( error == -1 ){ 
		gsim_free( inter );
		GSIM_PRINT_ERROR( "GASM_ERROR : Error in parsing assembly file" );
		return -1;
	}
	goto shortcut;
	/* 
	 * Stage 3: Validate the Ops
	 */
	if( gasm_verify( sim, inter, nread ) != 0 ){ 
		GSIM_PRINT_ERROR( "GASM_ERROR : Verification of assembly failed" );
		gsim_free( inter );
		return -1;
	}

	/* 
	 * Stage4: Assemble into binary format
	 */
	/* TODO */

	/* 
	 * Stage5: I/O; Write the Binary File Out
	 */
	if( gasm_write_object( ofile, inter, nread ) != 0 ){
		GSIM_PRINT_ERROR( "GASM_ERROR : Could not write object file" );
		gsim_free( inter );
		return -1;
	}

	/* 
	 * Stage5: Cleanup
	 */
shortcut:
	gsim_free( inter );

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;
}

/* -------------------------------------------------- GASM_PRINT_HELP */
/* 
 * GASM_PRINT_HELP
 * 
 */
static void gasm_print_help( char **argv )
{
#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif
	printf( "=====================================================\n" );
	printf( "                 --> GASM <--\n" );
	printf( "=====================================================\n" );
	printf( "usage : %s%s\n", argv[0], " -aoh" );
	printf( "=====================================================\n" );
	printf( " -a asm_file.s                 : assembly file\n" );
	printf( " -o output.o                   : output file\n" );
	printf( " -h                            : print this help\n" );
	printf( "=====================================================\n" );

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
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
	struct stat astat;
	/* ---- */

#ifdef GSIM_TRACE
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
	 * stat the file
	 * 
	 */
	if( stat( afile, &astat ) != 0 ){ 
		GSIM_PRINT_ERROR( "GASM_ERROR: Could not stat the assembly file" );
		gsim_free( afile );
		gsim_free( ofile );
		gsim_free( sim );
		return -1;		
	}	

	if( !(S_ISREG( astat.st_mode )) ){ 
		GSIM_PRINT_ERROR( "GASM_ERROR: Could not read the assembly file" );
		gsim_free( afile );
		gsim_free( ofile );
		gsim_free( sim );
		return -1;		
	}

	/*
	 * init the sim structures
	 */
	gsim_opcodes_init( sim );
	gsim_reg_init( sim );

	/* 
	 * run the assembler
	 */
	if( gasm_exec( sim, afile, ofile ) != 0 ){

		GSIM_PRINT_ERROR( "GASM_ERROR: Asssembly failed" );
		gsim_free( afile );
		gsim_free( ofile );
		gsim_free( sim );
		return -1;		
	}

	/* 
	 * free the sim 
	 */
	gsim_free( afile );
	gsim_free( ofile );
	gsim_free( sim );

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;	
}


/* EOF */
