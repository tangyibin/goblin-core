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
	uint64_t	options;

	/* -- simulation data */
	uint64_t	clock;		/*! GOBLIN-SIM GLOBAL CLOCK TICK */
	gsim_opcodes_t	opcodes;	/*! GOBLIN-SIM OPCODES */
};



#ifdef __cplusplus
} /* extern C */
#endif

#endif	/* _GOBLIN_SIM_TYPES_H_ */

/* EOF */
