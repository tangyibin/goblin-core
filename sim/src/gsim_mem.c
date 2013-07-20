/* 
 * 
 * _GSIM_MEM_C_ 
 * 
 * GOBLIN-SIM MEMORY HANDLERS
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


/* -------------------------------------------------- GSIM_FREE */
/* 
 * GSIM_FREE
 * 
 */
extern void gsim_free( void *ptr )
{
#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif
	if( ptr != NULL ) { 
		free( ptr );
		ptr = NULL;
	}

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return ;
}

/* -------------------------------------------------- GSIM_MALLOC */
/* 
 * GSIM_MALLOC
 * 
 */
extern void *gsim_malloc( size_t sz )
{
#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif
	static void *tmp	= NULL;

	/* 
	 * allocate the memory 
	 * 
	 */
	tmp	= malloc( sz );

	/* 
	 * check for null ptr return 
	 * 
	 */
	if( tmp == NULL ) { 
		return NULL;
	}
	
	/* 
	 * zero the memory 
	 * 
	 */
	memset( tmp, 0, sz );

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return tmp;	
}



/* EOF */
