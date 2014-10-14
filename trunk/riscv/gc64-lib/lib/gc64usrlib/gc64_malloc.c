/* 
 * _GC64_MALLOC_C_ 
 * 
 * GC64 USER LIBRARY 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "gc64-usr.h"



/* 
 * EXTERN INT SP_MALLOC( __SCRATCH VOID **PTR, SIZE_T SZ )
 * 
 */
extern int sp_malloc( __scratch void **ptr, size_t sz ){ 
	
	return GC64_OK;
}

/* 
 * EXTERN INT SP_CALLOC( __SCRATCH VOID **PTR, SIZE_T NMEMB, SIZE_T SZ )
 * 
 */
extern int sp_calloc( __scratch void **ptr, size_t nmemb, size_t sz ){ 
	
	return GC64_OK;
}

/* 
 * EXTERN INT SP_REALLOC( __SCRATCH VOID **NEWPTR, __SCRATCH VOID **OLDPTR, 
 * 				SIZE_T SZ )
 * 
 */
extern int sp_realloc( __scratch void **newptr, __scratch void **oldptr, 
			size_t sz ) {
	
	return GC64_OK;
}

/* 
 * EXTERN INT SP_FREE( __SCRATCH VOID **PTR )
 * 
 */
extern int sp_free( __scratch void **ptr )
{
	return GC64_OK;
}
