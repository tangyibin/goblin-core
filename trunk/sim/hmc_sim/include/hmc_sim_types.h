/* 
 * _HMC_SIM_TYPES_H_
 * 
 * HYBRID MEMORY CUBE SIMULATION LIBRARY
 * 
 * HMC TYPES HEADER FILE 
 * 
 * WARNING: DO NOT INCLUDE THIS FILE DIRECTLY
 *	    ALWAYS INCLUDE THE TOP-LEVEL HEADER 
 * 
 */

#ifndef _HMC_SIM_TYPES_H_
#define _HMC_SIM_TYPES_H_


#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <sys/types.h>

/* -------------------------------------------------- ENUMERATED TYPES */
typedef enum{
	HMC_LINK_DEV_DEV,		/*! HMC-SIM: HMC_LINK_DEF_T: DEVICE TO DEVICE LINK */ 
	HMC_LINK_HOST_DEV		/*! HMC-SIM: HMC_LINK_DEF_T: HOST TO DEVICE LINK */
}hmc_link_def_t;

/* -------------------------------------------------- DATA STRUCTURES */

struct hmc_link_t{

	uint32_t id;			/*! HMC-SIM: HMC_LINK_T: LINK ID */
	uint32_t quad;			/*! HMC-SIM: HMC_LINK_T: ASSOCIATED QUADRANT */
	uint32_t src_cub;		/*! HMC-SIM: HMC_LINK_T: SOURCE CUB */
	uint32_t dest_cub;		/*! HMC-SIM: HMC_LINK_T: DESTINATION CUB */

	hmc_link_def_t	link_type;	/*! HMC-SIM: HMC_LINK_T: LINK TYPE */
};

struct hmc_dram_t{

	uint16_t elems[8];		/*! HMC-SIM: HMC_DRAM_T: DRAM ELEMENTS */

	uint32_t id;			/*! HMC-SIM: HMC_DRAM_T: DRAM ID */
};

struct hmc_bank_t{
	
	struct hmc_dram_t *drams;	/*! HMC-SIM: HMC_BANK_T: DRAMS */

	uint32_t id;			/*! HMC-SIM: HMC_BANK_T: BANK ID */
					/* 16-BYTE BANK INTERLEAVE */	
};

struct hmc_vault_t{ 

	struct hmc_bank_t *banks;	/*! HMC-SIM: HMC_VAULT_T: BANK STRUCTURE */

	uint32_t id;			/*! HMC-SIM: HMC_VAULT_T: VAULT ID */
};

struct hmc_quad_t{ 

	struct hmc_vault_t *vaults;	/*! HMC-SIM: HMC_QUAD_T: VAULT STRUCTURE */

	uint32_t 	id;		/*! HMC-SIM: HMC_QUAD_T: QUADRANT ID */
};

struct hmc_dev_t{

	struct hmc_link_t *links;	/* HMC-SIM: HMC_DEV_T: LINK STRUCTURE */
	
	struct hmc_quad_t *quads;	/*! HMC-SIM: HMC_DEV_T: QUADRANT STRUCTURE */

	uint32_t id;			/*! HMC-SIM: HMC_DEV_T: CUBE ID */
};

struct hmcsim_t{

	struct hmc_dev_t *devs;		/*! HMC-SIM: HMCSIM_T: DEVICE STRUCTURES */

	uint32_t num_devs;		/*! HMC-SIM: HMCSIM_T: NUMBER OF DEVICES */ 
	uint32_t num_links;		/*! HMC-SIM: HMCSIM_T: LINKS PER DEVICE */	
	uint32_t num_vaults;		/*! HMC-SIM: HMCSIM_T: VAULTS PER DEVICE */
	uint32_t num_banks;		/*! HMC-SIM: HMCSIM_T: BANKS PER VAULT */
	uint32_t num_drams;		/*! HMC-SIM: HMCSIM_T: DRAMS PER BANK */
	uint32_t capacity;		/*! HMC-SIM: HMCSIM_T: CAPACITY PER DEVICE */

	FILE *tfile;			/*! HMC-SIM: HMCSIM_T: TRACE FILE HANDLER */

	struct hmc_dev_t	*__ptr_devs;	
	struct hmc_quad_t	*__ptr_quads;	
	struct hmc_vault_t	*__ptr_vaults;	
	struct hmc_bank_t 	*__ptr_banks;	
	struct hmc_dram_t 	*__ptr_drams;	
	struct hmc_link_t 	*__ptr_links;	
	uint64_t 		*__ptr_stor;
};



#ifdef __cplusplus
} /* extern C */
#endif

#endif	/* _HMC_SIM_H_ */

/* EOF */
