/* 
 * _GC64_USRFREE_C_ 
 * 
 * GC64 USER FREE FUNCTIONS
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "gc64-usr.h"

/* 
 * EXTERN VOID *
 * 
 */
extern void __gc64_usrfree() {

	/* vars */
	struct gc64entry_t *cur	= NULL;
	struct gc64entry_t *nxt	= NULL;
	/* ---- */

	if( __g_mem == NULL ){ 
		return ;
	}

	/* free all the allocations */
	cur	= __g_mem->start;
	while( cur != NULL ){ 
		nxt	= cur->next;
		free( cur );
		cur 	= nxt;
	}

	__g_mem->start 	= NULL;
	__g_mem->end	= NULL;
	
	free( __g_mem );
	__g_mem 	= NULL;
}

/* EOF */
