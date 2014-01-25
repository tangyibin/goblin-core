/* 
 * _MEM_SIM_TYPES_H_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY 
 * 
 * MEM SIM TYPES HEADER FILE
 * 
 * WARNING: DO NOT INCLUDE THIS FILE DIRECTLY
 *          ALWAYS INCLUDE THE TOP-LEVEL HEADER 
 * 
 */

#ifndef _MEM_SIM_TYPES_H_
#define _MEM_SIM_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include "mem_sim_macros.h"


/* ---------------------------------------------- ENUMERATED TYPES */
typedef enum{
	MEMSIM_BASIC,
	MEMSIM_HMC
}memsim_iface_t;

/* ---------------------------------------------- LOCAL MACROS */
#define	MEMSIM_AMO	0x0000000000000001
#define	MEMSIM_GA	0x0000000000000002

/* ---------------------------------------------- STRUCT TYPES */
struct memsim_entry_t{
	uint64_t buf[2];		/*! MEM-SIM: MEMSIM_ENTRY_T: BUFFER */
	uint64_t gconst;		/*! MEM-SIM: MEMSIM_ENTRY_T: GCONST */
	uint32_t rqst;			/*! MEM-SIM: MEMSIM_ENTRY_T: REQUEST TYPE */
	uint32_t valid;			/*! MEM-SIM: MEMSIM_ENTRY_T: VALID BIT */
};

struct memsim_slot_t{ 
	struct memsim_entry_t *entry;	/*! MEM-SIM: MEMSIM_SLOT_T: ENTRIES */
	uint32_t num_slots;		/*! MEM-SIM: MEMSIM_SLOT_T: NUMBER OF SLOTS */
	uint32_t id;			/*! MEM-SIM: MEMSIM_SLOT_T: ID */
};

struct memsim_t{ 

	uint32_t g_slots;		/*! MEM-SIM: MEMSIM_T: NUMBER OF TASK GROUP SLOTS */
	uint32_t s_slots;		/*! MEM-SIM: MEMSIM_T: NUMBER OF SOCKET SLOTS */
	uint32_t a_slots;		/*! MEM-SIM: MEMSIM_T: NUMBER OF SLOTS DEDICATED TO AMO */
	uint32_t ga_slots;		/*! MEM-SIM: MEMSIM_T: NUMBER OF GLOBAL ADDRESS SLOTS */

	memsim_iface_t iface;		/*! MEM-SIM: MEMSIM_T: MEMORY INTERFACE TYPE */

	uint32_t task_groups;		/*! MEM-SIM: MEMSIM_T: NUMBER OF TASK GROUPS */
	uint32_t task_procs;		/*! MEM-SIM: MEMSIM_T: NUMBER OF TASK PROCS */
	uint32_t tasks;			/*! MEM-SIM: MEMSIM_T: NUMBER OF TASKS */

	FILE *tfile;			/*! MEM-SIM: MEMSIM_T: TRACE FILE HANDLER */
	uint32_t tracelevel;		/*! MEM-SIM: MEMSIM_T: TRACELVEL */

	uint64_t opt;			/*! MEM-SIM: MEMSIM_T: RUNTIME OPTIONS */

	struct memsim_slot_t *group;	/*! MEM-SIM: MEMSIM_T: GROUP SLOT STRUCTURES */
	struct memsim_slot_t *socket;	/*! MEM-SIM: MEMSIM_T: SOCKET SLOT STRUCTURES */
	struct memsim_slot_t *amo;	/*! MEM-SIM: MEMSIM_T: AMO SLOT STRUCTURES */
	struct memsim_slot_t *global;	/*! MEM-SIM: MEMSIM_T: AMO SLOT STRUCTURES */

	struct memsim_slot_t *__ptr_slots;
	struct memsim_entry_t *__ptr_entry;
};

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _MEM_SIM_TYPES_H_ */

/* EOF */
