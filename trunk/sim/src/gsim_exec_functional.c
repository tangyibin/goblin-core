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


/* -------------------------------------------------- FUNCTION PROTOTYPES */
extern int gsim_clock( struct gsim_t *sim );

extern int gsim_exec_functional_inst( 	struct gsim_t *sim, 
					struct gsim_task_unit_t *task, 
					uint32_t l_r0,
					uint32_t l_r1,
					uint32_t l_r2,
					uint32_t l_opc,
					uint32_t l_ctr,
					uint32_t l_ctr_vec,
					uint32_t l_ctr_v0,
					uint32_t l_ctr_v1,
					uint32_t l_ctr_brk,
					uint32_t l_ctr_imm8,
					uint32_t l_ctr_imm4,
					int32_t  l_imm4,
					int64_t  l_imm8 );


/* -------------------------------------------------- GSIM_EXEC_FUNCTIONAL_TASK */
/* 
 * GSIM_EXEC_FUNCTIONAL_TASK
 * 
 */
static int gsim_exec_functional_task( 	struct gsim_t *sim, 
					struct gsim_task_unit_t *task )
{
	/* vars */
	uint64_t ip		= 0x00ll;
	uint64_t inst		= 0x00ll;
	uint32_t l_r0		= 0x00;
	uint32_t l_r1		= 0x00;
	uint32_t l_r2		= 0x00;
	uint32_t l_opc		= 0x00;
	uint32_t l_ctr		= 0x00;
	uint32_t l_ctr_vec	= 0x00;
	uint32_t l_ctr_v0	= 0x00;
	uint32_t l_ctr_v1	= 0x00;
	uint32_t l_ctr_brk	= 0x00;
	uint32_t l_ctr_imm8	= 0x00;
	uint32_t l_ctr_imm4	= 0x00;
	int32_t  l_imm4		= 0x00;
	int64_t  l_imm8		= 0x00ll;
	uint32_t u_r0		= 0x00;
	uint32_t u_r1		= 0x00;
	uint32_t u_r2		= 0x00;
	uint32_t u_opc		= 0x00;
	uint32_t u_ctr		= 0x00;
	uint32_t u_ctr_vec	= 0x00;
	uint32_t u_ctr_v0	= 0x00;
	uint32_t u_ctr_v1	= 0x00;
	uint32_t u_ctr_brk	= 0x00;
	uint32_t u_ctr_imm8	= 0x00;
	uint32_t u_ctr_imm4	= 0x00;
	int32_t  u_imm4		= 0x00;
	int64_t  u_imm8		= 0x00ll;
	/* ---- */

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif
	/* 
	 * crack the instruction 
	 * 
	 */
	gsim_disass( 	&(task->reg[0x30]),
                        &l_r0,
                        &l_r1,
                        &l_r2,
                        &l_opc,
                        &l_ctr,
                        &l_ctr_vec,
                        &l_ctr_v0,
                        &l_ctr_v1,
                        &l_ctr_brk,
                        &l_ctr_imm8,
                        &l_ctr_imm4,
                        &l_imm4,
                        &l_imm8,
                        &u_r0,
                        &u_r1,
                        &u_r2,
                        &u_opc,
                        &u_ctr,
                        &u_ctr_vec,
                        &u_ctr_v0,
                        &u_ctr_v1,
                        &u_ctr_brk,
                        &u_ctr_imm8,
                        &u_ctr_imm4,
                        &u_imm4,
                        &u_imm8 );

	/* 
	 * determine whether we execute the uppor or lower payload
	 * 
	 */
	if( task->ul == 0 ){ 
		/* execute the lower instruction */
		gsim_exec_functional_inst( 	sim, 
						task, 
						l_r0,
                        			l_r1,
                        			l_r2,
                    				l_opc,
                        			l_ctr,
                        			l_ctr_vec,
                        			l_ctr_v0,
                        			l_ctr_v1,
                        			l_ctr_brk,
                        			l_ctr_imm8,
                        			l_ctr_imm4,
                        			l_imm4,
                        			l_imm8 );

	}else{ 
		/* execute the upper instruction */
		gsim_exec_functional_inst( 	sim, 
						task, 
						u_r0,
                        			u_r1,
                        			u_r2,
                    				u_opc,
                        			u_ctr,
                        			u_ctr_vec,
                        			u_ctr_v0,
                        			u_ctr_v1,
                        			u_ctr_brk,
                        			u_ctr_imm8,
                        			u_ctr_imm4,
                        			u_imm4,
                        			u_imm8 );
	} 

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;
}

/* -------------------------------------------------- GSIM_EXEC_FUNCTIONAL_UNIT */
/* 
 * GSIM_EXEC_FUNCTIONAL_UNIT
 * 
 */
static int gsim_exec_funtional_unit( 	struct gsim_t *sim, 
					uint32_t partition, 
					uint32_t node, 
					uint32_t socket, 
					uint32_t task_group, 
					uint32_t task_proc ) 
{
	/* vars */
	struct gsim_task_proc_t *proc	= NULL;
	struct gsim_task_unit_t *task	= NULL;
	int rtn				= 0;
	/* ---- */

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

	/* 
	 * resolve the correct hardware unit 
	 * 
	 */
	proc	= &(sim->hw->partitions[partition].nodes[node].sockets[socket].task_groups[task_group].task_procs[task_proc]);

	/* 
	 * determine if the proc is active
	 * 
 	 */
	if( ( proc->state & GSIM_PROC_STATE_ENABLED) == 0 ) { 
		/* 
	 	 * not enabled, log this and return 
		 * 
	 	 */
		rtn = 0;
		goto proc_fini;
	}

	/* 
	 * if we got here, we are enabled
	 * go get the respective task 
	 * 
	 */
	task = &(proc->tasks[proc->cur]);	

	/*
	 * execute an instrution for the given task 
	 * 
	 */
	rtn = gsim_exec_functional_task( 	sim, 
						task );

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif

proc_fini:
	return rtn;	
}
						
/* -------------------------------------------------- GSIM_EXEC_FUNCTIONAL */
/* 
 * GSIM_EXEC_FUNCTIONAL
 * 
 */
extern int gsim_exec_functional( struct gsim_t *sim )
{
	/* vars */
	uint32_t i,j,k	= 0;
	uint32_t a,b	= 0;
	int S_UNITS	= (sim->task_groups * sim->task_procs * sim->tasks );
	int T_UNITS	= (sim->sockets * sim->nodes * sim->partitions)*S_UNITS;
	/* ---- */

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

	/* 
	 * verify the object file
	 * 
	 */

	/* 
	 * load the object file into memory 
	 * 
	 */	

	/* 
	 * init the args & task units 
	 * 
	 */

	/* 
	 * decide at what degree we define parallelism 
	 * this is setup in order to optimize the parallelism 
	 * on the simulation platform 
	 * 
 	 */
	if( T_UNITS > 2048 ){ 
		/* parallelize at the node level */
#pragma omp parallel shared( sim )
{
		for( i=0; i<sim->partitions; i++ ){ 
			#pragma omp for
			for( j=0; j<sim->nodes; j++ ){ 
				for( k=0; k<sim->sockets; k++ ){ 
					for( a=0; a<sim->task_groups; a++ ){ 
						for( b=0; b<sim->task_procs; b++ ){ 
							/* 
							 * compute the taask loaded
							 * into the current task_proc
							 */
						}
					}
				}
			}
			
			/* clock the sim */
			#pragma omp barrier	
			#pragma omp single
			{
				gsim_clock( sim );
			}
		}
}
	}else if( T_UNITS > 1024 ){ 
		/* parallelize at the socket level */
#pragma omp parallel shared( sim )
{
		for( i=0; i<sim->partitions; i++ ){ 
			for( j=0; j<sim->nodes; j++ ){ 
				#pragma omp for
				for( k=0; k<sim->sockets; k++ ){ 
					for( a=0; a<sim->task_groups; a++ ){ 
						for( b=0; b<sim->task_procs; b++ ){ 
							/* 
							 * compute the taask loaded
							 * into the current task_proc
							 */
						}
					}
				}
			}
			
			/* clock the sim */
			#pragma omp barrier	
			#pragma omp single
			{
				gsim_clock( sim );
			}
		}
}
	}else if( T_UNITS > 512 ){ 
		/* parallelize at the group level */
#pragma omp parallel shared( sim )
{
		for( i=0; i<sim->partitions; i++ ){ 
			for( j=0; j<sim->nodes; j++ ){ 
				for( k=0; k<sim->sockets; k++ ){ 
					#pragma omp for
					for( a=0; a<sim->task_groups; a++ ){ 
						for( b=0; b<sim->task_procs; b++ ){ 
							/* 
							 * compute the taask loaded
							 * into the current task_proc
							 */
						}
					}
				}
			}
			
			/* clock the sim */
			#pragma omp barrier	
			#pragma omp single
			{
				gsim_clock( sim );
			}
		}
}
	}else{ 
		/* parallelize at the proc level */
#pragma omp parallel shared( sim )
{
		for( i=0; i<sim->partitions; i++ ){ 
			for( j=0; j<sim->nodes; j++ ){ 
				for( k=0; k<sim->sockets; k++ ){ 
					for( a=0; a<sim->task_groups; a++ ){ 
						#pragma omp for
						for( b=0; b<sim->task_procs; b++ ){ 
							/* 
							 * compute the taask loaded
							 * into the current task_proc
							 */
						}
					}
				}
			}
			
			/* clock the sim */
			#pragma omp barrier	
			#pragma omp single
			{
				gsim_clock( sim );
			}
		}
}
	}

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;	
}


/* EOF */
