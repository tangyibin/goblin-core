/*
 * _GOBLIN_SIM_HW_H_
 * 
 * GOBLIN-SIM HARDWARE STRUCTURES HEADER FILE
 * 
 * WARNING: DO NOT INCLUDE THIS FILE DIRECTLY
 *          ALWAYS USE THE TOP-LEVEL HEADER: 
 *          GOBLIN_SIM.H
 * 
 */


#ifndef	_GOBLIN_SIM_HW_H_
#define _GOBLIN_SIM_HW_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <sys/types.h>
#include "hmc_sim.h"

/* --------------------------------------------- DATA STRUCTURES */
struct gsim_icache_t{ 
	
	/* -- id's */
	uint8_t			id;
};

struct gsim_task_unit_t{
	
	/* -- inclusive hw units */
	uint64_t		reg[64];

	/* -- id's */
	uint8_t			id;	
};

struct gsim_task_proc_t{
	
	/* -- inclusive hw units */
	struct gsim_task_unit_t *tasks;

	/* -- id's */
	uint8_t			id;	
};

struct gsim_task_group_t{
	
	/* -- inclusive hw units */
	struct gsim_task_proc_t *task_procs;
	struct gsim_icache_t 	*icache;
	
	/* -- id's */
	uint8_t			id;
};

struct gsim_socket_t{
	
	/* -- inclusive hw units */
	struct gsim_task_group_t *task_groups;
	struct hmcsim_t *hmc;
	
	/* -- id's */
	uint8_t			id;
	uint16_t		node;
	uint16_t		partition;
};

struct gsim_node_t{ 
	
	/* -- inclusive hw units */
	struct gsim_socket_t	*sockets;

	/* -- id's */
	uint16_t		id;	
};

struct gsim_partition_t{ 
	
	/* -- inclusive hw units */
	struct gsim_node_t	*nodes;

	/* -- id's */
	uint16_t		id;	
};

struct gsim_hw_t{ 
	
	/* -- inclusive hw units */
	struct gsim_partition_t	*partitions;


	/* -- pointers to aligned structures */
	struct gsim_partition_t		*__ptr_partition;
	struct gsim_node_t		*__ptr_node;
	struct gsim_socket_t		*__ptr_socket;
	struct gsim_task_group_t	*__ptr_task_group;
	struct gsim_task_proc_t		*__ptr_task_proc;
	struct gsim_task_unit_t		*__ptr_task;
	struct gsim_icache_t		*__ptr_icache;
	struct hmcsim_t			*__ptr_hmc;
};

#ifdef __cplusplus
} /* extern C */
#endif

#endif	/* _GOBLIN_SIM_HW_H_ */

/* EOF */
