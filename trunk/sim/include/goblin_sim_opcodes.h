/*
 * _GOBLIN_SIM_OPCODES_H_
 * 
 * GOBLIN-SIM OPCODES HEADER FILE 
 * 
 * WARNING: DO NOT INCLUDE THIS FILE DIRECTLY
 *          ALWAYS USE THE TOP-LEVEL HEADER: 
 *          GOBLIN_SIM.H
 * 
 */


#ifndef	_GOBLIN_SIM_OPCODES_H_
#define _GOBLIN_SIM_OPCODES_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <sys/types.h>

/* --------------------------------------------- MACROS */
#define GSIM_OPCODE_VALID	0x00000001	/*! INSTRUCTION OPCODE: VALID   */
#define GSIM_OPCODE_INVALID	0x10000000	/*! INSTRUCTION OPCODE: INVALID */

#define	GSIM_OPCODE_NOREG	0x00000001	/*! INSTRUCTION FORMAT: NO REGISTER ARGUMENTS */
#define	GSIM_OPCODE_RT		0x00000002	/*! INSTRUCTION FORMAT: Rt TARGET ARGUMENT ONLY */
#define	GSIM_OPCODE_RA		0x00000004	/*! INSTRUCTION FORMAT: Ra ARGUMENT ONLY */
#define	GSIM_OPCODE_RARB	0x00000008	/*! INSTRUCTION FORMAT: Ra,Rb ARGUMENTS ONLY */
#define	GSIM_OPCODE_RART	0x00000010	/*! INSTRUCTION FORMAT: Ra,Rt ARGUMENTS */
#define	GSIM_OPCODE_RARBRT	0x00000020	/*! INSTRUCTION FORMAT: Ra,Rb,Rt ARGUMENTS */
#define GSIM_OPCODE_VECTOR	0x00000040	/*! INSTRUCTION TYPE:   VECTOR MODE */

#define	GSIM_REG_RW		0x00000001	/*! REGISTER TYPE:      READ-WRITE */
#define	GSIM_REG_RO		0x00000002	/*! REGISTER TYPE:      READ-ONLY */

#define GSIM_INST_LOWER_R0	0x000000000000003F

/* --------------------------------------------- DATA STRUCTURES */
struct gsim_opcodes_t{
	uint32_t	valid[256];
	uint32_t	format[256];
	char		name[256][64];
};

struct gsim_reg_t{
	uint32_t	format[64];
	char		name[64][64];
};

#ifdef __cplusplus
} /* extern C */
#endif

#endif	/* _GOBLIN_SIM_TYPES_H_ */

/* EOF */
