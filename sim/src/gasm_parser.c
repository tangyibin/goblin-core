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
	char *buf	= NULL;
	uint64_t insts	= 0x00ll;
	uint64_t tmp	= 0x00ll;
	int imm		= 0;
	int line	= 0;
	/* ---- */

#ifdef GSIM_TRACE
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

	/* 
	 * rewind the file 
	 */
	rewind( ifile );

	buf = gsim_malloc( sizeof( char ) * 2048 );
	memset( buf, 0, sizeof( char ) * 2048 );

	/* 
	 * Parse the file
	 */
	while( !feof( ifile ) ){
	
		fgets( buf, 2048, ifile );

		if( (strlen( buf ) > 2 ) && (buf[0] != '#') ){ 

			/* 
			 * this buffer is an instruction 
			 */		
					
		}

		memset( buf, 0, sizeof( char ) * 2048 );
		imm = 0;
		tmp = 0x00ll;
		line++;
	}

	/* 
	 * close the file
	 */
	fclose( ifile );	

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return insts;	
}


/* EOF */
