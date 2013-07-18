/* 
 * 
 * _GASM_PARSER_C_ 
 * 
 * GASM ASM PARSERS
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


/* -------------------------------------------------- GASM_PARSER */
/* 
 * GASM_PARSER
 * 
 */
extern uint64_t gasm_parser( char *afile, uint64_t *inter, uint64_t nrows )
{
	/* vars */
	FILE *ifile	= NULL;
	uint64_t insts	= 0x00ll;
	/* ---- */

#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_ENTRY();
#endif

	/* 
	 * open the file 
	 */
	ifile	= fopen( afile, "r" );	
	if( ifile == NULL ){ 
		GSIM_PRINT_ERROR( "GASM_ERROR : Could not open assembly file" );
		return 0x00ll;
	}

	rewind( ifile );


	/* 
	 * close the file
	 */
	fclose( ifile );	

#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_EXIT();
#endif
	return insts;	
}


/* EOF */
