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

/* -------------------------------------------------- GSIM_EXEC_FUNCTIONAL */
/* 
 * GSIM_EXEC_FUNCTIONAL
 * 
 */
extern int gsim_exec_functional( struct gsim_t *sim )
{
	/* vars */
	uint32_t i,j,k	= 0;
	uint32_t a,b,c	= 0;
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
							for( c=0; c<sim->tasks; c++ ){ 
								/* compute the task */
							}
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
							for( c=0; c<sim->tasks; c++ ){ 
								/* compute the task */
							}
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
							for( c=0; c<sim->tasks; c++ ){ 
								/* compute the task */
							}
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
	}else if( T_UNITS > 256 ) { 
		/* parallelize at the proc level */
#pragma omp parallel shared( sim )
{
		for( i=0; i<sim->partitions; i++ ){ 
			for( j=0; j<sim->nodes; j++ ){ 
				for( k=0; k<sim->sockets; k++ ){ 
					for( a=0; a<sim->task_groups; a++ ){ 
						#pragma omp for
						for( b=0; b<sim->task_procs; b++ ){ 
							for( c=0; c<sim->tasks; c++ ){ 
								/* compute the task */
							}
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
		/* parallelize at the task level */
#pragma omp parallel shared( sim )
{
		for( i=0; i<sim->partitions; i++ ){ 
			for( j=0; j<sim->nodes; j++ ){ 
				for( k=0; k<sim->sockets; k++ ){ 
					for( a=0; a<sim->task_groups; a++ ){ 
						for( b=0; b<sim->task_procs; b++ ){ 
							#pragma omp for
							for( c=0; c<sim->tasks; c++ ){ 
								/* compute the task */
							}
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
