/* 
 * _MEMSIM_TREE_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM TREE FUNCTIONS
 * 
 * === Tree Structure === 
 * 
 *                     [ROOT]
 *                       |
 *                      / \
 *                     /   \
 *                READS     WRITES
 *                 |          |
 *                / \        / \
 *               /   \      /   \
 *              /     \    /     \ 
 *            -addr +addr -addr  +addr
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ FUNCTION PROTOTYPES */
extern int memsim_clear_entry( struct memsim_entry_t *ent );

/* ------------------------------------------------ MEMSIM_ROTATE_TREE */
/* 
 * MEMSIM_ROTATE_TREE
 * 
 */
extern int memsim_rotate_tree(	struct memsim_tree_t *tree )
{
	return MEMSIM_OK;
}

/* ------------------------------------------------ MEMSIM_TREE_FLUSH */
/* 
 * MEMSIM_TREE_FLUSH
 * 
 */
static int memsim_tree_flush(	struct memsim_tree_t *tree, 
				struct memsim_entry_t *entry )
{
	/* vars */
	/* ---- */

	/* 
	 * step 1, coalesce what we have into a read request 
	 *         and a write request
	 *
	 */

	/*
	 * step 2, force the request onto the socket queue
	 * 
	 */

	/* 
	 * step 3, zero the tick count 
	 * 
	 */
	tree->tick = 0;

	/* 
	 * step 4, clear the entry 
	 * 
	 */
	if( memsim_clear_entry( entry ) != MEMSIM_OK ){ 
		return MEMSIM_ERROR;
	}
	

	return MEMSIM_OK;
}

/* ------------------------------------------------ MEMSIM_INSERT_TREE_ENTRY */
/* 
 * MEMSIM_INSERT_TREE_ENTRY
 * 
 */
extern int memsim_insert_tree_entry(	struct memsim_tree_t *tree, 
					struct memsim_entry_t *entry, 
					int type )
{
	/* vars */
	int rtn	= 0;
	/* --- */

	/* 
	 * step 1: go get a blank tree entry 
	 * 
	 */
	if( tree->root == NULL ){ 
		/* tree is incorrectly setup */
		return MEMSIM_ERROR;
	}

	/* 
	 * Step 2: 
	 * determine what type it is
	 * and insert it
	 * 
	 */
	if( type == 0 ){ 
		/* read operation */
	}else if( type == 1 ){ 
		/* write operation */
	}else if( type == 2 ){ 
		/* amo operation */
	}else if( type == 3 ){ 
		/* flush operation */
		rtn	= memsim_tree_flush( tree, entry );
		return rtn;
	}else{ 
		return MEMSIM_ERROR;
	}

	/*
	 * step 3: update the tick count
	 * 
	 */
	tree->tick++;

	/* 
	 * step 4: rotate the tree
	 * 
	 */
	rtn	= memsim_rotate_tree( tree );	

	return rtn;
}

/* EOF */

