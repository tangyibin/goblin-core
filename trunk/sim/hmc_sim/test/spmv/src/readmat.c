/* 
 * _READMAT_C_ 
 * 
 * HMC-SIM SPMV MATRIX UTILITY FUNCTIONS 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "spmv.h"

/* ------------------------------------------------- ALLOCATE MEMORY */


/* ------------------------------------------------- READMAT */
/* 
 * reads an interprets the spmv input file 
 * 
 */
extern int readmat( char *matfile, struct csr_t *mat )
{
	/* vars */
	FILE *infile	= NULL;
	/* ---- */

	if( matfile == NULL ){ 
		return -1;
	}else if( mat == NULL ){ 
		return -1;
	}

	infile = fopen( matfile, "r" );
	if( infile == NULL ){ 
		printf( "ERROR : could not open matfile at %s\n", matfile );
		return -1;
	}

	fclose( infile );

	return 0;
}

/* EOF */
