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
extern int	hmcsim_init(	struct hmcsim_t *hmc, 
				uint32_t num_devs, 
				uint32_t num_links, 
				uint32_t num_vaults, 
				uint32_t queue_depth,
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

extern int      hmcsim_build_memrequest( struct hmcsim_t *hmc,
                                        uint8_t  cub,
                                        uint64_t addr,
                                        uint16_t  tag,
                                        hmc_rqst_t type,
                                        uint8_t link,
                                        uint64_t *payload,
                                        uint64_t *rqst_head,
                                        uint64_t *rqst_tail );

extern int      hmcsim_decode_memresponse(      struct hmcsim_t *hmc,
                                                uint64_t *packet,
                                                uint64_t *response_head,
                                                uint64_t *response_tail,
                                                hmc_response_t *type,
                                                uint8_t *length,
                                                uint16_t *tag,
                                                uint8_t *rtn_tag,
                                                uint8_t *src_link,
                                                uint8_t *rrp,
                                                uint8_t *frp,
                                                uint8_t *seq,
                                                uint8_t *dinv,
                                                uint8_t *errstat,
                                                uint8_t *rtc,
                                                uint32_t *crc );

extern int	hmcsim_send( struct hmcsim_t *hmc, uint64_t *packet );
extern int	hmcsim_recv( struct hmcsim_t *hmc, uint64_t *packet );


#ifdef __cplusplus
} /* extern C */
#endif

#endif	/* _HMC_SIM_H_ */

/* EOF */
