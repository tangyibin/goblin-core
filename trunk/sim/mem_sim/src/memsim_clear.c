/* 
 * _MEMSIM_CLEAR_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM CLEAR FUNCTIONS
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ MEMSIM_CLEAR_ENTRY */
/* 
 * MEMSIM_CLEAR_ENTRY
 * 
 */
extern int memsim_clear_entry(	struct memsim_entry_t *ent )
{
	/* vars */
	int i	= 0;
	/* ---- */

	/* 
	 * sanity check 
	 *
	 */
	if( ent == NULL ){ 
		return MEMSIM_ERROR;
	}

	ent->buf[0]	= 0x00ll;	
	ent->buf[1]	= 0x00ll;	
	ent->buf[2]	= 0x00ll;	
	ent->buf[3]	= 0x00ll;	

	ent->valid	= 0;

	for( i=0; i<32; i++ ){ 
		ent->tid[i]	= 0;
	}

	ent->num_tids	= 0;
	ent->rqst	= MEMSIM_UNK;

	return MEMSIM_OK;
}

/* EOF */
