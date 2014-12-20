/* 
 * _GC64_LIBFREE_C_
 * 
 * GC64 COMPILER LIBFREE FUNCTIONS
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include "gc64-comp.h"

/* 
 * EXTERN VOID GC64_LIBFREE
 * 
 */
extern void __gc64_libfree(){

	/* vars */
	void (*mem_free)() = __g_comp->fptr.mem_free;
	/* ---- */

	GC64_TRACE_FUNC_ENTRY(__g_comp);

	/* 
	 * free all the internal contents
	 * 
	 */
	/* -- free the spad struct contents */
	(*mem_free)();
	__g_comp->mem = NULL;

	/* -- free the dlopen'd handles */
	if( __g_comp->usrlib_handle != NULL ){ 
		dlclose( __g_comp->usrlib_handle );
		__g_comp->usrlib_handle = NULL;
	}

	GC64_TRACE_FUNC_EXIT(__g_comp);

	free( __g_comp );
	__g_comp = NULL;
}

/* EOF */
