// See LICENSE for license details 

#ifndef _RISCV_SPAD_H_
#define _RISCV_SPAD_H_

#include "processor.h"

// this class implements a processor's scratchpad memory 
class spad_t
{
public: 
	spad_t(size_t _spadsz);
	~spad_t();

	//-- PUBLIC FUNCTIONS 
	size_t get_size() { size_t tsize = spadsz; return tsize; }

private:
	size_t spadsz;		//-- size of the scratchpad memory 

	friend class processor_t;
};


#endif	/* _RISCV_SPAD_H_ */
/* EOF */
