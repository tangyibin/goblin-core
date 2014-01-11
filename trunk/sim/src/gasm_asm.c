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
	uint32_t vector	= 0x00;
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
				vector = 1;
			}

			format &= (~GSIM_OPCODE_VECTOR);

			/* validate the args */
			switch( format )
			{
				case GSIM_OPCODE_NOREG:
					if( count > 0 ){ 
						printf( "gasm: Incorrect instruction arguments at line %" PRIu64 "\n",
                                                                line );	
						printf( "\t>%s\n", inst );
						printf( "\t>Expecting %s\n", gsim_optable_t[cur].name );
						return -1;
					}
					break;
				case GSIM_OPCODE_RT:
					if( (count > 1) || (count==0) ){ 
						printf( "gasm: Incorrect instruction arguments at line %" PRIu64 "\n",
                                                                line );	
						printf( "\t>%s\n", inst );
						printf( "\t>Expecting %s %%RT\n", gsim_optable_t[cur].name );
						return -1;
					}
					break;
				case GSIM_OPCODE_RA:
					if( (count > 1) || (count==0) ){ 
						printf( "gasm: Incorrect instruction arguments at line %" PRIu64 "\n",
                                                                line );	
						printf( "\t>%s\n", inst );
						printf( "\t>Expecting %s %%RA\n", gsim_optable_t[cur].name );
						return -1;
					}
					break;
				case GSIM_OPCODE_RARB:
					if( (count > 2) || (count<2) ){ 
						printf( "gasm: Incorrect instruction arguments at line %" PRIu64 "\n",
                                                                line );	
						printf( "\t>%s\n", inst );
						printf( "\t>Expecting %s %%RA,%%RB\n", gsim_optable_t[cur].name );
						return -1;
					}
					break;
				case GSIM_OPCODE_RART:
					if( (count > 2) || (count<2) ){ 
						printf( "gasm: Incorrect instruction arguments at line %" PRIu64 "\n",
                                                                line );	
						printf( "\t>%s\n", inst );
						printf( "\t>Expecting %s %%RA,%%RT\n", gsim_optable_t[cur].name );
						return -1;
					}
					break;
				case GSIM_OPCODE_RARBRT:
					if( (count > 3) || (count<3) ){ 
						printf( "gasm: Incorrect instruction arguments at line %" PRIu64 "\n",
                                                                line );	
						printf( "\t>%s\n", inst );
						printf( "\t>Expecting %s %%RA,%%RB,%%RT\n", gsim_optable_t[cur].name );
						return -1;
					}
					break;
				case GSIM_OPCODE_RTRARB:
					if( (count > 3) || (count<3) ){ 
						printf( "gasm: Incorrect instruction arguments at line %" PRIu64 "\n",
                                                                line );	
						printf( "\t>%s\n", inst );
						printf( "\t>Expecting %s %%RT,%%RB,%%RA\n", gsim_optable_t[cur].name );
						return -1;
					}
					break;
				default:
					printf( "gasm: Incorrect instruction arguments at line %" PRIu64 "\n",
                                                                line );	
					printf( "\t>%s\n", inst );
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
