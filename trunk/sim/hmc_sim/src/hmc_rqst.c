/* 
 * _HMC_RQST_C_
 * 
 * HYBRID MEMORY CUBE SIMULATION LIBRARY 
 * 
 * MEMORY REQUEST HANDLERS
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hmc_sim.h"


/* ----------------------------------------------------- HMCSIM_BUILD_MEMREQUEST */
/* 
 * HMCSIM_BUILD_MEMREQUEST
 * 
 */
extern int	hmcsim_build_memrequest( struct hmcsim_t *hmc, 
					uint8_t  cub, 
					uint64_t addr, 
					uint8_t  tag, 
					uint8_t  flits, 
					hmc_rqst_t type, 
					uint64_t *request )
{
	/* vars */
	uint8_t cmd	= 0x00;
	uint64_t tmp	= 0x00ll;
	/* ---- */

	if( hmc == NULL ){ 
		return -1;
	}

	/* 
	 * validate the cub 
	 *
	 */
	if( cub >= hmc->num_devs ){ 
		return -1;
	}

	/* 
	 * validate flits
	 * 
	 */
	if( flits > 9 ){
		return -1;
	}

	/* 
	 * get the correct command bit sequence
	 *
	 */
	switch( type )
	{
		case WR16:
			break;
		case WR32:
			break;
		case WR48:
			break;
		case WR64:
			break;
		case WR80:
			break;
		case WR96:
			break;
		case WR112:
			break;
		case WR128:
			break;
		case MD_WR:
			break;
		default:
			return -1;
			break;
	}

	
	return 0;
}

/* EOF */
