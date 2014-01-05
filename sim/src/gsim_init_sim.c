/* 
 * 
 * _GSIM_INIT_SIM_ 
 * 
 * GOBLIN-SIM LIBRARY INIT FUNCTIONS
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


/* ----------------------------------------------------------- FUNCTION_PROTOTYPES */
extern int	gsim_opcodes_init( struct gsim_t *sim );
extern int	gsim_reg_init( struct gsim_t *sim );

/* ----------------------------------------------------------- GSIM_INIT_SIM */
/* 
 * GSIM_INIT_SIM
 * 
 */
extern int gsim_init_sim( struct gsim_t *sim )
{
#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

	/* 
	 * set the default sim attributes 
	 * 
	 */
	sim->options	= GSIM_OPT_DEFAULT;

	/* 
	 * zero the pointers
	 * 
	 */
	sim->config_file	= NULL;
	sim->log_file		= NULL;
	sim->trace_file		= NULL;
	sim->obj_file		= NULL;
	sim->obj_opts		= NULL;

	/*
	 * setup the opcodes table
	 * 
	 */
	if( gsim_opcodes_init( sim ) != 0 ){ 
		GSIM_PRINT_ERROR( "GSIM_ERROR: Failed to initialize the opcode table" );
		return -1;
	}

	/* 
	 * setup the registers table
	 * 
	 */
	if( gsim_reg_init( sim ) != 0 ){ 
		GSIM_PRINT_ERROR( "GSIM_ERROR: Failed to initialize the register table" );
		return -1;
	}

	/* 
	 * default stack size 
	 * 
	 */
	sim->stack_size	= GSIM_DEFAULT_STACK_SIZE;

	/*
	 * default hardware layout 
	 * 
 	 */
	sim->partitions		= 1;
	sim->nodes		= 1;
	sim->sockets		= 1;
	sim->task_groups	= 1;
	sim->task_procs		= 1;
	sim->tasks		= 1;
	sim->icache_ways	= 8;
	sim->icache_sets	= 1024;
	sim->amo_slots		= 1024;

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;
}

/* EOF */
