/* 
 * 
 * _GSIM_CONFIG_C_ 
 * 
 * GOBLIN-SIM CONFIG FILE INTERFACES
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "goblin_sim.h"


/* -------------------------------------------------- FUNCTION PROTOTYPES */
extern int gsim_config_func_parser(	uint32_t *enable_vector, uint32_t *enable_global_addr, 
					uint32_t *task_groups, uint32_t *task_procs, 
					uint32_t *tasks, uint32_t *icache_ways, 
					uint32_t *icache_sets, uint32_t *amo_slots, 
					uint32_t *partitions, uint32_t *nodes, 
					uint32_t *sockets, uint32_t *hmc_num_devs, 
					uint32_t *hmc_num_links, uint32_t *hmc_num_vaults,
					uint32_t *hmc_queue_depth, uint32_t *hmc_num_banks, 
					uint32_t *hmc_num_drams, uint32_t *hmc_capacity, 
					uint32_t *hmc_xbar_depth,
					char *cfile );

/* -------------------------------------------------- GSIM_CONFIG_READ */
/* 
 * GSIM_CONFIG_READ
 * 
 */
extern int gsim_config_read( struct gsim_t *sim )
{
#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_ENTRY();
#endif

	/* vars */
	uint32_t enable_vector		= 0;
	uint32_t enable_global_addr	= 0;
	uint32_t task_groups		= 0;
	uint32_t task_procs		= 0;
	uint32_t tasks			= 0;
	uint32_t icache_ways		= 0;
	uint32_t icache_sets		= 0;
	uint32_t amo_slots		= 0;
	uint32_t partitions		= 0;
	uint32_t nodes			= 0;
	uint32_t sockets		= 0;
	uint32_t hmc_num_devs		= 0;
	uint32_t hmc_num_links		= 0;
	uint32_t hmc_num_vaults		= 0;
	uint32_t hmc_queue_depth	= 0;
	uint32_t hmc_num_banks		= 0;
	uint32_t hmc_num_drams		= 0;
	uint32_t hmc_capacity		= 0;
	uint32_t hmc_xbar_depth		= 0;
	/* ---- */

	/* sanity check */
	if( sim == NULL ){ 
		return -1;
	}

	/* 
	 * call the parser generated by flex
	 * 
	 */
	if( gsim_config_func_parser(  	&enable_vector, &enable_global_addr, &task_groups, 
					&task_procs, &tasks, &icache_ways, 
					&icache_sets, &amo_slots, &partitions, 
					&nodes, &sockets, &hmc_num_devs, &hmc_num_links, 
					&hmc_num_vaults, &hmc_queue_depth, &hmc_num_banks, 
					&hmc_num_drams, &hmc_capacity, &hmc_xbar_depth,
					sim->config_file ) != 0 ) {
		return -1;
	}

	/* 
	 * global addressing option
	 *
	 */
	if( enable_global_addr == 1 ){
		sim->options |= GSIM_OPT_GLOBAL_ADDR;
	}else if( (sim->options & GSIM_OPT_GLOBAL_ADDR) > 0 ){
		sim->options &= ~GSIM_OPT_GLOBAL_ADDR;
	}

	/* 
	 * vector
	 *
	 */
	if( enable_vector == 1 ){
		sim->options |= GSIM_OPT_VECTOR;
	}else if( (sim->options & GSIM_OPT_VECTOR) > 0 ){ 
		sim->options &= ~GSIM_OPT_VECTOR;
	}

	/* -- hw */
	sim->task_groups 	= task_groups;
	sim->task_procs		= task_procs;
	sim->tasks		= tasks;
	sim->icache_ways	= icache_ways;
	sim->icache_sets	= icache_sets;
	sim->amo_slots		= amo_slots;

	/* -- hmc */
	sim->hmc_num_devs	= hmc_num_devs;
	sim->hmc_num_links	= hmc_num_links;
	sim->hmc_num_vaults	= hmc_num_vaults;
	sim->hmc_queue_depth	= hmc_queue_depth;
	sim->hmc_num_banks	= hmc_num_banks;
	sim->hmc_num_drams	= hmc_num_drams;
	sim->hmc_capacity	= hmc_capacity;
	sim->hmc_xbar_depth	= hmc_xbar_depth;

#ifdef GSIM_TRACE
	GSIM_PRINT_FUNC_EXIT();
#endif
	return 0;	
}


/* EOF */