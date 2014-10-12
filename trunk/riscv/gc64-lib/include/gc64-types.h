/* 
 * _GC64-TYPES_H_ 
 * 
 * GC64 TYPES INTERFACE HEADER
 * 
 * Provides basic types functionality 
 * 
 * 
 */

#ifndef _GC64-USR_H_
#define _GC64-USR_H_

/* 
 * REQUIRED HEADERS
 * 
 */
#include <stdint.h>

/* 
 * NAMED ADDRESS SPACE MACROS 
 * 
 */
#ifdef __SCRATCH
#define __scratch typedef __attribute__((address_space(200))) 
#define __SCRATCH typedef __attribute__((address_space(200))) 
#define


/*
 * ENUMS
 * 
 */
typedef enum gc64mem_t{
	GC64_MAIN	= 0x01, 
	GC64_SCRATCH	= 0x02,
	GC64_REMOTE	= 0x04 	
};


#endif /* _GC64-USR_H_ */
/* EOF */
