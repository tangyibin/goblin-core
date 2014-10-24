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


/* FUNCTION PROTOTYPES */
extern int __gc64_init();

/* 
 * STATIC VOID GC64_RUN_CONSTRUCTOR
 * 
 * STAGE 1: INITIATE THE DATA STRUCTURE
 * STAGE 2: INITIATE THE SCRATCHPAD MEMORY STRUCTURE
 * STAGE 3: WALK THE OBEJCT FILE AND INSERT THE OBJECTS INTO SCRATCHPAD 
 *
 */
static void 	gc64_run_constructor( void ) {

	GC64_PRINT_TRACE( "ENTERING CONSTRUCTOR\n" );

	/* 
	 * execute the initializer 
	 * 
 	 */
	__gc64_init();

	GC64_PRINT_TRACE( "EXITING CONSTRUCTOR\n" );
}

/* EOF */
