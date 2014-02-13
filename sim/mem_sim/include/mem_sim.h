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


/*!	\fn int memsim_rqst( struct memsim_t *msim, 
				uint64_t gconst, 
				memsim_rqst_t rqst, 
				uint64_t addr, 
				uint64_t payload0, 
				uint64_t payload1, 
				uint32_t *tid )
	\brief Initiates a memory request 
	\param *msim is a pointer to a valid memsim structure.
	\param gconst is a GC64 constant register value
	\param rqst is the request type
	\param addr is the target address for the request
	\param payload0 is an optional payload for the request [writes]
	\param payload1 is an optional payload for the request [CAS]
	\param *tid is the transaction id for a successful request
	\returns 0 on success, nonzero otherwise
*/
extern int memsim_rqst( struct memsim_t *msim, 
			uint64_t gconst,
			memsim_rqst_t rqst,
			uint64_t addr, 
			uint64_t payload0, 
			uint64_t payload1,
			uint32_t *tid );

/*!	\fn int memsim_reset( struct memsim_t *msim )
	\brief resets the target memsim instance
	\param *msim is a pointer to a valid memsim structure.
	\returns 0 on success, nonzero otherwise 
*/
extern int memsim_reset( struct memsim_t *msim );

/*!	\fn int memsim_trace_handle( struct memsim_t *msim, 
					FILE *tfile )
	\brief Sets the open file handle for internal memsim tracing
	\param *msim is a pointer to a valid memsim structure.
	\param *tfile is an open file handle
	\returns 0 on success, nonzero otherwise 
*/
extern int memsim_trace_handle( struct memsim_t *msim,
				FILE *tfile );

/*!	\fn int memsim_trace_level( struct memsim_t *msim, 
				uint32_t level )
	\brief Sets the trace level for the msim instance
	\param *msim is a pointer to a valid memsim structure.
	\param level is the designated trace level
	\returns 0 on success, nonzero otherwise
*/
extern int memsim_trace_level( struct memsim_t *msim, 
				uint32_t level );

/*!	\fn int memsim_set_hw( struct memsim_t *msim, 
				uint32_t num_links, 
				uint32_t num_lanes, 
				float gbps )
	\brief Initializes the base hardware configuration
	\param *msim is a pointer to a valid memsim structure
	\param num_links is the number of HMC links on the socket
	\param num_lanes is the number of SERDES lanes per link 
	\param gbps is the link data transfer rate in Gbps
	\returns 0 on success, nonzero otherwise 
*/
extern int memsim_set_hw( struct memsim_t *msim, 
				uint32_t num_links, 
				uint32_t num_lanes, 
				float gbps );

/*!	\fn int memsim_is_empty( struct memsim_t *msim )
	\brief Queries the msim instance and determines whether all queues
		are empty
	\param *msim is a pointer to a valid mesim structure
	\returns MEMSIM_OK on success, MEMSIM_NEMPTY otherwise
*/
extern int memsim_is_empty( struct memsim_t *msim );


/*!	\fn int memsim_query_tid( struct memsim_t *msim, uint32_t tid )
	\brief Queries the msim instance and determines whether the respective
		tid is present and valid
	\param *msim is a pointer to a valid mesim structure
	\param tid is a valid transaction ID
	\returns 1 if the tid is active and valid, 0 if the tid is not active and valid, nonzero on error
*/
extern int memsim_query_tid( struct memsim_t *msim, uint32_t tid );

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _MEM_SIM_H_ */

/* EOF */
