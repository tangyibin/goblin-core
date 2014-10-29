// See LICENSE for license details. 
// Scratchpad Memory Extension
// Originally Written by John Leidel: john.leidel@gmail.com
// www.gc64.org

#include "spad.h"
#include <cstdlib>
#include <iostream>
#include <assert.h>


/* 
 * default constructor 
 * 
 */
spad_t::spad_t() {
	spadsz		= 0;
	base_addr	= 0;
	align		= 0;	
	stor		= NULL;
}

/* 
 * constructor 
 * 
 */
spad_t::spad_t( size_t _spadsz, uint64_t _base_addr, size_t _align ) {

	spadsz		= _spadsz;
	base_addr	= _base_addr;
	align		= _align;

	/* 
	 * allocate the internal storage
	 * 
	 */
	stor = (char *)(malloc( spadsz ));
}

/* 
 * default deconstructor 
 * 
 */
spad_t::~spad_t() {

	if( stor != NULL ){ 
		free( stor );
		stor = NULL;
	}
}

/* 
 * spad_translate
 * 
 */
void * spad_t::translate( uint64_t _addr, bool store, bool fetch ) { 

	/* vars */
	uint64_t upper_addr	= base_addr + spadsz;
	uint64_t stride		= 0x00ll;
	int elem		= 0x00;
	char *tstor		= NULL;
	/* ---- */
	
	/* 
	 * check the bounds of the address request
	 * 
	 */	
	if( 	(_addr < base_addr) || 
		(_addr > upper_addr) ){ 
		
		return NULL;
	} 

	/* 
	 * get the stride into the physical storage 
	 * 
	 */
	stride 	= _addr - base_addr;
	elem	= stride/(sizeof(char));

	/* 
	 * todo: check the data alignment 
	 * 
 	 */

	/* 
	 * retrieve a full 8-bit payload value
	 * the caller must understand which portion 
	 * belongs to them 
	 *
 	 */
	tstor		= (char *)(&(stor[elem]));

	return (void *)(tstor);
}

/* EOF */
