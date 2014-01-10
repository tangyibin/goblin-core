/* 
 * 
 * _GSIM_FREE_SIM_
 * 
 * GOBLIN-SIM LIBRARY FREE FUNCTIONS
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


/* ----------------------------------------------------------- GSIM_FREE_SIM */
/* 
 * GSIM_FREE_SIM
 * 
 */
extern void gsim_free_sim( struct gsim_t *sim )
{
#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

	int i		= 0;
	int T_HMC	= 0;
	T_HMC	= sim->sockets*sim->nodes*sim->partitions;

	if( sim == NULL ){
		/* nothing to do, return */
		return ;
	}

	for( i=0; i<T_HMC; i++ ){ 
		//hmcsim_free( &(sim->hw->__ptr_hmc[i]) );	
	}

	if( sim->hw != NULL ){ 
		gsim_free( sim->hw->__ptr_partition );
		gsim_free( sim->hw->__ptr_node );
		gsim_free( sim->hw->__ptr_socket );
		gsim_free( sim->hw->__ptr_task_group );
		gsim_free( sim->hw->__ptr_task_proc );
		gsim_free( sim->hw->__ptr_task );
		gsim_free( sim->hw->__ptr_icache );
		gsim_free( sim->hw->__ptr_hmc );
		gsim_free( sim->hw );
	}

	/* 
	 * close all the file handles
	 * 
	 */

	if( sim->tfile != NULL ){ 
		fflush( sim->tfile );	
		fclose( sim->tfile );
		sim->tfile = NULL;
	}

	if( sim->lfile != NULL ){ 
		fflush( sim->lfile );
		fclose( sim->lfile );
		sim->lfile = NULL;
	}

	if( sim != NULL ){ 
		free( sim );
		sim = NULL;
	}

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return ;
}

/* EOF */
