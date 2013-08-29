/* 
 * _HMC_JTAG_C_
 * 
 * HYBRID MEMORY CUBE SIMULATION LIBRARY 
 * 
 * HMC JTAG READ AND WRITE FUNCTIONS
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hmc_sim.h"

/* ----------------------------------------------------- HMCSIM_JTAG_REG_READ */
/* 
 * HMCSIM_JTAG_REG_READ
 * 
 */
extern int	hmcsim_jtag_reg_read( struct hmcsim_t *hmc, uint32_t dev, uint64_t reg, uint64_t *result )
{
	if( hmc == NULL ){ 
		return -1;
	}	

	if( dev > hmc->num_devs ){
		return -1;
	}

	switch( reg )
	{
		case HMC_REG_EDR0:
			*result	= hmc->devs[dev].regs[HMC_REG_EDR0_IDX].reg;
			break;
		case HMC_REG_EDR1:
			*result	= hmc->devs[dev].regs[HMC_REG_EDR1_IDX].reg;
			break;
		case HMC_REG_EDR2:
			*result	= hmc->devs[dev].regs[HMC_REG_EDR2_IDX].reg;
			break;
		case HMC_REG_EDR3:
			*result	= hmc->devs[dev].regs[HMC_REG_EDR3_IDX].reg;
			break;
		case HMC_REG_ERR:
			*result	= hmc->devs[dev].regs[HMC_REG_ERR_IDX].reg;
			break;
		case HMC_REG_GC:
			*result	= hmc->devs[dev].regs[HMC_REG_GC_IDX].reg;
			break;
		case HMC_REG_LC0:
			*result	= hmc->devs[dev].regs[HMC_REG_LC0_IDX].reg;
			break;
		case HMC_REG_LC1:
			*result	= hmc->devs[dev].regs[HMC_REG_LC1_IDX].reg;
			break;
		case HMC_REG_LC2:
			*result	= hmc->devs[dev].regs[HMC_REG_LC2_IDX].reg;
			break;
		case HMC_REG_LC3:
			*result	= hmc->devs[dev].regs[HMC_REG_LC3_IDX].reg;
			break;
		case HMC_REG_LRLL0:
			*result	= hmc->devs[dev].regs[HMC_REG_LRLL0_IDX].reg;
			break;
		case HMC_REG_LRLL1:
			*result	= hmc->devs[dev].regs[HMC_REG_LRLL1_IDX].reg;
			break;
		case HMC_REG_LRLL2:
			*result	= hmc->devs[dev].regs[HMC_REG_LRLL2_IDX].reg;
			break;
		case HMC_REG_LRLL3:
			*result	= hmc->devs[dev].regs[HMC_REG_LRLL3_IDX].reg;
			break;
		case HMC_REG_LR0:
			*result	= hmc->devs[dev].regs[HMC_REG_LR0_IDX].reg;
			break;
		case HMC_REG_LR1:
			*result	= hmc->devs[dev].regs[HMC_REG_LR1_IDX].reg;
			break;
		case HMC_REG_LR2:
			*result	= hmc->devs[dev].regs[HMC_REG_LR2_IDX].reg;
			break;
		case HMC_REG_LR3:
			*result	= hmc->devs[dev].regs[HMC_REG_LR3_IDX].reg;
			break;
		case HMC_REG_IBTC0:
			*result	= hmc->devs[dev].regs[HMC_REG_IBTC0_IDX].reg;
			break;
		case HMC_REG_IBTC1:
			*result	= hmc->devs[dev].regs[HMC_REG_IBTC1_IDX].reg;
			break;
		case HMC_REG_IBTC2:
			*result	= hmc->devs[dev].regs[HMC_REG_IBTC2_IDX].reg;
			break;
		case HMC_REG_IBTC3:
			*result	= hmc->devs[dev].regs[HMC_REG_IBTC3_IDX].reg;
			break;
		case HMC_REG_AC:
			*result	= hmc->devs[dev].regs[HMC_REG_AC_IDX].reg;
			break;
		case HMC_REG_VCR:
			*result	= hmc->devs[dev].regs[HMC_REG_VCR_IDX].reg;
			break;
		case HMC_REG_FEAT:
			*result	= hmc->devs[dev].regs[HMC_REG_FEAT_IDX].reg;
			break;
		case HMC_REG_RVID:
			*result	= hmc->devs[dev].regs[HMC_REG_RVID_IDX].reg;
			break;
		default:
			return -1;
	}

	return 0;
}

/* ----------------------------------------------------- HMCSIM_JTAG_REG_WRITE */
/* 
 * HMCSIM_JTAG_REG_WRITE
 * 
 */
extern int	hmcsim_jtag_reg_write( struct hmcsim_t *hmc, uint32_t dev, uint64_t reg )
{
	if( hmc == NULL ){ 
		return -1;
	}	

	if( dev > hmc->num_devs ){
		return -1;
	}

	switch( reg )
	{
		case HMC_REG_EDR0:
			break;
		case HMC_REG_EDR1:
			break;
		case HMC_REG_EDR2:
			break;
		case HMC_REG_EDR3:
			break;
		case HMC_REG_ERR:
			break;
		case HMC_REG_GC:
			break;
		case HMC_REG_LC0:
			break;
		case HMC_REG_LC1:
			break;
		case HMC_REG_LC2:
			break;
		case HMC_REG_LC3:
			break;
		case HMC_REG_LRLL0:
			break;
		case HMC_REG_LRLL1:
			break;
		case HMC_REG_LRLL2:
			break;
		case HMC_REG_LRLL3:
			break;
		case HMC_REG_LR0:
			break;
		case HMC_REG_LR1:
			break;
		case HMC_REG_LR2:
			break;
		case HMC_REG_LR3:
			break;
		case HMC_REG_IBTC0:
			break;
		case HMC_REG_IBTC1:
			break;
		case HMC_REG_IBTC2:
			break;
		case HMC_REG_IBTC3:
			break;
		case HMC_REG_AC:
			break;
		case HMC_REG_VCR:
			break;
		case HMC_REG_FEAT:
			break;
		case HMC_REG_RVID:
			break;
		default:
			return -1;
	}

	return 0;
}

/* EOF */
