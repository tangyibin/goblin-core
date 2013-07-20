/* 
 * 
 * _GASM_ROW_C_ 
 * 
 * GASM ROW WALKER
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


/* -------------------------------------------------- GASM_ROW_WALKER */
/* 
 * GASM_ROW_WALKER
 * 
 */
extern uint64_t gasm_row_walker( char *afile )
{
	/* vars */
	uint64_t nrows	= 0x00ll;
	FILE *ifile	= NULL;
	char *buf	= NULL;
	char *tmp	= NULL;
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


	buf = gsim_malloc( sizeof( char ) * 2048 );
	memset( buf, 0, sizeof( char ) * 2048 );

	/* 
	 * walk the file 
	 */
	while( !feof( ifile ) ){ 

		/* 
	 	 * read a line
		 */
		fgets( buf, 2048, ifile );

		if( (strlen( buf ) > 2) && (buf[0] != '#') ){
			
			/* 
			 * parse the line and look for immediates
			 * immediates appear as '$value'
			 */
			tmp = strtok( buf, "$" );

			if( tmp != NULL ){
				/* 
				 * immediate present 
				 */
				nrows += 2;
			}else{ 
				/* 
				 * immediate not present 
				 */
				nrows += 1;
			}
		}

		memset( buf, 0, sizeof( char ) * 2048 );
		tmp = NULL;
	}

	/* 
	 * close the file
	 */
	fclose( ifile );	

	/* 
	 * free memory 
	 */
	gsim_free( buf );

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return nrows;	
}


/* EOF */
