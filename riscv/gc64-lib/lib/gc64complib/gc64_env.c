/* 
 * _GC64_ENV_C_ 
 * 
 * GC64 COMPILER LIBRARY ENVIRONMENT RESOLUTION
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "gc64-comp.h"

struct {
	const char *const name;
	const char *const desc;
	const char *const vals;
}gc64_env_opts[] = {
	{ "GC64_TRACE",		"Sets the trace level",			"0x00=disabled;" },
	{ "GC64_USR_TRACE",	"Sets the user library trace level",	"0x00=disabled;" },
	{ NULL, NULL, NULL }
};


static void __print_env() {
	
	/* vars */
	int i	= 0;
	/* ---- */

	printf( "--------------------------------------------------\n" );
	printf( "          GC64 ENVIRONMENT VARIABLES\n" );
	printf( "--------------------------------------------------\n" );

	for( i=0; gc64_env_opts[i].name != NULL; i++ ){ 
		printf( "\tNAME   : %s\n", gc64_env_opts[i].name );
		printf( "\tDESC   : %s\n", gc64_env_opts[i].desc );
		printf( "\tVALUES : %s\n\n", gc64_env_opts[i].vals );
	}

	printf( "--------------------------------------------------\n" );
}

/* 
 * EXTERN INT GC64_ENV( STRUCT GC64COMP_T *COMP )
 * 
 *
 */
extern int gc64_env( struct gc64comp_t *comp ){ 

	/* vars */
	char *ptr	= NULL;
	/* ---- */

	/* sanity check */
	if( comp == NULL ){ 
		return -1;
	}

	/*
	 * MCS_PRINT_ENV
	 *
	 */
	ptr	= getenv( "GC64_PRINT_ENV" );
	if( ptr != NULL ){ 
		__print_env();
	}

	/* 
	 * GC64_TRACE
	 * 
	 */
	ptr	= getenv( "GC64_TRACE" );
	if( ptr != NULL ){ 
		if( atoi( ptr ) > 0 ){ 
			comp->trace = atoi(ptr);
		} 
	}

	/* 
	 * GC64_USR_TRACE
	 * 
	 */
	ptr	= getenv( "GC64_USR_TRACE" );
	if( ptr != NULL ){ 
		if( atoi( ptr ) > 0 ){ 
			comp->usr_trace = atoi(ptr);
		} 
	}

	return GC64_OK;
}


/* EOF */
