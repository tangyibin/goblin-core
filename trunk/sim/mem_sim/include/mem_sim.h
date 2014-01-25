/* 
 * _MEM_SIM_H_
 * 
 * GC64 MEMORY INTERFACE SIMULATION MODULE
 * 
 * MAIN HEADER FILE 
 * 
 */

/*!	\file mem_sim.h
	\brief GoblinCore-64 Memory Interface Simulation Library Header FIle

	The MEM_SIM library is a standard C library that provides functional
	simulation support for experimenting with various memory interface
	modules in association with the GoblinCore-64 architecture.  

*/

#ifndef _MEM_SIM_H_
#define _MEM_SIM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sys/types.h>
#include "mem_sim_types.h"
#include "mem_sim_macros.h"

/* ------------------------------------------------ FUNCTION PROTOTYPES */

extern int memsim_init(	struct memsim_t *msim, 
			memsim_iface_t iface, 
			memsim_alg_t alg,
			uint32_t task_groups,
			uint32_t task_procs, 
			uint32_t tasks, 
			uint32_t g_slots, 
			uint32_t s_slots, 
			uint32_t a_slots, 
			uint32_t ga_slots, 
			uint64_t opt );
extern int memsim_free( struct memsim_t *msim );

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _MEM_SIM_H_ */

/* EOF */
