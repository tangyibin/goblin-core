/* 
 * _MEMSIM_CP_SLOT_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM COPY SLOT 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ MEMSIM_CP_ENTRY */
/* 
 * MEMSIM_CP_ENTRY
 * 
 */
extern int memsim_cp_entry( struct memsim_entry_t *src, struct memsim_entry_t *dest ) 
{
	/* vars */
	uint32_t i	= 0;
	/* ---- */

	/* 
	 * sanity check 
	 * 
	 */
	if( src == NULL ){ 
		return MEMSIM_ERROR;
	}else if( dest == NULL ){ 
		return MEMSIM_ERROR;
	}

	dest->buf[0]	= src->buf[0];
	dest->buf[1]	= src->buf[1];
	dest->buf[2]	= src->buf[2];
	dest->buf[3]	= src->buf[3];

	dest->gconst	= src->gconst;
	dest->valid	= src->valid;
	dest->num_tids	= src->num_tids;
	dest->rqst	= src->rqst;

	for( i=0; i<32; i++ ){ 
		dest->tid[i]	= src->tid[i];
	}

	return MEMSIM_OK;
}

/* EOF */
