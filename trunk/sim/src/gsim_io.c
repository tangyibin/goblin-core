/* 
 * 
 * _GSIM_IO_C_ 
 * 
 * GOBLIN-SIM LIBELF IO INTERFACES
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


/* -------------------------------------------------- GSIM_IO_OPEN_LOGFILE */
/* 
 * GSIM_IO_OPEN_LOGFILE
 * 
 */
extern int gsim_io_open_logfile( struct gsim_t *sim )
{
#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

	if( sim->log_file == NULL) {
		/* 
		 * use the standard output file name
		 *
	  	 */
		sim->lfile = fopen( "./gsim_log.out", "w+" );
		if( sim->lfile == NULL ){ 
			return -1;
		}
	}else{ 

		/* 
		 * use the trace file specified
		 * by the user
		 * 
		 */
		sim->lfile = fopen( sim->log_file, "w+" );
		if( sim->lfile == NULL ){
			return -1;
		}
	}


	/* 
	 * print the header
	 * 
	 */
	fprintf( sim->lfile, "===============================================================\n" );
	fprintf( sim->lfile, " Goblin-Sim Version %d.%d\n", GSIM_MAJOR_VERSION, GSIM_MINOR_VERSION );
	fprintf( sim->lfile, "===============================================================\n" );
	fprintf( sim->lfile, " Sim Configuration: \n" );
	fprintf( sim->lfile, " -- Partitions    : 0x%08x\n", sim->partitions );
	fprintf( sim->lfile, " -- Nodes         : 0x%08x\n", sim->nodes );
	fprintf( sim->lfile, " -- Sockets       : 0x%08x\n", sim->sockets );
	fprintf( sim->lfile, " -- Task Groups   : 0x%08x\n", sim->task_groups );
	fprintf( sim->lfile, " -- Task Procs    : 0x%08x\n", sim->task_procs );
	fprintf( sim->lfile, " -- Tasks         : 0x%08x\n", sim->tasks );
	fprintf( sim->lfile, " -- Total Tasks   : 0x%016llx\n", (uint64_t)(sim->partitions *
									sim->nodes *
									sim->sockets * 
									sim->task_groups *
									sim->task_procs *
									sim->tasks) );
	fprintf( sim->lfile, " -- ICACHE        : %d-Way Set Assoc; %d Sets\n", sim->icache_ways,
											sim->icache_sets );
	fprintf( sim->lfile, " -- AMO Slots     : 0x%08x\n", sim->amo_slots ); 

	if( sim->trace_file != NULL ){ 
		fprintf( sim->lfile, " -- Trace File    : %s\n", sim->trace_file ); 
	}else{
		fprintf( sim->lfile, " -- Trace File    : ./gsim_trace.out\n" ); 
	}

	fprintf( sim->lfile, " -- Config File   : %s\n", sim->config_file ); 
	fprintf( sim->lfile, " -- OBJ File      : %s %s\n", sim->obj_file, sim->obj_opts ); 
	

	fprintf( sim->lfile, "===============================================================\n" );


	fflush( sim->lfile );	

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;	
}




/* -------------------------------------------------- GSIM_IO_OPEN_TRACEFILE */
/* 
 * GSIM_IO_OPEN_TRACEFILE
 * 
 */
extern int gsim_io_open_tracefile( struct gsim_t *sim )
{
#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

	if( sim->trace_file != NULL) {
		/* 
		 * use the standard output file name
		 *
	  	 */
		sim->tfile = fopen( "./gsim_trace.out", "w+" );
		if( sim->tfile == NULL ){ 
			return -1;
		}
	}else{ 

		/* 
		 * use the trace file specified
		 * by the user
		 * 
		 */
		sim->tfile = fopen( sim->trace_file, "w+" );
		if( sim->tfile == NULL ){
			return -1;
		}
	}

	

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;	
}


/* EOF */
