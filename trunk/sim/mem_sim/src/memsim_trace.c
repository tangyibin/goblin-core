/* 
 * _MEMSIM_TRACE_C_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY
 * 
 * 
 * MEMSIM TRACE 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ MEMSIM_PRINT_HEADER */
/* 
 * MEMSIM_PRINT_HEADER
 * 
 */
static void memsim_print_header( struct memsim_t *msim )
{
	fprintf( msim->tfile, "%s\n", "#-----------------------------------------------------" );	
	fprintf( msim->tfile, "%s\n", "# MEM-SIM VERSION: MEMSIM_MAJOR_VERSION.MEMSIM_MINOR_VERSION" );
	fprintf( msim->tfile, "%s\n", "#-----------------------------------------------------" );	
	fprintf( msim->tfile, "%s%d\n", "# GROUP SLOTS     : ", msim->g_slots );
	fprintf( msim->tfile, "%s%d\n", "# SOCKET SLOTS    : ", msim->s_slots );
	fprintf( msim->tfile, "%s%d\n", "# AMO SLOTS       : ", msim->a_slots );
	fprintf( msim->tfile, "%s%d\n", "# GLOBAL SLOTS    : ", msim->ga_slots );
	fprintf( msim->tfile, "%s%d\n", "# TASK GROUPS     : ", msim->task_groups);
	fprintf( msim->tfile, "%s%d\n", "# TASK PROCS      : ", msim->task_procs);
	fprintf( msim->tfile, "%s%d\n", "# TASKS           : ", msim->tasks);
	fprintf( msim->tfile, "%s0x%016llx\n", "# OPTIONS         : ", msim->opt); 

	switch( msim->iface )
	{
		case MEMSIM_BASIC:
			fprintf( msim->tfile, "%s\n", "# IFACE           : MEMSIM_BASIC");
			break;
		case MEMSIM_HMC:
			fprintf( msim->tfile, "%s\n", "# IFACE           : MEMSIM_HMC");
			break;
		default:
			fprintf( msim->tfile, "%s\n", "# IFACE           : MEMSIM_UNK");
			break;
	}

	switch( msim->alg )
	{
		case MEMSIM_SIMPLE:
			fprintf( msim->tfile, "%s\n", "# ALGO            : MEMSIM_SIMPLE");
			break;
		case MEMSIM_CACHE:
			fprintf( msim->tfile, "%s\n", "# ALGO            : MEMSIM_CACHE");
			break;
		case MEMSIM_EXP:
			fprintf( msim->tfile, "%s\n", "# ALGO            : MEMSIM_EXP");
			break;
		default:
			fprintf( msim->tfile, "%s\n", "# ALGO            : MEMSIM_UNK");
			break;
	}

	fprintf( msim->tfile, "%s\n", "#-----------------------------------------------------" );	
}

/* ------------------------------------------------ MEMSIM_TRACE_LEVEL */
/* 
 * MEMSIM_TRACE_LEVEL
 * 
 */
extern int memsim_trace_level(	struct memsim_t *msim, 
				uint32_t level )
{
	if( msim == NULL ){ 
		return MEMSIM_ERROR;
	}

	msim->tracelevel = level;	

	return MEMSIM_OK;
}

/* ------------------------------------------------ MEMSIM_TRACE_HANDLE */
/* 
 * MEMSIM_TRACE_HANDLE
 * 
 */
extern int memsim_trace_handle(	struct memsim_t *msim, 
				FILE *tfile )
{
	/* 
	 * sanity check 
	 *
	 */
	if( msim == NULL ){ 
		return MEMSIM_ERROR;
	}

	if( tfile == NULL ){ 
		return MEMSIM_ERROR;
	}

	msim->tfile	= tfile;

	memsim_print_header( msim );

	return MEMSIM_OK;
}

/* EOF */
