/* 
 * _GC64_FPTRS_C_
 * 
 * GC64 COMPILER SCRATCHPAD FUNCTION POINTER INIT
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include "gc64-comp.h"


/* 
 * EXTERN INT GC64_LOAD_USRLIB
 * 
 * Resolves all the user library function pointers
 * 
 */
static int gc64_load_usrlib( struct gc64comp_t *comp){
	/* vars */
	void *handle		= NULL;
	char *lib		= NULL;
	char *error		= NULL;
	char default_lib[]	= "/home/jleidel/riscv/gc64/libgc64usr.so";
	/* ---- */

	return GC64_OK;
	/* 
	 * decide which library to use
	 * 
 	 * TODO : eventually, make this peer into the env vars
	 * 
	 */
	lib	= &(default_lib[0]);

	handle = dlopen( lib, RTLD_NOW|RTLD_NODELETE );

	if( handle == NULL ){ 
		printf( "Error : could not open default_lib : %s\n", default_lib );
		printf( "Error : %s\n", dlerror() );
		return GC64_ERROR;
	}

	comp->usrlib_handle	= handle;

	/* 
	 * walk and resolve all the necesary fptrs 
	 * 
	 */	
	/* __gc64_usrinit */ 
	(comp->fptr.mem_init)	= (struct gc64sp_t *(*)(uint64_t,uint64_t))dlsym(comp->usrlib_handle, 
											"__gc64_usrinit");
	
	if( (error = dlerror()) != NULL ){ 
		return GC64_ERROR;
	}	
	
	/* __gc64_usrfree */ 
	(comp->fptr.mem_free)	= (void (*)())dlsym(comp->usrlib_handle, 
								"__gc64_usrfree");
	
	if( (error = dlerror()) != NULL ){ 
		return GC64_ERROR;
	}	
	
	return GC64_OK;
}

/* 
 * EXTERN INT GC64_COMP_FPTRS()
 * 
 * Resolve all the necessary function pointers
 * 
 */
extern int gc64_comp_fptrs(struct gc64comp_t *comp) {

	if( comp == NULL ){ 
		return GC64_ERROR;
	}

	if( gc64_load_usrlib(comp) != 0 ){ 
		return GC64_ERROR;
	}

	return GC64_OK;
}

/* EOF */
