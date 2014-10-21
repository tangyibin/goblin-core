/* 
 * _GC64_ENV_C_ 
 * 
 * GC64 COMPILER LIBRARY ENVIRONMENT RESOLUTION
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "gc64-comp.h"

/* 
 * EXTERN INT GC64_ENV( STRUCT GC64COMP_T *COMP )
 * 
 *
 */
extern int gc64_env( struct gc64comp_t *comp ){ 

	/* sanity check */
	if( comp == NULL ){ 
		return -1;
	}

	return GC64_OK;
}


/* EOF */
