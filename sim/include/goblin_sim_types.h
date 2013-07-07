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

	/* -- simulation data */
	uint64_t		clock;		/*! GOBLIN-SIM GLOBAL CLOCK TICK */
	struct gsim_opcodes_t	opcodes;	/*! GOBLIN-SIM OPCODES TABLE */
	struct gsim_reg_t	registers;	/*! GOBLIN-SIM REGISTER TABLE */

	/* -- software environment */
	uint64_t	stack_size;		/*! GOBLIN-SIM STACK SIZE */

	/* -- hardware layout */
	uint32_t	task_groups;		/*! GOBLIN-SIM TASK GROUPS */
	uint32_t 	task_procs;		/*! GOBLIN-SIM TASK PROCS */
	uint32_t 	tasks;			/*! GOBLIN-SIM TASKS */
};



#ifdef __cplusplus
} /* extern C */
#endif

#endif	/* _GOBLIN_SIM_TYPES_H_ */

/* EOF */
