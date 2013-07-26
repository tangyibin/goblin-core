/* 
 * 
 * _GSIM_EXEC_FUNCTIONAL_C_
 * 
 * GOBLIN-SIM FUNCTIONAL SIMULATION EXECUTION 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


/* -------------------------------------------------- GSIM_EXEC_FUNCTIONAL */
/* 
 * GSIM_EXEC_FUNCTIONAL
 * 
 */
extern int gsim_exec_functional( struct gsim_t *sim )
{
#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

	/* 
	 * verify the object file
	 * 
	 */


#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;	
}


/* EOF */
