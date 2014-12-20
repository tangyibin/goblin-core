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
extern int gc64_comp_fptrs(struct gc64comp_t *comp);
extern int gc64_env(struct gc64comp_t *comp);

/* -- temporary fix */
extern struct gc64sp_t *__gc64_usrinit( uint64_t base, uint64_t size );

/* 
 * GLOBALS//EXTERNS
 * 
 */
struct gc64comp_t *__g_comp;

/* 
 * STATIC INT GC64_INIT_SPAD()
 * 
 * INIT'S THE SCRATCHPAD MEMORY INTERFACE
 *
 */
static int gc64_init_spad(struct gc64comp_t *comp) {

	/* vars */
	struct gc64sp_t *(*mem_init)(uint64_t,uint64_t) 	= comp->fptr.mem_init;
	struct gc64sp_t *lmem					= NULL;
	/* ---- */

	/* 
	 * init the spad handlers
	 * 
	 */	
	#if 0
	lmem	= (*mem_init)(	GC64_DEFAULT_SPAD_BASE_ADDR, 
				GC64_DEFAULT_SPAD_SIZE );
	#endif
	lmem	= __gc64_usrinit( GC64_DEFAULT_SPAD_BASE_ADDR, GC64_DEFAULT_SPAD_SIZE );

	if( lmem == NULL ){ 
		return GC64_ERROR;
	}

	/* 
	 * init our local copy of the pointer
	 * 
	 */
	comp->mem	= lmem;

	return GC64_OK;
}


/* 
 * EXTERN INT __GC64_INIT( VOID ) 
 * 
 * STAGE 1: INITIATE THE DATA STRUCTURE
 * STAGE 2: WALK THE ENV VARS
 * STAGE 3: LOAD ALL THE FUNCTION POINTERS 
 * STAGE 4: INITIATE THE SCRATCHPAD MEMORY STRUCTURE
 * STAGE 5: WALK THE OBEJCT FILE AND INSERT THE OBJECTS INTO SCRATCHPAD 
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

	printf( "__GC64_INIT()\n" );

	/* 
	 * STAGE 1: INIT THE DATA STRUCTURE 
	 * 
	 */
	printf( "...STAGE1\n" );
	comp->mem		= NULL;
	comp->status		= 0x00ll;
	comp->trace		= 0x00ll;
	comp->usr_trace		= 0x00ll;

	/* -- function pointers */
	comp->fptr.mem_init	= NULL;
	comp->fptr.mem_free	= NULL;

	/* 
	 * STAGE 2: WALK THE ENV VARS
	 *
	 */
	printf( "...STAGE2\n" );
	if( gc64_env( comp ) != GC64_OK ){ 
		return GC64_ERROR;
	}

	/* 
	 * STAGE 3: LOAD ALL THE FUNCTION POINTERS FROM OTHER OBJECTS
	 *
 	 */	
	printf( "...STAGE3\n" );
	if( gc64_comp_fptrs(comp) != GC64_OK ){ 
		return GC64_ERROR;
	}

	/*
	 * STAGE 4: INIT THE SCRATCHPAD MEMORY STRUCTURE
	 * 
	 */
	printf( "...STAGE4\n" );
	if( gc64_init_spad(comp) != GC64_OK ){ 
		return GC64_ERROR;
	} 

	/* 
	 * STAGE 5: WALK THE DATA STRUCTURE AND INSERT THE SCRATCHPAD OBJECTS
	 * 
	 */
	printf( "...STAGE5\n" );


	/* 
	 * set the global to the new structure
	 * 
	 */
	__g_comp	= comp;

	return GC64_OK;
}

/* EOF */
