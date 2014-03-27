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
#include <inttypes.h>
#include "mem_sim.h"


/* ------------------------------------------------ MEMSIM_INIT */
/* 
 * MEMSIM_INIT
 * 
 */
extern int memsim_init(	struct memsim_t *msim, 
			memsim_iface_t iface, 
			memsim_alg_t alg,
			uint32_t task_groups, 
			uint32_t task_procs, 
			uint32_t tasks, 
			uint32_t g_slots, 
			uint32_t s_slots, 
			uint32_t a_slots,
			uint32_t ga_slots,
			uint64_t opt )
{
	/* vars */
	uint64_t total			= 0;
	uint64_t i			= 0;
	uint32_t j			= 0;
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
	msim->clock		= 0x00;

	msim->l1_cache_sets	= 0x00;
	msim->l2_cache_sets	= 0x00;
	msim->l3_cache_sets	= 0x00;

	msim->l1_cache_ways	= 0x00;
	msim->l2_cache_ways	= 0x00;
	msim->l3_cache_ways	= 0x00;

	msim->l1_cache_size	= 0x00;
	msim->l2_cache_size	= 0x00;
	msim->l3_cache_size	= 0x00;

	msim->l1		= NULL;
	msim->l2		= NULL;
	msim->l3		= NULL;

	if( (iface != MEMSIM_BASIC) && (iface != MEMSIM_HMC) ){ 
		return MEMSIM_ERROR;
	}

	msim->iface	= iface;

	switch( alg )
	{
		case MEMSIM_SIMPLE:
		case MEMSIM_CACHE:
		case MEMSIM_EXP:
			msim->alg = alg;
			break;
		default:
			return MEMSIM_ERROR;
			break;
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
	 * zero all the entries
	 * 
	 */
	for( i=0; i<total; i++ ){ 
		tmp_e[i].buf[0]	= 0x00ll;
		tmp_e[i].buf[1]	= 0x00ll;
		tmp_e[i].buf[2]	= 0x00ll;
		tmp_e[i].buf[3]	= 0x00ll;
		tmp_e[i].gconst	= 0x00ll;
		tmp_e[i].valid	= 0x00;
		tmp_e[i].rqst	= MEMSIM_UNK;

		tmp_e[i].num_tids = 0;

		for( j=0; j<MEMSIM_TIDS_PER_ENTRY; j++ ){ 
			tmp_e[i].tid[j]	= 0;
		}
		
	}
	
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

	/* 
	 * setup the tid handlers 
	 * 
	 */
	msim->__ptr_tid	= malloc( sizeof( struct memsim_tid_t ) 
			* task_groups * task_procs * tasks * 8 );
	if( msim->__ptr_tid == NULL ){ 
		return MEMSIM_ERROR;
	}

	for( i=0; i<(uint64_t)(task_groups * task_procs * tasks * 8); i++ ){ 
		msim->__ptr_tid[i].gconst	= 0x00ll;
		msim->__ptr_tid[i].id		= (uint32_t)(i);
		msim->__ptr_tid[i].valid	= 0x00;
	
	}

	msim->num_tids	= task_groups * task_procs * tasks * 8;
	msim->tids	= msim->__ptr_tid;

	/* 
	 * init the hardware 
	 * 
 	 */
	msim->hw.num_links	= 4;
	msim->hw.num_lanes	= 8;
	msim->hw.gbps		= (float)(10);

	/*
	 * payps = ((( gbps * num_lanes ) / 64 ) / 1Ghz ) * num_links
	 * 
	 */	
	msim->hw.payps		= (uint64_t)( (((((float)(msim->hw.gbps)*(float)(MEMSIM_GIGABIT)) * 
						(float)(msim->hw.num_lanes)) / (float)(64)) /
						(float)(1000000000.0))) 
					* (uint64_t)(msim->hw.num_links);
#if 0
	msim->hw.payps		= (uint64_t)( (((float)(msim->hw.num_lanes) * 
						(float)(msim->hw.gbps)  *
						(float)(MEMSIM_GIGABIT) )
					/(float)(8))/8  ) * (uint64_t)(msim->hw.num_links);
#endif
	
	return MEMSIM_OK;
}

/* EOF */
