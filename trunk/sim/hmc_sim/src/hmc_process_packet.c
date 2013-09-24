/* 
 * _HMC_PROCESS_PACKET_C_
 * 
 * HYBRID MEMORY CUBE SIMULATION LIBRARY 
 * 
 * HMC PACKET PROCESSORS FOR MEM OPS
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hmc_sim.h"

/* ----------------------------------------------------- FUNCTION PROTOTYPES */
extern int	hmcsim_trace( struct hmcsim_t *hmc, char *str );
extern int	hmcsim_util_zero_packet( struct hmc_queue_t *queue );



/* ----------------------------------------------------- HMCSIM_PROCESS_RQST */
/* 
 * HMCSIM_PROCESS_RQST
 * 
 */
extern int	hmcsim_process_rqst( 	struct hmcsim_t *hmc, 
					uint32_t dev, 
					uint32_t quad, 
					uint32_t vault, 
					uint32_t slot )
{
	/* vars */
	struct hmc_queue_t *queue	= NULL;
	uint64_t head			= 0x00ll;
	uint64_t tail			= 0x00ll;

	uint32_t length			= 0x00;
	uint32_t cmd			= 0x00;
	uint32_t tag			= 0x00;
	uint64_t addr			= 0x00ll; 
	/* ---- */

	if( hmc == NULL ){ 
		return -1;
	}

	/* 
	 * Step 1: get the request
	 * 
	 */
	queue	= &(hmc->devs[dev].quads[quad].vaults[vault].rqst_queue[slot]);
	head	= queue->packet[0];	

	/* -- get the packet length [10:7] */
	length	= (uint32_t)((head & 0x780) >> 7 );	
	
	/* -- decide where the tail is */	
	tail	= queue->packet[ ((length*2)-1) ];

	/* 
	 * Step 2: decode it 
	 * 
 	 */
	/* -- cmd = [5:0] */
	cmd	= (uint32_t)(head & 0x3F);

	/* -- tag = [23:15] */
	tag	= (uint32_t)((head & 0xFF8000) >> 15 );	

	/* -- addr = [57:24] */
	addr	= ((head >> 24) & 0x3FFFFFFFF );

	/* 
	 * Step 3: perform the op 
	 * 
 	 */
	switch( cmd )
	{
		case 0x08:
			/* WR16 */
			break;
		case 0x09:
			/* WR32 */
			break;
		case 0x0A:
			/* WR48 */
			break;
		case 0x0B:
			/* WR64 */
			break;
		case 0x0C:
			/* WR80 */
			break;
		case 0x0D:
			/* WR96 */
			break;
		case 0x0E:
			/* WR112 */
			break;
		case 0x0F:
			/* WR128 */
			break;
		case 0x10:
			/* MD_WR */
			break;
		case 0x11:
			/* BWR */
			break;
		case 0x12:
			/* TWOADD8 */
			break;
		case 0x13:
			/* ADD16 */
			break;
		case 0x18:
			/* P_WR16 */
			break;
		case 0x19:
			/* P_WR32 */
			break;
		case 0x1A:
			/* P_WR48 */
			break;
		case 0x1B:
			/* P_WR64 */
			break;
		case 0x1C:
			/* P_WR80 */
			break;
		case 0x1D:
			/* P_WR96 */
			break;
		case 0x1E:
			/* P_WR112 */
			break;
		case 0x1F:
			/* P_WR128 */
			break;
		case 0x21:
			/* P_BWR */
			break;
		case 0x22:
			/* P2ADD8 */
			break;
		case 0x23:
			/* P_ADD16 */
			break;
		case 0x30:
			/* RD16 */
			break;
		case 0x31:
			/* RD32 */
			break;
		case 0x32:
			/* RD48 */
			break;
		case 0x33:
			/* RD64 */
			break;
		case 0x34:
			/* RD80 */
			break;
		case 0x35:
			/* RD96 */
			break;
		case 0x36:
			/* RD112 */
			break;
		case 0x37:
			/* RD128 */
			break;
		case 0x28:
			/* MD_RD */
			break;
		case 0x00:
			/* FLOW_NULL */
			break;
		case 0x01:
			/* PRET */
			break;
		case 0x02:
			/* TRET */
			break;
		case 0x03:
			/* IRTRY */
			break;
		default:
			break;
	}

	/* 
 	 * Step 4: register the response
	 * 
 	 */

	/* -- find a response slot */

	/* -- build the response */

	/* 
	 * Step 5: invalidate the request queue slot
	 * 
 	 */	
	hmcsim_util_zero_packet( queue );

	return 0;
}

/* EOF */
