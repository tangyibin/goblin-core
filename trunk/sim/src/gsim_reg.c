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
#include <string.h>
#include "goblin_sim.h"


/* -------------------------------------------------- GSIM_REG_DUMP */
/* 
 * GSIM_REG_DUMP 
 * 
 */
#ifdef GSIM_DEBUG
static void gsim_reg_dump( struct gsim_t *sim )
{
#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_ENTRY();
#endif
	/* vars */
	uint32_t i	= 0;
	char RW[3]	= "RW";
	char RO[3]	= "RO";
	char INVALID[8]	= "INVALID";
	char *format	= NULL;
	/* ---- */

	/* 
	 * sanity check 
	 * 
	 */
	if( sim == NULL ){ 
		return ;
	}	

	/* 
	 * print the reg info 
	 * 
 	 */
	printf( "====================================================================\n" );
	printf( "[INDEX]    [NAME]    [RW/RO]\n" );
	for( i=0; i<0x3F; i++ ){ 

		/* 
		 * select the format
		 *
		 */
		switch( sim->registers.format[i] ){ 
			case GSIM_REG_RW:
				format = &(RW[0]);
				break;
			case GSIM_REG_RO:
				format = &(RO[0]);
				break;
			case GSIM_REG_INVALID:
				format = &(INVALID[0]);
				break;
			default:
				format = &(INVALID[0]);
				break;
		}	

		printf( "0x%02x%10s%10s\n", i, sim->registers.name[i], format );
	}
	printf( "====================================================================\n" );

#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_EXIT();
#endif
	return ;
}
#endif /* GSIM_DEBUG */

/* -------------------------------------------------- GSIM_REG_INIT */
/* 
 * GSIM_REG_INIT
 * 
 */
extern int gsim_reg_init( struct gsim_t *sim )
{
#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_ENTRY();
#endif
	/* vars */
	uint32_t i			= 0;
	struct gsim_reg_t *reg		= NULL;
	/* ---- */

	/* 
	 * check the sim structure
	 * 
	 */
	if( sim == NULL ){ 
		/* nothing to do, return */
		return -1;
	}	

	reg	= &(sim->registers);

	/* 
	 * zero the register table
	 * 
	 */
	memset( reg->format, 0, sizeof( uint32_t ) * 64 );
	memset( reg->name, 0, sizeof( char ) * 64 * 64 );
	
	/* 
	 * populate the register table
	 * 
	 */

	/* -- USER REGISTERS */
	for( i=0; i<32; i++ ) {
		reg->format[i]	= GSIM_REG_RW;
		sprintf( reg->name[i], "%s%d", "r", i );
	}

	/* -- STACK POINTER */
	reg->format[0x20]	= GSIM_REG_RW;
	sprintf( reg->name[0x20], "%s", "sp" );

	/* -- FRAME POINTER */
	reg->format[0x21]	= GSIM_REG_RW;
	sprintf( reg->name[0x21], "%s", "fp" );
	
	/* -- PIC */
	reg->format[0x22]	= GSIM_REG_RW;
	sprintf( reg->name[0x22], "%s", "pic" );

	/* -- UPLEVEL FRAME POINTER */
	reg->format[0x23]	= GSIM_REG_RW;
	sprintf( reg->name[0x23], "%s", "up" );
	
	/* -- RETURN POINTER */
	reg->format[0x24]	= GSIM_REG_RW;
	sprintf( reg->name[0x24], "%s", "rp" );

	/* -- CC0 */
	reg->format[0x25]	= GSIM_REG_RW;
	sprintf( reg->name[0x25], "%s", "cc0" );

	/* -- CC1 */
	reg->format[0x26]	= GSIM_REG_RW;
	sprintf( reg->name[0x26], "%s", "cc1" );

	/* -- CC2 */
	reg->format[0x27]	= GSIM_REG_RW;
	sprintf( reg->name[0x27], "%s", "cc2" );

	/* -- CC3 */
	reg->format[0x28]	= GSIM_REG_RW;
	sprintf( reg->name[0x28], "%s", "cc3" );

	/* -- TQ */
	reg->format[0x29]	= GSIM_REG_RW;
	sprintf( reg->name[0x29], "%s", "tq" );

	/* -- VL */
	reg->format[0x2A]	= GSIM_REG_RW;
	sprintf( reg->name[0x2A], "%s", "vl" );

	/* -- VS */
	reg->format[0x2B]	= GSIM_REG_RW;
	sprintf( reg->name[0x2B], "%s", "vs" );

	/* -- GMODE */
	reg->format[0x2C]	= GSIM_REG_RW;
	sprintf( reg->name[0x2C], "%s", "gmode" );

	/* -- PMASK */
	reg->format[0x2D]	= GSIM_REG_RW;
	sprintf( reg->name[0x2D], "%s", "pmask" );

	/* -- PREAD */
	reg->format[0x2E]	= GSIM_REG_RW;
	sprintf( reg->name[0x2E], "%s", "pread" );

	/* -- TID */
	reg->format[0x2F]	= GSIM_REG_RW;
	sprintf( reg->name[0x2F], "%s", "tid" );

	/* -- 0x30 */
	reg->format[0x30]	= GSIM_REG_INVALID;
	sprintf( reg->name[0x30], "%s", "INVALID" );

	/* -- 0x31 */
	reg->format[0x31]	= GSIM_REG_INVALID;
	sprintf( reg->name[0x31], "%s", "INVALID" );

	/* -- 0x32 */
	reg->format[0x32]	= GSIM_REG_INVALID;
	sprintf( reg->name[0x32], "%s", "INVALID" );

	/* -- 0x33 */
	reg->format[0x33]	= GSIM_REG_RO;
	sprintf( reg->name[0x33], "%s", "gkey" );

	/* -- GEXC */
	reg->format[0x34]	= GSIM_REG_RO;
	sprintf( reg->name[0x34], "%s", "gexc" );

	/* -- ZERO */
	reg->format[0x35]	= GSIM_REG_RO;
	sprintf( reg->name[0x35], "%s", "zero" );

	/* -- IMM32 */
	reg->format[0x36]	= GSIM_REG_RO;
	sprintf( reg->name[0x36], "%s", "imm32" );

	/* -- IMM64 */
	reg->format[0x37]	= GSIM_REG_RO;
	sprintf( reg->name[0x37], "%s", "imm64" );

	/* -- GCONST */
	reg->format[0x38]	= GSIM_REG_RO;
	sprintf( reg->name[0x38], "%s", "gconst" );

	/* -- EQ */
	reg->format[0x39]	= GSIM_REG_RO;
	sprintf( reg->name[0x39], "%s", "eq" );

	/* -- GT */
	reg->format[0x3A]	= GSIM_REG_RO;
	sprintf( reg->name[0x3A], "%s", "gt" );

	/* -- GTE */
	reg->format[0x3B]	= GSIM_REG_RO;
	sprintf( reg->name[0x3B], "%s", "gte" );

	/* -- LT */
	reg->format[0x3C]	= GSIM_REG_RO;
	sprintf( reg->name[0x3C], "%s", "lt" );

	/* -- LTE */
	reg->format[0x3D]	= GSIM_REG_RO;
	sprintf( reg->name[0x3D], "%s", "lte" );

	/* -- NE */
	reg->format[0x3E]	= GSIM_REG_RO;
	sprintf( reg->name[0x3E], "%s", "ne" );

	/* -- PVAL */
	reg->format[0x3F]	= GSIM_REG_RO;
	sprintf( reg->name[0x3F], "%s", "pval" );

#ifdef GSIM_DEBUG
	gsim_reg_dump( sim );
	GSIM_PRINT_FUNC_EXIT();
#endif

	return 0;
}

/* EOF */
