/* 
 * _GC64_CONSTRUCTOR_C_
 * 
 * GC64 COMPILER CONSTRUCTOR LIBRARY 
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "gc64-comp.h"

/* 
 * SPECIAL ELF SECTION DEFINITIONS FOR CONSTRUCTOR
 * 
 */
__attribute__ ((constructor(0))) __attribute((__section__(".init.text"))) static void gc64_run_constructor( void );


/* 
 * EXTERN INT __GC64_INIT( VOID ) 
 * 
 * STAGE 1: INITIATE THE DATA STRUCTURE
 * STAGE 2: INITIATE THE SCRATCHPAD MEMORY STRUCTURE
 * STAGE 3: WALK THE OBEJCT FILE AND INSERT THE OBJECTS INTO SCRATCHPAD 
 *
 */
extern int __gc64_init( void ){ 

	/* VARS */
	struct gc64comp_t *comp	= NULL;
	/* ---- */

	if( __g_comp != NULL ){ 
		/* 
		 * an error has occurred, abort
	 	 *
		 */
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

/* 
 * STATIC VOID GC64_RUN_CONSTRUCTOR
 * 
 * STAGE 1: INITIATE THE DATA STRUCTURE
 * STAGE 2: INITIATE THE SCRATCHPAD MEMORY STRUCTURE
 * STAGE 3: WALK THE OBEJCT FILE AND INSERT THE OBJECTS INTO SCRATCHPAD 
 *
 */
static void 	gc64_run_constructor( void ) {

	/* 
	 * execute the initializer 
	 * 
 	 */
	__gc64_init();
}

/* EOF */
