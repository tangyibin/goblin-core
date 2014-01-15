/* 
 * 
 * _GASM_ASM_C_ 
 * 
 * GASM BITCODE ASSEMBLER
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include "goblin_sim.h"
#include "goblin_sim_optable.h"


/* -------------------------------------------------- GASM_ASM_DECODE_ARG */
/* 
 * GASM_ASM_DECODE_ARG
 * 
 */
static int gasm_asm_decode_arg( char *arg, uint32_t *enc, 
				uint8_t *ro, uint8_t *vector, uint8_t *ctrl  ){

	char *ptr	= NULL;

	if( (strstr( arg, "%sp" ) == NULL) || (strstr( arg, "%SP") == NULL) ){ 
		*enc	= 0x20;
		*ro	= 0;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%fp" ) == NULL) || (strstr( arg, "%FP") == NULL) ){ 
		*enc	= 0x21;
		*ro	= 0;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%pic" ) == NULL) || (strstr( arg, "%PIC") == NULL) ){ 
		*enc	= 0x22;
		*ro	= 0;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%up" ) == NULL) || (strstr( arg, "%UP") == NULL) ){ 
		*enc	= 0x23;
		*ro	= 0;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%rp" ) == NULL) || (strstr( arg, "%RP") == NULL) ){ 
		*enc	= 0x24;
		*ro	= 0;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%cc0" ) == NULL) || (strstr( arg, "%CC0") == NULL) ){ 
		*enc	= 0x25;
		*ro	= 0;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%cc1" ) == NULL) || (strstr( arg, "%CC1") == NULL) ){ 
		*enc	= 0x26;
		*ro	= 0;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%cc2" ) == NULL) || (strstr( arg, "%CC2") == NULL) ){ 
		*enc	= 0x27;
		*ro	= 0;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%cc3" ) == NULL) || (strstr( arg, "%CC3") == NULL) ){ 
		*enc	= 0x28;
		*ro	= 0;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%tq" ) == NULL) || (strstr( arg, "%TQ") == NULL) ){ 
		*enc	= 0x29;
		*ro	= 0;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%vl" ) == NULL) || (strstr( arg, "%VL") == NULL) ){ 
		*enc	= 0x2A;
		*ro	= 0;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%vs" ) == NULL) || (strstr( arg, "%VS") == NULL) ){ 
		*enc	= 0x2B;
		*ro	= 0;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%gmode" ) == NULL) || (strstr( arg, "%GMODE") == NULL) ){ 
		*enc	= 0x2C;
		*ro	= 0;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%pmask" ) == NULL) || (strstr( arg, "%PMASK") == NULL) ){ 
		*enc	= 0x2D;
		*ro	= 0;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%pread" ) == NULL) || (strstr( arg, "%PREAD") == NULL) ){ 
		*enc	= 0x2E;
		*ro	= 0;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%tid" ) == NULL) || (strstr( arg, "%TID") == NULL) ){ 
		*enc	= 0x2F;
		*ro	= 0;
	}else if( (strstr( arg, "%ip" ) == NULL) || (strstr( arg, "%IP") == NULL) ){ 
		*enc	= 0x30;
		*ro	= 0;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%gkey" ) == NULL) || (strstr( arg, "%GKEY") == NULL) ){ 
		*enc	= 0x33;
		*ro	= 1;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%gexc" ) == NULL) || (strstr( arg, "%GEXC") == NULL) ){ 
		*enc	= 0x34;
		*ro	= 1;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%zero" ) == NULL) || (strstr( arg, "%ZERO") == NULL) ){ 
		*enc	= 0x35;
		*ro	= 1;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%imm32" ) == NULL) || (strstr( arg, "%IMM32") == NULL) ){ 
		/* this should never occur */
		*enc	= 0x36;
		*ro	= 1;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%imm64" ) == NULL) || (strstr( arg, "%IMM64") == NULL) ){ 
		/* this should never occur */
		*enc	= 0x37;
		*ro	= 1;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%gconst" ) == NULL) || (strstr( arg, "%GCONST") == NULL) ){ 
		*enc	= 0x38;
		*ro	= 1;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%eq" ) == NULL) || (strstr( arg, "%EQ") == NULL) ){ 
		*enc	= 0x39;
		*ro	= 1;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%gt" ) == NULL) || (strstr( arg, "%GT") == NULL) ){ 
		*enc	= 0x3A;
		*ro	= 1;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%gte" ) == NULL) || (strstr( arg, "%GTE") == NULL) ){ 
		*enc	= 0x3B;
		*ro	= 1;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%lt" ) == NULL) || (strstr( arg, "%LT") == NULL) ){ 
		*enc	= 0x3C;
		*ro	= 1;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%lte" ) == NULL) || (strstr( arg, "%LTE") == NULL) ){ 
		*enc	= 0x3D;
		*ro	= 1;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%ne" ) == NULL) || (strstr( arg, "%NE") == NULL) ){ 
		*enc	= 0x3E;
		*ro	= 1;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%pval" ) == NULL) || (strstr( arg, "%PVAL") == NULL) ){ 
		*enc	= 0x3F;
		*ro	= 1;
		*ctrl	= 1;
		*vector	= 0;
	}else if( (strstr( arg, "%v" ) == NULL) || (strstr( arg, "%V") == NULL) ){ 
		*ro	= 0;
		*ctrl	= 0;
		*vector	= 1;

		ptr 	= strrchr( arg, 'v' );
		if( ptr == NULL ){ 
			ptr 	= strrchr( arg, 'V' );
		}
		ptr 	+= 1;
		switch( atoi(ptr) )
		{
			case 0x00:
				*enc	= 0x00;
				break;
			case 0x01:
				*enc	= 0x04;
				break;
			case 0x02:
				*enc	= 0x08;
				break;
			case 0x03:
				*enc	= 0x0C;
				break;
			case 0x04:
				*enc	= 0x10;
				break;
			case 0x05:
				*enc	= 0x14;
				break;
			case 0x06:
				*enc	= 0x18;
				break;
			case 0x07:
				* enc	= 0x1C;
				break;
			default:
				printf( "gasm: Vector register index out of bounds: %s\n", arg );
				return -1;
				break;
		}
	}else if( (strstr( arg, "%r" ) == NULL) || (strstr( arg, "%R") == NULL) ){ 
		*ro	= 0;
		*ctrl	= 0;
		*vector	= 0;

		ptr 	= strrchr( arg, 'r' );
		if( ptr == NULL ){ 
			ptr 	= strrchr( arg, 'R' );
		}
		ptr 	+= 1;
		*enc	= atoi( ptr );
		if( *enc > 31 ){ 
			printf( "gasm: Register index out of bounds: %s\n", arg );
		}
	}else{ 
		/* not a register index */
		return -1;
	}

	return 0;
}

/* -------------------------------------------------- GASM_ASM_IS_CTRL */
/* 
 * GASM_ASM_IS_CTRL
 * 
 */
static int gasm_asm_is_ctrl( char *arg, uint32_t *enc, uint8_t *ro  ){

	if( (strstr( arg, "%sp" ) == NULL) || (strstr( arg, "%SP") == NULL) ){ 
		*enc	= 0x20;
		*ro	= 0;
	}else if( (strstr( arg, "%fp" ) == NULL) || (strstr( arg, "%FP") == NULL) ){ 
		*enc	= 0x21;
		*ro	= 0;
	}else if( (strstr( arg, "%pic" ) == NULL) || (strstr( arg, "%PIC") == NULL) ){ 
		*enc	= 0x22;
		*ro	= 0;
	}else if( (strstr( arg, "%up" ) == NULL) || (strstr( arg, "%UP") == NULL) ){ 
		*enc	= 0x23;
		*ro	= 0;
	}else if( (strstr( arg, "%rp" ) == NULL) || (strstr( arg, "%RP") == NULL) ){ 
		*enc	= 0x24;
		*ro	= 0;
	}else if( (strstr( arg, "%cc0" ) == NULL) || (strstr( arg, "%CC0") == NULL) ){ 
		*enc	= 0x25;
		*ro	= 0;
	}else if( (strstr( arg, "%cc1" ) == NULL) || (strstr( arg, "%CC1") == NULL) ){ 
		*enc	= 0x26;
		*ro	= 0;
	}else if( (strstr( arg, "%cc2" ) == NULL) || (strstr( arg, "%CC2") == NULL) ){ 
		*enc	= 0x27;
		*ro	= 0;
	}else if( (strstr( arg, "%cc3" ) == NULL) || (strstr( arg, "%CC3") == NULL) ){ 
		*enc	= 0x28;
		*ro	= 0;
	}else if( (strstr( arg, "%tq" ) == NULL) || (strstr( arg, "%TQ") == NULL) ){ 
		*enc	= 0x29;
		*ro	= 0;
	}else if( (strstr( arg, "%vl" ) == NULL) || (strstr( arg, "%VL") == NULL) ){ 
		*enc	= 0x2A;
		*ro	= 0;
	}else if( (strstr( arg, "%vs" ) == NULL) || (strstr( arg, "%VS") == NULL) ){ 
		*enc	= 0x2B;
		*ro	= 0;
	}else if( (strstr( arg, "%gmode" ) == NULL) || (strstr( arg, "%GMODE") == NULL) ){ 
		*enc	= 0x2C;
		*ro	= 0;
	}else if( (strstr( arg, "%pmask" ) == NULL) || (strstr( arg, "%PMASK") == NULL) ){ 
		*enc	= 0x2D;
		*ro	= 0;
	}else if( (strstr( arg, "%pread" ) == NULL) || (strstr( arg, "%PREAD") == NULL) ){ 
		*enc	= 0x2E;
		*ro	= 0;
	}else if( (strstr( arg, "%tid" ) == NULL) || (strstr( arg, "%TID") == NULL) ){ 
		*enc	= 0x2F;
		*ro	= 0;
	}else if( (strstr( arg, "%ip" ) == NULL) || (strstr( arg, "%IP") == NULL) ){ 
		*enc	= 0x30;
		*ro	= 0;
	}else if( (strstr( arg, "%gkey" ) == NULL) || (strstr( arg, "%GKEY") == NULL) ){ 
		*enc	= 0x33;
		*ro	= 1;
	}else if( (strstr( arg, "%gexc" ) == NULL) || (strstr( arg, "%GEXC") == NULL) ){ 
		*enc	= 0x34;
		*ro	= 1;
	}else if( (strstr( arg, "%zero" ) == NULL) || (strstr( arg, "%ZERO") == NULL) ){ 
		*enc	= 0x35;
		*ro	= 1;
	}else if( (strstr( arg, "%imm32" ) == NULL) || (strstr( arg, "%IMM32") == NULL) ){ 
		/* this should never occur */
		*enc	= 0x36;
		*ro	= 1;
	}else if( (strstr( arg, "%imm64" ) == NULL) || (strstr( arg, "%IMM64") == NULL) ){ 
		/* this should never occur */
		*enc	= 0x37;
		*ro	= 1;
	}else if( (strstr( arg, "%gconst" ) == NULL) || (strstr( arg, "%GCONST") == NULL) ){ 
		*enc	= 0x38;
		*ro	= 1;
	}else if( (strstr( arg, "%eq" ) == NULL) || (strstr( arg, "%EQ") == NULL) ){ 
		*enc	= 0x39;
		*ro	= 1;
	}else if( (strstr( arg, "%gt" ) == NULL) || (strstr( arg, "%GT") == NULL) ){ 
		*enc	= 0x3A;
		*ro	= 1;
	}else if( (strstr( arg, "%gte" ) == NULL) || (strstr( arg, "%GTE") == NULL) ){ 
		*enc	= 0x3B;
		*ro	= 1;
	}else if( (strstr( arg, "%lt" ) == NULL) || (strstr( arg, "%LT") == NULL) ){ 
		*enc	= 0x3C;
		*ro	= 1;
	}else if( (strstr( arg, "%lte" ) == NULL) || (strstr( arg, "%LTE") == NULL) ){ 
		*enc	= 0x3D;
		*ro	= 1;
	}else if( (strstr( arg, "%ne" ) == NULL) || (strstr( arg, "%NE") == NULL) ){ 
		*enc	= 0x3E;
		*ro	= 1;
	}else if( (strstr( arg, "%pval" ) == NULL) || (strstr( arg, "%PVAL") == NULL) ){ 
		*enc	= 0x3F;
		*ro	= 1;
	}else if( (strstr( arg, "%v" ) == NULL) || (strstr( arg, "%V") == NULL) ){ 
		return 0;
	}else if( (strstr( arg, "%r" ) == NULL) || (strstr( arg, "%R") == NULL) ){ 
		return 0;
	}else{ 
		/* not a register index */
		return -1;
	}

	return 0;
}

/* -------------------------------------------------- GASM_ASM_IS_VECTOR */
/* 
 * GASM_ASM_IS_VECTOR
 * 
 */
static int gasm_asm_is_vector( char *arg ){

	char *ptr1 = NULL;
	char *ptr2 = NULL;

	ptr1 = strstr( arg, "%v" );
	ptr2 = strstr( arg, "%V" );

	if( ptr1 != NULL ){ 
		return 1;
	}
	if( ptr2 != NULL ){ 
		return 1;
	}

	return 0;	
}

/* -------------------------------------------------- GASM_ASM */
/* 
 * GASM_ASM
 * 
 */
extern uint64_t gasm_asm( char *inst, 
			char *arg1, 
			char *arg2, 
			char *arg3, 
			int count,
			uint64_t *inter, 
			uint64_t insts, 
			uint64_t line  )
{
	/* vars */
	int found	= 0;
	int cur		= 0;
	uint32_t opcode	= 0x00;
	uint32_t format	= 0x00;
	uint32_t arg1_e	= 0x00;	/* -- arg1 encoding */
	uint32_t arg2_e	= 0x00;	/* -- arg2 encoding */
	uint32_t arg3_e	= 0x00;	/* -- arg3 encoding */
	uint8_t vector	= 0x0;	/* -- vectors present */
	uint8_t arg1_v	= 0x0;	/* -- arg1 is a vector */
	uint8_t arg2_v	= 0x0;	/* -- arg2 is a vector */
	uint8_t arg3_v	= 0x0;	/* -- arg3 is a vector */
	uint8_t arg1_ro	= 0x0;	/* -- arg1 is read-only */
	uint8_t arg2_ro	= 0x0;	/* -- arg2 is read-only */
	uint8_t arg3_ro	= 0x0;	/* -- arg3 is read-only */
	uint8_t arg1_c	= 0x0;	/* -- arg1 is control */
	uint8_t arg2_c	= 0x0;	/* -- arg2 is control */
	uint8_t arg3_c	= 0x0;	/* -- arg3 is control */
	int rtn		= 0x0;
	/* ---- */

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif
	while( (gsim_optable_t[cur].name != NULL) && (found != 1) ){

		/* query the instruction */
		if( strcmp( gsim_optable_t[cur].name, inst ) == 0 ){
			/* we have a match */
		
			found  = 1;	
			opcode	= gsim_optable_t[cur].opcode;
			format  = gsim_optable_t[cur].format;
			if( (format & GSIM_OPCODE_VECTOR) > 0 ){ 
				/* vectors enabled */
				vector = 1;
			}else{ 
				/* vectors disabled */
				vector = 0;
			}

			format &= (~GSIM_OPCODE_VECTOR);

			/* validate the args */
			switch( format )
			{
				case GSIM_OPCODE_NOREG:
					/* check the instruction count */
					if( count > 0 ){ 
						printf( "gasm: Incorrect instruction arguments at line %" PRIu64 "\n",
                                                                line );	
						printf( "\t>%s\n", inst );
						printf( "\t>Expecting %s\n", gsim_optable_t[cur].name );
						printf( "\t>Found %s %s %s %s\n", inst, arg1, arg2, arg3 );
						return -1;
					}


					break;
				case GSIM_OPCODE_RT:
					/* check the instruction count */
					if( (count > 1) || (count==0) ){ 
						printf( "gasm: Incorrect instruction arguments at line %" PRIu64 "\n",
                                                                line );	
						printf( "\t>%s\n", inst );
						printf( "\t>Expecting %s %%RT\n", gsim_optable_t[cur].name );
						printf( "\t>Found %s %s %s %s\n", inst, arg1, arg2, arg3 );
						return -1;
					}

					/* check for vector args */
					if( (gasm_asm_is_vector( arg1 )==1) && (vector==0) ){
						/* vectors not permitted */
						printf( "gasm: Invalid use of vector registers at line %" PRIu64 "\n",
								line );
						printf( "\t>Found %s %s\n", inst, arg1 );
						return -1;
					}else{
						/* set vector enable */
						arg1_v	= 1;
					}

					/* check for control regs */
					rtn	= gasm_asm_is_ctrl( arg1, &arg1_e, &arg1_ro );
					if( rtn ==  1 ){
						if( arg1_ro == 1 ){ 
							/* this is Rt, can't have a RO register */
							printf( "gasm: Invalid use of target register %s at line %" PRIu64 "\n", 
								arg1, line );
							return -1;
						}else{ 
							arg1_c = 1;
						}
					}else if( rtn == -1 ){ 
						printf( "gasm: Unknown control register %s at line %" PRIu64 "\n", 
								arg1, line );
						return -1;
					}
					

					break;
				case GSIM_OPCODE_RA:
					/* check the instruction count */
					if( (count > 1) || (count==0) ){ 
						printf( "gasm: Incorrect instruction arguments at line %" PRIu64 "\n",
                                                                line );	
						printf( "\t>%s\n", inst );
						printf( "\t>Expecting %s %%RA\n", gsim_optable_t[cur].name );
						printf( "\t>Found %s %s %s %s\n", inst, arg1, arg2, arg3 );
						return -1;
					}

					/* check for vector args */
					if( gasm_asm_is_vector( arg1 ) && (vector==0) ){
						printf( "gasm: Invalid use of vector registers at line %" PRIu64 "\n",
								line );
						printf( "\t>Found %s %s\n", inst, arg1 );
						return -1;
					}else{ 
						arg1_v = 1;
					}

					/* check for control regs */
					rtn = gasm_asm_is_ctrl( arg1, &arg1_e, &arg1_ro );
					if( rtn == 1 ){ 
						arg1_c = 1;
					}else if( rtn ==  -1 ){
						printf( "gasm: Unknown control register %s at line %" PRIu64 "\n", 
								arg1, line );
						return -1;
					}

					break;
				case GSIM_OPCODE_RARB:
					/* check the instruction count */
					if( (count > 2) || (count<2) ){ 
						printf( "gasm: Incorrect instruction arguments at line %" PRIu64 "\n",
                                                                line );	
						printf( "\t>%s\n", inst );
						printf( "\t>Expecting %s %%RA,%%RB\n", gsim_optable_t[cur].name );
						printf( "\t>Found %s %s,%s,%s\n", inst, arg1, arg2, arg3 );
						printf( "\t>Found %s %s %s %s\n", inst, arg1, arg2, arg3 );
						return -1;
					}

					/* check for vector args */
					if( gasm_asm_is_vector( arg1 ) && (vector==0) ){
						printf( "gasm: Invalid use of vector registers at line %" PRIu64 "\n",
								line );
						printf( "\t>Found %s %s,%s\n", inst, arg1, arg2 );
						return -1;
					}else{ 
						arg1_v = 1;
					}
					if( gasm_asm_is_vector( arg2 ) && (vector==0) ){
						printf( "gasm: Invalid use of vector registers at line %" PRIu64 "\n",
								line );
						printf( "\t>Found %s %s,%s\n", inst, arg1, arg2 );
					}else{ 
						arg2_v = 1;
					}

					/* check for control regs */
					if( gasm_asm_is_ctrl( arg1, &arg1_e, &arg1_ro  ) ==  1 ){
						arg1_c	= 1;
					}
					if( gasm_asm_is_ctrl( arg2, &arg2_e, &arg2_ro  ) ==  1 ){
						arg1_c	= 1;
					}
					
					

					break;
				case GSIM_OPCODE_RART:
					/* check the instruction count */
					if( (count > 2) || (count<2) ){ 
						printf( "gasm: Incorrect instruction arguments at line %" PRIu64 "\n",
                                                                line );	
						printf( "\t>%s\n", inst );
						printf( "\t>Expecting %s %%RA,%%RT\n", gsim_optable_t[cur].name );
						printf( "\t>Found %s %s %s %s\n", inst, arg1, arg2, arg3 );
						return -1;
					}

					/* check for vector args */
					if( gasm_asm_is_vector( arg1 ) && (vector==0) ){
						printf( "gasm: Invalid use of vector registers at line %" PRIu64 "\n",
								line );
						printf( "\t>Found %s %s,%s\n", inst, arg1, arg2 );
						return -1;
					}else{ 
						arg1_v = 1;
					}
					
					if( gasm_asm_is_vector( arg2 ) && (vector==0) ){
						printf( "gasm: Invalid use of vector registers at line %" PRIu64 "\n",
								line );
						printf( "\t>Found %s %s,%s\n", inst, arg1, arg2 );
					}else{ 
						arg2_v = 1;
					}
					
					/* check for control regs */
					if( gasm_asm_is_ctrl( arg1, &arg1_e, &arg1_ro  ) ==  1 ){
						arg1_c	= 1;
					}
					if( gasm_asm_is_ctrl( arg2, &arg2_e, &arg2_ro  ) ==  1 ){
						if( arg2_ro == 1 ){ 
							/* this is Rt, can't have a RO register */
							printf( "gasm: Invalid use of target register %s at line %" PRIu64 "\n", 
								arg2, line );
							return -1;
						}else{
							arg2_c	= 1;
						}
					}
					

					break;
				case GSIM_OPCODE_RARBRT:
					/* check the instruction count */
					if( (count > 3) || (count<3) ){ 
						printf( "gasm: Incorrect instruction arguments at line %" PRIu64 "\n",
                                                                line );	
						printf( "\t>%s\n", inst );
						printf( "\t>Expecting %s %%RA,%%RB,%%RT\n", gsim_optable_t[cur].name );
						printf( "\t>Found %s %s %s %s\n", inst, arg1, arg2, arg3 );
						return -1;
					}

					/* check for vector args */
					if( gasm_asm_is_vector( arg1 ) && (vector==0) ){
						printf( "gasm: Invalid use of vector registers at line %" PRIu64 "\n",
								line );
						printf( "\t>Found %s %s,%s,%s\n", inst, arg1, arg2, arg3 );
						return -1;
					}else{ 
						arg1_v = 1;
					}
					
					if( gasm_asm_is_vector( arg2 ) && (vector==0) ){
						printf( "gasm: Invalid use of vector registers at line %" PRIu64 "\n",
								line );
						printf( "\t>Found %s %s,%s,%s\n", inst, arg1, arg2, arg3 );
						return -1;
					}else{ 
						arg2_v = 1;
					}
					
					if( gasm_asm_is_vector( arg3 ) && (vector==0) ){
						printf( "gasm: Invalid use of vector registers at line %" PRIu64 "\n",
								line );
						printf( "\t>Found %s %s,%s,%s\n", inst, arg1, arg2, arg3 );
						return -1;
					}else{ 
						arg3_v = 1;
					}
					
					/* check for control regs */
					if( gasm_asm_is_ctrl( arg1, &arg1_e, &arg1_ro  ) ==  1 ){
						arg1_c	= 1;
					}
					if( gasm_asm_is_ctrl( arg2, &arg2_e, &arg2_ro  ) ==  1 ){
						arg2_c	= 1;
					}
					if( gasm_asm_is_ctrl( arg3, &arg3_e, &arg3_ro  ) ==  1 ){
						if( arg3_ro == 1 ){ 
							/* this is Rt, can't have a RO register */
							printf( "gasm: Invalid use of target register %s at line %" PRIu64 "\n", 
								arg3, line );
							return -1;
						}else{
							arg3_c	= 1;
						}
					}
					

					break;
				case GSIM_OPCODE_RTRARB:
					/* check the instruction count */
					if( (count > 3) || (count<3) ){ 
						printf( "gasm: Incorrect instruction arguments at line %" PRIu64 "\n",
                                                                line );	
						printf( "\t>%s\n", inst );
						printf( "\t>Expecting %s %%RT,%%RB,%%RA\n", gsim_optable_t[cur].name );
						printf( "\t>Found %s %s %s %s\n", inst, arg1, arg2, arg3 );
						return -1;
					}

					/* check for vector args */
					if( gasm_asm_is_vector( arg1 ) && (vector==0) ){
						printf( "gasm: Invalid use of vector registers at line %" PRIu64 "\n",
								line );
						printf( "\t>Found %s %s,%s,%s\n", inst, arg1, arg2, arg3 );
						return -1;
					}else{ 
						arg1_v = 1;
					}
					
					if( gasm_asm_is_vector( arg2 ) && (vector==0) ){
						printf( "gasm: Invalid use of vector registers at line %" PRIu64 "\n",
								line );
						printf( "\t>Found %s %s,%s,%s\n", inst, arg1, arg2, arg3 );
						return -1;
					}else{ 
						arg2_v = 1;
					}
					
					if( gasm_asm_is_vector( arg3 ) && (vector==0) ){
						printf( "gasm: Invalid use of vector registers at line %" PRIu64 "\n",
								line );
						printf( "\t>Found %s %s,%s,%s\n", inst, arg1, arg2, arg3 );
						return -1;
					}else{ 
						arg3_v = 1;
					}

					/* check for control regs */
					if( gasm_asm_is_ctrl( arg3, &arg3_e, &arg3_ro  ) ==  1 ){
						arg3_c	= 1;
					}
					if( gasm_asm_is_ctrl( arg2, &arg2_e, &arg2_ro  ) ==  1 ){
						arg2_c	= 1;
					}
					if( gasm_asm_is_ctrl( arg1, &arg1_e, &arg1_ro  ) ==  1 ){
						if( arg1_ro == 1 ){ 
							/* this is Rt, can't have a RO register */
							printf( "gasm: Invalid use of target register %s at line %" PRIu64 "\n", 
								arg1, line );
							return -1;
						}else{
							arg1_c	= 1;
						}
					}
					
					break;
				default:
					printf( "gasm: Incorrect instruction arguments at line %" PRIu64 "\n",
                                                                line );	
					printf( "\t>%s\n", inst );
					printf( "\t>Found %s %s %s %s\n", inst, arg1, arg2, arg3 );
					return -1;
					break;
			}
		}else{ 
			cur++;
		}
	}

	if( found != 1 ){ 
		printf( "gasm: Unknown instruction at line %" PRIu64 "\n", line );
		printf( "\t%s\n", inst );
		return -1;
	}

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;	
}

/* EOF */
