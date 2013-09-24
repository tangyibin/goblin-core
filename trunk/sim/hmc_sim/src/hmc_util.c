/* 
 * _HMC_UTIL_C_
 * 
 * HYBRID MEMORY CUBE SIMULATION LIBRARY 
 * 
 * UTILITY FUNCTIONS
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hmc_sim.h"


/* ----------------------------------------------------- HMCSIM_UTIL_ZERO_PACKET */
/* 
 * HMCSIM_UTIL_ZERO_PACKET
 * 
 */
extern int hmcsim_util_zero_packet( struct hmc_queue_t *queue  )
{
	/* vars */
	uint64_t i	= 0;
	/* ---- */

	/* 
	 * sanity check 
	 * 
 	 */
	if( queue == NULL ){ 
		return -1;
	}

	for( i=0; i<HMC_MAX_UQ_PACKET; i++){
		queue->packet[i]	= 0x00ll;
	}

	queue->valid = HMC_RQST_INVALID;

	return 0;
}

/* ----------------------------------------------------- HMCSIM_UTIL_SET_MAX_BLOCKSIZE */
/* 
 * HMCSIM_UTIL_SET_MAX_BLOCKSIZE
 * See Table38 in the HMC Spec : pg 58
 * 
 */
extern int hmcsim_util_set_max_blocksize( struct hmcsim_t *hmc, uint32_t dev, uint32_t bsize )
{
	/* vars */
	uint64_t tmp = 0x00ll;
	/* ---- */

	/* 
	 * sanity check 
	 * 
	 */
	if( hmc == NULL ){ 
		return -1;
	} 

	if( dev > (hmc->num_devs-1) ){ 

		/* 
	 	 * device out of range 
		 * 
		 */
	
		return -1;
	}

	/* 
	 * decide which values to set 
	 * 
	 */
	switch( bsize )
	{
		case 32: 
			tmp = 0x0000000000000000;
			break;
		case 64:
			tmp = 0x0000000000000001;
			break;
		case 128:
		default : 
			
			tmp = 0x0000000000000002;
			break;
	}

	/* 
	 * write the register 
	 * 
 	 */
	hmc->devs[dev].regs[HMC_REG_AC_IDX].reg |= tmp;

	return 0;
}

/* ----------------------------------------------------- HMCSIM_UTIL_SET_ALL_MAX_BLOCKSIZE */
/* 
 * HMCSIM_UTIL_SET_ALL_MAX_BLOCKSIZE
 * See Table38 in the HMC Spec : pg 58
 * 
 */
extern int hmcsim_util_set_all_max_blocksize( struct hmcsim_t *hmc, uint32_t bsize )
{
	/* vars */
	uint32_t i = 0;
	/* ---- */
	
	if( hmc == NULL ){ 
		return -1;
	}

	/* 
	 * check the bounds of the block size
	 *
 	 */
	if( (bsize != 32) && 
		(bsize != 64) &&
		(bsize != 128) ){
		return -1;
	}

	for( i=0; i<hmc->num_devs; i++ ){ 
		hmcsim_util_set_max_blocksize( hmc, i, bsize );
	}
	
	return 0;
}

/* ----------------------------------------------------- HMCSIM_UTIL_GET_MAX_BLOCKSIZE */
/* 
 * HMCSIM_UTIL_GET_MAX_BLOCKSIZE
 * See Table38 in the HMC Spec : pg 58
 * 
 */
extern int hmcsim_util_get_max_blocksize( struct hmcsim_t *hmc, uint32_t dev, uint32_t *bsize )
{
	/* vars */
	uint64_t reg	= 0x00ll;
	uint64_t code	= 0x00ll;
	/* ---- */

	/* 
	 * sanity check 
	 * 
	 */
	if( hmc == NULL ){ 
		return -1;
	} 

	if( dev > (hmc->num_devs-1) ){ 

		/* 
	 	 * device out of range 
		 * 
		 */
	
		return -1;
	}

	if( bsize == NULL ){ 
		return -1;
	}

	/*
	 * retrieve the register value 
 	 * 
	 */
	reg = hmc->devs[dev].regs[HMC_REG_AC_IDX].reg;
	

	/* 
	 * get the lower four bits 
	 * 
	 */
	code = (reg & 0xF);

	/* 
	 * decode it for the standard 
	 * device initialization table
	 * 
	 */	
	switch( code )
	{
		case 0x0:
			/* 32 bytes */
			*bsize = 32;
			break;
		case 0x1:
			/* 64 bytes */
			*bsize = 64;
			break;
		case 0x2:
			/* 128 bytes */
			*bsize = 128;
			break;
		case 0x8:
			/* 32 bytes */
			*bsize = 32;
			break;
		case 0x9:
			/* 64 bytes */
			*bsize = 64;
			break;
		case 0xA:
			/* 32 bytes */
			*bsize = 32;
			break;
		case 0x3:
		case 0x4:
		case 0x5:
		case 0x6:
		case 0x7:
		case 0xB:
		case 0xC:
		case 0xD:
		case 0xE:
		case 0xF:
			/* 
	 		 * vendor specific
			 *
			 */
			break;
		default:
			break;
	}

	return 0;
}

/* EOF */
