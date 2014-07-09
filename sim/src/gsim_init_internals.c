/* 
 * 
 * _GSIM_INIT_INTERNALS_C_ 
 * 
 * GOBLIN-SIM INTERNAL HW INITIALIZATION
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


/* -------------------------------------------------- GSIM_HW_RESET */
/* 
 * GSIM_HW_RESET
 * 
 */
extern int gsim_hw_reset( struct gsim_t *sim )
{
	/* vars */
	uint32_t	i = 0;
	uint32_t	j = 0;
	uint32_t	k = 0;
	uint32_t	a = 0;
	uint32_t	b = 0;
	uint32_t	c = 0;
	struct gsim_task_unit_t *task	= NULL;
	/* ---- */

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

	for( i=0; i<sim->partitions; i++ ){ 

		sim->hw->partitions[i].id	= (uint16_t)(i);

		/* -- nodes */
		for( j=0; j<sim->nodes; j++ ){

			sim->hw->partitions[i].nodes[j].id	= (uint16_t)(j);

			/* -- sockets */
			for( k=0; k<sim->sockets; k++ ){ 

				sim->hw->partitions[i].nodes[j].sockets[k].id		= (uint8_t)(k);
				sim->hw->partitions[i].nodes[j].sockets[k].node		= (uint8_t)(j);
				sim->hw->partitions[i].nodes[j].sockets[k].partition	= (uint8_t)(i);

				/* -- task groups */
				for( a=0; a<sim->task_groups; a++ ){ 

					sim->hw->partitions[i].nodes[j].sockets[k].task_groups[a].id = (uint8_t)(a);
	
					/* -- task procs */
					for( b=0; b<sim->task_procs; b++ ){

						sim->hw->partitions[i].nodes[j].sockets[k].task_groups[a].task_procs[b].id = (uint8_t)(b);
					
						sim->hw->partitions[i].nodes[j].sockets[k].task_groups[a].task_procs[b].state = 
									GSIM_PROC_STATE_DISABLED;	
						sim->hw->partitions[i].nodes[j].sockets[k].task_groups[a].task_procs[b].cur = 0x0;

						/* -- tasks */
						for( c=0; c<sim->tasks; c++ ){ 
							task = &(sim->hw->partitions[i].nodes[j].sockets[k].task_groups[a].task_procs[b].tasks[c]);
							task->id	= (uint8_t)(c);
							task->ul	= 0x0;			/* lower instruction word */

							/* -- zero the register file */
							memset( task->reg, 0, sizeof( uint64_t ) * 64 );

							/* -- init the gconst reg */
							task->reg[0x38]	|= ( (uint64_t)( (uint64_t)(i)       )	& GSIM_REG_GCONST_PID );
							task->reg[0x38]	|= ( (uint64_t)( (uint64_t)(j) << 16 ) 	& GSIM_REG_GCONST_NID );
							task->reg[0x38]	|= ( (uint64_t)( (uint64_t)(k) << 32 ) 	& GSIM_REG_GCONST_SID );
							task->reg[0x38]	|= ( (uint64_t)( (uint64_t)(a) << 40 ) 	& GSIM_REG_GCONST_TG );
							task->reg[0x38]	|= ( (uint64_t)( (uint64_t)(b) << 48 ) 	& GSIM_REG_GCONST_TP );
							task->reg[0x38]	|= ( (uint64_t)( (uint64_t)(c) << 56 ) 	& GSIM_REG_GCONST_TC );
						
							/* -- TODO : init the comparitor regs */
							task->reg[0x39]	= 0x0000000000000000;
							task->reg[0x3A]	= 0x0000000000000000;
							task->reg[0x3B]	= 0x0000000000000000;
							task->reg[0x3C]	= 0x0000000000000000;
							task->reg[0x3D]	= 0x0000000000000000;
							task->reg[0x3E]	= 0x0000000000000000;

							/* -- TODO : init the exception status & mask */						
	
						} /* tasks */
					} /* task procs */
				} /* task groups & icache */
			} /* sockets */
		} /* nodes */
	} /* partitions */


#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;
}

/* -------------------------------------------------- GSIM_INIT_INTERNALS */
/* 
 * GSIM_INIT_INTERNALS
 * 
 */
extern int gsim_init_internals( struct gsim_t *sim )
{
	/* vars */
	uint32_t	i = 0;
	uint32_t	j = 0;
	uint32_t	k = 0;
	uint32_t	a = 0;
	uint32_t	b = 0;

	uint32_t	cur_node	= 0;
	uint32_t	cur_socket	= 0;
	uint32_t	cur_tg		= 0;
	uint32_t 	cur_tp		= 0;
	uint32_t 	cur_t		= 0;
	/* ---- */

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

	/* 
	 * we assume that everything is sane at this point
	 * initialize the hardware elements 
	 *
	 */

	/* -- outer hardware structure */
	sim->hw	= gsim_malloc( sizeof( struct gsim_hw_t ) );
	if( sim->hw == NULL ){ 
		GSIM_PRINT_ERROR( "GSIM_ERROR : could not allocate memory for hardware structure" );
		return -1;
	}	


	/* 
	 * init all our pointers to null 
	 * 
 	 */
	sim->hw->__ptr_partition	= NULL;
	sim->hw->__ptr_node		= NULL;
	sim->hw->__ptr_socket		= NULL;
	sim->hw->__ptr_task_group	= NULL;
	sim->hw->__ptr_task_proc	= NULL;
	sim->hw->__ptr_task		= NULL;
	sim->hw->__ptr_icache		= NULL;
	sim->hw->__ptr_hmc		= NULL;

	
	/* 
	 * allocate each memory unit 
	 *
	 */	
	/* -- partitions */
	sim->hw->__ptr_partition	= gsim_malloc( sizeof( struct gsim_partition_t ) * sim->partitions );
	if( sim->hw->__ptr_partition == NULL ){ 
		GSIM_PRINT_ERROR( "GSIM_ERROR : could not allocate memory for hardware partitions" );
		return -1;
	}

	/* -- nodes */
	sim->hw->__ptr_node		= gsim_malloc( sizeof( struct gsim_node_t ) 
							* sim->nodes
							* sim->partitions );
	if( sim->hw->__ptr_node == NULL ){ 
		GSIM_PRINT_ERROR( "GSIM_ERROR : could not allocate memory for hardware nodes" );
		gsim_free( sim->hw->__ptr_partition );
		return -1;
	}

	/* -- sockets */
	sim->hw->__ptr_socket		= gsim_malloc( sizeof( struct gsim_socket_t ) 
							* sim->sockets
							* sim->nodes
							* sim->partitions );
	if( sim->hw->__ptr_socket == NULL ){ 
		GSIM_PRINT_ERROR( "GSIM_ERROR : could not allocate memory for hardware sockets" );
		gsim_free( sim->hw->__ptr_partition );
		gsim_free( sim->hw->__ptr_node );
		return -1;
	}

	/* -- task_groups */
	sim->hw->__ptr_task_group	= gsim_malloc( sizeof( struct gsim_task_group_t ) 
							* sim->task_groups
							* sim->sockets
							* sim->nodes
							* sim->partitions );
	if( sim->hw->__ptr_task_group == NULL ){ 
		GSIM_PRINT_ERROR( "GSIM_ERROR : could not allocate memory for hardware task_groups" );
		gsim_free( sim->hw->__ptr_partition );
		gsim_free( sim->hw->__ptr_node );
		gsim_free( sim->hw->__ptr_socket );
		return -1;
	}

	/* -- task_procs */
	sim->hw->__ptr_task_proc		= gsim_malloc( sizeof( struct gsim_task_proc_t ) 
							* sim->task_procs
							* sim->task_groups
							* sim->sockets
							* sim->nodes
							* sim->partitions );
	if( sim->hw->__ptr_task_proc == NULL ){ 
		GSIM_PRINT_ERROR( "GSIM_ERROR : could not allocate memory for hardware task_procs" );
		gsim_free( sim->hw->__ptr_partition );
		gsim_free( sim->hw->__ptr_node );
		gsim_free( sim->hw->__ptr_socket );
		gsim_free( sim->hw->__ptr_task_group );
		return -1;
	}

	/* -- task_units */
	sim->hw->__ptr_task		= gsim_malloc( sizeof( struct gsim_task_unit_t ) 
							* sim->tasks
							* sim->task_procs
							* sim->task_groups
							* sim->sockets
							* sim->nodes
							* sim->partitions );
	if( sim->hw->__ptr_task == NULL ){ 
		GSIM_PRINT_ERROR( "GSIM_ERROR : could not allocate memory for hardware tasks" );
		gsim_free( sim->hw->__ptr_partition );
		gsim_free( sim->hw->__ptr_node );
		gsim_free( sim->hw->__ptr_socket );
		gsim_free( sim->hw->__ptr_task_group );
		gsim_free( sim->hw->__ptr_task_proc );
		return -1;
	}

	/* -- icache */
	sim->hw->__ptr_icache	= gsim_malloc( sizeof( struct gsim_icache_t ) 
							* sim->task_groups
							* sim->sockets
							* sim->nodes
							* sim->partitions );
	if( sim->hw->__ptr_icache == NULL ){ 
		GSIM_PRINT_ERROR( "GSIM_ERROR : could not allocate memory for hardware icache" );
		gsim_free( sim->hw->__ptr_partition );
		gsim_free( sim->hw->__ptr_node );
		gsim_free( sim->hw->__ptr_socket );
		gsim_free( sim->hw->__ptr_task_group );
		gsim_free( sim->hw->__ptr_task_proc );
		gsim_free( sim->hw->__ptr_task );
		return -1;
	}

	/* -- hmc */
	sim->hw->__ptr_hmc	= gsim_malloc( sizeof( struct hmcsim_t ) 
							* sim->sockets
							* sim->nodes
							* sim->partitions );
	if( sim->hw->__ptr_hmc == NULL ){ 
		GSIM_PRINT_ERROR( "GSIM_ERROR : could not allocate memory for hardware icache" );
		gsim_free( sim->hw->__ptr_partition );
		gsim_free( sim->hw->__ptr_node );
		gsim_free( sim->hw->__ptr_socket );
		gsim_free( sim->hw->__ptr_task_group );
		gsim_free( sim->hw->__ptr_task_proc );
		gsim_free( sim->hw->__ptr_task );
		gsim_free( sim->hw->__ptr_icache );
		return -1;
	}

	/* 
	 * we already have our partition pointer 
	 *
	 */
	sim->hw->partitions	= sim->hw->__ptr_partition;

	/* -- init each partiiton and descend into each unit */
	for( i=0; i<sim->partitions; i++ ){ 

		sim->hw->partitions[ i ].nodes	= &(sim->hw->__ptr_node[ cur_node ]);

		/* -- nodes */
		for( j=0; j<sim->nodes; j++ ){

			sim->hw->partitions[ i ].nodes[ j ].sockets	= 
							&(sim->hw->__ptr_socket[ cur_socket ]);

			/* -- sockets */
			for( k=0; k<sim->sockets; k++ ){ 

				sim->hw->partitions[ i ].nodes[ j ].sockets[ k ].task_groups = 
							&(sim->hw->__ptr_task_group[ cur_tg ]);

				sim->hw->partitions[ i ].nodes[ j ].sockets[ k ].hmc =
							&(sim->hw->__ptr_hmc[ cur_tg ]);
				/*
				 * init the hmc instance 
	 			 *
				 */
				if( hmcsim_init( sim->hw->partitions[ i ].nodes[ j ].sockets[ k ].hmc, 
						sim->hmc_num_devs, 
						sim->hmc_num_links, 
						sim->hmc_num_vaults, 
						sim->hmc_queue_depth, 
						sim->hmc_num_banks, 
						sim->hmc_num_drams, 
						sim->hmc_capacity, 
						sim->hmc_xbar_depth ) != 0 ){
					GSIM_PRINT_ERROR( "GSIM_ERROR : could not init the hmc devices" );
					gsim_free( sim->hw->__ptr_partition );
					gsim_free( sim->hw->__ptr_node );
					gsim_free( sim->hw->__ptr_socket );
					gsim_free( sim->hw->__ptr_task_group );
					gsim_free( sim->hw->__ptr_task_proc );
					gsim_free( sim->hw->__ptr_task );
					gsim_free( sim->hw->__ptr_icache );
					return -1;
				}	

				/* -- task groups */
				for( a=0; a<sim->task_groups; a++ ){ 

					sim->hw->partitions[ i ].nodes[ j ].sockets[ k ].task_groups[ a ].task_procs = 
								&(sim->hw->__ptr_task_proc[ cur_tp ]);
					sim->hw->partitions[ i ].nodes[ j ].sockets[ k ].task_groups[ a ].icache = 
								&(sim->hw->__ptr_icache[ cur_tp ]);

					/* -- task procs */
					for( b=0; b<sim->task_procs; b++ ){

						sim->hw->partitions[ i ].nodes[ j ].sockets[ k ].task_groups[ a ].task_procs[ b ].tasks = 
							&(sim->hw->__ptr_task[ cur_t ]);

						cur_t += sim->tasks;


					} /* task procs */

					cur_tp++;

				} /* task groups */

				cur_tg++;

			} /* sockets */
			
			cur_socket++;

		} /* nodes */
		
		cur_node++;

	} /* partitions */
		


	/* 
	 * now that everything is allocated
	 * put the hardware in reset 
	 *
	 */
	gsim_hw_reset( sim );

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;	
}


/* EOF */
