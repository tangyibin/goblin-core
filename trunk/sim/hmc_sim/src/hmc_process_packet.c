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
extern int	hmcsim_trace_rqst( 	struct hmcsim_t *hmc, 
					char *rqst, 
					uint32_t dev, 
					uint32_t quad, 
					uint32_t vault, 
					uint32_t bank, 
					uint64_t addr1, 
					uint32_t size );
extern int	hmcsim_util_zero_packet( struct hmc_queue_t *queue );
extern int	hmcsim_util_decode_bank( struct hmcsim_t *hmc, 
					uint32_t dev, 
					uint32_t bsize, 
					uint64_t addr,
					uint32_t *bank );


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

	uint32_t t_slot			= hmc->queue_depth+1;
	uint32_t j			= 0x00;
	uint32_t length			= 0x00;
	uint32_t cmd			= 0x00;
	uint32_t tag			= 0x00;
	uint32_t bsize			= 0x00;
	uint32_t bank			= 0x00;
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

	/* -- block size */
	hmcsim_util_get_max_blocksize( hmc, dev, &bsize );

	/* -- get the bank */
	hmcsim_util_decode_bank( hmc, dev, bsize, addr, &bank );

	/* 
 	 * Step 3: find a response slot
	 *         if no slots available, then this operation must stall
	 * 
 	 */

	/* -- find a response slot */
	for( j=hmc->queue_depth-1; j>= 0; j++ ){
		if( hmc->devs[dev].quads[quad].vaults[vault].rsp_queue[j].valid == HMC_RQST_INVALID ){
			t_slot = j;
		}
	}

	if( t_slot == hmc->queue_depth+1 ){

		/* STALL */

		queue->valid = HMC_RQST_STALLED;

		/* 
		 * print a stall trace
		 * 
		 */

		return HMC_STALL;
	}	

	/* 
	 * Step 3: perform the op 
	 * 
 	 */
	switch( cmd )
	{
		case 0x08:
			/* WR16 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"WR16", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x09:
			/* WR32 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"WR32", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x0A:
			/* WR48 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"WR48", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x0B:
			/* WR64 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"WR64", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x0C:
			/* WR80 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"WR80", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x0D:
			/* WR96 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"WR96", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x0E:
			/* WR112 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"WR112", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x0F:
			/* WR128 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"WR128", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x10:
			/* MD_WR */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"MD_WR", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x11:
			/* BWR */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"BWR", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x12:
			/* TWOADD8 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"TWOADD8", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x13:
			/* ADD16 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"ADD16", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x18:
			/* P_WR16 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"P_WR16", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x19:
			/* P_WR32 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"P_WR32", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x1A:
			/* P_WR48 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"P_WR48", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x1B:
			/* P_WR64 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"P_WR64", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x1C:
			/* P_WR80 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"P_WR80", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x1D:
			/* P_WR96 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"P_WR96", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x1E:
			/* P_WR112 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"P_WR112", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x1F:
			/* P_WR128 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"P_WR128", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x21:
			/* P_BWR */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"P_BWR", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x22:
			/* P2ADD8 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"P2ADD8", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x23:
			/* P_ADD16 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"P_ADD16", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x30:
			/* RD16 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"RD16", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x31:
			/* RD32 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"RD32", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x32:
			/* RD48 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"RD48", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x33:
			/* RD64 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"RD64", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x34:
			/* RD80 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"RD80", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x35:
			/* RD96 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"RD96", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x36:
			/* RD112 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"RD112", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x37:
			/* RD128 */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"RD128", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x28:
			/* MD_RD */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"MD_RD", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x00:
			/* FLOW_NULL */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"FLOW_NULL", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x01:
			/* PRET */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"PRET", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x02:
			/* TRET */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"TRET", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		case 0x03:
			/* IRTRY */

			if( (hmc->tracelevel & HMC_TRACE_CMD) > 0 ){ 
				hmcsim_trace_rqst(	hmc, 
							"IRTRY", 
							dev, 
							quad,
							vault, 
							bank, 
							addr, 
							length );
			}

			break;
		default:
			break;
	}

	/* 
 	 * Step 4: build and register the response with vault response queue
	 * 
 	 */

	/* -- build the response */

	/* -- register the response */

	/* 
	 * Step 5: invalidate the request queue slot
	 * 
 	 */	
	hmcsim_util_zero_packet( queue );

	return 0;
}

/* EOF */
