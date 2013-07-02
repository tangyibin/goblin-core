/*
 * _GOBLIN_SIM_H_
 * 
 * GOBLIN-SIM MAIN HEADER FILE 
 */


#ifndef	_GOBLIN_SIM_H_
#define _GOBLIN_SIM_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <sys/types.h>
#include "goblin_sim_types.h"
#include "goblin_sim_macros.h"

/* --------------------------------------------- DATA STRUCTURES */

/* --------------------------------------------- FUNCTION PROTOTYPES */

extern void	gsim_free( void *ptr );
extern void 	*gsim_malloc( size_t sz );

extern int	gsim_config_read( struct gsim_t *sim );

#ifdef __cplusplus
} /* extern C */
#endif

#endif	/* _GOBLIN_SIM_H_ */

/* EOF */
