/* 
 * _MEM_SIM_MACROS_H_ 
 * 
 * MEMORY INTERFACE SIMULATION LIBRARY 
 * 
 * MACROS HEADER FILE 
 * 
 */

#ifndef _MEM_SIM_MACROS_H_ 
#define _MEM_SIM_MACROS_H_ 

#ifdef __cplusplus
extern "C" {
#endif


/* ------------------------------------------------ VERSION MACROS */
#ifndef MEMSIM_MAJOR_VERSION
#define MEMSIM_MAJOR_VERSION	0
#endif

#ifndef MEMSIM_MINOR_VERSION
#define MEMSIM_MINOR_VERSION	1
#endif


/* ------------------------------------------------ RETURN CODES */
#define		MEMSIM_STALL	-2
#define		MEMSIM_ERROR	-1
#define		MEMSIM_OK	0

/* ------------------------------------------------ VALUE MACROS */
#define MEMSIM_TIDS_PER_ENTRY	32

#ifndef GSIM_REG_GCONST_PID
#define	GSIM_REG_GCONST_PID	0x000000000000FFFF
#endif

#ifndef GSIM_REG_GCONST_NID
#define	GSIM_REG_GCONST_NID	0x00000000FFFF0000
#endif

#ifndef GSIM_REG_GCONST_SID
#define	GSIM_REG_GCONST_SID	0x000000FF00000000
#endif

#ifndef GSIM_REG_GCONST_TG
#define	GSIM_REG_GCONST_TG	0x0000FF0000000000
#endif

#ifndef GSIM_REG_GCONST_TP
#define	GSIM_REG_GCONST_TP	0x00FF000000000000
#endif

#ifndef GSIM_REG_GCONST_TC
#define	GSIM_REG_GCONST_TC	0xFF00000000000000
#endif

/* ------------------------------------------------ TRACE MACROS */
#define	MEMSIM_PRINT_TRACE( s )		( fprintf( stdout, "MEMSIM_TRACE %s:%d : %s\n", __FUNCTION__, __LINE__, s ))


#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _MEM_SIM_MACROS_H_ */

/* EOF */
