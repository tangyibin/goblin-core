/* 
 * _GC64_SPAD_C_ 
 * 
 * GC64 COMPILER LIBRARY SCRATCHPAD FUNCTIONS 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "gc64-comp.h"


#define	GC64_BASE_ADDR		0x0000000080000000
#define	GC64_DEFAULT_SIZE	20000000

/* 
 * EXTERN INT GC64_SPAD_INIT( STRUCT GC64COMP_T *COMP )
 * 
 *
 */
extern int gc64_spad_init( struct gc64comp_t *comp ){ 

	/* sanity check */
	if( comp == NULL ){ 
		return -1;
	}

	if( comp->mem != NULL ){ 
		return -1;
	}	

	/* 
	 * allocate memory for the memory structure 
	 * 
	 */
	comp->mem	= malloc( sizeof( struct gc64sp_t ) );
	if( comp->mem == NULL ){
		return -1;
	}

	/* 
	 * init the values 
	 * 
	 */
	comp->mem->base_addr	= GC64_BASE_ADDR;
	comp->mem->tsize	= GC64_DEFAULT_SIZE;
	comp->mem->used		= 0x00ll;
	comp->mem->free		= GC64_DEFAULT_SIZE;
	comp->mem->nentry	= 0x00ll;
	comp->mem->start	= NULL;
	comp->mem->end		= NULL;
	

	return 0;
}


/* EOF */
