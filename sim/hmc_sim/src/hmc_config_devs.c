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
	uint32_t cur_quad	= 0;
	uint32_t cur_vault	= 0;
	uint32_t cur_bank	= 0;
	uint32_t cur_dram	= 0;
	uint32_t cur_link	= 0;
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
		 * clear the valid bit
		 * 
		 */
		hmc->devs[i].valid = 0;

		/* 
	 	 * zero the sequence number
		 * 
		 */
		hmc->devs[i].seq = 0x00;

		/* 
		 * clear the message buffers
		 * 
		 */
		memset( hmc->devs[i].rqst_packet, 0, sizeof( uint64_t ) * 18 );
		memset( hmc->devs[i].response_packet, 0, sizeof( uint64_t ) * 18 );

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
		
			cur_vault += hmc->num_vaults;

		}
	
		cur_quad+=4;
	}	

	return 0;
}

/* EOF */
