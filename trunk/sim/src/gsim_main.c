/* 
 * 
 * _GSIM_MAIN_C_ 
 * 
 * GOBLIN-SIM MAIN SIMULATION FILE 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


/* -------------------------------------------------- GSIM_SANITY_CHECK */
/* 
 * GSIM_SANITY_CHECK
 * 
 */
static int gsim_sanity_check( struct gsim_t *sim )
{
#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif
	/* 
	 * check the sim structure 
	 *
	 */
	if( sim == NULL ){ 
		return -1;
	}

	/* 
	 * check for a valid object 
	 *
	 */
	if( sim->obj_file == NULL ){ 
		return -1;
	}

	/* 
	 * do we allow a null stack? 
	 */
	#if 0
	if( sim->stack_size <= 8 ){
		return -1;
	}
	#endif

	/* 
	 * check hardware details
	 * 
	 */
	if( (sim->partitions > 0xFFFFFFFF) || (sim->partitions == 0) ){
		GSIM_PRINT_ERROR( "GSIM_ERROR: partitions out of bounds" );
		return -1;
	}

	if( (sim->nodes > 0xFFFFFFFF) || (sim->nodes == 0) ){
		GSIM_PRINT_ERROR( "GSIM_ERROR: nodes out of bounds" );
		return -1;
	}

	if( (sim->sockets > 0xFFFF) || (sim->sockets == 0) ){
		GSIM_PRINT_ERROR( "GSIM_ERROR: sockets out of bounds" );
		return -1;
	}

	if( (sim->task_groups > 0xFFFF) || (sim->task_groups == 0) ){
		GSIM_PRINT_ERROR( "GSIM_ERROR: task_groups out of bounds" );
		return -1;
	}

	if( (sim->task_procs > 0xFFFF) || (sim->task_procs == 0) ){
		GSIM_PRINT_ERROR( "GSIM_ERROR: task_procs out of bounds" );
		return -1;
	}

	if( (sim->tasks > 0xFFFF) || (sim->tasks == 0) ){
		GSIM_PRINT_ERROR( "GSIM_ERROR: tasks out of bounds" );
		return -1;
	}

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;
}

/* -------------------------------------------------- GSIM_PRINT_HELP */
/* 
 * GSIM_PRINT_HELP 
 * 
 */
static void gsim_print_help( char **argv )
{
#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif
	printf( "================================================================\n" );
	printf( " GSIM VERSION %d.%d\n", GSIM_MAJOR_VERSION, GSIM_MINOR_VERSION );
	printf( "================================================================\n" );
	printf( " usage : %s -cCfhILtTvV\n", argv[0] );
	printf( " Options:\n" );
	printf( " -c                             : enable C++ cycle accurate sim\n" );
	printf( " -C /path/to/config.cfg         : simualtion config file\n" );
	printf( " -e                             : dump all instruction encodings\n" );
	printf( " -f                             : enable functional sim\n" );
	printf( " -h                             : print this help menu\n" );
	printf( " -I /path/to/inst.instr         : simulation instruction file\n" );
	printf( " -L /path/to/sim.log            : simulation log file\n" );
	printf( " -O /path/to/object.{o,exe} args: object file and args\n" );
	printf( " -S stack_size_in_bytes         : set the stack size\n" );
	printf( " -t                             : enable tracing\n" );
	printf( " -T /path/to/tracefile          : simulation trace file\n" );
	printf( " -v                             : enable verilog simulation\n" );
	printf( " -V /path/to/object.o           : dissasemble and validate object\n" );
	printf( "================================================================\n" );
	printf( " Note:\n" );
	printf( " Functional simulation is the default [-f]\n" );
	printf( "================================================================\n" );

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return ;
}

/* -------------------------------------------------- MAIN */
/* 
 * MAIN 
 * 
 */
int main( int argc, char **argv )
{
	/* vars */
	int ret			= 0;
	struct gsim_t	*sim	= NULL;
	char *tmp		= NULL;
	char *tok		= NULL;
	/* ---- */


#ifdef GSIM_DEBUG
	GSIM_PRINT_MSG( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
	GSIM_PRINT_MSG( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
	GSIM_PRINT_MSG( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
	GSIM_PRINT_MSG( "!!WARNING!!  RUNNING IN DEBUG MODE!" );
	GSIM_PRINT_MSG( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
	GSIM_PRINT_MSG( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
	GSIM_PRINT_MSG( "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" );
#endif


	/* 
	 * check the incoming arg count 
	 * 
	 */	
	if( argc < 3 ){ 
		GSIM_PRINT_ERROR( "Insufficient program arguments" );	
		gsim_print_help( argv );
		return -1;
	}

	/* 
	 * allocate the simulation data
	 */
	sim = gsim_malloc( sizeof( struct gsim_t ) );
	if( sim == NULL ){ 
		GSIM_PRINT_ERROR( "GSIM_ERROR: Cannot allocate memoy for sim" );
		return -1;
	}

	if( gsim_init_sim( sim ) != 0 ){ 
		GSIM_PRINT_ERROR( "GSIM_ERROR: Failed to initialize simualtion data" );
		goto gsim_cleanup;
		return -1;
	}

	/*
	 * Parse the command line args
	 */
	while(( ret = getopt( argc, argv, "cC:efhI:L:O:S:tT:vV:" )) != -1 )
	{
		switch ( ret )
		{
			case 'c': 
				/* enable c++ cycle accurate simulation */
				if( (sim->options & GSIM_OPT_CYCLE_FUNC) > 0 ){
					sim->options &= ~GSIM_OPT_CYCLE_FUNC;
				}

				if( (sim->options & GSIM_OPT_CYCLE_HDL) > 0 ){
					sim->options &= ~GSIM_OPT_CYCLE_HDL;
				}

				sim->options |= GSIM_OPT_CYCLE_ACCUR;
			
				#ifdef GSIM_DEBUG
				GSIM_PRINT_MSG( "Setting option GSIM_OPT_CYCLE_ACCUR" );
				#endif

				break;
			case 'C': 
				/* config file */
				sim->config_file = gsim_malloc( (size_t)(sizeof( char ) * strlen( optarg )+1) );

				if( sim->config_file == NULL ) {
					GSIM_PRINT_ERROR( "GSIM_ERROR: Cannot allocate memory for config_file" );
					goto gsim_cleanup;
				}
				snprintf( sim->config_file, strlen( optarg )+1, "%s", optarg );
				break;
			case 'e': 
				/* 
				 * dump all legal instructions encodings 
				 */
				
				sim->options |= GSIM_OPT_DUMPINST;

				#ifdef GSIM_DEBUG
				GSIM_PRINT_MSG( "Setting option GSIM_OPT_DUMPINST" );
				#endif

				break;
			case 'f': 
				/* enable functional simulation
				 * not cycle accurate 
				 */

				if( (sim->options & GSIM_OPT_CYCLE_ACCUR) > 0 ){
					sim->options &= ~GSIM_OPT_CYCLE_ACCUR;
				}

				if( (sim->options & GSIM_OPT_CYCLE_HDL) > 0 ){
					sim->options &= ~GSIM_OPT_CYCLE_HDL;
				}

				sim->options |= GSIM_OPT_CYCLE_FUNC;
			
				#ifdef GSIM_DEBUG
				GSIM_PRINT_MSG( "Setting option GSIM_OPT_CYCLE_FUNC" );
				#endif

				break;
			case 'h': 
				/* print help */
				gsim_print_help( argv );
				return 0;
				break;
			case 'I': 
				/* instruction file */
				sim->inst_file = gsim_malloc( (size_t)(sizeof( char ) * strlen( optarg )+1) );

				if( sim->inst_file == NULL ) {
					GSIM_PRINT_ERROR( "GSIM_ERROR: Cannot allocate memory for inst_file" );
					goto gsim_cleanup;
				}
				snprintf( sim->inst_file, strlen( optarg )+1, "%s", optarg );
				break;
			case 'L':
				/* log file */
				sim->log_file = gsim_malloc( (size_t)(sizeof( char ) * strlen( optarg )+1) );

				if( sim->log_file == NULL ) {
					GSIM_PRINT_ERROR( "GSIM_ERROR: Cannot allocate memory for log_file" );
					goto gsim_cleanup;
				}
				snprintf( sim->log_file, strlen( optarg )+1, "%s", optarg );
				break;
			case 'O':
				/* object file + options */
				tmp = gsim_malloc( (size_t)(sizeof( char ) * strlen( optarg )+1) );
				
				if( tmp == NULL ){ 
					GSIM_PRINT_ERROR( "GSIM_ERROR: Cannot allocate memory for tmp [object file]" );
					goto gsim_cleanup;
				}

				/* 
				 * the object and see if there is an object file 
				 * followed by spaces; eg ARGV exists 
				 */

				snprintf( tmp, strlen( optarg )+1, "%s", optarg );
				tok = strtok( tmp, " " );
				if( (tok != NULL) && (strcmp( tmp, tok)!=0) ) { 
					/*
					 * found an ARGV 
					 *
					 */
					sim->obj_file = gsim_malloc( (size_t)(sizeof( char ) * strlen( tok )) );
					if( sim->obj_file == NULL ){ 
						GSIM_PRINT_ERROR( "GSIM_ERROR: Cannot allocate memory for obj_file" );
						gsim_free( tmp );
						goto gsim_cleanup;	
					}
					snprintf( sim->obj_file, strlen( tok ), "%s", tok );

					tok = strtok( NULL, " " );

					sim->obj_opts = gsim_malloc( (size_t)(sizeof( char ) * strlen( tok )) );
					if( sim->obj_file == NULL ){ 
						GSIM_PRINT_ERROR( "GSIM_ERROR: Cannot allocate memory for obj_opts" );
						gsim_free( tmp );
						goto gsim_cleanup;	
					}
					snprintf( sim->obj_opts, strlen( tok ), "%s", tok );
					
				}else{
					sim->obj_file = gsim_malloc( (size_t)(sizeof( char ) * strlen( optarg )) );
					if( sim->obj_file == NULL ){ 
						GSIM_PRINT_ERROR( "GSIM_ERROR: Cannot allocate memory for obj_file" );
						gsim_free( tmp );
						goto gsim_cleanup;	
					}

					sim->obj_opts = NULL;
				}

				gsim_free( tmp );

				break;
			case 'S': 
				/* set stack size */
				sim->stack_size	= atoi(optarg);
				break;
			case 't': 
				/* enable tracing */
				sim->options |= GSIM_OPT_TRACING;

				#ifdef GSIM_DEBUG
				GSIM_PRINT_MSG( "Setting option GSIM_OPT_TRACING" );
				#endif

				break;
			case 'T': 
				/* set the trace file : default = gsim.trace */
				sim->trace_file = gsim_malloc( (size_t)(sizeof( char ) * strlen( optarg )) );

				if( sim->trace_file == NULL ) {
					GSIM_PRINT_ERROR( "GSIM_ERROR: Cannot allocate memory for trace_file" );
					goto gsim_cleanup;
				}
				snprintf( sim->trace_file, strlen( optarg ), "%s", optarg );
				break;
			case 'v': 
				/* enable verilog simulation */

				if( (sim->options & GSIM_OPT_CYCLE_FUNC) > 0 ){
					sim->options &= ~GSIM_OPT_CYCLE_FUNC;
				}

				if( (sim->options & GSIM_OPT_CYCLE_ACCUR) > 0 ){
					sim->options &= ~GSIM_OPT_CYCLE_ACCUR;
				}

				sim->options |= GSIM_OPT_CYCLE_HDL;
			
				#ifdef GSIM_DEBUG
				GSIM_PRINT_MSG( "Setting option GSIM_OPT_CYCLE_HDL" );
				#endif

				break;
			case 'V': 
				/* validate the target object file, but do not execute */
				sim->options |= GSIM_OPT_VALIDATE;

				#ifdef GSIM_DEBUG
				GSIM_PRINT_MSG( "Setting option GSIM_OPT_VALIDATE" );
				#endif

				break;
			case '?':
			default:
				printf( "%s%s%s\n", "Unknown Option: see ", argv[0], " -h" );
				gsim_print_help( argv );
				return -1;
				break;
		}
	}

	#ifdef GSIM_TRACE
	GSIM_PRINT_MSG( "DONE PARSING CLI ARGS" );
	#endif

	/* 
	 * check to see if we simply dump the instructions
	 *
	 */
	if( (sim->options & GSIM_OPT_DUMPINST) > 0 ) { 
		
		gsim_dump_inst( sim );
		
		goto gsim_cleanup;
	}

	/* 
	 * read the config file
	 *
	 */
	if( gsim_config_read( sim ) != 0 ){
		GSIM_PRINT_ERROR( "Could not find a valid configuration" );
		gsim_free( sim );
		return -1;
	}
	
	/* 
	 * sanity check the options 
	 * 
 	 */
	if( gsim_sanity_check( sim ) != 0 ){ 
		GSIM_PRINT_ERROR( "Sanity check of simulation arguments failed!" );
		gsim_free_sim( sim );
		return -1;
	}

	/* 
	 * init the sim internals 
	 * 
	 */
	if( gsim_init_internals( sim ) != 0 ){ 
		GSIM_PRINT_ERROR( "Failed to initialize hardware internals" );
		gsim_free_sim( sim );
		return -1;
	}

	/*
	 * crack and validate
	 * all the instructions
	 *
	 */
	

	/* 
	 * open the log file
	 * 
	 */
	if( gsim_io_open_logfile( sim) != 0 ){
		GSIM_PRINT_ERROR( "Failed to open logfile" );	
		gsim_free( sim );
		return -1;
	}

	/* 
	 * open trace file 
	 * 
	 */
	if( (sim->options & GSIM_OPT_TRACING) > 0 ){ 
		/* 
	 	 * tracing is enabled, open
		 * a tracefile
		 *
		 */
		if( gsim_io_open_tracefile( sim ) != 0 ){
			GSIM_PRINT_ERROR( "Failed to open tracefile" );	
			gsim_free( sim );
			return -1;
		}
	}
	

	/* 
	 * run the simulation
	 * 
	 */
	if( (sim->options & GSIM_OPT_CYCLE_FUNC) > 0 ){ 

		/* 
		 * execute functional sim
		 *
		 */
		if( gsim_exec_functional( sim ) != 0 ){ 
		
			GSIM_PRINT_ERROR( "Functional simulation failed!" );	
			gsim_free_sim( sim );
		}

	}else if( (sim->options & GSIM_OPT_CYCLE_ACCUR) > 0 ){
		
		/* 
		 * execute cycle accurate sim 
		 * 
		 */

	}else if( (sim->options & GSIM_OPT_CYCLE_HDL) > 0 ){
		
		/* 
		 * execute hdl sim 
		 * 
		 */

	}else{
		GSIM_PRINT_ERROR( "Failed to execute any simulations; See goblin-sim -h" );	
		gsim_free( sim );
		return -1;
	}

gsim_cleanup:
	/* 
	 * done running the sim; free the memory
	 * 
	 */
	gsim_free_sim( sim );

	printf( "Goblin-Sim Successfully Completed\n" );

	return 0;
}


/* EOF */
