/* 
 * _GC64_INIT_C_
 * 
 * GC64 COMPILER SCRATCHPAD INIT FUNCTIONS 
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "gc64-comp.h"


/* 
 * FUNCTION PROTOTYPES
 * 
 */
extern int gc64_comp_fptrs();

struct gc64comp_t *__g_comp;

/* 
 * EXTERN INT __GC64_INIT( VOID ) 
 * 
 * STAGE 1: INITIATE THE DATA STRUCTURE
 * STAGE 2: INITIATE THE SCRATCHPAD MEMORY STRUCTURE
 * STAGE 3: WALK THE OBEJCT FILE AND INSERT THE OBJECTS INTO SCRATCHPAD 
 *
 */
extern int __gc64_init(){ 

	/* VARS */
	struct gc64comp_t *comp	= NULL;
	/* ---- */

	if( __g_comp != NULL ){ 
		/* 
		 * an error has occurred, abort
	 	 *
		 */
		GC64_PRINT_TRACE( "__g_comp already initialized" );
		exit( -1 );
	}else{ 
		comp = malloc( sizeof( struct gc64comp_t ) );
		if( comp == NULL ){ 
			/* 
			 * error occurred, abort
			 *
			 */
			exit( -1 );
		}
	}

	/* 
	 * STAGE 1: INIT THE DATA STRUCTURE 
	 * 
	 */
	comp->mem	= NULL;
	comp->status	= 0x00ll;
	
	if( gc64_comp_fptrs() ){ 
		return GC64_ERROR;
	}

	/*
	 * STAGE 2: INIT THE SCRATCHPAD MEMORY STRUCTURE
	 * 
	 */

	/* 
	 * STAGE 3: WALK THE DATA STRUCTURE AND INSERT THE SCRATCHPAD OBJECTS
	 * 
	 */

	/* 
	 * set the global to the new structure
	 * 
	 */
	__g_comp	= comp;

	return GC64_OK;
}

/* EOF */
