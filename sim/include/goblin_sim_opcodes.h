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

/* --------------------------------------------- INSTRUCTION FORMAT */
/* 
 * Instruction Set Format
 * - Little Endian
 * - Minimum Instruction Payload = 8 bytes
 * - Maximum Instruction Payload = 16 bytes [2 x 8 byte words]
 * - All instruction data is contained in lower 8 bytes
 * - All immediate values are contained in upper 8 bytes
 * - Instruction data is split into two 4 byte instruction payloads
 * 
 * - Instruction Data
 * FIELD:    [CTR][OPC][R2][R1][R0][CTR][OPC][R2][R1][R0]
 * WIDTH:    [  6][  8][ 6][ 6][ 6][  6][  8][ 6][ 6][ 6]
 * BITS:     63                                         0
 * 
 * - Immediate Values [8-byte immediate]
 * FIELD:    [                   IMM8                   ]
 * WIDTH:    [                   64                     ]
 * BITS:    127                                        64
 * 
 * - Immediate Values [4-byte immediate]
 * FIELD:    [       IMM4         ][      IMM4          ]               
 * WIDTH:    [       32           ][      32            ]
 * BITS:    127                                        64
 * 
 * 
 */


/* --------------------------------------------- MACROS */
#define GSIM_OPCODE_VALID	0x00000001		/*! INSTRUCTION OPCODE: VALID   */
#define GSIM_OPCODE_INVALID	0x10000000		/*! INSTRUCTION OPCODE: INVALID */

#define	GSIM_OPCODE_NOREG	0x00000001		/*! INSTRUCTION FORMAT: NO REGISTER ARGUMENTS */
#define	GSIM_OPCODE_RT		0x00000002		/*! INSTRUCTION FORMAT: Rt TARGET ARGUMENT ONLY */
#define	GSIM_OPCODE_RA		0x00000004		/*! INSTRUCTION FORMAT: Ra ARGUMENT ONLY */
#define	GSIM_OPCODE_RARB	0x00000008		/*! INSTRUCTION FORMAT: Ra,Rb ARGUMENTS ONLY */
#define	GSIM_OPCODE_RART	0x00000010		/*! INSTRUCTION FORMAT: Ra,Rt ARGUMENTS */
#define	GSIM_OPCODE_RARBRT	0x00000020		/*! INSTRUCTION FORMAT: Ra,Rb,Rt ARGUMENTS */
#define GSIM_OPCODE_VECTOR	0x00000040		/*! INSTRUCTION TYPE:   VECTOR MODE */

#define	GSIM_REG_RW		0x00000001		/*! REGISTER TYPE:      READ-WRITE */
#define	GSIM_REG_RO		0x00000002		/*! REGISTER TYPE:      READ-ONLY */

#define GSIM_INST_LOWER_R0	0x000000000000003F	/*! REGISTER: LOWER, R0 */
#define GSIM_INST_LOWER_R1	0x0000000000000FC0	/*! REGISTER: LOWER, R1 */
#define GSIM_INST_LOWER_R2	0x000000000003F000	/*! REGISTER: LOWER, R2 */
#define GSIM_INST_LOWER_OPC	0x0000000003FC0000	/*! OPCODE:   LOWER */
#define GSIM_INST_LOWER_CTRL	0x00000000FC000000	/*! CONTROL:  CONTROL BLOCK */
#define GSIM_INST_LOWER_VEC	0x000000000400000	/*! CONTROL:  VEC */
#define GSIM_INST_LOWER_V0	0x0000000008000000	/*! CONTROL:  V0 */
#define GSIM_INST_LOWER_V1	0x0000000010000000	/*! CONTROL:  V1 */
#define GSIM_INST_LOWER_BRK	0x0000000020000000	/*! CONTROL:  BRK */
#define GSIM_INST_LOWER_IMM8	0x0000000040000000	/*! CONTROL:  IMM8 */
#define GSIM_INST_LOWER_IMM4	0x0000000080000000	/*! CONTROL:  IMM4 */

#define GSIM_INST_UPPER_R0	0x0000003F00000000	/*! REGISTER: UPPER, R0 */
#define GSIM_INST_UPPER_R1	0x00000FC000000000	/*! REGISTER: UPPER, R1 */
#define GSIM_INST_UPPER_R2	0x0003F00000000000	/*! REGISTER: UPPER, R2 */
#define GSIM_INST_UPPER_OPC	0x03FC000000000000	/*! OPCODE:   UPPER */
#define GSIM_INST_UPPER_CTRL	0xFC00000000000000	/*! CONTROL:  CONTROL BLOCK */
#define GSIM_INST_UPPER_VEC	0x0400000000000000	/*! CONTROL:  VEC */
#define GSIM_INST_UPPER_V0	0x0800000000000000	/*! CONTROL:  V0 */
#define GSIM_INST_UPPER_V1	0x1000000000000000	/*! CONTROL:  V1 */
#define GSIM_INST_UPPER_BRK	0x2000000000000000	/*! CONTROL:  BRK */
#define GSIM_INST_UPPER_IMM8	0x4000000000000000	/*! CONTROL:  IMM8 */
#define GSIM_INST_UPPER_IMM4	0x8000000000000000	/*! CONTROL:  IMM4 */

#define GSIM_INST_IMM8		0xFFFFFFFFFFFFFFFF	/*! IMM: 8-BYTE IMMEDIATE */
#define GSIM_INST_LOWER_IMM4	0x00000000FFFFFFFF	/*! IMM: LOWER 4-BYTE IMMEDIATE */
#define GSIM_INST_UPPER_IMM4	0xFFFFFFFF00000000	/*! IMM: UPPER 4-BYTE IMMEDIATE */

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
