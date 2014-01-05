%{
/* 
 * _GSIM_CONFIG_PARSER_LEX_
 *
 * PARSER LEX DRIVER 
 *  
 */ 

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "goblin_sim.h"

enum {
	LOOKUP 			= 0, 
	ENABLE_VECTOR 		= 1, 
	ENABLE_GLOBAL_ADDR	= 2, 
	TASK_GROUPS		= 3, 
	TASK_PROCS		= 4, 
	TASKS			= 5,
	ICACHE_WAYS		= 6, 
	ICACHE_SETS		= 7, 
	AMO_SLOTS		= 8, 
	PARTITIONS		= 9, 
	NODES			= 10, 
	SOCKETS			= 11,
	HMC_NUM_DEVS		= 12,
	HMC_NUM_LINKS		= 13,
	HMC_NUM_VAULTS		= 14,
	HMC_QUEUE_DEPTH		= 15,
	HMC_NUM_BANKS		= 16,
	HMC_NUM_DRAMS		= 17,
	HMC_CAPACITY		= 18,
	HMC_XBAR_DEPTH		= 19
};

int state;
int gsim_config_func( int type, char *word );
uint32_t *__enable_vector;
uint32_t *__enable_global_addr;
uint32_t *__task_groups;
uint32_t *__task_procs;
uint32_t *__tasks;
uint32_t *__icache_ways;
uint32_t *__icache_sets;
uint32_t *__amo_slots;
uint32_t *__partitions;
uint32_t *__nodes;
uint32_t *__sockets;
uint32_t *__hmc_num_devs;
uint32_t *__hmc_num_links;
uint32_t *__hmc_num_vaults;
uint32_t *__hmc_queue_depth;
uint32_t *__hmc_num_banks;
uint32_t *__hmc_num_drams;
uint32_t *__hmc_capacity;
uint32_t *__hmc_xbar_depth;
%}

%option nounput
%option noyywrap

%%
\n			{	state = LOOKUP;	}
^ENABLE_VECTOR		{ 	state = ENABLE_VECTOR; }
^ENABLE_GLOBAL_ADDR	{ 	state = ENABLE_GLOBAL_ADDR; }
^TASK_GROUPS		{ 	state = TASK_GROUPS; }
^TASK_PROCS		{ 	state = TASK_PROCS; }
^TASKS			{ 	state = TASKS; }
^ICACHE_WAYS		{ 	state = ICACHE_WAYS; }
^ICACHE_SETS		{ 	state = ICACHE_SETS; }
^AMO_SLOTS		{	state = AMO_SLOTS; }
^PARTITIONS		{	state = PARTITIONS; }
^NODES			{ 	state = NODES;	}
^SOCKETS		{ 	state = SOCKETS; }
^HMC_NUM_DEVS		{ 	state = HMC_NUM_DEVS; }
^HMC_NUM_LINKS		{ 	state = HMC_NUM_LINKS; }
^HMC_NUM_VAULTS		{ 	state = HMC_NUM_VAULTS; }
^HMC_QUEUE_DEPTH	{ 	state = HMC_QUEUE_DEPTH; }
^HMC_NUM_BANKS		{ 	state = HMC_NUM_BANKS; }
^HMC_NUM_DRAMS		{ 	state = HMC_NUM_DRAMS; }
^HMC_CAPACITY		{ 	state = HMC_CAPACITY; }
^HMC_XBAR_DEPTH		{ 	state = HMC_XBAR_DEPTH; }
[a-zA-Z0-9\/.-_]+	{ if( state != LOOKUP ) gsim_config_func( state, yytext ); }
. ;
%%

extern int gsim_config_func_parser( 	uint32_t *enable_vector, uint32_t *enable_global_addr, 
					uint32_t *task_groups, uint32_t *task_procs, 
					uint32_t *tasks, uint32_t *icache_ways, 
					uint32_t *icache_sets, uint32_t *amo_slots, 
					uint32_t *partitions, uint32_t *nodes, 
					uint32_t *sockets, 
					uint32_t *hmc_num_devs, 
					uint32_t *hmc_num_links, uint32_t *hmc_num_vaults, 
					uint32_t *hmc_queue_depth, uint32_t *hmc_num_banks, 
					uint32_t *hmc_num_drams, uint32_t *hmc_capacity, 
					uint32_t *hmc_xbar_depth,
					char *cfile )
{
	__enable_vector		= enable_vector;
	__enable_global_addr	= enable_global_addr;
	__task_groups		= task_groups;
	__task_procs		= task_procs;
	__tasks			= tasks;
	__icache_ways		= icache_ways;
	__icache_sets		= icache_sets;
	__amo_slots		= amo_slots;
	__partitions		= partitions;
	__nodes			= nodes;
	__sockets		= sockets;
	__hmc_num_devs		= hmc_num_devs;
	__hmc_num_links		= hmc_num_links;
	__hmc_num_vaults	= hmc_num_vaults;
	__hmc_queue_depth	= hmc_queue_depth;
	__hmc_num_banks		= hmc_num_banks;
	__hmc_num_drams		= hmc_num_drams;
	__hmc_capacity		= hmc_capacity;
	__hmc_xbar_depth	= hmc_xbar_depth; 

	yyin = fopen( cfile, "r" );
	
	yylex();

	fclose( yyin );
	yyin = NULL;

	return 0;
}

int gsim_config_func( int type, char *word )
{
	switch( type )
	{
		case HMC_NUM_DEVS:
			*__hmc_num_devs		= (uint32_t)(atoi( word ));
			break;
		case HMC_NUM_LINKS:
			*__hmc_num_links	= (uint32_t)(atoi( word ));
			break;
		case HMC_NUM_VAULTS:
			*__hmc_num_vaults	= (uint32_t)(atoi( word ));
			break;
		case HMC_QUEUE_DEPTH:
			*__hmc_queue_depth	= (uint32_t)(atoi( word ));
			break;
		case HMC_NUM_BANKS:
			*__hmc_num_banks	= (uint32_t)(atoi( word ));
			break;
		case HMC_NUM_DRAMS:
			*__hmc_num_drams	= (uint32_t)(atoi( word ));
			break;
		case HMC_CAPACITY:
			*__hmc_capacity		= (uint32_t)(atoi( word ));
			break;
		case HMC_XBAR_DEPTH:
			*__hmc_xbar_depth	= (uint32_t)(atoi( word ));
			break;
		case ENABLE_VECTOR : 
			*__enable_vector 	= (uint32_t)(atoi( word ));
			break;
		case ENABLE_GLOBAL_ADDR:
			*__enable_global_addr 	= (uint32_t)(atoi( word ));
			break;
		case TASK_GROUPS:
			*__task_groups 		= (uint32_t)(atoi( word ));
			break;
		case TASK_PROCS:
			*__task_procs 		= (uint32_t)(atoi( word ));
			break;
		case TASKS:
			*__tasks 		= (uint32_t)(atoi( word ));
			break;
		case ICACHE_WAYS: 
			*__icache_ways		= (uint32_t)(atoi( word ));
			break;
		case ICACHE_SETS: 
			*__icache_sets		= (uint32_t)(atoi( word ));
			break;
		case AMO_SLOTS:
			*__amo_slots		= (uint32_t)(atoi( word ));
			break;
		case PARTITIONS:
			*__partitions		= (uint32_t)(atoi( word ));
			break;
		case NODES: 
			*__nodes		= (uint32_t)(atoi( word ));
			break;
		case SOCKETS:
			*__sockets		= (uint32_t)(atoi( word ));
			break;
		default:
			break;
	}

	return 0;
}
