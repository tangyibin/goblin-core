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



static void 	gc64_run_constructor( void ) {
	/* VARS */
	struct gc64comp_t *comp	= NULL;
	int rtn			= 0;
	/* ---- */

	if( __g_comp != NULL ){ 
		/* 
		 * an error has occurred, abort
	 	 *
		 */
		rtn	= -1;
		exit( rtn );

	}else{ 
		comp = malloc( sizeof( struct gc64comp_t ) );
		if( comp == NULL ){ 
			/* 
			 * error occurred, abort
			 *
			 */
			rtn	= -1;
			exit( rtn );
		}
	}

	/* 
	 * set the global to the new structure
	 * 
	 */
	__g_comp	= comp;

}

/* EOF */
