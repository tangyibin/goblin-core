/* 
 * 
 * 
 * _PHYSRAND_MAIN_C_ 
 * 
 * HMCSIM PHYSICAL ADDRESS RANDOM TESTS
 * 
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "hmc_sim.h"


/* ------------------------------------------------------------------- MAIN */
/* 
 * MAIN 
 * 
 */
int main( int argc, char **argv )
{
	/* vars */
	int ret		= 0;
	/* ---- */

	while(( ret = getopt( argc, argv, "h" )) != -1 )
	{
		switch( ret )
		{
			case 'h': 
				break;
			default:
				break;
		}
	}

	return 0;
}

/* EOF */
