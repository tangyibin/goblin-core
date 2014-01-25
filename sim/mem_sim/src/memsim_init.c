/* 
 * _MEMSIM_INIT_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * INITIALIZATION FUNCTIONS 
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ MEMSIM_INIT* /
/* 
 * MEMSIM_INIT
 * 
 */
extern int memsim_init(	struct memsim_t *msim, 
			uint32_t task_groups, 
			uint32_t task_procs, 
			uint32_t tasks, 
			memsim_iface_t iface, 
			uint32_t g_slots, 
			uint32_t s_slots, 
			uint32_t a_slots,
			uint32_t ga_slots,
			uint64_t opt )
{
	/* vars */
	uint64_t total			= 0;
	uint64_t i			= 0;
	uint64_t cur			= 0;
	struct memsim_entry_t *tmp_e	= NULL;
	struct memsim_slot_t *tmp	= NULL;
	/* ---- */

	/* 
	 * sanity check 
	 *
	 */
	if( msim == NULL ){ 
		return MEMSIM_ERROR;
	}

	msim->__ptr_slots	= NULL;
	msim->__ptr_entry	= NULL;
	msim->group		= NULL;
	msim->socket		= NULL;
	msim->amo		= NULL;

	msim->opt		= opt;

	msim->tfile		= NULL;
	msim->tracelevel	= 0x00;

	msim->g_slots		= g_slots;	
	msim->s_slots		= s_slots;	
	msim->a_slots		= a_slots;	
	msim->ga_slots		= ga_slots;	

	msim->task_groups	= task_groups;
	msim->task_procs	= task_procs;
	msim->tasks		= tasks;

	if( (iface != MEMSIM_BASIC) && (iface != MEMSIM_HMC) ){ 
		return MEMSIM_ERROR;
	}

	/* 
	 * allocate memory for the slots
	 * 
	 */
	total = (uint64_t)(task_groups) + (uint64_t)(1);

	if( (opt & MEMSIM_GA) > 0 ){ 
		total += 1;
	}
	if( (opt & MEMSIM_AMO) > 0 ){ 
		total += 1;
	}

	if( total == 0 ){ 
		return MEMSIM_ERROR;
	}

	tmp 	= malloc( sizeof( struct memsim_slot_t ) * total );
	if( tmp == NULL ){ 
		return MEMSIM_ERROR;
	}

	msim->__ptr_slots	= tmp;

	/* 
	 * setup the pointers to the slot structures 
	 * 
	 */
	msim->group	= &(tmp[0]);
	cur		= (uint64_t)(task_groups);
	msim->socket	= &(tmp[cur]);
	cur 		+= 1;

	if( (opt & MEMSIM_AMO) > 0 ){ 
		msim->amo	= &(tmp[cur]);
		cur	+= 1;
	}

	if( (opt & MEMSIM_GA) > 0 ){ 
		msim->global	= &(tmp[cur]);
		cur	+= 1;
	}

	/* 
	 * allocate memory for the actual slot entries
	 * 
 	 */
	total	= (uint64_t)(task_groups)*(uint64_t)(g_slots);
	total	+= (uint64_t)(s_slots);
	if( (opt & MEMSIM_AMO) > 0 ){ 
		total += a_slots;
	}

	if( (opt & MEMSIM_GA) > 0 ){ 
		total += ga_slots;
	}

	tmp_e	= malloc( sizeof( struct memsim_entry_t ) * total );	
	if( tmp_e == NULL ){ 
		return MEMSIM_ERROR;
	}

	msim->__ptr_entry	= tmp_e;
	
	/* 
	 * setup the pointers to the necessary slots 
	 * 
 	 */
	cur = 0x00;
	for( i=0; i<(uint64_t)(task_groups); i++ ){ 
		msim->group[i].entry	= &(tmp_e[cur]);
		msim->group[i].num_slots = g_slots;
		msim->group[i].id	= i;
		cur += (uint64_t)(g_slots);
	}

	msim->socket[0].entry		= &(tmp_e[cur]);
	msim->socket[0].num_slots	= s_slots;
	msim->socket[0].id		= 0;
	cur += (uint64_t)(s_slots);

	if( (opt & MEMSIM_AMO) > 0 ){ 
		msim->amo[0].entry	= &(tmp_e[cur]);
		msim->amo[0].num_slots	= a_slots;
		msim->amo[0].id		= 0;
		cur += (uint64_t)(a_slots);
	}

	if( (opt & MEMSIM_GA) > 0 ){
		msim->global[0].entry	= &(tmp_e[cur]);
		msim->global[0].num_slots = ga_slots;
		msim->global[0].id	= 0;
	}

	return MEMSIM_OK;
}

/* EOF */