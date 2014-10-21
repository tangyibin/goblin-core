// See LICENSE for license details 

#ifndef _RISCV_SPAD_H_
#define _RISCV_SPAD_H_

#include <stdint.h>
#include "processor.h"

//-- error macros
#define SPAD_OK			0
#define	SPAD_ADDR_BOUND		-1

// -- we define a base union type in order to avoid
// -- unnecessary data conversion for loads and stores
union spad_value{ 
	int8_t 		s_i8;
	uint8_t		s_u8;
	int16_t		s_i16;
	uint16_t 	s_u16;
	int32_t		s_i32;
	uint32_t 	s_u32;
	int64_t		s_i64;
	uint64_t	s_u64;
	float		s_f;
	double		s_d;
};

// this class implements a processor's scratchpad memory 
class spad_t
{
public: 
	spad_t();
	spad_t(size_t _spadsz, uint64_t _base_addr, size_t _align );
	~spad_t();

	//-- PUBLIC QUERY FUNCTIONS 
	size_t	get_size() { size_t tsize = spadsz; return tsize; }
	size_t	get_alignment() { size_t talign = align; return talign; }
	uint64_t get_base_addr() { uint64_t ba = base_addr; return ba; } 	 
	void *translate( uint64_t _addr, bool store, bool fetch );

	//-- PUBLIC MEMORY MODIFICATION FUNCTIONS
	//spad_value load( uint64_t _addr, int *err );
	//void store( spad_value value, uint64_t _addr, int *err );

private:
	size_t spadsz;		//-- size of the scratchpad memory 
	size_t align;		//-- alignment restrictions in bytes 
	uint64_t base_addr;	//-- base address of the scratchpad memory 

	char *stor;		//-- storage for the scratchpad backend 	

	friend class processor_t;
	friend class mmu_t;
};


#endif	/* _RISCV_SPAD_H_ */
/* EOF */
