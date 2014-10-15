/* 
 * _GC64-TYPES_H_ 
 * 
 * GC64 TYPES INTERFACE HEADER
 * 
 * Provides basic types functionality 
 * 
 * 
 */

#ifndef _GC64_TYPES_H_
#define _GC64_TYPES_H_

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
#ifndef __SCRATCH
#define __scratch __attribute__((address_space(200))) 
#define __SCRATCH __attribute__((address_space(200))) 
#endif	/* __SCRATCH */


/*
 * RETURN TYPES
 * 
 */
#define	GC64_OK		0x00
#define GC64_NULLPTR	0x01
#define GC64_ERROR	0xFF

/*
 * ENUMS
 * 
 */
typedef enum {
	GC64_MAIN	= 0x01, 
	GC64_SCRATCH	= 0x02,
	GC64_REMOTE	= 0x04 	
}gc64mem_t;


/* 
 * STRUCTURES 
 * 
 */

/* -- gc64entry_t */
struct gc64entry_t{
	uint64_t base_addr;
	size_t size;
	struct gc64entry_t *next;
};

/* -- gc64sp_t */
struct gc64sp_t{
	uint64_t base_addr;
	uint64_t tsize;
	uint64_t used;
	uint64_t free;
	uint64_t nentry;
	struct gc64entry_t *entry;
};

/* -- gc64comp_t */
struct gc64comp_t{
	struct gc64sp_t *mem;
	uint64_t status;	
};



#ifdef __cplusplus
}	/* EXTERN C */
#endif	/* __CPLUSPLUS */
#endif /* _GC64-TYPES_H_ */
/* EOF */
