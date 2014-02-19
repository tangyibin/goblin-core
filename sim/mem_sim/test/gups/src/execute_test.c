/* _EXECUTE_TEST_C_ 
 * 
 * MEMSIM GUPS TEST EXECUTION 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "mem_sim.h"

/* --------------------------------------------- GUPS MACROS */
#define		POLY		0x0000000000000007UL
#define		PERIOD		1317624576693539401L

/* --------------------------------------------- STATUS MACROS */
#define		GUPS_START	0x0000
#define		GUPS_STAGE1	0x0001
#define		GUPS_STAGE2	0x0002
#define		GUPS_STAGE3	0x0003
#define		GUPS_STAGE4	0x0004
#define		GUPS_STAGE5	0x0005
#define		GUPS_STAGE6	0x0006
#define		GUPS_STAGE7	0x0007
#define		GUPS_STAGE8	0x0008
#define		GUPS_STAGE9	0x0009
#define		GUPS_STAGE10	0x000A
#define		GUPS_STAGE11	0x000B
#define		GUPS_STAGE12	0x000C
#define		GUPS_STAGE13	0x000D

/* --------------------------------------------- STRUCTURES */
struct tid_t{

	/* local values */
	uint64_t	TableSize;	/* local value of TableSize */
	uint64_t	ran;		/* local value of ran */
	uint64_t	idx;		/* local value of idx */
	uint64_t	shift;		/* local result of shift value */

	/* outstanding tids */
	uint32_t	ld_TS;		/* load TableSize */
	uint32_t	ld_ran;		/* load ran[j] */
	uint32_t	st_ran; 	/* store ran[j]	*/
	uint32_t	ld_SC;		/* scatter load */

	uint8_t		ld_TS_v;	/* valid : load TableSize */
	uint8_t		ld_ran_v;	/* valid : load ran[j] */
	uint8_t		st_ran_v; 	/* valid : store ran[j]	*/
	uint8_t		ld_SC_v;	/* valid : scatter load */

	/* status & control */
	uint32_t	done;		/* signals the thread is done */
	uint64_t	cur;		/* starting j value */
	uint64_t	end;		/* ending j value */
	uint64_t	status;		/* current status value */
};


/* --------------------------------------------- HPCC_starts */
/* 
 * inits the ran array; pulled from HPCC RandomAccess
 * 
 */
uint64_t HPCC_starts( int64_t n ){ 
	int i, j;
	uint64_t m2[64];
	uint64_t temp,ran;

	while(n<0 ){ 
		n+=PERIOD;
	}

	while( n > PERIOD ){ 
		n-=PERIOD;
	}

	if( n == 0 ){ return (uint64_t)(0x1); }

	temp = 0x1;
	for( i=0; i<64; i++ ){ 
		m2[i]	= temp;
		temp	= (temp << 1) ^ ((int64_t) temp < 0 ? POLY : 0 );
		temp	= (temp << 1) ^ ((int64_t) temp < 0 ? POLY : 0 );
	}

	for( i=62; i>=0; i-- ){ 
		if((n>>i)&i){
			break;
		}
	}

	ran = 0x2;
	while( i > 0 ){ 
		temp = 0;
		for( j=0; j<64; j++ ){ 
			if((ran >>j) & 1){
				temp ^= m2[j];
			}
		}
		
		ran = temp;
		i -= 1;
		if((n>>i) & 1 ){
			ran = (ran << 1 ) ^ ((int64_t) ran < 0 ? POLY : 0 );
		}
	}

	return ran;
}

/* --------------------------------------------- EXECUTE_TEST */
/* 
 * EXECUTE TEST
 * 
 * Executes an unbinned GUPS : 
 *
 * 
 * for( j=0; j<NUPDATE/num_threads;j++ ){ 
 * 
 * 	ran[j]	= (ran[j]<<1) ^(ran[j] < 0 ? POLY : 0)
 *	Table[ ran[j] & (TableSize-1) ] ^= ran[j]
 * 
 * }
 * 
 * Finite State Machine : 
 * 
 * 0. 	Start
 * 1.	load TableSize scalar [hoisted]
 * 2.	subtract one from TableSize
 * 3.	load rand[ j ]
 * 4.	shift-left ran[ j ] { loads must clear }
 * 5.	compare ran[j] < 0 ? POLY : 0 
 * 6.	logical xor ran[j] and result from 4
 * 7.	write ran[j]
 * 8.	logical and ran[j] & TableSize-1
 * 9.	calculate address {scatter}
 * 10.	load of Table at index from 8. {wait for load to clear}
 * 12.	xor clock { Table [ index ] ^ ran[j] }
 * 12.	write Table[ index ]	{ do we use an amo here? }
 * 13.	Flow Control for loop 
 * 
 */
extern int execute_test(	struct memsim_t *msim, 
				uint64_t *gconst, 
				uint32_t num_threads, 
				long num_req ){ 

	/* vars */
	int ret			= 0;
	uint32_t done		= 0;
	uint32_t l_tid		= 0x00;
	uint32_t i		= 0;
	uint32_t update		= 0;
	long j			= 0;
	uint64_t k		= 0;
	uint64_t niter		= 0x00ll;
	uint64_t TableSize	= 0x00ll;
	uint64_t *ran		= NULL;
	uint64_t *Table		= NULL;
	uint64_t NUPDATE	= (uint64_t)(num_req) * (uint64_t)(4);
	struct tid_t *tids	= NULL;
	/* ---- */

	/* 
	 * allocate memory 
	 * 
	 */
	tids	= malloc( sizeof( struct tid_t ) * num_threads );
	if( tids == NULL ){ 
		printf( "ERROR : COULD NOT ALLOCATE MEMORY FOR tids\n" );
		return -1;
	}	

	ran	= malloc( sizeof( uint64_t ) * num_threads );
	if( ran == NULL ){ 
		printf( "ERROR : COULD NOT ALLOCATE MEMORY FOR ran\n" );
		free( tids );
		return -1;
	}	

	Table	= malloc( sizeof( uint64_t ) * num_req );
	if( Table == NULL ){ 
		printf( "ERROR : COULD NOT ALLOCATE MEMORY FOR Table\n" );
		free( tids );
		free( ran );
		return -1;
	}

	printf( "ALLOCATED GUPS MEMORY\n" );

	printf( "INITIALIZING GUPS DATA FOR %"PRIu32" THREADS\n", num_threads );

	for( i=0; i<num_threads; i++ ){ 

		tids[i].TableSize	= 0x00ll;
		tids[i].ran		= 0x00ll;
		tids[i].idx		= 0x00ll;
		tids[i].shift		= 0x00ll;
		tids[i].ld_TS		= 0x00;
		tids[i].ld_ran		= 0x00;
		tids[i].st_ran		= 0x00;
		tids[i].ld_SC		= 0x00;
		tids[i].ld_TS_v		= 0x0;
		tids[i].ld_ran_v	= 0x0;
		tids[i].st_ran_v	= 0x0;
		tids[i].ld_SC_v		= 0x0;
		tids[i].done		= 0x00;
		tids[i].cur		= 0x00ll;
		tids[i].end		= 0x00ll;
		tids[i].status		= GUPS_STAGE1;
	}

	for( j=0; j<num_req; j++ ){ 
		Table[j]	= (uint64_t)(j);	
	}

	for( i=0; i<num_threads; i++ ){ 
		ran[i]	= HPCC_starts( (int64_t)((NUPDATE/num_threads) * i) );
	}

	niter	= (uint64_t)(NUPDATE)/(uint64_t)(num_threads);

	TableSize = (uint64_t)(num_req);

	/* setup the cur & end */
	if( (uint64_t)(num_threads) < (uint64_t)(NUPDATE) ){ 
		/* split the requests */
		for( k=0; k<(uint64_t)(num_threads); k++){ 
			tids[k].cur	= niter*k;
			tids[k].status	= GUPS_STAGE1;
		
			if( k == (uint64_t)(num_threads-1)){
				tids[k].end	= (uint64_t)(NUPDATE-1);
			}else{
				tids[k].end	= tids[k].cur + (niter-1);
			}
		}	
	}else{ 
		/* init everyone to zero */
		for( i=0; i<num_threads; i++ ){ 
			tids[i].cur	= 0x00ll;
			tids[i].end	= 0x00ll;
			tids[i].done	= 1;
		}

		/* everyone gets a value */
		for( k=0; k<num_req; k++ ){ 
			tids[k].cur	= (uint64_t)(k);
			tids[k].end	= (uint64_t)(k);
			tids[k].status	= GUPS_STAGE1;
			tids[k].done	= 0;
		}
	}

	printf( "INITIALIZED GUPS DATA\n" );
	printf( "BEGINNING EXECUTION FOR %"PRIu32" THREADS\n", num_threads );

	/* 
	 * begin the test loop 
	 * 
	 */
	while( done < num_threads ){ 
		
		/* 
		 * each clock cycle iterate through all 
	 	 * the threads
		 * 
		 */
		for( i=0; i<num_threads; i++ ){ 

			if( tids[i].done == 1 ){ 
				/* the thread is done, do nothing */
			}else if( tids[i].status == GUPS_START ){
				/* not used for this benchmark */
			}else if( tids[i].status == GUPS_STAGE1 ){ 

				/* load TableSize */
				ret	= memsim_rqst( 	msim, 
							gconst[i], 
							MEMSIM_RD8, 
							(uint64_t)(&TableSize), 
							0x00ll,
							0x00ll, 
							&l_tid );

				if( ret == 0 ){ 
					tids[i].status	= GUPS_STAGE2;
					tids[i].ld_TS	= l_tid;
					tids[i].ld_TS_v	= 1;
				}

			}else if( tids[i].status == GUPS_STAGE2 ){ 
				
				/* subtract one from TableSize */

				update	 = 0;

				if( tids[i].ld_TS_v == 1 ){
					/* check for the load completion */
					if( memsim_query_tid( msim, 
							tids[i].ld_TS ) == 0 ){ 
						/* tid is clear */
						tids[i].ld_TS_v	= 0;
					}else{ 
						/* tid is not clear */
						update++;
					}
				}

				if( update == 0 ){ 

					/* perform the subtract */
					tids[i].TableSize -= 1;
					tids[i].status	= GUPS_STAGE3;

				}else{ 
					/* memory stall */
				}
				
			}else if( tids[i].status == GUPS_STAGE3 ){ 

				/* load ran[j] */
				ret	= memsim_rqst( 	msim, 
							gconst[i], 
							MEMSIM_RD8, 
							(uint64_t)(&ran[tids[i].cur]), 
							0x00ll,
							0x00ll, 
							&l_tid );

				if( ret == 0 ){ 
					tids[i].status	= GUPS_STAGE4;
					tids[i].ld_ran	= l_tid;
					tids[i].ld_ran_v= 1;
				}


			}else if( tids[i].status == GUPS_STAGE4 ){

 				/* 4.	shift-left ran[ j ] { loads must clear } */

				update = 0;	
				if( tids[i].ld_ran_v == 1 ){ 
					/* check for the load completion */
					if( memsim_query_tid( msim, 
							tids[i].ld_ran ) == 0 ){
						/* tid is clear */
						tids[i].ld_ran_v = 0;
					}else{ 
						/* tid is not clear */
						update++;
					}

					if( update == 0 ){ 
						/* perform the shift */
						tids[i].shift = ran[tids[i].cur]<<1;
						tids[i].status = GUPS_STAGE5;
					}else{ 
						/* memory stall */
					}
				}

			}else if( tids[i].status == GUPS_STAGE5 ){
			}else if( tids[i].status == GUPS_STAGE6 ){
			}else if( tids[i].status == GUPS_STAGE7 ){
			}else if( tids[i].status == GUPS_STAGE8 ){
			}else if( tids[i].status == GUPS_STAGE9 ){
			}else if( tids[i].status == GUPS_STAGE10 ){
			}else if( tids[i].status == GUPS_STAGE11 ){
			}else if( tids[i].status == GUPS_STAGE12 ){
			}else if( tids[i].status == GUPS_STAGE13 ){
			}

		}/* -- end for loop */

		/* 
		 * clock the sim 
		 *
		 */
		memsim_clock( msim );
	}/* -- end test loop */

	printf( "SUCCESS : EXECUTION COMPLETE\n" );

	free( tids );
	free( ran );
	free( Table );

	return 0;
}
/* EOF */
