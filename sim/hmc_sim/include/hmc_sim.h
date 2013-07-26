/* 
 * _HMC_SIM_H_
 * 
 * HYBRID MEMORY CUBE SIMULATION LIBRARY
 * 
 * MAIN HEADER FILE 
 * 
 */

#ifndef _HMC_SIM_H_
#define _HMC_SIM_H_


#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <sys/types.h>
#include "hmc_sim_types.h"
#include "hmc_sim_macros.h"

/* -------------------------------------------- FUNCTION PROTOTYPES */
extern int	hcmsim_init(	struct hmcsim_t *hmc, 
				uint32_t num_devs, 
				uint32_t num_links, 
				uint32_t num_vaults, 
				uint32_t num_banks, 
				uint32_t num_drams, 
				uint32_t capacity );

#ifdef __cplusplus
} /* extern C */
#endif

#endif	/* _HMC_SIM_H_ */

/* EOF */
