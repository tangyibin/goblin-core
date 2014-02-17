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
#include <inttypes.h>
#include <stdlib.h>
#include "mem_sim.h"


/* ------------------------------------------------ CONSTANTS */
const char c_MEMSIM_RD4[]		= "MEMSIM_RD4";
const char c_MEMSIM_WR4[]		= "MEMSIM_WR4";
const char c_MEMSIM_RD8[]		= "MEMSIM_RD8";
const char c_MEMSIM_WR8[]		= "MEMSIM_WR8";
const char c_MEMSIM_FENCE[]		= "MEMSIM_FENCE";
const char c_MEMSIM_UNK[]		= "MEMSIM_UNK";
const char c_MEMSIM_HMC_RD16[]		= "MEMSIM_HMC_RD16";
const char c_MEMSIM_HMC_RD32[]		= "MEMSIM_HMC_RD32";
const char c_MEMSIM_HMC_RD48[]		= "MEMSIM_HMC_RD48";
const char c_MEMSIM_HMC_RD64[]		= "MEMSIM_HMC_RD64";
const char c_MEMSIM_HMC_RD80[]		= "MEMSIM_HMC_RD80";
const char c_MEMSIM_HMC_RD96[]		= "MEMSIM_HMC_RD96";
const char c_MEMSIM_HMC_RD112[]		= "MEMSIM_HMC_RD112";
const char c_MEMSIM_HMC_RD128[]		= "MEMSIM_HMC_RD128";
const char c_MEMSIM_HMC_WR16[]		= "MEMSIM_HMC_WR16";
const char c_MEMSIM_HMC_WR32[]		= "MEMSIM_HMC_WR32";
const char c_MEMSIM_HMC_WR48[]		= "MEMSIM_HMC_WR48";
const char c_MEMSIM_HMC_WR64[]		= "MEMSIM_HMC_WR64";
const char c_MEMSIM_HMC_WR80[]		= "MEMSIM_HMC_WR80";
const char c_MEMSIM_HMC_WR96[]		= "MEMSIM_HMC_WR96";
const char c_MEMSIM_HMC_WR112[]		= "MEMSIM_HMC_WR112";
const char c_MEMSIM_HMC_WR128[]		= "MEMSIM_HMC_WR128";




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
	fflush( msim->tfile );
}

/* ------------------------------------------------ MEMSIM_TRACE_MEMBUS */
/* 
 * MEMSIM_TRACE_MEMBUS
 * 
 */
extern int memsim_trace_membus( struct memsim_t *msim, 
				struct memsim_entry_t *ent ){

	/* vars */
	uint32_t i 	= 0;
	const char *buf	= NULL;
	/* ---- */

	if( msim->tfile == NULL ){ 
		return MEMSIM_ERROR;
	}

	/* setup the buffer */
	switch( ent->rqst )
	{
		case MEMSIM_RD4:
			buf	= &c_MEMSIM_RD4[0];
			break;
		case MEMSIM_WR4:
			buf	= &c_MEMSIM_WR4[0];
			break;
		case MEMSIM_RD8:
			buf	= &c_MEMSIM_RD8[0];
			break;
		case MEMSIM_WR8:
			buf	= &c_MEMSIM_WR8[0];
			break;
		case MEMSIM_FENCE:
			buf	= &c_MEMSIM_FENCE[0];
			break;
		case MEMSIM_UNK:
			buf	= &c_MEMSIM_UNK[0];
			break;
		case MEMSIM_HMC_RD16:
			buf	= &c_MEMSIM_HMC_RD16[0];
			break;
		case MEMSIM_HMC_RD32:
			buf	= &c_MEMSIM_HMC_RD32[0];
			break;
		case MEMSIM_HMC_RD48:
			buf	= &c_MEMSIM_HMC_RD48[0];
			break;
		case MEMSIM_HMC_RD64:
			buf	= &c_MEMSIM_HMC_RD64[0];
			break;
		case MEMSIM_HMC_RD80:
			buf	= &c_MEMSIM_HMC_RD80[0];
			break;
		case MEMSIM_HMC_RD96:
			buf	= &c_MEMSIM_HMC_RD96[0];
			break;
		case MEMSIM_HMC_RD112:
			buf	= &c_MEMSIM_HMC_RD112[0];
			break;
		case MEMSIM_HMC_RD128:
			buf	= &c_MEMSIM_HMC_RD128[0];
			break;
		case MEMSIM_HMC_WR16:
			buf	= &c_MEMSIM_HMC_WR16[0];
			break;
		case MEMSIM_HMC_WR32:
			buf	= &c_MEMSIM_HMC_WR32[0];
			break;
		case MEMSIM_HMC_WR48:
			buf	= &c_MEMSIM_HMC_WR48[0];
			break;
		case MEMSIM_HMC_WR64:
			buf	= &c_MEMSIM_HMC_WR64[0];
			break;
		case MEMSIM_HMC_WR80:
			buf	= &c_MEMSIM_HMC_WR80[0];
			break;
		case MEMSIM_HMC_WR96:
			buf	= &c_MEMSIM_HMC_WR96[0];
			break;
		case MEMSIM_HMC_WR112:
			buf	= &c_MEMSIM_HMC_WR112[0];
			break;
		case MEMSIM_HMC_WR128:
			buf	= &c_MEMSIM_HMC_WR128[0];
			break;
		default:
			return MEMSIM_ERROR;
			break;
	}
	
	for( i=0; i<ent->num_tids; i++ ){ 
	
		fprintf( msim->tfile, 	"MEMSIM_TRACE : %" PRIu64
					" : MEMORY_BUS"
					" : 0x%016" PRIx64
					" : %" PRIu32
					" : %s\n", 
					msim->clock,
					ent->gconst,
					ent->tid[i],
					buf);
	}

	fflush( msim->tfile );

	return MEMSIM_OK;
}	
/* ------------------------------------------------ MEMSIM_TRACE_MEMOP */
/* 
 * MEMSIM_TRACE_MEMOP
 * 
 */
extern int memsim_trace_memop( struct memsim_t *msim, 
				struct memsim_entry_t *ent ){

	/* vars */
	uint32_t i 	= 0;
	const char *buf	= NULL;
	/* ---- */

	if( msim->tfile == NULL ){ 
		return MEMSIM_ERROR;
	}

	/* setup the buffer */
	switch( ent->rqst )
	{
		case MEMSIM_RD4:
			buf	= &c_MEMSIM_RD4[0];
			break;
		case MEMSIM_WR4:
			buf	= &c_MEMSIM_WR4[0];
			break;
		case MEMSIM_RD8:
			buf	= &c_MEMSIM_RD8[0];
			break;
		case MEMSIM_WR8:
			buf	= &c_MEMSIM_WR8[0];
			break;
		case MEMSIM_FENCE:
			buf	= &c_MEMSIM_FENCE[0];
			break;
		case MEMSIM_UNK:
			buf	= &c_MEMSIM_UNK[0];
			break;
		case MEMSIM_HMC_RD16:
			buf	= &c_MEMSIM_HMC_RD16[0];
			break;
		case MEMSIM_HMC_RD32:
			buf	= &c_MEMSIM_HMC_RD32[0];
			break;
		case MEMSIM_HMC_RD48:
			buf	= &c_MEMSIM_HMC_RD48[0];
			break;
		case MEMSIM_HMC_RD64:
			buf	= &c_MEMSIM_HMC_RD64[0];
			break;
		case MEMSIM_HMC_RD80:
			buf	= &c_MEMSIM_HMC_RD80[0];
			break;
		case MEMSIM_HMC_RD96:
			buf	= &c_MEMSIM_HMC_RD96[0];
			break;
		case MEMSIM_HMC_RD112:
			buf	= &c_MEMSIM_HMC_RD112[0];
			break;
		case MEMSIM_HMC_RD128:
			buf	= &c_MEMSIM_HMC_RD128[0];
			break;
		case MEMSIM_HMC_WR16:
			buf	= &c_MEMSIM_HMC_WR16[0];
			break;
		case MEMSIM_HMC_WR32:
			buf	= &c_MEMSIM_HMC_WR32[0];
			break;
		case MEMSIM_HMC_WR48:
			buf	= &c_MEMSIM_HMC_WR48[0];
			break;
		case MEMSIM_HMC_WR64:
			buf	= &c_MEMSIM_HMC_WR64[0];
			break;
		case MEMSIM_HMC_WR80:
			buf	= &c_MEMSIM_HMC_WR80[0];
			break;
		case MEMSIM_HMC_WR96:
			buf	= &c_MEMSIM_HMC_WR96[0];
			break;
		case MEMSIM_HMC_WR112:
			buf	= &c_MEMSIM_HMC_WR112[0];
			break;
		case MEMSIM_HMC_WR128:
			buf	= &c_MEMSIM_HMC_WR128[0];
			break;
		default:
			return MEMSIM_ERROR;
			break;
	}
	
	for( i=0; i<ent->num_tids; i++ ){ 
	
		fprintf( msim->tfile, 	"MEMSIM_TRACE : %" PRIu64
					" : MEMORY_OP"
					" : 0x%016" PRIx64
					" : %" PRIu32
					" : %s\n", 
					msim->clock,
					ent->gconst,
					ent->tid[i],
					buf);
	}

	fflush( msim->tfile );

	return MEMSIM_OK;
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
