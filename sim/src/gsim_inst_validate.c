/* 
 * 
 * _GSIM_INST_VALIDATE_C_
 * 
 * GOBLIN-SIM INSTRUCTION VALIDATION
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


/* -------------------------------------------------- GSIM_INST_VALIDATE */
/* 
 * GSIM_INST_VALIDATE
 * 
 */
extern int gsim_inst_validate( 	struct gsim_t *sim, 
				uint32_t r0, 
				uint32_t r1, 
				uint32_t r2, 
				uint32_t opc, 
				uint32_t ctr, 
				uint32_t ctr_vec, 
				uint32_t ctr_v0, 
				uint32_t ctr_v1, 
				uint32_t ctr_brk,
				uint32_t ctr_imm4, 
				uint32_t ctr_imm8, 
				int32_t  imm4, 
				int64_t  imm8 )
{
	/* vars */
	uint32_t format	= 0;
	/* ---- */

#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_ENTRY();
#endif

	/*
	 * Stage1: Validate the opcode 
	 */
	if( (opc > 0xFF) || (sim->opcodes.valid[opc] == GSIM_OPCODE_INVALID) ){
		/* -- invalid */

		#ifdef GSIM_DEBUG
		printf( "GSIM_INST_VALIDATE: Failed to verify opcode : 0x%08x\n", opc );
		#endif

		return -1;
	}

	/* 
	 * Stage2: Test the vector state 
	 */	
	if( (ctr_vec == 1) && ((sim->opcodes.format[opc] & GSIM_OPCODE_VECTOR)==0) ){
		/* invalid vector instruction */

		#ifdef GSIM_DEBUG
		printf( "GSIM_INST_VALIDATE: Invalid vector operation : 0x%08x\n", opc );
		#endif

		return -1;
	}

	if( ((sim->opcodes.format[opc] & GSIM_OPCODE_RART)==0) 
		& (ctr_v0 == 0) & (ctr_v1 == 0) )
	{
		/* invalid vector arguments */

		#ifdef GSIM_DEBUG
		printf( "GSIM_INST_VALIDATE: Invalid vector register args :\
			opc=0x%08x, r0=0x%08x, r1=0x%08x, r2=0x%08x\n", opc, r0, r1, r2 );
		#endif
	}	

	/* 
	 * Stage3: Validate the Registers
	 */

	if( (r0 > 0x3F) || (r1 > 0x3F) || (r2 > 0x3F) ){
		#ifdef GSIM_DEBUG
		printf( "GSIM_INST_VALIDATE: Invalid register indexes :\
			opc=0x%08x, r0=0x%08x, r1=0x%08x, r2=0x%08x\n", opc, r0, r1, r2 );
		#endif

		return -1;
	}

	if( (sim->opcodes.format[opc] & GSIM_OPCODE_VECTOR) > 0 ){
		format = sim->opcodes.format[opc] & ~GSIM_OPCODE_VECTOR;
	}else{
		format = sim->opcodes.format[opc];
	}

	switch( format )
	{
		case GSIM_OPCODE_NOREG: 
			if( (r0 != 0x35) || (r1 != 0x35) || (r2 != 0x35) ){
				#ifdef GSIM_DEBUG
				printf( "GSIM_INST_VALIDATE: Invalid register args: All must be 0x35 :\
					opc=0x%08x, r0=0x%08x, r1=0x%08x, r2=0x%08x\n", opc, r0, r1, r2 );
				#endif
				return -1;
			}
			break;
		case GSIM_OPCODE_RT:
			if( (r0 != 0x35) || (r1 != 0x35) ){
				#ifdef GSIM_DEBUG
				printf( "GSIM_INST_VALIDATE: Invalid register args: r0,r1 must be 0x35 :\
					opc=0x%08x, r0=0x%08x, r1=0x%08x, r2=0x%08x\n", opc, r0, r1, r2 );
				#endif
				return -1;
			}
			break;
		case GSIM_OPCODE_RA:
			if( (r2 != 0x35) || (r1 != 0x35) ){
				#ifdef GSIM_DEBUG
				printf( "GSIM_INST_VALIDATE: Invalid register args: r1,r2 must be 0x35 :\
					opc=0x%08x, r0=0x%08x, r1=0x%08x, r2=0x%08x\n", opc, r0, r1, r2 );
				#endif
				return -1;
			}
			break;
		case GSIM_OPCODE_RARB:
			if( (r2 != 0x35)  ){
				#ifdef GSIM_DEBUG
				printf( "GSIM_INST_VALIDATE: Invalid register args: r2 must be 0x35 :\
					opc=0x%08x, r0=0x%08x, r1=0x%08x, r2=0x%08x\n", opc, r0, r1, r2 );
				#endif
				return -1;
			}
			break;
		case GSIM_OPCODE_RART:
			if( (r1 != 0x35)  ){
				#ifdef GSIM_DEBUG
				printf( "GSIM_INST_VALIDATE: Invalid register args: r1 must be 0x35 :\
					opc=0x%08x, r0=0x%08x, r1=0x%08x, r2=0x%08x\n", opc, r0, r1, r2 );
				#endif
				return -1;
			}
			break;
		case GSIM_OPCODE_RARBRT:
		default:
			break;
	}


	if( ctr_imm4 == 1 ){ 

		if( (r0 != 0x36) && (r1 != 0x36) ){
			
			#ifdef GSIM_DEBUG
			printf( "GSIM_INST_VALIDATE: Invalid imm4 bit set: r0 or r1 must be 0x36 :\
					opc=0x%08x, r0=0x%08x, r1=0x%08x, r2=0x%08x\n", opc, r0, r1, r2 );
			#endif

			return -1;
		}

	}

	if( ctr_imm8 == 1 ){ 

		if( (r0 != 0x37) && (r1 != 0x37) ){
			
			#ifdef GSIM_DEBUG
			printf( "GSIM_INST_VALIDATE: Invalid imm4 bit set: r0 or r1 must be 0x37 :\
					opc=0x%08x, r0=0x%08x, r1=0x%08x, r2=0x%08x\n", opc, r0, r1, r2 );
			#endif

			return -1;
		}

	}

	if( r2 > 0x2F ){ 
		#ifdef GSIM_DEBUG
		printf( "GSIM_INST_VALIDATE: Invalid register target: opc=0x%08x, r2=0x%08x\n", opc, r2 );
		#endif
		
		return -1;
	}

	if( sim->registers.format[r0] == GSIM_REG_INVALID ){ 
		#ifdef GSIM_DEBUG
		printf( "GSIM_INST_VALIDATE: Invalid register: opc=0x%08x, r0=0x%08x\n", opc, r0 );
		#endif
		
		return -1;
	}

	if( sim->registers.format[r1] == GSIM_REG_INVALID ){ 
		#ifdef GSIM_DEBUG
		printf( "GSIM_INST_VALIDATE: Invalid register: opc=0x%08x, r1=0x%08x\n", opc, r1 );
		#endif
		
		return -1;
	}

	if( sim->registers.format[r2] == GSIM_REG_INVALID ){ 
		#ifdef GSIM_DEBUG
		printf( "GSIM_INST_VALIDATE: Invalid register: opc=0x%08x, r2=0x%08x\n", opc, r2 );
		#endif
		
		return -1;
	}

#ifdef GSIM_DEBUG
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;	
}


/* EOF */
