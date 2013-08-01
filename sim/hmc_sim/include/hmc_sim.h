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

extern int	hmcsim_free( struct hmcsim_t *hmc );

extern int	hmcsim_link_config( struct hmcsim_t *hmc, 
					uint32_t src_dev,
					uint32_t dest_dev, 
					uint32_t src_link,
					uint32_t dest_link, 
					hmc_link_def_t type );

extern int	hmcsim_trace_handle( struct hmcsim_t *hmc, FILE *tfile );
extern int	hmcsim_trace_level( struct hmcsim_t *hmc, uint32_t level );

#ifdef __cplusplus
} /* extern C */
#endif

#endif	/* _HMC_SIM_H_ */

/* EOF */
