/* 
 * _GC64_USRINIT_C_ 
 * 
 * GC64 USER INIT FUNCTIONS
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "gc64-usr.h"

struct gc64sp_t *__g_mem;

/* 
 * EXTERN INT GC64_OK
 * 
 */
extern int gc64_ok() {

	if( __g_mem != NULL ){ 
		return GC64_OK;
	}else{ 
		return GC64_ERROR;
	}
}

/* 
 * EXTERN STRUCT GC64SP_T *__GC64_USERINIT( UINT64_T BASE_ADDR, UINT64_T TSIZE )
 * 
 */
extern struct gc64sp_t *__gc64_usrinit( uint64_t base_addr, uint64_t tsize ) {

	/* vars */
	struct gc64sp_t *tmem	= NULL;
	/* ---- */

	if( __g_mem != NULL ){ 
		return __g_mem;
	}

	tmem	= malloc( sizeof( struct gc64sp_t ) );
	if( tmem == NULL ){ 
		return NULL;
	}

	/* 
	 * init the structure
	 * 
	 */ 
	tmem->base_addr = base_addr;
	tmem->tsize	= tsize;
	tmem->used	= 0x00ll;
	tmem->free	= tsize;
	tmem->nentry	= 0x00ll;
	tmem->start	= NULL;
	tmem->end	= NULL;
	__g_mem = tmem;
	return __g_mem;

}

/* EOF */
