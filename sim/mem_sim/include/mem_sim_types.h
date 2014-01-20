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
#include <sys/types.h>
#include "mem_sim_macros.h"


/* ---------------------------------------------- ENUMERATED TYPES */
typdef enum{
	MEMSIM_BASIC,
	MEMSIM_HMC
}memsim_iface_t;

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _MEM_SIM_TYPES_H_ */

/* EOF */
