/* 
 * 
 * _GSIM_DUMP_INST_C_
 * 
 * GOBLIN-SIM INSTRUCTION DUMP FUNCTIONS
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


/* -------------------------------------------------- GSIM_GEN_INST */
/* 
 * GSIM_GEN_INST
 * 
 */
extern void gsim_gen_inst( struct gsim_t *sim, uint32_t inst )
{
	/* vars */
	uint32_t tmp	= 0;
	uint32_t vect	= 0;
	/* ---- */
#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif


	/* 
	 * determine the register args
	 */
	if( (sim->opcodes.format[inst] & GSIM_OPCODE_VECTOR) > 0 ){ 
		vect	= 1;
		tmp 	= (sim->opcodes.format[inst] & ~GSIM_OPCODE_VECTOR);
	}else{ 
		tmp	= sim->opcodes.format[inst];
	}

	switch( tmp ) {
		case GSIM_OPCODE_NOREG:
			
			/* 
			 * just print the instruction
			 */		
			printf( "%s\n", sim->opcodes.name[inst] );

			break;
		case GSIM_OPCODE_RT:

			/* 
			 * print inst + %rN
			 */
			printf( "%s%s%c%s%d\n", sim->opcodes.name[inst], "  ", 37, "r", gsim_rand_reg_r() );

			/* 
			 * print inst + %vN
			 */
			if( vect == 1 ){ 
				printf( "%s%s%c%s%d\n", sim->opcodes.name[inst], "  ", 37, "v", gsim_rand_reg_v() );
			}

			/* 
			 * print inst + %r[32-y]; y is RW
			 */
			printf( "%s%s%c%s\n", sim->opcodes.name[inst], "  ", 37, 
					sim->registers.name[gsim_rand_reg_ctrl_rw()] );

			break;
		case GSIM_OPCODE_RA: 
			
			/* 
			 * print inst + %rN
			 */
			printf( "%s%s%c%s%d\n", sim->opcodes.name[inst], "  ", 37, "r", gsim_rand_reg_r() );

			/* 
			 * print inst + %vN
			 */
			if( vect == 1 ){ 
				printf( "%s%s%c%s%d\n", sim->opcodes.name[inst], "  ", 37, "v", gsim_rand_reg_v() );
			}

			/* 
			 * print inst + %r[32-y]; y is RW
			 */
			printf( "%s%s%c%s\n", sim->opcodes.name[inst], "  ", 37, 
					sim->registers.name[gsim_rand_reg_ctrl()] );

			break;
		case GSIM_OPCODE_RARB:
			
			/* 
			 * print inst + %rN + %rN
			 */
			printf( "%s%s%c%s%d%s%c%s%d\n", sim->opcodes.name[inst], 
						"  ", 37, "r", gsim_rand_reg_r(), 
						",", 37, "r", gsim_rand_reg_r() );

			/* 
			 * print inst + %vN + %vN
			 */
			if( vect == 1 ){ 
				printf( "%s%s%c%s%d%s%c%s%d\n", sim->opcodes.name[inst], 
					"  ", 37, "v", gsim_rand_reg_v(), 
					",", 37, "v", gsim_rand_reg_v() );
			}

			/* 
			 * print inst + %r[32-y] + %rN; y is RW
			 */
			printf( "%s%s%c%s%s%c%s%d\n", sim->opcodes.name[inst], "  ", 37, 
					sim->registers.name[gsim_rand_reg_ctrl()], 
					",", 37, "r", gsim_rand_reg_r() );

			break;
		case GSIM_OPCODE_RART:
			
			/* 
			 * print inst + %rN + %rN
			 */
			printf( "%s%s%c%s%d%s%c%s%d\n", sim->opcodes.name[inst], 
						"  ", 37, "r", gsim_rand_reg_r(), 
						",", 37, "r", gsim_rand_reg_r() );

			if( vect == 1 ){ 
				/* 
			 	 * print inst + %vN + %vN
			 	 */
				printf( "%s%s%c%s%d%s%c%s%d\n", sim->opcodes.name[inst], 
					"  ", 37, "v", gsim_rand_reg_v(), 
					",", 37, "v", gsim_rand_reg_v() );

				/* 
			 	 * print inst + %rN + %vN
			 	 */
				printf( "%s%s%c%s%d%s%c%s%d\n", sim->opcodes.name[inst], 
					"  ", 37, "v", gsim_rand_reg_r(), 
					",", 37, "v", gsim_rand_reg_v() );
			}

			/* 
			 * print inst + %r[32-y] + %rN; y is RW
			 */
			printf( "%s%s%c%s%s%c%s%d\n", sim->opcodes.name[inst], "  ", 37, 
					sim->registers.name[gsim_rand_reg_ctrl()], 
					",", 37, "r", gsim_rand_reg_r() );

			break;
		case GSIM_OPCODE_RARBRT:
			
			/* 
			 * print inst + %rN + %rN + %rN
			 */
			printf( "%s%s%c%s%d%s%c%s%d%s%c%s%d\n", sim->opcodes.name[inst], 
						"  ", 37, "r", gsim_rand_reg_r(), 
						",", 37, "r", gsim_rand_reg_r(), 
						",", 37, "r", gsim_rand_reg_r() );

			if( vect == 1 ){ 
				/* 
			 	 * print inst + %vN + %vN + %vN
			 	 */
				printf( "%s%s%c%s%d%s%c%s%d%s%c%s%d\n", sim->opcodes.name[inst], 
						"  ", 37, "v", gsim_rand_reg_v(), 
						",", 37, "v", gsim_rand_reg_v(), 
						",", 37, "v", gsim_rand_reg_v() );

				/* 
			 	 * print inst + %vN + %rN + %vN
			 	 */
				printf( "%s%s%c%s%d%s%c%s%d%s%c%s%d\n", sim->opcodes.name[inst], 
						"  ", 37, "v", gsim_rand_reg_v(), 
						",", 37, "r", gsim_rand_reg_r(), 
						",", 37, "v", gsim_rand_reg_v() );
			}

			/* 
			 * print inst + %r[32-y] + %rN + %rN; y is RW
			 */
			printf( "%s%s%c%s%s%c%s%d%s%c%s%d\n", sim->opcodes.name[inst], "  ", 37, 
					sim->registers.name[gsim_rand_reg_ctrl()], 
					",", 37, "r", gsim_rand_reg_r(),
					",", 37, "r", gsim_rand_reg_r() );

			break;
		default:
			
			/* 
			 * who am I?  print something unknown
			 */
			printf( "#-- UNKNOWN INSTRUCTION : opc=0x%08x\n", inst );

			break;
	}

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif

	return ;
}

/* -------------------------------------------------- GSIM_DUMP_INST */
/* 
 * GSIM_DUMP_INST 
 * 
 */
extern void gsim_dump_inst( struct gsim_t *sim )
{
	/* vars */
	uint32_t i	= 0;
	/* ---- */


#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

	GSIM_PRINT_MSG( "DUMPING INSTRUCTION TABLE...." );

	/* 
	 * for each instruction, 
	 * make sure its valid and generate
	 * its various arg types 
	 */
	for( i=0; i<256; i++ ){ 

		if( sim->opcodes.valid[i] == GSIM_OPCODE_VALID ){ 

			/* 
			 * dump the instruction info
			 *
			 */
			gsim_gen_inst( sim, i );
		}

	}


#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return ;
}


/* EOF */
