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

/*!	\fn int memsim_init( struct memsim_t *msim, 
			memsim_iface_t iface, 
			memsim_alg_t alg,
			uint32_t task_groups,
			uint32_t task_procs, 
			uint32_t tasks, 
			uint32_t g_slots, 
			uint32_t s_slots, 
			uint32_t a_slots, 
			uint32_t ga_slots, 
			uint64_t opt )
	\brief Initializes the internal MEM_SIM state with the necessary 
		hardware configuration options.  
	\param *msim is a pointer to a valid memsim structure.  Must not be null.
	\param iface is the interface type: MEMSIM_BASIC or MEMSIM_HMC
	\param alg is the coalescing algorithm: MEMSIM_SIMPLE or MEMSIM_EXP
	\param task_groups is the number of task groups on the socket
	\param task_procs is the number of task procs in a task group
	\param tasks is the number of tasks per task proc
	\param g_slots is the number of interface slots at the group interface
	\param s_slots is the number of interface slots at the socket interface
	\param a_slots is the number of interface slots at the amo interface [socket]
	\param ga_slots is the number of interface slots at the global addressing interface
	\param opt is a OR'd set of memsim options: MEMSIM_AMO, MEMSIM_GA  
	\returns 0 on success, nonzero otherwise 
*/
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

/*!	\fn int memsim_free( struct memsim_t *msim )
	\brief Frees all the internal memsim state 
	\param *msim is a pointer to a valid memsim structure.  
	\returns 0 on success, nonzero otherwise 
*/
extern int memsim_free( struct memsim_t *msim );

/*!	\fn int memsim_clock( struct memsim_t *msim )
	\brief Initiates a clock signal event for the memsim instance.
	\param *msim is a pointer to a valid memsim structure.
	\returns 0 on success, nonzero otherwise
*/
extern int memsim_clock( struct memsim_t *msim );

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _MEM_SIM_H_ */

/* EOF */
