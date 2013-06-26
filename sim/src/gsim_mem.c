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
	if( ptr != NULL ) { 
		free( ptr );
		ptr = NULL;
	}

	return ;
}

/* -------------------------------------------------- GSIM_MALLOC */
/* 
 * GSIM_MALLOC
 * 
 */
extern int gsim_malloc( void **ptr, size_t sz )
{
	void *tmp	= NULL;

	/* 
	 * check to see if the pointer is NULL
	 *
	 */
	if( ptr == NULL ){ 
		return -1;
	}

	/* 
	 * check to see if the pointer is already
	 * allocated
	 *
	 */
	if( *ptr != NULL ){ 
		return -1;
	}	

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
		return -1;
	}
	
	/* 
	 * zero the memory 
	 * 
	 */
	memset( tmp, 0, sz );

	/* 
	 * set the pointer to the correct value 
	 * 
	 */
	*ptr = tmp;

	tmp = NULL;	
	
	return 0;	
}



/* EOF */
