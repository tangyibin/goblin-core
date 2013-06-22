/*
 * _GOBLIN_SIM_MACROS_H_
 * 
 * GOBLIN-SIM MACROS HEADER FILE 
 * 
 * WARNING: DO NOT INCLUDE THIS FILE DIRECTLY
 *          ALWAYS USE THE TOP-LEVEL HEADER: 
 *          GOBLIN_SIM.H
 * 
 */


#ifndef	_GOBLIN_SIM_MACROS_H_
#define _GOBLIN_SIM_MACROS_H_

#ifdef __cplusplus
extern "C" {
#endif


/* --------------------------------------------- VERSION MACROS */
#ifndef GSIM_MAJOR_VERSION
#define GSIM_MAJOR_VERSION	0
#endif

#ifndef GSIM_MINOR_VERSION
#define GSIM_MINOR_VERSION	1
#endif

#ifndef GSIM_SVN_VERSION
#define GSIM_SVN_VERSION	0000
#endif


/* --------------------------------------------- SIMULATION OPTION MACROS */
#define	GSIM_OPT_TRACING	0x0000000000000001	/*! RUNTIME OPTIONS: ENABLE TRACING */
#define GSIM_OPT_EXCEPTIONS	0x0000000000000002	/*! RUNTIME OPTIONS: ENABLE EXCEPTIONS */
#define GSIM_OPT_TASKING	0x0000000000000003	/*! RUNTIME OPTIONS: ENABLE TASKING */

#define GSIM_OPT_DEFAULT	(GSIM_OPT_EXCEPTIONS|
				GSIM_OPT_TASKING)


#ifdef __cplusplus
} /* extern C */
#endif

#endif	/* _GOBLIN_SIM_MACROS_H_ */

/* EOF */
