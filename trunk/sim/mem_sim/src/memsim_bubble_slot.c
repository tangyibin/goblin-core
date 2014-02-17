/* 
 * _MEMSIM_BUBBLE_SLOT_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM BUBBLE SLOT FUNCTION
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ FUNCTION PROTOTYPES */
extern int memsim_clear_entry( struct memsim_entry_t *ent );


/* ------------------------------------------------ MEMSIM_BUBBLE_SLOT */
/* 
 * MEMSIM_BUBBLE_SLOT
 * 
 */
extern int memsim_bubble_slot(	struct memsim_slot_t *slot )
{
	/* vars */
	uint32_t i	= 0;
	uint32_t j	= 0;
	uint32_t k	= 0;
	uint32_t swap	= 0;
	/* ---- */

	/* 
	 * sanity check 
	 *
	 */
	if( slot == NULL ){ 
		return MEMSIM_ERROR;
	}

	/* 
	 * walk the slots and bubble up the entries 
	 * 
	 */
	for( i=1; i<slot->num_slots; i++ ){ 
		if( slot->entry[i].valid == 1 ){ 
			swap = i;

			/*for( j=i-1; j>=0; j-- ){*/
			for( j=0; j<i; i++ ){
				if( slot->entry[j].valid == 0 ){
					swap = j;
					j = i;
				}
			}

			if( swap != i ){ 
				/* perform the swap */
				slot->entry[swap].buf[0] = slot->entry[i].buf[0];
				slot->entry[swap].buf[1] = slot->entry[i].buf[1];
				slot->entry[swap].buf[2] = slot->entry[i].buf[2];
				slot->entry[swap].buf[3] = slot->entry[i].buf[3];
				slot->entry[swap].gconst = slot->entry[i].gconst;
				slot->entry[swap].valid  = slot->entry[i].valid;
				slot->entry[swap].num_tids = slot->entry[i].num_tids;
				slot->entry[swap].rqst   = slot->entry[i].rqst;	

				for( k=0; k<32; k++ ){ 
					slot->entry[swap].tid[k] = slot->entry[i].tid[k];
				}

				/* clear the original entry */
				memsim_clear_entry( &(slot->entry[i]) );
			}else{
				/* no space left */
				goto no_space;
			}
		}
	}

no_space:

	return MEMSIM_OK;
}

/* EOF */
