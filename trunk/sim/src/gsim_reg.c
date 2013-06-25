/* 
 * 
 * _GSIM_REG_C_ 
 * 
 * GOBLIN-SIM REGISTER FUNCTIONS
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "goblin_sim.h"


/* -------------------------------------------------- GSIM_REG_INIT */
/* 
 * GSIM_REG_INIT
 * 
 */
static int gsim_reg_init( struct gsim_t *sim )
{
	/* vars */
	uint32_t i	= 0;
	/* ---- */

	/* 
	 * check the sim structure
	 * 
	 */
	if( sim == NULL ){ 
		/* nothing to do, return */
		return -1;
	}	

	/* 
	 * zero the register table
	 * 
	 */
	
	/* 
	 * populate the register table
	 * 
	 */

	/* -- USER REGISTERS */
	for( i=0; i<32; i++ ) {
		sim->register.format[i]	= GSIM_REG_RW;
		sprintf( sim->register.name[i], "%s%d", "r", i );
	}

	/* -- STACK POINTER */
	sim->register.format[0x20]	= GSIM_REG_RW;
	sprintf( sim->register.name[0x20], "%s", "sp" );

	/* -- FRAME POINTER */
	sim->register.format[0x21]	= GSIM_REG_RW;
	sprintf( sim->register.name[0x21], "%s", "fp" );
	
	/* -- PIC */
	sim->register.format[0x22]	= GSIM_REG_RW;
	sprintf( sim->register.name[0x22], "%s", "pic" );

	/* -- UPLEVEL FRAME POINTER */
	sim->register.format[0x23]	= GSIM_REG_RW;
	sprintf( sim->register.name[0x23], "%s", "up" );
	
	/* -- RETURN POINTER */
	sim->register.format[0x24]	= GSIM_REG_RW;
	sprintf( sim->register.name[0x24], "%s", "rp" );

	/* -- CC0 */
	sim->register.format[0x25]	= GSIM_REG_RW;
	sprintf( sim->register.name[0x25], "%s", "cc0" );

	/* -- CC1 */
	sim->register.format[0x26]	= GSIM_REG_RW;
	sprintf( sim->register.name[0x26], "%s", "cc1" );

	/* -- CC2 */
	sim->register.format[0x27]	= GSIM_REG_RW;
	sprintf( sim->register.name[0x27], "%s", "cc2" );

	/* -- CC3 */
	sim->register.format[0x28]	= GSIM_REG_RW;
	sprintf( sim->register.name[0x28], "%s", "cc3" );

	/* -- TQ */
	sim->register.format[0x29]	= GSIM_REG_RW;
	sprintf( sim->register.name[0x29], "%s", "tq" );

	/* -- VL */
	sim->register.format[0x2A]	= GSIM_REG_RW;
	sprintf( sim->register.name[0x2A], "%s", "vl" );

	/* -- VS */
	sim->register.format[0x2B]	= GSIM_REG_RW;
	sprintf( sim->register.name[0x2B], "%s", "vs" );

	/* -- GMODE */
	sim->register.format[0x2C]	= GSIM_REG_RW;
	sprintf( sim->register.name[0x2C], "%s", "gmode" );

	/* -- PMASK */
	sim->register.format[0x2D]	= GSIM_REG_RW;
	sprintf( sim->register.name[0x2D], "%s", "pmask" );

	/* -- PREAD */
	sim->register.format[0x2E]	= GSIM_REG_RW;
	sprintf( sim->register.name[0x2E], "%s", "pread" );

	/* -- TID */
	sim->register.format[0x2F]	= GSIM_REG_RW;
	sprintf( sim->register.name[0x2F], "%s", "tid" );

	/* -- 0x30 */
	sim->register.format[0x30]	= GSIM_REG_INVALID;
	sprintf( sim->register.name[0x30], "%s", "INVALID" );

	/* -- 0x31 */
	sim->register.format[0x31]	= GSIM_REG_INVALID;
	sprintf( sim->register.name[0x31], "%s", "INVALID" );

	/* -- 0x32 */
	sim->register.format[0x32]	= GSIM_REG_INVALID;
	sprintf( sim->register.name[0x32], "%s", "INVALID" );

	/* -- 0x33 */
	sim->register.format[0x33]	= GSIM_REG_INVALID;
	sprintf( sim->register.name[0x33], "%s", "INVALID" );

	/* -- 0x34 */
	sim->register.format[0x34]	= GSIM_REG_INVALID;
	sprintf( sim->register.name[0x34], "%s", "INVALID" );

	/* -- ZERO */
	sim->register.format[0x35]	= GSIM_REG_RO;
	sprintf( sim->register.name[0x35], "%s", "zero" );

	/* -- IMM32 */
	sim->register.format[0x36]	= GSIM_REG_RO;
	sprintf( sim->register.name[0x36], "%s", "imm32" );

	/* -- IMM64 */
	sim->register.format[0x37]	= GSIM_REG_RO;
	sprintf( sim->register.name[0x37], "%s", "imm64" );

	/* -- GCONST */
	sim->register.format[0x38]	= GSIM_REG_RO;
	sprintf( sim->register.name[0x38], "%s", "gconst" );

	/* -- EQ */
	sim->register.format[0x39]	= GSIM_REG_RO;
	sprintf( sim->register.name[0x39], "%s", "eq" );

	/* -- GT */
	sim->register.format[0x3A]	= GSIM_REG_RO;
	sprintf( sim->register.name[0x3A], "%s", "gt" );

	/* -- GTE */
	sim->register.format[0x3B]	= GSIM_REG_RO;
	sprintf( sim->register.name[0x3B], "%s", "gte" );

	/* -- LT */
	sim->register.format[0x3C]	= GSIM_REG_RO;
	sprintf( sim->register.name[0x3C], "%s", "lt" );

	/* -- LTE */
	sim->register.format[0x3D]	= GSIM_REG_RO;
	sprintf( sim->register.name[0x3D], "%s", "lte" );

	/* -- NE */
	sim->register.format[0x3E]	= GSIM_REG_RO;
	sprintf( sim->register.name[0x3E], "%s", "ne" );

	/* -- PVAL */
	sim->register.format[0x3F]	= GSIM_REG_RO;
	sprintf( sim->register.name[0x3F], "%s", "pval" );

	return 0;
}

/* EOF */
