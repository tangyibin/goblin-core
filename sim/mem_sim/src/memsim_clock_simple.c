/* 
 * _MEMSIM_CLOCK_SIMPLE_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM CLOCK SIMPLE BACKEND
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ FUNCTION PROTOTYPES */
extern int memsim_tid_push( struct memsim_t *msim, uint32_t tid );
extern int memsim_tick_count( struct memsim_entry_t *ent, uint64_t *ticks );
extern int memsim_trace_memop( struct memsim_t *msim, struct memsim_entry_t *ent );
extern int memsim_clear_entry( struct memsim_entry_t *ent );
extern int memsim_bubble_slot( struct memsim_slot_t *slot );

/* ------------------------------------------------ MEMSIM_CLOCK_SIMPLE_PROCESS_SOCKET */
static int memsim_clock_simple_process_socket( struct memsim_t *msim ){

	/* vars */
	uint64_t count	= 0x00ll;
	uint64_t ticks	= 0x00ll;
	int done	= 0;
	uint32_t cur	= 0;
	/* ---- */

	/* 
	 * process the slot entries within this clock cycle
	 * 
	 */
	while( (done != 1) && (count<msim->hw.payps) ){ 
	
		/*
		 * check the 'cur' element
	 	 * 
		 */
		ticks = 0x00ll;

		if( msim->socket->entry[cur].valid == 1 ){ 

			/* 
			 * cur element is valid, process it 
			 *
			 */
				
			/* 
			 * First, determine the number of ticks
			 * required to process this entry
			 * If we don't have enough ticks, 
			 * we're done.
			 * 
			 * Each 64-bit element requires a tick
			 *
			 */ 
			if( memsim_tick_count( &(msim->socket->entry[cur]), &ticks ) != 0 ){
				return MEMSIM_ERROR;
			}
			
			if( (count+ticks) <= msim->hw.payps ){ 
				
				/* 
				 * we're within range.
				 * push the request 
				 *
				 */

				/* print the trace */
				if( (msim->tracelevel & MEMSIM_TRACE_MEMOP ) > 0 ){ 
					memsim_trace_memop( msim, 
							&(msim->socket->entry[cur]) );
				}

				/* clear the entry */
				memsim_clear_entry( &(msim->socket->entry[cur]) );

				/* bump the count */
				count += ticks;
	
			}else{
				/* 
				 * out of range, time to stall 
				 *
				 */
				done = 1;
			}

		}

		if( (cur+1) >= msim->socket->num_slots ){ 
			/* 
			 * Last element
			 *
			 */
			done = 1;
		}else{ 
			cur += 1;
		}
	
	} 

	/* 
	 * bubble the slot entries
	 * 
	 */
	if( memsim_bubble_slot( msim->socket ) != 0 ){ 
		return MEMSIM_ERROR;
	}

	return MEMSIM_OK;
}

/* ------------------------------------------------ MEMSIM_CLOCK_SIMPLE_PROCESS_AMO */
static int memsim_clock_simple_process_amo( struct memsim_t *msim ){
	return MEMSIM_OK;
}

/* ------------------------------------------------ MEMSIM_CLOCK_SIMPLE_PROCESS_GLOBAL */
static int memsim_clock_simple_process_global( struct memsim_t *msim ){
	return MEMSIM_OK;
}

/* ------------------------------------------------ MEMSIM_CLOCK_SIMPLE_PROCESS_TASKGROUP */
static int memsim_clock_simple_process_taskgroup( struct memsim_t *msim, uint32_t group ){
	return MEMSIM_OK;
}

/* ------------------------------------------------ MEMSIM_CLOCK_SIMPLE */
/* 
 * MEMSIM_CLOCK_SIMPLE
 * 
 * 
 * This backend implementation does nothing but pass
 * the slot entries between queues. It does not request coalescing 
 * whatsoever.  
 * 
 */
extern int memsim_clock_simple( struct memsim_t *msim )
{
	/* vars */
	uint32_t i	= 0;
	/* ---- */

	/* 
	 * process the socket queues 
	 * 
	 */
	/* -- socket queue */
	if( memsim_clock_simple_process_socket( msim ) != 0 ){ 
		return MEMSIM_ERROR;
	}

	/* -- amo queue */
	if( (msim->opt & MEMSIM_AMO) > 0 ){
		if( memsim_clock_simple_process_amo( msim ) != 0 ){ 
			return MEMSIM_ERROR;
		}
	}

	/* -- global queue */
	if( (msim->opt & MEMSIM_GA) > 0 ){ 
		if( memsim_clock_simple_process_global( msim ) != 0 ){ 
			return MEMSIM_ERROR;
		}
	}

	/* 
	 * process each of the local task group queues
	 * 
 	 */
	for( i=0; i<msim->task_groups; i++ ){ 
		if( memsim_clock_simple_process_taskgroup( msim, i ) != 0 ){ 
			return MEMSIM_ERROR;
		}
	}

	return MEMSIM_OK;
}

/* EOF */
