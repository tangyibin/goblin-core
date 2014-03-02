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

typedef enum{
	MEMSIM_SIMPLE,
	MEMSIM_CACHE,
	MEMSIM_EXP
}memsim_alg_t;

/* TODO : ADD THE AMO's */
typedef enum{
	MEMSIM_RD8,
	MEMSIM_WR8,
	MEMSIM_RD4,
	MEMSIM_WR4,
	MEMSIM_FENCE,
	MEMSIM_UNK,
	MEMSIM_HMC_RD16,
	MEMSIM_HMC_RD32,
	MEMSIM_HMC_RD48,
	MEMSIM_HMC_RD64,
	MEMSIM_HMC_RD80,
	MEMSIM_HMC_RD96,
	MEMSIM_HMC_RD112,
	MEMSIM_HMC_RD128,
	MEMSIM_HMC_WR16,
	MEMSIM_HMC_WR32,
	MEMSIM_HMC_WR48,
	MEMSIM_HMC_WR64,
	MEMSIM_HMC_WR80,
	MEMSIM_HMC_WR96,
	MEMSIM_HMC_WR112,
	MEMSIM_HMC_WR128
}memsim_rqst_t;

/* ---------------------------------------------- LOCAL MACROS */
#define	MEMSIM_AMO	0x0000000000000001
#define	MEMSIM_GA	0x0000000000000002

/* ---------------------------------------------- STRUCT TYPES */
struct memsim_entry_t{
	uint64_t buf[4];		/*! MEM-SIM: MEMSIM_ENTRY_T: BUFFER */
	uint64_t gconst;		/*! MEM-SIM: MEMSIM_ENTRY_T: GCONST */
	uint32_t valid;			/*! MEM-SIM: MEMSIM_ENTRY_T: VALID BIT */
	uint32_t tid[32];		/*! MEM-SIM: MEMSIM_ENTRY_T: TID ARRAY */
	uint32_t num_tids;		/*! MEM-SIM: MEMSIM_ENTRY_T: NUMBER OF CORRESPONDING TIDS */
	memsim_rqst_t rqst;		/*! MEM-SIM: MEMSIM_ENTRY_T: REQUEST TYPE */
};

struct memsim_line_t{
	uint8_t	valid;			/*! MEM-SIM: MEMSIM_LINE_T: CACHE VALID BIT */
	uint32_t tag;			/*! MEM-SIM: MEMSIM_LINE_T: CACHE TAG */
	uint64_t clock;			/*! MEM-SIM: MEMSIM_LINE_T: CACHE LRU CLOCK VALUE */
	uint64_t data[8];		/*! MEM-SIM: MEMSIM_LINE_T: CACHE LINE DATA BLOCK */
};

struct memsim_cache_t{
	uint8_t ways;			/*! MEM-SIM: MEMSIM_CACHE_T: CACHE WAYS */
	uint32_t sets;			/*! MEM-SIM: MEMSIM_CACHE_T: SETS */
	struct memsim_line_t *cache;	/*! MEM-SIM: MEMSIM_CACHE_T: CACHE STRUCTURE */
};

struct memsim_hw_t{ 
	uint64_t payps;			/*! MEM-SIM: MEMSIM_HW_T : MAX PAYLOADS PER SECOND */
	uint32_t num_links;		/*! MEM-SIM: MEMSIM_HW_T : NUMBER OF LINKS */
	uint32_t num_lanes;		/*! MEM-SIM: MEMSIM_HW_T : NUMBER OF LANES PER LINK */
	float gbps;			/*! MEM-SIM: MEMSIM_HW_T : SERDES RATE IN gbps */
};

struct memsim_slot_t{ 
	struct memsim_entry_t *entry;	/*! MEM-SIM: MEMSIM_SLOT_T: ENTRIES */
	uint32_t num_slots;		/*! MEM-SIM: MEMSIM_SLOT_T: NUMBER OF SLOTS */
	uint32_t id;			/*! MEM-SIM: MEMSIM_SLOT_T: ID */
};

struct memsim_tid_t{
	uint64_t gconst;		/*! MEM-SIM: MEMSIM_TID_T: GCONST ENTRY FOR THIS TID */
	uint32_t id;			/*! MEM-SIM: MEMSIM_TID_T: THE ID OF THIS TID */
	uint32_t valid;			/*! MEM-SIM: MEMSIM_TID_T: VALID BIT */	
};

struct memsim_t{ 

	uint32_t g_slots;		/*! MEM-SIM: MEMSIM_T: NUMBER OF TASK GROUP SLOTS */
	uint32_t s_slots;		/*! MEM-SIM: MEMSIM_T: NUMBER OF SOCKET SLOTS */
	uint32_t a_slots;		/*! MEM-SIM: MEMSIM_T: NUMBER OF SLOTS DEDICATED TO AMO */
	uint32_t ga_slots;		/*! MEM-SIM: MEMSIM_T: NUMBER OF GLOBAL ADDRESS SLOTS */

	memsim_iface_t iface;		/*! MEM-SIM: MEMSIM_T: MEMORY INTERFACE TYPE */
	memsim_alg_t alg;		/*! MEM-SIM: MEMSIM_T: MEMORY INTERFACE ALGORITHM */

	uint32_t task_groups;		/*! MEM-SIM: MEMSIM_T: NUMBER OF TASK GROUPS */
	uint32_t task_procs;		/*! MEM-SIM: MEMSIM_T: NUMBER OF TASK PROCS */
	uint32_t tasks;			/*! MEM-SIM: MEMSIM_T: NUMBER OF TASKS */

	uint32_t l1_cache_sets;		/*! MEM-SIM: MEMSIM_T: NUMBER OF L1 CACHE SETS */
	uint32_t l2_cache_sets;		/*! MEM-SIM: MEMSIM_T: NUMBER OF L2 CACHE SETS */
	uint32_t l3_cache_sets;		/*! MEM-SIM: MEMSIM_T: NUMBER OF L3 CACHE SETS */

	uint32_t l1_cache_ways;		/*! MEM-SIM: MEMSIM_T: NUMBER OF L1 CACHE WAYS */
	uint32_t l2_cache_ways;		/*! MEM-SIM: MEMSIM_T: NUMBER OF L2 CACHE WAYS */
	uint32_t l3_cache_ways;		/*! MEM-SIM: MEMSIM_T: NUMBER OF L3 CACHE WAYS */

	uint32_t l1_cache_size;		/*! MEM-SIM: MEMSIM_T: SIZE OF L1 CACHE */
	uint32_t l2_cache_size;		/*! MEM-SIM: MEMSIM_T: SIZE OF L2 CACHE */
	uint32_t l3_cache_size;		/*! MEM-SIM: MEMSIM_T: SIZE OF L3 CACHE */

	uint32_t num_tids;		/*! MEM-SIM: MEMSIM_T: NUMBER OF TIDS */

	FILE *tfile;			/*! MEM-SIM: MEMSIM_T: TRACE FILE HANDLER */
	uint32_t tracelevel;		/*! MEM-SIM: MEMSIM_T: TRACELVEL */

	uint64_t opt;			/*! MEM-SIM: MEMSIM_T: RUNTIME OPTIONS */

	uint64_t clock;			/*! MEM-SIM: MEMSIM_T: CLOCK */

	struct memsim_cache_t *l1;	/*! MEM-SIM: MEMSIM_T: L1 CACHE */
	struct memsim_cache_t *l2;	/*! MEM-SIM: MEMSIM_T: L2 CACHE */
	struct memsim_cache_t *l3;	/*! MEM-SIM: MEMSIM_T: L3 CACHE */

	struct memsim_slot_t *group;	/*! MEM-SIM: MEMSIM_T: GROUP SLOT STRUCTURES */
	struct memsim_slot_t *socket;	/*! MEM-SIM: MEMSIM_T: SOCKET SLOT STRUCTURES */
	struct memsim_slot_t *amo;	/*! MEM-SIM: MEMSIM_T: AMO SLOT STRUCTURES */
	struct memsim_slot_t *global;	/*! MEM-SIM: MEMSIM_T: AMO SLOT STRUCTURES */

	struct memsim_tid_t *tids;	/*! MEM-SIM: MEMSIM_T: TID HANDLERS */

	struct memsim_hw_t hw;		/*! MEM-SIM: MEMSIM_T: HARDWARE CONFIGURATION */

	struct memsim_slot_t *__ptr_slots;
	struct memsim_entry_t *__ptr_entry;
	struct memsim_tid_t *__ptr_tid;
};

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _MEM_SIM_TYPES_H_ */

/* EOF */
