/* 
 * _GC64_CONSTRUCTOR_C_
 * 
 * GC64 COMPILER CONSTRUCTOR LIBRARY 
 * 
 */

#include "gc64-usr.h"

/* 
 * SPECIAL ELF SECTION DEFINITIONS FOR CONSTRUCTOR
 * 
 */
__attribute__ ((constructor(0))) __attribute((__section(".init.text"))) static void g64_run_constructor( void );



static void 	gc64_run_constructor( void ) {
}

/* EOF */
