/* 
 * _MEMSIM_RQST_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM RQST FUNCTIONS
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


#define BITFIELD	0x3C00000000

/* ------------------------------------------------ FUNCTION_PROTOTYPES */
extern int memsim_validate_rqst( memsim_rqst_t rqst );
extern int memsim_find_slot( struct memsim_slot_t *slot, uint32_t *rtn );
extern int memsim_tid_pop( struct memsim_t *msim, uint32_t *tid ); 

/* ------------------------------------------------ MEMSIM_RQST_DEST */
/* 
 * MEMSIM_RQST_DEST
 * 
 */
extern int memsim_rqst_dest( struct memsim_entry_t *entry )
{
	int rtn		= 3;
	uint64_t addr	= entry->buf[0];
	uint64_t dest	= 0x00ll;

	/* we assume a single socket node for now */
	/* we do, however, consider the scratchpad memories */

	dest	= ((addr & BITFIELD)>>34);

	if( dest == 0xF ){
		/* destination is a scratchpad memory */
		rtn	= 1;
	}else{
		/* destination is an hmc memory */
		rtn	= 0;
	}

	return rtn;
}

/* ------------------------------------------------ MEMSIM_RQST_TYPE */
/* 
 * MEMSIM_RQST_TYPE
 * 
 */
extern int memsim_rqst_type( memsim_rqst_t rqst )
{
	int rtn	= 3;

	switch( rqst )
	{
		case MEMSIM_RD8:
		case MEMSIM_RD4:
			rtn = 0;
			break;
		case MEMSIM_WR8:
		case MEMSIM_WR4:
			rtn = 1;
			break;
		case MEMSIM_FENCE:
			rtn = 3;
			break;
		case MEMSIM_UNK:
		default:	
			rtn = -1;
			break;
	}

	return rtn;
}

/* ------------------------------------------------ MEMSIM_RQST */
/* 
 * MEMSIM_RQST
 * 
 */
extern int memsim_rqst(	struct memsim_t *msim, 
			uint64_t gconst, 
			memsim_rqst_t rqst, 
			uint64_t addr, 
			uint64_t payload0,
			uint64_t payload1, 
			uint32_t *ftid )
{
	/* vars */	
	uint32_t tid	= 0x00;
	uint32_t slot	= 0x00;
	uint64_t pid	= 0x00ll;
	uint64_t nid	= 0x00ll;
	uint64_t sid	= 0x00ll;
	uint64_t tp	= 0x00ll;
	uint64_t tg	= 0x00ll;
	uint64_t tc	= 0x00ll;
	struct memsim_slot_t *tmp_g	= NULL;
	/* ---- */

	/* 
	 * sanity check 
	 *
	 */
	if( msim == NULL ){ 
		return MEMSIM_ERROR;
	}

	if( ftid == NULL ){ 
		return MEMSIM_ERROR;
	}

	/* 
	 * validate the request type
 	 * 
	 */
	if( memsim_validate_rqst( rqst ) != MEMSIM_OK ){ 
		return MEMSIM_ERROR;
	}

	/* 
	 * step 1: crack the gconst field
	 * 
 	 */
	pid	= (gconst & GSIM_REG_GCONST_PID);
	nid	= (gconst & GSIM_REG_GCONST_NID)>>16;
	sid	= (gconst & GSIM_REG_GCONST_SID)>>32;
	tg	= (gconst & GSIM_REG_GCONST_TG)>>40;
	tp	= (gconst & GSIM_REG_GCONST_TP)>>48;
	tc	= (gconst & GSIM_REG_GCONST_TC)>>56;

	/* 
	 * step 2: validate the gconst field values
 	 * 
 	 */
	if( tg >= (uint64_t)(msim->task_groups) ){
		return MEMSIM_ERROR;	
	}else if( tp >= (uint64_t)(msim->task_procs) ){
		return MEMSIM_ERROR;
	}else if( tc >= (uint64_t)(msim->tasks) ){ 
		return MEMSIM_ERROR;
	}

	/* 
	 * step 3: find an open slot
	 * 
	 */
	tmp_g	= &(msim->group[tg]);
	if( memsim_find_slot( tmp_g, &slot ) != MEMSIM_OK ){ 
		return MEMSIM_STALL;
	}

	if( memsim_tid_pop( msim, &tid ) != MEMSIM_OK ){ 
		return MEMSIM_STALL;
	}	

	/* 
	 * step 4: enter the request in the slot
	 * 
 	 */
	tmp_g->entry[slot].gconst	= gconst;
	tmp_g->entry[slot].valid	= 1;
	tmp_g->entry[slot].rqst		= rqst;
	tmp_g->entry[slot].buf[0]	= addr;
	tmp_g->entry[slot].buf[1]	= payload0;
	tmp_g->entry[slot].buf[2]	= payload1;
	tmp_g->entry[slot].tid[0]	= tid;
	tmp_g->entry[slot].num_tids	= 1;

	msim->tids[tid].valid		= 1;
	msim->tids[tid].gconst		= gconst;

	/* 
	 * set the tid 
	 * 
	 */
	*ftid	= tid;
	
	return MEMSIM_OK;
}

/* EOF */
