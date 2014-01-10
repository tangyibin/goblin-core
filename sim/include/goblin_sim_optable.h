/*
 * _GOBLIN_SIM_OPTABLE_H_
 * 
 * GOBLIN-SIM OPCODE TABLE HEADER FILE 
 * 
 * 
 */


#ifndef	_GOBLIN_SIM_OPTABLE_H_
#define _GOBLIN_SIM_OPTABLE_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <sys/types.h>

/* --------------------------------------------- MACROS */
#define GSIM_OPCODE_VALID	0x00000001		/*! INSTRUCTION OPCODE: VALID   */
#define GSIM_OPCODE_INVALID	0x10000000		/*! INSTRUCTION OPCODE: INVALID */

#define GSIM_OPCODE_UNK		0x00000000		/*! INSTRUCTION FORMAT: UNKNOWN */
#define	GSIM_OPCODE_NOREG	0x00000001		/*! INSTRUCTION FORMAT: NO REGISTER ARGUMENTS */
#define	GSIM_OPCODE_RT		0x00000002		/*! INSTRUCTION FORMAT: Rt TARGET ARGUMENT ONLY */
#define	GSIM_OPCODE_RA		0x00000004		/*! INSTRUCTION FORMAT: Ra ARGUMENT ONLY */
#define	GSIM_OPCODE_RARB	0x00000008		/*! INSTRUCTION FORMAT: Ra,Rb ARGUMENTS ONLY */
#define	GSIM_OPCODE_RART	0x00000010		/*! INSTRUCTION FORMAT: Ra,Rt ARGUMENTS */
#define	GSIM_OPCODE_RARBRT	0x00000020		/*! INSTRUCTION FORMAT: Ra,Rb,Rt ARGUMENTS */
#define	GSIM_OPCODE_RTRARB	0x00000040		/*! INSTRUCTION FORMAT: Rt,Ra,Rb ARGUMENTS */
#define GSIM_OPCODE_VECTOR	0x00000080		/*! INSTRUCTION TYPE:   VECTOR MODE */

#define	GSIM_REG_RW		0x00000001		/*! REGISTER TYPE:      READ-WRITE */
#define	GSIM_REG_RO		0x00000002		/*! REGISTER TYPE:      READ-ONLY */
#define	GSIM_REG_INVALID	0x10000000		/*! REGISTER TYPE:      INVALID */

/* --------------------------------------------- DATA STRUCTURES */

struct {
	const char *const name;
	uint32_t opcode;
	uint32_t format;
} gsim_optable_t[] = {
	/* instruction  opcode             options                      */
	{ "nop",	0x00,	GSIM_OPCODE_NOREG|GSIM_OPCODE_VECTOR	},
	{ "mov",	0x01, 	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR 	},
	{ "ld.ub",	0x02,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "ld.uw",	0x03,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "ld.ud",	0x04,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "ld.uq", 	0x05, 	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "ld.sb",	0x06,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "ld.sw",	0x07,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "ld.sd", 	0x08, 	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "st.ub",	0x09,	GSIM_OPCODE_RTRARB|GSIM_OPCODE_VECTOR	},
	{ "st.uw", 	0x0A,	GSIM_OPCODE_RTRARB|GSIM_OPCODE_VECTOR	},
	{ "st.ud",	0x0B,	GSIM_OPCODE_RTRARB|GSIM_OPCODE_VECTOR	},
	{ "st.uq",	0x0C, 	GSIM_OPCODE_RTRARB|GSIM_OPCODE_VECTOR	},
	{ "st.sb",	0x0D,	GSIM_OPCODE_RTRARB|GSIM_OPCODE_VECTOR	}, 
	{ "st.sw", 	0x0E,	GSIM_OPCODE_RTRARB|GSIM_OPCODE_VECTOR	},
	{ "st.sd", 	0x0F,	GSIM_OPCODE_RTRARB|GSIM_OPCODE_VECTOR	},
	{ "ld.ga",	0x1A,	GSIM_OPCODE_RARBRT			},
	{ "st.ga",	0x1B,	GSIM_OPCODE_RTRARB			},
	{ "fence",	0x1F,	GSIM_OPCODE_NOREG			},
	{ "and",	0x20,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "andc",	0x21,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "or",		0x22,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "orc", 	0x23,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "nand",	0x24,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "nor",	0x25,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "xor",	0x26,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "xnor",	0x27,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "add.sq",	0x30,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "add.uq", 	0x31,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "sub.sq",	0x32,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "sub.uq",	0x33,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "mul.sq",	0x34,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "mul.uq",	0x35,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "div.sq",	0x36,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "div.uq",	0x37,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "abs.sq",	0x38,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "neg.sq",	0x39,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "shfl.sq",	0x3A,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "shfl.uq",	0x3B,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "shfr.sq",	0x3C,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "shfr.uq",	0x3D,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "cmp.sq",	0x3E,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "cmp.uq",	0x3F,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "add.fs", 	0x40,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "add.fd", 	0x41,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "sub.fs",	0x42,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "sub.fd",	0x43,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "mul.fs",	0x44,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "mul.fd",	0x45,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "div.fs",	0x46,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "div.fd",	0x47,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "abs.fs",	0x48,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "abs.fd",	0x49,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "neg.fs",	0x4A,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "neg.fd",	0x4B,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "cmp.fs",	0x4E,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "cmp.fd", 	0x4F,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "cvt.fd.fs",	0x50,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "cvt.fd.sq",	0x51,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "cvt.fd.uq",	0x52,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "cvt.fs.fd",	0x53,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "cvt.fs.sq",	0x54,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "cvt.fs.uq",	0x55,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "cvt.sq.fs",	0x56,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "cvt.sq.fd",	0x57,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "cvt.sq.uq",	0x58,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "cvt.uq.sq",	0x59,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "cvt.uq.fs",	0x5A,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "cvt.uq.fd",	0x5B,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "amo.add.sd",	0x60,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.add.sq",	0x61,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.sub.sd",	0x62,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.sub.sq",	0x63,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.exch.sd",0x64,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.exch.sq",0x65,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.min.sd",	0x66,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.min.sq",	0x67,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.max.sd",	0x68,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.max.sq",	0x69,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.inc.sd",	0x6A,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.inc.sq",	0x6B,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.dec.sd",	0x6C,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.dec.sq",	0x6D,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.cas.sd",	0x6E,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.cas.sq",	0x6F,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.and.sd",	0x70,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.and.sq",	0x71,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.or.sd",	0x72,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.or.sq",	0x73,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.xor.sd",	0x74,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "amo.xor.sq",	0x75,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "min.sq",	0x80,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "min.uq",	0x81,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "max.sq",	0x82,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "max.uq",	0x83,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "min.fs",	0x90,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "min.fd",	0x91,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "max.fs",	0x92,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "max.fd",	0x93,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "sel.cc3.ne",	0xA0,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "sel.cc3.eq",	0xA0,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "sel.cc3.gt",	0xA1,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "sel.cc3.lt",	0xA2,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "sel.cc3.gte",0xA3,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "sel.cc3.lte",0xA4,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "rtn",	0xB0,	GSIM_OPCODE_NOREG			},
	{ "br",		0xBA,	GSIM_OPCODE_RT				},
	{ "br",		0xBB,	GSIM_OPCODE_RARBRT			},
	{ "bra",	0xC0,	GSIM_OPCODE_RT				},
	{ "bra",	0xC1,	GSIM_OPCODE_RARBRT			},
	{ "call",	0xCA,	GSIM_OPCODE_RT				},
	{ "call",	0xCB,	GSIM_OPCODE_RARBRT			},
	{ "calla",	0xD0,	GSIM_OPCODE_RT				},
	{ "calla",	0xD1,	GSIM_OPCODE_RART			},
	{ "system",	0xDA,	GSIM_OPCODE_RA				},	
	{ "spawn",	0xDB,	GSIM_OPCODE_RT				},
	{ "join",	0xDC,	GSIM_OPCODE_RA				},
	{ "iwait",	0xDD,	GSIM_OPCODE_RT				},
	{ "peg",	0xDE,	GSIM_OPCODE_NOREG			},
	{ "future",	0xDF,	GSIM_OPCODE_RART			},
	{ "popcnt",	0xE0,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "addc",	0xE1,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "subb",	0xE3,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "mulu",	0xE5,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "lzc",	0xEA,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "tzc",	0xEB,	GSIM_OPCODE_RART|GSIM_OPCODE_VECTOR	},
	{ "bsel",	0xEC,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "getc",	0xF1,	GSIM_OPCODE_RT|GSIM_OPCODE_VECTOR	},
	{ "setc", 	0xF2,	GSIM_OPCODE_RA|GSIM_OPCODE_VECTOR	},
	{ "getb",	0xF3,	GSIM_OPCODE_RT|GSIM_OPCODE_VECTOR	},
	{ "setb",	0xF4,	GSIM_OPCODE_RA|GSIM_OPCODE_VECTOR	},
	{ "dshfl",	0xFA,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "dshfr",	0xFD,	GSIM_OPCODE_RARBRT|GSIM_OPCODE_VECTOR	},
	{ "lfshv",	0xFF,	GSIM_OPCODE_RA|GSIM_OPCODE_VECTOR	},

	{ NULL, 	0x00,	GSIM_OPCODE_INVALID }
};


#ifdef __cplusplus
} /* extern C */
#endif

#endif	/* _GOBLIN_SIM_OPTABLE_H_ */

/* EOF */
