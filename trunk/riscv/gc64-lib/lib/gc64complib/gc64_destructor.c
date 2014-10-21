/* 
 * _GC64_DESTRUCTOR_C_
 * 
 * GC64 COMPILER DESTRUCTOR LIBRARY 
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "gc64-comp.h"

/* 
 * SPECIAL ELF SECTION DEFINITIONS FOR DESTRUCTOR
 * 
 */
__attribute__ ((destructor(0))) __attribute((__section__(".exit.text"))) static void gc64_run_destructor( void );


/* FUNCTION PROTOTYPES */
extern void __gc64_libfree();

/* 
 * STATIC VOID GC64_RUN_DESTRUCTOR
 * 
 */
static void 	gc64_run_destructor( void ) {

	if( __g_comp != NULL ){ 
		__gc64_libfree();
	}
}

/* EOF */
