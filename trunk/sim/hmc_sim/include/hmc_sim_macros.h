/* 
 * _HMC_SIM_MACROS_H_
 * 
 * HYBRID MEMORY CUBE SIMULATION LIBRARY
 * 
 * MACROS HEADER FILE 
 * 
 */

#ifndef _HMC_SIM_MACROS_H_
#define _HMC_SIM_MACROS_H_


#ifdef __cplusplus
extern "C" {
#endif


/* -------------------------------------------- RETURN CODES */
#define		HMC_ERROR		-1
#define		HMC_OK			0
#define		HMC_STALL		2

/* -------------------------------------------- MACROS */
#define		HMC_MAX_DEVS		8
#define		HMC_MAX_LINKS		8
#define		HMC_MIN_LINKS		4
#define		HMC_MAX_CAPACITY	8
#define		HMC_MIN_CAPACITY	2
#define		HMC_MAX_VAULTS		4
#define		HMC_MIN_VAULTS		4
#define		HMC_MAX_BANKS		8
#define		HMC_MIN_BANKS		16
#define		HMC_MIN_DRAMS		20
#define		HMC_MAX_DRAMS		20
#define		HMC_MIN_QUEUE_DEPTH	2
#define		HMC_MAX_QUEUE_DEPTH	65536
#define 	HMC_MAX_UQ_PACKET	18

#define		HMC_RQST_VALID		1
#define		HMC_RQST_INVALID	0

#define		HMC_1GB		1073741824

#ifdef __cplusplus
} /* extern C */
#endif

#endif	/* _HMC_SIM_MACROS_H_ */

/* EOF */
