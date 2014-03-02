/* 
 * _MEMSIM_FREE_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM FREE 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ MEMSIM_FREE */
/* 
 * MEMSIM_FREE
 * 
 */
extern int memsim_free(	struct memsim_t *msim )
{
	/* 
	 * sanity check 
	 *
	 */
	if( msim == NULL ){ 
		return MEMSIM_ERROR;
	}

	if( msim->tfile != NULL ){ 
		fflush( msim->tfile );
	}

	if( msim->l1 != NULL ){ 
		free( msim->l1 );
		msim->l1 = NULL;
	}

	if( msim->l2 != NULL ){ 
		free( msim->l2 );
		msim->l2 = NULL;
	}

	if( msim->l3 != NULL ){ 
		free( msim->l3 );
		msim->l3 = NULL;
	}

	if( msim->__ptr_tid != NULL ){ 
		free( msim->__ptr_tid );
		msim->__ptr_tid	= NULL;
	}

	if( msim->__ptr_entry != NULL ){ 
		free( msim->__ptr_entry );
		msim->__ptr_entry = NULL;
	}

	if( msim->__ptr_slots != NULL ){ 
		free( msim->__ptr_slots );
		msim->__ptr_slots = NULL;
	}

	return MEMSIM_OK;
}

/* EOF */
