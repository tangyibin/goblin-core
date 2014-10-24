/* 
 * _GC64-USR_H_ 
 * 
 * GC64 USER INTERFACE HEADER
 * 
 * Provides basic user interface functionality 
 * 
 * 
 */

#ifndef _GC64_USR_H_
#define _GC64_USR_H_


#ifdef __cplusplus
extern "C"
{
#endif

/* 
 * REQUIRED HEADERS
 * 
 */
#include "gc64-types.h"


/* 
 * 
 * DATA 
 * 
 */
extern struct gc64sp_t *__g_mem;

/* 
 * 
 * FUNCTIONS 
 * 
 */
/* -- basic operation */
extern int	gc64_ok();

/* -- memory allocation */
extern int	sp_malloc( __scratch void **ptr, size_t sz );
extern int	sp_calloc( __scratch void **ptr, size_t nmemb, size_t size );
extern int 	sp_realloc( __scratch void **newptr, __scratch void **oldptr, size_t size );
extern int	sp_free( __scratch void **ptr );


#ifdef __cplusplus
} 	/* EXTERN C */
#endif	/* __CPLUSPLUS */
#endif 	/* _GC64_USR_H_ */
/* EOF */
