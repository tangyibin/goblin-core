/* 
 * 
 * _GASM_IO_C_ 
 * 
 * GASM ROW WALKER
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


/* -------------------------------------------------- GASM_WRITE_OBJECT */
/* 
 * GASM_WRITE_OBJECT
 * 
 */
extern int gasm_write_object( char *ofile, uint64_t *inter, uint64_t nread )
{
	/* vars */
	uint64_t i	= 0x00ll;
	FILE *outfile	= NULL;
	/* ---- */

#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_ENTRY();
#endif

	/* 
	 * open the file 
	 */
	outfile = fopen( ofile, "w+b" );
	if( ofile != NULL ){ 
		GSIM_PRINT_ERROR( "GASM_ERROR : Could not open object file" );
		return -1;
	}

	/* 
	 * write all the instructions
	 */
	for( i=0; i<nread; i++ ){ 
		fwrite( &(inter[i]), sizeof( uint64_t ), 1, outfile );
	}	

	/* 
	 * close the file 
	 */
	fclose( outfile );

#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;	
}


/* EOF */
