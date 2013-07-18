/*
 * _GOBLIN_SIM_H_
 * 
 * GOBLIN-SIM MAIN HEADER FILE 
 */


#ifndef	_GOBLIN_SIM_H_
#define _GOBLIN_SIM_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <sys/types.h>
#include "goblin_sim_types.h"
#include "goblin_sim_macros.h"

/* --------------------------------------------- DATA STRUCTURES */

/* --------------------------------------------- FUNCTION PROTOTYPES */

extern void	gsim_free( void *ptr );
extern void 	*gsim_malloc( size_t sz );

extern int	gsim_config_read( struct gsim_t *sim );

extern int	gsim_disass(	uint64_t *inst, 
				uint32_t *l_r0, 
				uint32_t *l_r1, 
				uint32_t *l_r2, 
				uint32_t *l_opc, 
				uint32_t *l_ctr, 
				uint32_t *l_ctr_vec, 
				uint32_t *l_ctr_v0, 
				uint32_t *l_ctr_v1, 
				uint32_t *l_ctr_brk, 
				uint32_t *l_ctr_imm8, 
				uint32_t *l_ctr_imm4, 
				int32_t  *l_imm4, 
				int64_t  *l_imm8, 
				uint32_t *u_r0,
				uint32_t *u_r1, 
				uint32_t *u_r2, 
				uint32_t *u_opc, 
				uint32_t *u_ctr, 
				uint32_t *u_ctr_vec, 
				uint32_t *u_ctr_v0, 
				uint32_t *u_ctr_v1, 
				uint32_t *u_ctr_brk, 
				uint32_t *u_ctr_imm8, 
				uint32_t *u_ctr_imm4, 
				int32_t  *u_imm4, 
				int64_t  *u_imm8 );

extern int	gsim_inst_validate( 	struct gsim_t *sim, 
					uint32_t r0, 
					uint32_t r1, 
					uint32_t r2, 
					uint32_t opc, 
					uint32_t ctr, 
					uint32_t ctr_vec, 
					uint32_t ctr_v0, 
					uint32_t ctr_v1, 
					uint32_t ctr_brk, 
					uint32_t ctr_imm4, 
					uint32_t ctr_imm8, 
					int32_t  imm4, 
					int64_t  imm8 );

#ifdef __cplusplus
} /* extern C */
#endif

#endif	/* _GOBLIN_SIM_H_ */

/* EOF */
