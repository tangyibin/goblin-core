/* 
 * 
 * _GSIM_EXEC_FUNCTIONAL_INST_C_
 * 
 * GOBLIN-SIM FUNCTIONAL SIMULATION EXECUTION: INDIVIDUAL INSTRUCTIONS
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


/* -------------------------------------------------- GSIM_EXEC_FUNCTIONAL_INST */
/* 
 * GSIM_EXEC_FUNCTIONAL_INST
 * 
 */
extern int gsim_exec_functional_inst( 	struct gsim_t *sim, 
					struct gsim_task_unit_t *task, 
					uint32_t l_r0,
					uint32_t l_r1,
					uint32_t l_r2,
					uint32_t l_opc,
					uint32_t l_ctr,
					uint32_t l_ctr_vec,
					uint32_t l_ctr_v0,
					uint32_t l_ctr_v1,
					uint32_t l_ctr_brk,
					uint32_t l_ctr_imm8,
					uint32_t l_ctr_imm4,
					int32_t  l_imm4,
					int64_t  l_imm8 )
{
#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif

	return 0;
}

/* EOF */
