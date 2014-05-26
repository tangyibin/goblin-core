/* 
 * _MEMSIM_TREE_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM TREE FUNCTIONS
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ MEMSIM_ROTATE_TREE */
/* 
 * MEMSIM_ROTATE_TREE
 * 
 */
extern int memsim_rotate_tree(	struct memsim_tree_t *tree )
{
	return MEMSIM_OK;
}

/* ------------------------------------------------ MEMSIM_INSERT_ENTRY */
/* 
 * MEMSIM_INSERT_ENTRY
 * 
 */
extern int memsim_insert_entry(	struct memsim_tree_t *tree )
{
	/* vars */
	int rtn	= 0;
	/* --- */

	/* 
	 * step 1: go get a blank tree entry 
	 * 
	 */

	/*
	 * step 2: insert it 
	 * 
	 */

	/* 
	 * step 3: rotate the tree
	 * 
	 */
	rtn	= memsim_rotate_tree( tree );	

	return rtn;
}

/* EOF */

