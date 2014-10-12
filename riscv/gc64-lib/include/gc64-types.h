/* 
 * _GC64-TYPES_H_ 
 * 
 * GC64 TYPES INTERFACE HEADER
 * 
 * Provides basic types functionality 
 * 
 * 
 */

#ifndef _GC64-TYPES_H_
#define _GC64-TYPES_H_

#ifdef __cplusplus
extern "C"
#endif	/* __CPLUSPLUS */

/* 
 * REQUIRED HEADERS
 * 
 */
#include <stdint.h>
#include <limits.h>

/* 
 * NAMED ADDRESS SPACE MACROS 
 * 
 */
#ifdef __SCRATCH
#define __scratch typedef __attribute__((address_space(200))) 
#define __SCRATCH typedef __attribute__((address_space(200))) 
#endif	/* __SCRATCH */


/*
 * ENUMS
 * 
 */
typedef enum gc64mem_t{
	GC64_MAIN	= 0x01, 
	GC64_SCRATCH	= 0x02,
	GC64_REMOTE	= 0x04 	
};


#ifdef __cplusplus
}	/* EXTERN C */
#endif	/* __CPLUSPLUS */
#endif /* _GC64-TYPES_H_ */
/* EOF */
