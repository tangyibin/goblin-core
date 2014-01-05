/*
 * _GOBLIN_SIM_TYPES_H_
 * 
 * GOBLIN-SIM DATA TYPES HEADER FILE 
 * 
 * WARNING: DO NOT INCLUDE THIS FILE DIRECTLY
 *          ALWAYS USE THE TOP-LEVEL HEADER: 
 *          GOBLIN_SIM.H
 * 
 */


#ifndef	_GOBLIN_SIM_TYPES_H_
#define _GOBLIN_SIM_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <sys/types.h>
#include "goblin_sim_opcodes.h"
#include "goblin_sim_macros.h"
#include "goblin_sim_hw.h"

/* --------------------------------------------- DATA STRUCTURES */
struct gsim_t{
	/* -- simulation setup */
	uint64_t	options;		/*! GOBLIN-SIM GLOBAL OPTIONS */
	char *		config_file;		/*! GOBLIN-SIM CONFIGURATION FILE NAME */
	char *		log_file;		/*! GOBLIN-SIM LOG FILE */
	char *		inst_file;		/*! GOBLIN-SIM INSTRUCTION FILE */
	char *		trace_file;		/*! GOBLIN-SIM TRACE FILE */
	char *		obj_file;		/*! GOBLIN-SIM OBJECT FILE */
	char *		obj_opts;		/*! GOBLIN-SIM OBJECT ARGV */

	/* -- file pointers */
	FILE *tfile;				/*! GOBLIN-SIM TRACE FILE HANDLE */
	FILE *lfile;				/*! GOBlIN-SIM LOG FILE HANDLE */


	/* -- simulation data */
	uint64_t		clock;		/*! GOBLIN-SIM GLOBAL CLOCK TICK */
	struct gsim_opcodes_t	opcodes;	/*! GOBLIN-SIM OPCODES TABLE */
	struct gsim_reg_t	registers;	/*! GOBLIN-SIM REGISTER TABLE */

	/* -- software environment */
	uint64_t	stack_size;		/*! GOBLIN-SIM STACK SIZE */

	/* -- hardware layout */
	uint32_t	partitions;		/*! GOBLIN-SIM NUMBER OF PARTITIONS */
	uint32_t	nodes;			/*! GOBLIN-SIM NODES PER PARTITION */
	uint32_t	sockets;		/*! GOBLIN-SIM SOCKETS PER NODE */
	uint32_t	task_groups;		/*! GOBLIN-SIM TASK GROUPS */
	uint32_t 	task_procs;		/*! GOBLIN-SIM TASK PROCS */
	uint32_t 	tasks;			/*! GOBLIN-SIM TASKS */
	uint32_t 	icache_ways;		/*! GOBLIN-SIM ICACHE WAYS */
	uint32_t	icache_sets;		/*! GOBLIN-SIM ICACHE SETS */
	uint32_t	amo_slots;		/*! GOBLIN-SIM AMO SLOTS */

	/* -- hmc layout */
	uint32_t 	hmc_num_devs;		/*! GOBLIN-SIM NUMBER OF HMC DEVICES PER SOCKET */
	uint32_t	hmc_num_links;		/*! GOBLIN-SIM NUMBER OF LINKS PER HMC DEVICE */
	uint32_t	hmc_num_vaults;		/*! GOBLIN-SIM NUMBER OF VAULTS PER HMC DEVICE */
	uint32_t 	hmc_queue_depth;	/*! GOBLIN-SIM NUMBER OF QUEUE SLOTS PER VAULT */
	uint32_t	hmc_num_banks;		/*! GOBLIN-SIM NUMBER OF BANKS PER DEVICE */
	uint32_t 	hmc_num_drams;		/*! GOBLIN-SIM NUMBER OF DRAMS PER DEVICE */
	uint32_t 	hmc_capacity;		/*! GOBLIN-SIM NUMBER OF GB PER DEVICE */
	uint32_t	hmc_xbar_depth;		/*! GOBLIN-SIM NUMBER OF QUEUE SLOTS PER LINK */

	/* -- hardware units */
	struct gsim_hw_t *hw;			/*! GOBLIN-SIM HARDWARE STRUCTURE */	
};



#ifdef __cplusplus
} /* extern C */
#endif

#endif	/* _GOBLIN_SIM_TYPES_H_ */

/* EOF */
