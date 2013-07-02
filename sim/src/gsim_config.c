/* 
 * 
 * _GSIM_CONFIG_C_ 
 * 
 * GOBLIN-SIM CONFIG FILE INTERFACES
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


/* -------------------------------------------------- GSIM_CONFIG_READ */
/* 
 * GSIM_CONFIG_READ
 * 
 */
extern int gsim_config_read( struct gsim_t *sim )
{
#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_ENTRY();
#endif


	/* sanity check */
	if( sim == NULL ){ 
		return -1;
	}


#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;	
}


/* EOF */
