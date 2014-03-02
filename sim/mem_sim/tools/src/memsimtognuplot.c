/* _MEMSIMTOGNUPLOT_C_ 
 * 
 * MEMSIM TRACE FILE TO GNUPLOT CONVERSION UTILITY 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>

/* --------------------------------------------------------- MACROS */
#define BUFLEN	1024


/* --------------------------------------------------------- INTERNAL STRUCTURES */
struct mtog_count_t{
	uint64_t *busop;
	uint64_t *memop;
	uint64_t *rd8;
	uint64_t *wr8;
	uint64_t *rd4;
	uint64_t *wr4;
	uint64_t *fence;
	uint64_t *unk;
	uint64_t *hmc_rd16;
	uint64_t *hmc_rd32;
	uint64_t *hmc_rd48;
	uint64_t *hmc_rd64;
	uint64_t *hmc_rd80;
	uint64_t *hmc_rd96;
	uint64_t *hmc_rd112;
	uint64_t *hmc_rd128;	
	uint64_t *hmc_wr16;
	uint64_t *hmc_wr32;
	uint64_t *hmc_wr48;
	uint64_t *hmc_wr64;
	uint64_t *hmc_wr80;
	uint64_t *hmc_wr96;
	uint64_t *hmc_wr112;
	uint64_t *hmc_wr128;	
};

struct mtog_t{
	struct mtog_count_t count;
	uint64_t num_clocks;
	int verbose;
	char *fname;
};

/* ----------------------------------------------------------------------------- */

/* --------------------------------------------------------- MTOG_FREE */
/* 
 * MTOG_FREE
 * 
 */
static int mtog_free( struct mtog_t *mtog ){ 
	
	if( mtog == NULL ){ 
		return 0;
	}

	if( mtog->count.busop != NULL ){ 
		free( mtog->count.busop );
		mtog->count.busop = NULL;
	}

	if( mtog->count.memop != NULL ){ 
		free( mtog->count.memop );
		mtog->count.memop = NULL;
	}

	if( mtog->count.rd8 != NULL ){ 
		free( mtog->count.rd8 );
		mtog->count.rd8 = NULL;
	}

	if( mtog->count.wr8 != NULL ){ 
		free( mtog->count.wr8 );
		mtog->count.wr8 = NULL;
	}

	if( mtog->count.rd4 != NULL ){ 
		free( mtog->count.rd4 );
		mtog->count.rd4 = NULL;
	}

	if( mtog->count.wr4 != NULL ){ 
		free( mtog->count.wr4 );
		mtog->count.wr4 = NULL;
	}

	if( mtog->count.fence != NULL ){ 
		free( mtog->count.fence );
		mtog->count.fence = NULL;
	}

	if( mtog->count.unk != NULL ){ 
		free( mtog->count.unk );
		mtog->count.unk = NULL;
	}

	if( mtog->count.hmc_rd16 != NULL ){ 
		free( mtog->count.hmc_rd16 );
		mtog->count.hmc_rd16 = NULL;
	}

	if( mtog->count.hmc_rd32 != NULL ){ 
		free( mtog->count.hmc_rd32 );
		mtog->count.hmc_rd32 = NULL;
	}

	if( mtog->count.hmc_rd48 != NULL ){ 
		free( mtog->count.hmc_rd48 );
		mtog->count.hmc_rd48 = NULL;
	}

	if( mtog->count.hmc_rd64 != NULL ){ 
		free( mtog->count.hmc_rd32 );
		mtog->count.hmc_rd32 = NULL;
	}

	if( mtog->count.hmc_rd80 != NULL ){ 
		free( mtog->count.hmc_rd80 );
		mtog->count.hmc_rd80 = NULL;
	}

	if( mtog->count.hmc_rd96 != NULL ){ 
		free( mtog->count.hmc_rd96 );
		mtog->count.hmc_rd96 = NULL;
	}

	if( mtog->count.hmc_rd112 != NULL ){ 
		free( mtog->count.hmc_rd112 );
		mtog->count.hmc_rd112 = NULL;
	}

	if( mtog->count.hmc_rd128 != NULL ){ 
		free( mtog->count.hmc_rd128 );
		mtog->count.hmc_rd128 = NULL;
	}

	if( mtog->count.hmc_wr16 != NULL ){ 
		free( mtog->count.hmc_wr16 );
		mtog->count.hmc_wr16 = NULL;
	}

	if( mtog->count.hmc_wr32 != NULL ){ 
		free( mtog->count.hmc_wr32 );
		mtog->count.hmc_wr32 = NULL;
	}

	if( mtog->count.hmc_wr48 != NULL ){ 
		free( mtog->count.hmc_wr48 );
		mtog->count.hmc_wr48 = NULL;
	}

	if( mtog->count.hmc_wr64 != NULL ){ 
		free( mtog->count.hmc_wr32 );
		mtog->count.hmc_wr32 = NULL;
	}

	if( mtog->count.hmc_wr80 != NULL ){ 
		free( mtog->count.hmc_wr80 );
		mtog->count.hmc_wr80 = NULL;
	}

	if( mtog->count.hmc_wr96 != NULL ){ 
		free( mtog->count.hmc_wr96 );
		mtog->count.hmc_wr96 = NULL;
	}

	if( mtog->count.hmc_wr112 != NULL ){ 
		free( mtog->count.hmc_wr112 );
		mtog->count.hmc_wr112 = NULL;
	}

	if( mtog->count.hmc_wr128 != NULL ){ 
		free( mtog->count.hmc_wr128 );
		mtog->count.hmc_wr128 = NULL;
	}


	return 0;
}

/* --------------------------------------------------------- PRINT_RESULTS */
/* 
 * PRINT_RESULTS
 * 
 */
static int print_results( struct mtog_t *mtog ){ 

	/* vars */
	FILE *ofile 	= NULL;
	uint64_t i 	= 0;
	/* ---- */

	/* 
	 * busop 
	 *
	 */
	ofile	= fopen( "busop.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.busop[i] );
	}

	/* 
	 * memop 
	 *
	 */
	ofile	= fopen( "memop.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.memop[i] );
	}

	/* 
	 * rd8 
	 *
	 */
	ofile	= fopen( "rd8.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.rd8[i] );
	}

	/* 
	 * wr8 
	 *
	 */
	ofile	= fopen( "wr8.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.wr8[i] );
	}

	/* 
	 * rd4 
	 *
	 */
	ofile	= fopen( "rd4.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.rd4[i] );
	}

	/* 
	 * wr4 
	 *
	 */
	ofile	= fopen( "wr4.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.wr4[i] );
	}

	/* 
	 * fence 
	 *
	 */
	ofile	= fopen( "fence.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.fence[i] );
	}

	/* 
	 * unk
	 *
	 */
	ofile	= fopen( "unk.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.unk[i] );
	}

	/* 
	 * hmc_rd16
	 *
	 */
	ofile	= fopen( "hmc_rd16.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.hmc_rd16[i] );
	}

	/* 
	 * hmc_rd32
	 *
	 */
	ofile	= fopen( "hmc_rd32.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.hmc_rd32[i] );
	}

	/* 
	 * hmc_rd48
	 *
	 */
	ofile	= fopen( "hmc_rd48.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.hmc_rd48[i] );
	}

	/* 
	 * hmc_rd64
	 *
	 */
	ofile	= fopen( "hmc_rd64.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.hmc_rd64[i] );
	}

	/* 
	 * hmc_rd80
	 *
	 */
	ofile	= fopen( "hmc_rd80.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.hmc_rd80[i] );
	}

	/* 
	 * hmc_rd96
	 *
	 */
	ofile	= fopen( "hmc_rd96.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.hmc_rd96[i] );
	}

	/* 
	 * hmc_rd112
	 *
	 */
	ofile	= fopen( "hmc_rd112.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.hmc_rd112[i] );
	}

	/* 
	 * hmc_rd128
	 *
	 */
	ofile	= fopen( "hmc_rd128.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.hmc_rd128[i] );
	}

	/* 
	 * hmc_wr16
	 *
	 */
	ofile	= fopen( "hmc_wr16.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.hmc_wr16[i] );
	}

	/* 
	 * hmc_wr32
	 *
	 */
	ofile	= fopen( "hmc_wr32.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.hmc_wr32[i] );
	}

	/* 
	 * hmc_wr48
	 *
	 */
	ofile	= fopen( "hmc_wr48.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.hmc_wr48[i] );
	}

	/* 
	 * hmc_wr64
	 *
	 */
	ofile	= fopen( "hmc_wr64.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.hmc_wr64[i] );
	}

	/* 
	 * hmc_wr80
	 *
	 */
	ofile	= fopen( "hmc_wr80.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.hmc_wr80[i] );
	}

	/* 
	 * hmc_wr96
	 *
	 */
	ofile	= fopen( "hmc_wr96.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.hmc_wr96[i] );
	}

	/* 
	 * hmc_wr112
	 *
	 */
	ofile	= fopen( "hmc_wr112.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.hmc_wr112[i] );
	}

	/* 
	 * hmc_wr128
	 *
	 */
	ofile	= fopen( "hmc_wr128.out", "w+" );
	if( ofile == NULL ){ 
		return -1;
	}
	for( i=0; i<mtog->num_clocks; i++ ){ 
		fprintf( ofile, "%"PRIu64 " %"PRIu64 "\n", i, mtog->count.hmc_wr128[i] );
	}

	return 0;
}

/* --------------------------------------------------------- ALLOC_MEM */
/* 
 * ALLOC_MEM
 * 
 */
static int alloc_mem( struct mtog_t *mtog ){ 

	/* vars */
	uint64_t i	= 0x00ll;
	/* ---- */

	mtog->count.busop=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.busop == NULL ){ return -1; }
	mtog->count.memop=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.memop == NULL ){ return -1; }
	mtog->count.rd8=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.rd8 == NULL ){ return -1; }
	mtog->count.wr8=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.wr8 == NULL ){ return -1; }
	mtog->count.rd4=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.rd4 == NULL ){ return -1; }
	mtog->count.wr4=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.wr4 == NULL ){ return -1; }
	mtog->count.fence=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.fence == NULL ){ return -1; }
	mtog->count.unk=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.unk == NULL ){ return -1; }
	mtog->count.hmc_rd16=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.hmc_rd16 == NULL ){ return -1; }
	mtog->count.hmc_rd32=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.hmc_rd32 == NULL ){ return -1; }
	mtog->count.hmc_rd48=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.hmc_rd48 == NULL ){ return -1; }
	mtog->count.hmc_rd64=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.hmc_rd64 == NULL ){ return -1; }
	mtog->count.hmc_rd80=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.hmc_rd80 == NULL ){ return -1; }
	mtog->count.hmc_rd96=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.hmc_rd96 == NULL ){ return -1; }
	mtog->count.hmc_rd112=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.hmc_rd112 == NULL ){ return -1; }
	mtog->count.hmc_rd128=malloc(sizeof(uint64_t)*mtog->num_clocks);	
	if( mtog->count.hmc_rd128 == NULL ){ return -1; }
	mtog->count.hmc_wr16=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.hmc_wr16 == NULL ){ return -1; }
	mtog->count.hmc_wr32=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.hmc_wr32 == NULL ){ return -1; }
	mtog->count.hmc_wr48=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.hmc_wr48 == NULL ){ return -1; }
	mtog->count.hmc_wr64=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.hmc_wr64 == NULL ){ return -1; }
	mtog->count.hmc_wr80=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.hmc_wr80 == NULL ){ return -1; }
	mtog->count.hmc_wr96=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.hmc_wr96 == NULL ){ return -1; }
	mtog->count.hmc_wr112=malloc(sizeof(uint64_t)*mtog->num_clocks);
	if( mtog->count.hmc_wr112 == NULL ){ return -1; }
	mtog->count.hmc_wr128=malloc(sizeof(uint64_t)*mtog->num_clocks);	
	if( mtog->count.hmc_wr128 == NULL ){ return -1; }

	/* 
	 * zero the arrays 
	 * 
	 */
	for( i=0; i<mtog->num_clocks; i++ ){ 

		mtog->count.busop[i]=0x00ll;
		mtog->count.memop[i]=0x00ll;
		mtog->count.rd8[i]=0x00ll;
		mtog->count.wr8[i]=0x00ll;
		mtog->count.rd4[i]=0x00ll;
		mtog->count.wr4[i]=0x00ll;
		mtog->count.fence[i]=0x00ll;
		mtog->count.unk[i]=0x00ll;
		mtog->count.hmc_rd16[i]=0x00ll;
		mtog->count.hmc_rd32[i]=0x00ll;
		mtog->count.hmc_rd48[i]=0x00ll;
		mtog->count.hmc_rd64[i]=0x00ll;
		mtog->count.hmc_rd80[i]=0x00ll;
		mtog->count.hmc_rd96[i]=0x00ll;
		mtog->count.hmc_rd112[i]=0x00ll;
		mtog->count.hmc_rd128[i]=0x00ll;	
		mtog->count.hmc_wr16[i]=0x00ll;
		mtog->count.hmc_wr32[i]=0x00ll;
		mtog->count.hmc_wr48[i]=0x00ll;
		mtog->count.hmc_wr64[i]=0x00ll;
		mtog->count.hmc_wr80[i]=0x00ll;
		mtog->count.hmc_wr96[i]=0x00ll;
		mtog->count.hmc_wr112[i]=0x00ll;
		mtog->count.hmc_wr128[i]=0x00ll;	

	}

	return 0;
}

/* --------------------------------------------------------- SCAN_CLOCKS */
/* 
 * SCAN_CLOCKS
 * 
 */
static int scan_clocks( FILE *infile, struct mtog_t *mtog ){ 

	/* vars */
	char buf[BUFLEN];
	char *pch	= NULL;
	char *pend	= NULL;
	int ne		= 0;
	int flag	= 1;
	uint64_t tc	= 0x00ll;
	/* ---- */

	memset( buf, 0, sizeof( char ) * BUFLEN );

	fseek( infile, 0, SEEK_END );

	/* 
	 * step back three newline chars
	 * 
	 */
	while( (ne < 3) && (flag>0) ){ 
		if( fgetc( infile ) == '\n' ){
			ne++;
		}
		
		if( fseek( infile, -2, SEEK_CUR ) == -1 ){ 
			flag = 0;
		}
	}

	/* 
	 * grab a few lines and parse for the clock value 
	 * 
 	 */
	while( !feof( infile ) ){ 

		/* 
	 	 * get a line from the file 
	 	 * 
	 	 */
		fgets( buf, 1024, infile );

		/* 
	 	 * make sure its not a comment or partial line 
		 * 
		 */
		if( (buf[0] != '\n') && (strlen(buf) > 10) ){ 
			
			/* 
			 * found a valid line, parse it 
			 *
			 */
			pch	= strtok( buf, " " );
	
			/* 
	 	 	 * get the second string ":"
			 *
			 */
			if( pch != NULL ){ 
				pch = strtok( NULL, " " );
			}

			/* 
			 * get the third string "<val>"
			 * 
			 */
			if( pch != NULL ){ 
				pch = strtok( NULL, " " );
			}

			/* 
			 * get the value
			 *
			 */
			if( pch != NULL ){
				tc = strtoll( pch, &pend, 10 );
				
				if( tc > mtog->num_clocks ){ 
					mtog->num_clocks = tc;
				}
			}
		}
	}

	if( mtog->verbose == 1 ){ 
		printf( "Notice : found %"PRIu64" clocks\n", mtog->num_clocks );
	}

	return 0;
}

/* --------------------------------------------------------- PARSE */
/* 
 * PARSE
 * 
 */
static int parse( FILE *infile, struct mtog_t *mtog ){ 

	/* vars */
	char buf[BUFLEN];
	char *pch	= NULL;
	char *pend	= NULL;
	uint64_t tc	= 0x00ll;
	/* ---- */


	while( !feof( infile ) ){ 
		/* 
	 	 * get a line from the file 
		 *
		 */
		memset( buf, 0, sizeof( char ) * BUFLEN );
		fgets( buf, 1024, infile );

		/* 
		 * make sure its not a comment or partial line 
		 * 
		 */
		if( (buf[0] != '\n') && 
			(strlen(buf) > 10) &&
			(buf[0] != '#') ){
			
			/*
			 * found a valid line, parse it 
			 *
		 	 */
			pch	= strtok( buf, " " );
		
			/* 
			 * get the second string ":"
			 * 
			 */
			if( pch != NULL ){ 
				pch = strtok( NULL, " " );
			}	 

			/* 
			 * get the third string "<val>"
			 *
			 */
			if( pch != NULL ){ 
				pch = strtok( NULL, " " );
			}

			/* 
			 * get the clock value 
			 * 
			 */
			if( pch != NULL ){ 
				tc = strtoull( pch, &pend, 10 );
			}

			/*
		 	 * get the fourth string ":"
			 *
			 */
			if( pch != NULL ){ 
				pch = strtok( NULL, " " );
			}

			/* 
			 * get the fifth string "<mem/busop>"
		 	 *
			 */
			if( pch != NULL ){ 
				pch = strtok( NULL, " " );
			}

			/* 
			 * determine the operation type 
			 *
			 */
			if( strcmp( pch, "MEMORY_BUS" ) == 0 ){ 
				mtog->count.busop[tc]++;
			}else if( strcmp( pch, "MEMORY_OP" ) == 0 ){ 
				mtog->count.memop[tc]++;
			}else{ 
				printf( "Found a bogus value : %s\n", pch );
			}

			/* 
			 * forward to the operation type 
			 *
			 */
			if( pch != NULL ){ 
				/* 6 */
				pch = strtok( NULL, " " );
				/* 7 */
				pch = strtok( NULL, " " );
				/* 8 */
				pch = strtok( NULL, " " );
				/* 9 */
				pch = strtok( NULL, " " );
				/* 10 */
				pch = strtok( NULL, " " );
				/* 11 */
				pch = strtok( NULL, "\n" );
			}

			/* 
			 * determine the operation code 
			 * 
			 */
			if( strcmp( pch, "MEMSIM_RD8" ) == 0 ){ 
				mtog->count.rd8[tc]++;
			}else if( strcmp( pch, "MEMSIM_WR8" ) == 0 ){ 
				mtog->count.wr8[tc]++;
			}else if( strcmp( pch, "MEMSIM_RD4" ) == 0 ){ 
				mtog->count.rd4[tc]++;
			}else if( strcmp( pch, "MEMSIM_WR4" ) == 0 ){ 
				mtog->count.rd4[tc]++;
			}else if( strcmp( pch, "MEMSIM_FENCE" ) == 0 ){ 
				mtog->count.fence[tc]++;
			}else if( strcmp( pch, "MEMSIM_UNK" ) == 0 ){ 
				mtog->count.unk[tc]++;
			}else if( strcmp( pch, "MEMSIM_HMC_RD16" ) == 0 ){ 
				mtog->count.hmc_rd16[tc]++;
			}else if( strcmp( pch, "MEMSIM_HMC_RD32" ) == 0 ){ 
				mtog->count.hmc_rd32[tc]++;
			}else if( strcmp( pch, "MEMSIM_HMC_RD48" ) == 0 ){ 
				mtog->count.hmc_rd48[tc]++;
			}else if( strcmp( pch, "MEMSIM_HMC_RD64" ) == 0 ){ 
				mtog->count.hmc_rd64[tc]++;
			}else if( strcmp( pch, "MEMSIM_HMC_RD80" ) == 0 ){ 
				mtog->count.hmc_rd80[tc]++;
			}else if( strcmp( pch, "MEMSIM_HMC_RD96" ) == 0 ){ 
				mtog->count.hmc_rd96[tc]++;
			}else if( strcmp( pch, "MEMSIM_HMC_RD112" ) == 0 ){ 
				mtog->count.hmc_rd112[tc]++;
			}else if( strcmp( pch, "MEMSIM_HMC_RD128" ) == 0 ){ 
				mtog->count.hmc_rd128[tc]++;
			}else if( strcmp( pch, "MEMSIM_HMC_WR16" ) == 0 ){ 
				mtog->count.hmc_wr16[tc]++;
			}else if( strcmp( pch, "MEMSIM_HMC_WR32" ) == 0 ){ 
				mtog->count.hmc_wr32[tc]++;
			}else if( strcmp( pch, "MEMSIM_HMC_WR48" ) == 0 ){ 
				mtog->count.hmc_wr48[tc]++;
			}else if( strcmp( pch, "MEMSIM_HMC_WR64" ) == 0 ){ 
				mtog->count.hmc_wr64[tc]++;
			}else if( strcmp( pch, "MEMSIM_HMC_WR80" ) == 0 ){ 
				mtog->count.hmc_wr80[tc]++;
			}else if( strcmp( pch, "MEMSIM_HMC_WR96" ) == 0 ){ 
				mtog->count.hmc_wr96[tc]++;
			}else if( strcmp( pch, "MEMSIM_HMC_WR112" ) == 0 ){ 
				mtog->count.hmc_wr112[tc]++;
			}else if( strcmp( pch, "MEMSIM_HMC_WR128" ) == 0 ){ 
				mtog->count.hmc_wr128[tc]++;
			}else{	
				printf( "Found a bogus value : %s\n", pch );
			}
		}
	}

	return 0;
}

/* --------------------------------------------------------- MTOG_CONVERT */
/* 
 * MTOG_CONVERT
 * 
 */
static int mtog_convert( struct mtog_t *mtog ){ 

	/* vars */
	FILE *infile = NULL;
	/* ---- */
	
	if( mtog == NULL ){ 
		return -1;
	}

	/* 
	 * stage 1: open the file 
	 * 
	 */
	infile = fopen( mtog->fname, "r" );
	if( infile == NULL ){ 
		printf( "Error : failed to open file : %s\n", mtog->fname );
		return -1;
	}

	/* 
	 * stage 2: scan the number of clock cycles
	 *          scan from the bottom up 
         * 
	 */
	if( scan_clocks( infile, mtog ) != 0 ){ 
		printf( "Error : failed to retrieve teh number of clock cycles\n" );
		fclose( infile );
		infile = NULL;
		return -1;
	}

	/* 
	 * stage 3: allocate memory for count arrays 
	 * 
	 */
	if( alloc_mem( mtog ) != 0 ){ 
		printf( "Error : failed to allocate memory\n" );
		fclose( infile );
		infile = NULL;
		return -1;
	}

	/* 
	 * stage 4: parse the whole file 
	 * 
 	 */
	rewind( infile );

	if( parse( infile, mtog ) != 0 ){ 
		printf( "Error : failed to parse the file\n" );
		fclose( infile );
		infile = NULL;
		return -1;
	}

	/* 
	 * stage 5: close the file 
	 * 
 	 */
	fclose( infile );
	infile = NULL;

	/* 
	 * stage 6: print the result files
	 * 
	 */
	if( print_results( mtog ) != 0 ){ 
		printf( "Error : failed to print results files\n" );
		return -1;
	}

	return 0;
}

/* --------------------------------------------------------- INIT_STRUCTS */
/* 
 * INIT_STRUCTS
 * 
 */
static int init_structs( struct mtog_t *mtog ){ 

	if( mtog == NULL ){ 
		return -1;
	}

	mtog->count.busop=NULL;
	mtog->count.memop=NULL;
	mtog->count.rd8=NULL;
	mtog->count.wr8=NULL;
	mtog->count.rd4=NULL;
	mtog->count.wr4=NULL;
	mtog->count.fence=NULL;
	mtog->count.unk=NULL;
	mtog->count.hmc_rd16=NULL;
	mtog->count.hmc_rd32=NULL;
	mtog->count.hmc_rd48=NULL;
	mtog->count.hmc_rd64=NULL;
	mtog->count.hmc_rd80=NULL;
	mtog->count.hmc_rd96=NULL;
	mtog->count.hmc_rd112=NULL;
	mtog->count.hmc_rd128=NULL;	
	mtog->count.hmc_wr16=NULL;
	mtog->count.hmc_wr32=NULL;
	mtog->count.hmc_wr48=NULL;
	mtog->count.hmc_wr64=NULL;
	mtog->count.hmc_wr80=NULL;
	mtog->count.hmc_wr96=NULL;
	mtog->count.hmc_wr112=NULL;
	mtog->count.hmc_wr128=NULL;	

	return 0;
}

/* --------------------------------------------------------- SANITY_CHECK */
/* 
 * SANITY_CHECK
 * 
 */
static int sanity_check( struct mtog_t *mtog ){
	if( mtog == NULL ){ 
		return -1;
	}

	if( mtog->fname == NULL ){
		printf( "Error : filename is null\n" );
		return -1;
	}

	return 0;
}

/* --------------------------------------------------------- MAIN */
/* 
 * MAIN
 * 
 */
extern int main( int argc, char **argv ){

	/* vars */
	int ret		= 0;
	struct mtog_t 	mtog;
	/* ---- */

	/* 
	 * init the structure
	 * 
 	 */
	if( init_structs( &mtog ) != 0 ){ 
		printf( "Error : failed to init the internal structures\n" );
		return -1;
	}

	/* 
	 * parse the command line args 
	 * 
	 */
	while(( ret = getopt( argc, argv, "F:hv" )) != -1 ){ 

		switch( ret )
		{
			case 'F' : 
				mtog.fname = malloc( sizeof( char ) * (strlen(optarg)+1) );
				if( mtog.fname == NULL ){ 
					printf( "Error : could not allocate memory for filename\n" );
					return -1;
				}

				strcpy( mtog.fname, optarg );

				break;
			case 'h' : 
				printf( "usage : %s%s", argv[0], " -F /path/to/tracefile -hv\n" );
				return 0;
				break;
			case 'v' :
				printf( "Enabling verbosity\n" );
				mtog.verbose = 1;
				break;
			case '?' :
			default :
				printf( "Unknown Option!\n" );
				printf( "usage : %s%s", argv[0], " -F /path/to/tracefile -hv\n" );
				return -1;
				break;
		}

	}

	/* 
	 * sanity check 
	 * 
 	 */
	if( sanity_check( &mtog ) != 0 ){ 
		printf( "Error : failed to sanity check args\n" );
		mtog_free( &mtog );
		return -1;
	}

	/* 
	 * mtog_convert 
	 * 
	 */
	if( mtog_convert( &mtog ) != 0 ){ 
		printf( "Error : failed to convert file\n" );
		mtog_free( &mtog );
		return -1;
	}

	/* 
	 * free the memory 
	 * 
 	 */
	if( mtog_free( &mtog ) != 0 ){ 
		printf( "Error : failed to free memory\n" );
		return -1;
	}

	return 0;
}

/* EOF */
