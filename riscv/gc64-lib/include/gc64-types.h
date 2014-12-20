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
	struct gc64entry_t *start;
	struct gc64entry_t *end;
};

/* -- gc64fptr_t */
struct gc64fptr_t{
	struct gc64sp_t *(*mem_init)(uint64_t,uint64_t);
	void (*mem_free)();
};

/* -- gc64comp_t */
struct gc64comp_t{
	struct gc64fptr_t fptr;
	struct gc64sp_t *mem;
	
	void *usrlib_handle;
	
	uint64_t status;	
	uint64_t trace;
	uint64_t usr_trace;
};

/*
 * MACROS
 * 
 */
#define	GC64_BYTE_ALIGNMENT 		2
#define GC64_DEFAULT_SPAD_SIZE		20000000
#define GC64_DEFAULT_SPAD_BASE_ADDR	0x0000000080000000

/* 
 * TRACE MACROS
 *
 */
#define GC64_TRACE_FUNC			0x00000000000000001

#define GC64_PRINT_TRACE( s )		{ printf( "GC64_TRACE: %s:%d : %s\n", __FUNCTION__, __LINE__, s ); }
#define GC64_TRACE_FUNC_ENTRY( c )	{									\
						if( c != NULL ){						\
							if( (c->trace & 0x00000000000000001) > 0 ){		\
								fprintf( stdout, "GC64_FUNC_ENTRY: %s:%s\n",	\
									__FILE__,				\
									__FUNCTION__ );				\
							}							\
						}								\
					}

#define GC64_TRACE_FUNC_EXIT( c )	{									\
						if( c != NULL ){						\
							if( (c->trace & 0x00000000000000001) > 0 ){		\
								fprintf( stdout, "GC64_FUNC_EXIT: %s:%s\n",	\
									__FILE__,				\
									__FUNCTION__ );				\
							}							\
						}								\
					}

#ifdef __cplusplus
}	/* EXTERN C */
#endif	/* __CPLUSPLUS */
#endif /* _GC64-TYPES_H_ */
/* EOF */
