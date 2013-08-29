/* 
 * _HMC_CONFIG_DEVS_C_
 * 
 * HYBRID MEMORY CUBE SIMULATION LIBRARY 
 * 
 * HMC DEVICE CONFIGURATION FUNCTIONS
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hmc_sim.h"

/* ----------------------------------------------------- HMCSIM_CONFIG_DEV_REG */
/* 
 * HMCSIM_CONFIG_DEV_REG
 * 
 */
static int	hmcsim_config_dev_reg( struct hmcsim_t *hmc, uint32_t dev )
{

	hmc->devs[dev].regs[HMC_REG_EDR0_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_EDR0_IDX].phy_idx	= HMC_REG_EDR0; 
	hmc->devs[dev].regs[HMC_REG_EDR0_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_EDR1_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_EDR1_IDX].phy_idx	= HMC_REG_EDR1; 
	hmc->devs[dev].regs[HMC_REG_EDR1_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_EDR2_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_EDR2_IDX].phy_idx	= HMC_REG_EDR2; 
	hmc->devs[dev].regs[HMC_REG_EDR2_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_EDR3_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_EDR3_IDX].phy_idx	= HMC_REG_EDR3; 
	hmc->devs[dev].regs[HMC_REG_EDR3_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_ERR_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_ERR_IDX].phy_idx	= HMC_REG_ERR; 
	hmc->devs[dev].regs[HMC_REG_ERR_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_GC_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_GC_IDX].phy_idx	= HMC_REG_GC; 
	hmc->devs[dev].regs[HMC_REG_GC_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_LC0_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_LC0_IDX].phy_idx	= HMC_REG_LC0; 
	hmc->devs[dev].regs[HMC_REG_LC0_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_LC1_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_LC1_IDX].phy_idx	= HMC_REG_LC1; 
	hmc->devs[dev].regs[HMC_REG_LC1_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_LC2_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_LC2_IDX].phy_idx	= HMC_REG_LC2; 
	hmc->devs[dev].regs[HMC_REG_LC2_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_LC3_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_LC3_IDX].phy_idx	= HMC_REG_LC3; 
	hmc->devs[dev].regs[HMC_REG_LC3_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_LRLL0_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_LRLL0_IDX].phy_idx	= HMC_REG_LRLL0; 
	hmc->devs[dev].regs[HMC_REG_LRLL0_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_LRLL1_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_LRLL1_IDX].phy_idx	= HMC_REG_LRLL1; 
	hmc->devs[dev].regs[HMC_REG_LRLL1_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_LRLL2_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_LRLL2_IDX].phy_idx	= HMC_REG_LRLL2; 
	hmc->devs[dev].regs[HMC_REG_LRLL2_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_LRLL3_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_LRLL3_IDX].phy_idx	= HMC_REG_LRLL3; 
	hmc->devs[dev].regs[HMC_REG_LRLL3_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_LR0_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_LR0_IDX].phy_idx	= HMC_REG_LR0; 
	hmc->devs[dev].regs[HMC_REG_LR0_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_LR1_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_LR1_IDX].phy_idx	= HMC_REG_LR1; 
	hmc->devs[dev].regs[HMC_REG_LR1_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_LR2_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_LR2_IDX].phy_idx	= HMC_REG_LR2; 
	hmc->devs[dev].regs[HMC_REG_LR2_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_LR3_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_LR3_IDX].phy_idx	= HMC_REG_LR3; 
	hmc->devs[dev].regs[HMC_REG_LR3_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_IBTC0_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_IBTC0_IDX].phy_idx	= HMC_REG_IBTC0; 
	hmc->devs[dev].regs[HMC_REG_IBTC0_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_IBTC1_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_IBTC1_IDX].phy_idx	= HMC_REG_IBTC1; 
	hmc->devs[dev].regs[HMC_REG_IBTC1_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_IBTC2_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_IBTC2_IDX].phy_idx	= HMC_REG_IBTC2; 
	hmc->devs[dev].regs[HMC_REG_IBTC2_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_IBTC3_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_IBTC3_IDX].phy_idx	= HMC_REG_IBTC3; 
	hmc->devs[dev].regs[HMC_REG_IBTC3_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_AC_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_AC_IDX].phy_idx	= HMC_REG_AC; 
	hmc->devs[dev].regs[HMC_REG_AC_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_VCR_IDX].type	= HMC_RW; 
	hmc->devs[dev].regs[HMC_REG_VCR_IDX].phy_idx	= HMC_REG_VCR; 
	hmc->devs[dev].regs[HMC_REG_VCR_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_FEAT_IDX].type	= HMC_RO;
	hmc->devs[dev].regs[HMC_REG_FEAT_IDX].phy_idx	= HMC_REG_FEAT; 
	hmc->devs[dev].regs[HMC_REG_FEAT_IDX].reg	= 0x00ll;
	
	hmc->devs[dev].regs[HMC_REG_RVID_IDX].type	= HMC_RO;
	hmc->devs[dev].regs[HMC_REG_RVID_IDX].phy_idx	= HMC_REG_RVID; 
	hmc->devs[dev].regs[HMC_REG_RVID_IDX].reg	= 0x00ll;
	

	return 0;	
}


/* ----------------------------------------------------- HMCSIM_CONFIG_DEVICES */
/* 
 * HMCSIM_CONFIG_DEVICES
 * 
 */
extern int	hmcsim_config_devices( struct hmcsim_t *hmc )
{
	/* vars */
	uint32_t i		= 0;
	uint32_t j		= 0;
	uint32_t k		= 0;
	uint32_t x		= 0;
	uint32_t y		= 0;
	uint32_t a		= 0;
	uint32_t cur_quad	= 0;
	uint32_t cur_vault	= 0;
	uint32_t cur_bank	= 0;
	uint32_t cur_dram	= 0;
	uint32_t cur_link	= 0;
	uint32_t cur_queue	= 0;
	uint32_t cur_xbar	= 0;
	//uint32_t cur_stor	= 0;
	/* ---- */

	/* 
	 * sanity check 
	 * 
	 */
	if( hmc == NULL ){ 
		return -1;
	}

	/* 
	 * set the device pointers
	 * 
	 */
	hmc->devs	= hmc->__ptr_devs;		

	/* 
	 * zero the sequence number
	 * 
	 */
	hmc->seq 	= 0x00;

	/* 
	 * for each device, set the sub-device pointers
	 * 
	 */

	for( i=0; i<hmc->num_devs; i++ ){

		/* 
		 * set the id 
		 *
		 */
		hmc->devs[i].id	= i;
		
		/* 
	 	 * zero the sequence number
		 * 
		 */
		hmc->devs[i].seq = 0x00;

		/* 
	 	 * config the register file 
		 * 
		 */
		hmcsim_config_dev_reg( hmc, i );

		/* 
	 	 * xbars on each device
	 	 * 
		 */
		hmc->devs[i].xbar		= &(hmc->__ptr_xbars[i]);

		hmc->devs[i].xbar->xbar_rqst	= &(hmc->__ptr_xbar_rqst[cur_xbar]);
		hmc->devs[i].xbar->xbar_rsp	= &(hmc->__ptr_xbar_rsp[cur_xbar]);

		/* 
		 * set all the valid bits
		 *
	 	 */
		for( a=0; a<hmc->xbar_depth; a++ ){
			hmc->devs[i].xbar->xbar_rqst[a].valid	= 0x00000000;
			hmc->devs[i].xbar->xbar_rsp[a].valid	= 0x00000000;
		}

		cur_xbar += hmc->xbar_depth;

		/* 
		 * links on each device
		 *
		 */
		hmc->devs[i].links	= &(hmc->__ptr_links[cur_link]);

		for( j=0; j<hmc->num_links; j++ ){

			/* 
			 * set the id 
			 *
			 */
			hmc->devs[i].links[j].id	= j;

			/* 
			 * set the type and cubs 
			 * by default, everyone connects to the host
			 *
			 */	
			hmc->devs[i].links[j].type	= HMC_LINK_HOST_DEV;
			hmc->devs[i].links[j].src_cub	= 0;
			hmc->devs[i].links[j].src_cub	= i;
		
			/* 
			 * set the associated quad
			 *
			 */
			if( hmc->num_links == 4 ){ 

				/* 
				 * one to one relationship 
				 * 
				 */
				hmc->devs[i].links[j].quad = j;

			}else {
				/* 
				 * two to one relationship
				 * 
			 	 */

				switch( j )
				{	
					case 0:
					case 1:
						hmc->devs[i].links[j].quad = 0;
						break;
					case 2:
					case 3:
						hmc->devs[i].links[j].quad = 1;
						break;
					case 4:
					case 5:
						hmc->devs[i].links[j].quad = 2;
						break;
					case 6:
					case 7:
						hmc->devs[i].links[j].quad = 3;
						break;
					default:
						hmc->devs[i].links[j].quad = 0;
						break;
							
				}
			}

		}

		cur_link += hmc->num_links;

		/* 
		 * quads on each device
		 * 
		 */
		hmc->devs[i].quads	= &(hmc->__ptr_quads[cur_quad]);

		for( j=0; j<4; j++ ){ 

			/* 
			 * set the id 
			 *
			 */
			hmc->devs[i].quads[j].id	= j;

			/* 
			 * vaults in each quad
			 *
			 */
			hmc->devs[i].quads[j].vaults	= &(hmc->__ptr_vaults[cur_vault]);

			for( k=0; k<hmc->num_vaults; k++ ){ 

				/* 
				 * set the id 
				 *
				 */
				hmc->devs[i].quads[j].vaults[k].id	= k;
	
				/* 
				 * banks in each vault
				 * 
				 */
				hmc->devs[i].quads[j].vaults[k].banks	= &(hmc->__ptr_banks[cur_bank]);

				/* 
				 * request and response queues 
				 * 
				 */
				hmc->devs[i].quads[j].vaults[k].rqst_queue	= &(hmc->__ptr_vault_rqst[cur_queue]);
				hmc->devs[i].quads[j].vaults[k].rsp_queue	= &(hmc->__ptr_vault_rsp[cur_queue]);
			
				/* 
				 * clear the valid bits
				 * 
				 */	
				for( a=0; a<hmc->queue_depth; a++ ){
					hmc->devs[i].quads[j].vaults[k].rqst_queue[a].valid	= 0x00000000;
					hmc->devs[i].quads[j].vaults[k].rsp_queue[a].valid	= 0x00000000;
				}
				
				for( x=0; x<hmc->num_banks; x++ ){ 

					/* 
					 * set the id 
					 *
					 */
					hmc->devs[i].quads[j].vaults[k].banks[x].id	= x;

					/* 
					 * drams in each bank
					 * 
					 */
					hmc->devs[i].quads[j].vaults[k].banks[x].drams = 
									&(hmc->__ptr_drams[cur_dram]);	

					for( y=0; y<hmc->num_drams; y++ ){ 
			
						/* 
						 * set the id
						 *
						 */
						hmc->devs[i].quads[j].vaults[k].banks[x].drams[y].id = y;
					}

					cur_dram += hmc->num_drams;

				}
			
				cur_bank += hmc->num_banks; 

			}
	
			cur_queue += hmc->queue_depth;	
			cur_vault += hmc->num_vaults;

		}
	
		cur_quad+=hmc->num_quads;
	}	

	return 0;
}

/* EOF */
