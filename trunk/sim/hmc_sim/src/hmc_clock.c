/* 
 * _HMC_CLOCK_C_
 * 
 * HYBRID MEMORY CUBE SIMULATION LIBRARY 
 * 
 * CLOCK FUNCTIONS
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hmc_sim.h"


/* ----------------------------------------------------- FUNCTION PROTOTYPES */
extern int hmcsim_trace( struct hmcsim_t *hmc, char *str );
extern int hmcsim_process_bank_conflicts( struct hmcsim_t *hmc, 
						uint32_t dev, 
						uint32_t quad, 
						uint32_t vault, 
						uint64_t *addr ); 
extern int hmcsim_process_rqst( struct hmcsim_t *hmc, 
				uint32_t dev, 
				uint32_t quad, 
				uint32_t vault, 
				uint32_t slot );



/* ----------------------------------------------------- HMCSIM_CLOCK_PROCESS_RQST_QUEUE */
/* 
 * HMCSIM_CLOCK_PROCESS_RQST_QUEUE
 * 
 */
static int hmcsim_clock_process_rqst_queue( 	struct hmcsim_t *hmc, 
						uint32_t dev, 
						uint32_t link )
{
	/* vars */
	uint32_t i	= 0;
	uint32_t j	= 0;
	uint32_t found	= 0;
	uint32_t success= 0;
	uint32_t len	= 0;
	uint32_t t_link	= 0;
	uint32_t t_slot	= 0;
	uint32_t t_quad = 0;
	uint32_t t_vault= hmc->queue_depth+1;
	uint8_t	cub	= 0;
	uint8_t plink	= 0;
	uint64_t header	= 0x00ll;
	uint64_t tail	= 0x00ll;
	/* ---- */

	/* 
	 * walk the queue and process all the valid
	 * slots
	 * 
	 */

	for( i=0; i<hmc->xbar_depth; i++ ){
		
		if( hmc->devs[dev].xbar[link].xbar_rqst[i].valid == HMC_RQST_VALID ){ 
			
			/* 
			 * process me
			 * 
			 */			

			/* 
			 * Step 1: Get the header
			 * 
			 */
			header = hmc->devs[dev].xbar[link].xbar_rqst[i].packet[0];

			/* 
			 * Step 2: Get the CUB.  
			 *
			 */
			cub = (uint8_t)( header & 0x3F );	

			/* Step 3: If it is equal to `dev`
			 *         then we have a local request.
			 * 	   Otherwise, its a request to forward to
			 * 	   an adjacent device.
			 */
		
			/* 
			 * Stage 4: Get the packet length
			 * 
			 */
			len = (uint32_t)( (header & 0x780) >> 7);
			len *= 2;

			/* 
			 * Stage 5: Get the packet tail
			 * 
			 */		
			tail = hmc->devs[dev].xbar[link].xbar_rqst[i].packet[len-1];


			/* 
			 * Stage 6: Get the link
			 * 
			 */
			plink = (uint8_t)( (tail & 0x7000000) >> 24 );

			if( cub == (uint8_t)(dev) ){
				/* 
				 * local request
				 *
				 */
				
				/* 
				 * 7a: Retrieve the vault id
				 * 
				 */
				/* TODO: RETRIEVE THE VAULT FROM THE ADDRESS */
				t_vault = 0;

				/* 
				 * 8a: Retrieve the quad id
				 * 
				 */
				t_quad = plink % hmc->num_quads;
					
				
				/* 
				 * 9a: Search the vault queue for valid slot
				 *     Search bottom-up
				 * 
				 */
				t_slot = hmc->queue_depth+1;

				for( j=hmc->queue_depth-1; j>=0; j-- ){
					if( hmc->devs[dev].quads[t_quad].vaults[t_vault].rqst_queue[j].valid == HMC_RQST_INVALID ){
						t_slot = j;	
					}
				}

				if( t_slot == hmc->queue_depth+1 ){ 
					/* STALL */
				}else {

					/*
					 * push it into the designated queue slot
					 * 
					 */
					hmc->devs[dev].quads[t_quad].vaults[t_vault].rqst_queue[t_slot].valid = HMC_RQST_VALID;
					for( j=0; j<HMC_MAX_UQ_PACKET; j++ ){ 
						hmc->devs[dev].quads[t_quad].vaults[t_vault].rqst_queue[t_slot].packet[j] = 
							hmc->devs[dev].xbar[link].xbar_rqst[i].packet[j];
					}

				}

			}else{

				/* 
				 * forward request to remote device
				 *
				 */

				/* 
				 * Stage 7b: Decide whether cub is accessible
				 * 
				 */
				found = 0;
	
				while( (found != 1) && (j<hmc->num_links) ){ 
					
					if( hmc->devs[dev].links[j].dest_cub == cub ){ 
						found = 1;
						t_link = j;
					}

					j++;
				}

				if( found == 0 ){ 
					/* 
					 * oh snap! can't route to that CUB
					 *
					 */
					/* -- TODO, RETURN AN ERROR */
				}else{ 
					/* 
					 * 8b: routing is good, look for an empty slot
					 * in the target xbar link queue
					 *
					 */
					t_slot = hmc->xbar_depth+1;
					for( j=hmc->xbar_depth-1; j>= 0; j-- ){
	
						/* 
						 * walk the queue from the bottom
						 * up
						 */			
						if( hmc->devs[cub].xbar[t_link].xbar_rqst[j].valid == 
							HMC_RQST_INVALID ) {
							t_slot = j;
						}
					}

					/* 
				 	 * 9b: If available, insert into remote xbar slot 
					 * 
					 */
					if( t_slot == hmc->xbar_depth+1 ){
						/* 
						 * STALL!
						 *
						 */
						success = 0;
					}else {
						/* 
						 * put the new link in the link field
						 *  
						 */
						 hmc->devs[dev].xbar[link].xbar_rqst[i].packet[len-1] |= 
										((uint64_t)(plink)<<24);

						/* 
						 * transfer the packet to the target slot
						 * 
						 */
						hmc->devs[cub].xbar[t_link].xbar_rqst[t_slot].valid = 
							HMC_RQST_VALID;	
						for( j=0; j<HMC_MAX_UQ_PACKET; j++ ){ 
							hmc->devs[cub].xbar[t_link].xbar_rqst[t_slot].packet[j] = 
							hmc->devs[dev].xbar[link].xbar_rqst[i].packet[j];
						}	

						/* 
						 * signal success
						 *
						 */
						success = 1;
					}
				}
			}

			if( success == 1 ){ 
			
				/* 
				 * clear the packet 
				 * 
				 */
				hmc->devs[dev].xbar[link].xbar_rqst[i].valid = HMC_RQST_INVALID;
				memset( hmc->devs[dev].xbar[link].xbar_rqst[i].packet, 0, sizeof( uint64_t ) * HMC_MAX_UQ_PACKET ); 
			}

		}

		success = 0;
	}		

	return 0;
}


/* ----------------------------------------------------- HMCSIM_CLOCK_CHILD_XBAR */
/* 
 * HMCSIM_CLOCK_CHILD_XBAR
 * 
 */
static int hmcsim_clock_child_xbar( struct hmcsim_t *hmc )
{
	/* vars */
	uint32_t i	= 0;
	uint32_t j	= 0;
	uint32_t host_l	= 0;
	/* ---- */

	/* 
	 * walk each device and interpret the links
	 * if you find a HOST link, no dice. 
	 * otherwise, process the xbar queues
	 * 
	 */
	for( i=0; i<hmc->num_devs; i++ ){ 
		
		/* 
		 * walk the links
	 	 * 
	 	 */
		
		for( j=0; j<hmc->num_links; j++ ){ 
			
			if( (hmc->devs[i].links[j].type == HMC_LINK_HOST_DEV) &&
				(hmc->devs[i].links[j].src_cub == (hmc->num_devs+1) )){ 
				/* 
				 * This device is connected directly
				 * to the host processor 
				 * We want to record this such that we can skip it
			 	 *
				 */
				host_l++;
			}

		}

		/* 
		 * if no host links found, process the queues
	 	 *
		 */
		if( host_l == 0 ) {

			/* 
			 * walk the xbar queues and process the 
			 * incoming packets
			 *
			 */
			for( j=0; j<hmc->num_links; j++ ){ 

				hmcsim_clock_process_rqst_queue( hmc, i, j );

			}		
		}

		/* 
		 * reset the host links
		 *
		 */
		host_l	= 0;
	}

	return 0;
}


/* ----------------------------------------------------- HMCSIM_CLOCK_ROOT_XBAR */
/* 
 * HMCSIM_CLOCK_ROOT_XBAR
 * 
 */
static int hmcsim_clock_root_xbar( struct hmcsim_t *hmc )
{
	/* vars */
	uint32_t i	= 0;
	uint32_t j	= 0;
	uint32_t host_l	= 0;
	/* ---- */

	/* 
	 * walk each device and interpret the links
	 * if you find a HOST link, process it. 
	 * otherwise, ignore it
	 * 
	 */
	for( i=0; i<hmc->num_devs; i++ ){ 
		
		/* 
		 * walk the links
	 	 * 
	 	 */
		
		for( j=0; j<hmc->num_links; j++ ){ 
			
			if( (hmc->devs[i].links[j].type == HMC_LINK_HOST_DEV) &&
				(hmc->devs[i].links[j].src_cub == (hmc->num_devs+1) )){ 
				host_l++;
			}

		}

		/* 
		 * if no host links found, process the queues
	 	 *
		 */
		if( host_l != 0 ) {

			/* 
			 * walk the xbar queues and process the 
			 * incoming packets
			 *
			 */
			for( j=0; j<hmc->num_links; j++ ){ 

				hmcsim_clock_process_rqst_queue( hmc, i, j );

			}		
		}

		/* 
		 * reset the host links
		 *
		 */
		host_l	= 0;
	}

	return 0;
}

/* ----------------------------------------------------- HMCSIM_CLOCK_BANK_CONFLICTS */
/* 
 * HMCSIM_CLOCK_BANK_CONFLICTS
 * 
 */
static int hmcsim_clock_bank_conflicts( struct hmcsim_t *hmc )
{
	/* vars */
	uint32_t i	= 0;
	uint32_t j	= 0;
	uint32_t k	= 0;
	uint32_t x	= 0;
	uint64_t tmp	= 0x00ll;
	uint64_t addr[HMC_MAX_BANKS];
	/* ---- */

	/*
	 * clear the address array 
	 * 
	 */
	for( i=0; i<hmc->num_banks; i++ ){
		addr[i]	= 0x00ll;
	}

	/* 
	 * Walk each device+vault combination
	 * and examine the request queues for 
	 * bank conflicts
	 * 
 	 */
	for( i=0; i<hmc->num_devs; i++){ 
		for( j=0; j<hmc->num_quads; j++ ){
			for( k=0; j<hmc->num_vaults; k++ ){ 

				/* 
				 * process the first 
				 * min( HMC_NUM_BANKS, queue_depth )
				 * queue slots and examine
				 * the addresses
				 *
				 */

				if( hmc->queue_depth > HMC_MAX_BANKS ){ 

					/* 
					 * queue_depth is > MAX_BANKS
					 *
					 */
					for( x=0; x<hmc->num_banks; x++ ){

						/* 
						 * collect the first 'x' 
						 * addresses
						 *
						 */
						tmp = 0x00ll;
						tmp = 
						   (hmc->devs[i].quads[j].vaults[k].rqst_queue[x].packet[0]>>24)
						   &0x3FFFFFFFF;
						addr[x] = tmp;
					}

				} else {

					/* 
					 * queue_depth is < NUM_BANKS
					 *
					 */
					for( x=0; x<hmc->queue_depth; x++ ){

						/* 
						 * collect the first 'x' 
						 * addresses
						 *
						 */
						tmp = 0x00ll;
						tmp = 
						   (hmc->devs[i].quads[j].vaults[k].rqst_queue[x].packet[0]>>24)
						   &0x3FFFFFFFF;
						addr[x] = tmp;

					}

				}

				/* 
				 * process the bank conflicts
				 * 
			 	 */
				hmcsim_process_bank_conflicts( hmc, i, j, k, &(addr[0]) ); 
			}
		}
	}
	

	return 0;
}

/* ----------------------------------------------------- HMCSIM_CLOCK_ANALYSIS_PHASE */
/* 
 * HMCSIM_CLOCK_ANALYSIS_PHASE
 * 
 */
static int hmcsim_clock_analysis_phase( struct hmcsim_t *hmc )
{
	/* 
	 * This is where we put all the inner-clock
	 * analysis phases.  The current phases
	 * are as follows: 
 	 * 
	 * 1) Bank conflict analysis
	 * 2) TODO: cache detection analysis
	 * 
	 */

	/* 
	 * 1) Bank Conflict Analysis
	 * 
	 */
	if( hmcsim_clock_bank_conflicts( hmc ) != 0 ){
		return -1;
	}

	/* 
	 * 2) Cache Detection Analysis
	 * 
	 */

	return 0;
}

/* ----------------------------------------------------- HMCSIM_CLOCK_RW_OPS */
/* 
 * HMCSIM_CLOCK_RW_OPS
 * 
 */
static int hmcsim_clock_rw_ops( struct hmcsim_t *hmc )
{
	/* vars */
	uint32_t i	= 0;
	uint32_t j	= 0;
	uint32_t k	= 0;
	uint32_t x	= 0;
	uint32_t test	= 0x00000000;
	/* ---- */

	for( i=0; i<hmc->num_devs; i++){ 
		for( j=0; j<hmc->num_quads; j++ ){
			for( k=0; j<hmc->num_vaults; k++ ){ 
					
				/* 
				 * process the first 
				 * min( HMC_NUM_BANKS, queue_depth )
				 * queue slots and process the requests
				 *
				 */

				if( hmc->queue_depth > HMC_MAX_BANKS ){ 

					/* 
					 * queue_depth is > MAX_BANKS
					 *
					 */
					for( x=0; x<hmc->num_banks; x++ ){
			
						/* 
						 * determine whether the 
						 * queue slot is valid and not	
						 * a bank conflict
						 *
						 */
						test = 0x00000000;
						test = hmc->devs[i].quads[j].vaults[k].rqst_queue[x].valid;

						if( (test > 0 ) && (test != 2) ){

							/* 
							 * valid and no conflict 
							 * process the request
							 * 
							 */
							hmcsim_process_rqst( hmc, i, j, k, x );
						}
					}

				} else {

					/* 
					 * queue_depth is < NUM_BANKS
					 *
					 */
					for( x=0; x<hmc->queue_depth; x++ ){

						/* 
						 * determine whether the 
						 * queue slot is valid and not	
						 * a bank conflict
						 *
						 */
						test = 0x00000000;
						test = hmc->devs[i].quads[j].vaults[k].rqst_queue[x].valid;

						if( (test > 0 ) && (test != 2) ){

							/* 
							 * valid and no conflict 
							 * process the request
							 * 
							 */
							hmcsim_process_rqst( hmc, i, j, k, x );
						}
					}

				}
			}
		}
	}

	return 0;
}

/* ----------------------------------------------------- HMCSIM_CLOCK_REG_RESPONSES */
/* 
 * HMCSIM_CLOCK_REG_RESPONSES
 * 
 */
static int hmcsim_clock_reg_responses( struct hmcsim_t *hmc )
{
	return 0;
}

/* ----------------------------------------------------- HMCSIM_CLOCK_REORG_XBAR_RQST */
/* 
 * HMCSIM_CLOCK_REORG_XBAR_RQST 
 * 
 */
static int hmcsim_clock_reorg_xbar_rqst( struct hmcsim_t *hmc, uint32_t dev, uint32_t link )
{
	/* vars */
	uint32_t i	= 0;
	uint32_t j	= 0;
	uint32_t slot   = 0;
	/* ---- */

	/* 
	 * walk the request queue starting at slot 1 
	 * 
	 */
	for( i=1; i<hmc->xbar_depth; i++ )
	{
		/* 
		 * if the slot is valid, look upstream in the queue
		 *
		 */
		if( hmc->devs[dev].xbar[link].xbar_rqst[i].valid == 1 ){

			/*
			 * find the lowest appropriate slot
			 *
			 */
			slot = i;
			for( j=(i-1); j>=0; j-- ){
				if( hmc->devs[dev].xbar[link].xbar_rqst[j].valid == 0 ){
					slot = j;
				}
			}

			/* 
		 	 * check to see if a new slot was found
			 * if so, perform the swap 
			 *
			 */
			if( slot != i ){

				/* 
				 * perform the swap 
				 *
				 */
				for( j=0; j<HMC_MAX_UQ_PACKET; j++ ){ 

					hmc->devs[dev].xbar[link].xbar_rqst[slot].packet[j] = 
						hmc->devs[dev].xbar[link].xbar_rqst[i].packet[j];	

					hmc->devs[dev].xbar[link].xbar_rqst[i].packet[j] =0x00ll;	
					
				}

				hmc->devs[dev].xbar[link].xbar_rqst[slot].valid = 1;	
				hmc->devs[dev].xbar[link].xbar_rqst[i].valid    = 0;	
			}
		} /* else, slot not valid.. move along */
	}

	return 0;
}

/* ----------------------------------------------------- HMCSIM_CLOCK_REORG_XBAR_RSP */
/* 
 * HMCSIM_CLOCK_REORG_XBAR_RSP 
 * 
 */
static int hmcsim_clock_reorg_xbar_rsp( struct hmcsim_t *hmc, uint32_t dev, uint32_t link )
{
	/* vars */
	uint32_t i	= 0;
	uint32_t j	= 0;
	uint32_t slot   = 0;
	/* ---- */

	/* 
	 * walk the response queue starting at slot 1 
	 * 
	 */
	for( i=1; i<hmc->xbar_depth; i++ )
	{
		/* 
		 * if the slot is valid, look upstream in the queue
		 *
		 */
		if( hmc->devs[dev].xbar[link].xbar_rsp[i].valid == 1 ){

			/*
			 * find the lowest appropriate slot
			 *
			 */
			slot = i;
			for( j=(i-1); j>=0; j-- ){
				if( hmc->devs[dev].xbar[link].xbar_rsp[j].valid == 0 ){
					slot = j;
				}
			}

			/* 
		 	 * check to see if a new slot was found
			 * if so, perform the swap 
			 *
			 */
			if( slot != i ){

				/* 
				 * perform the swap 
				 *
				 */
				for( j=0; j<HMC_MAX_UQ_PACKET; j++ ){ 

					hmc->devs[dev].xbar[link].xbar_rsp[slot].packet[j] = 
						hmc->devs[dev].xbar[link].xbar_rsp[i].packet[j];	

					hmc->devs[dev].xbar[link].xbar_rsp[i].packet[j] =0x00ll;	
					
				}

				hmc->devs[dev].xbar[link].xbar_rsp[slot].valid = 1;	
				hmc->devs[dev].xbar[link].xbar_rsp[i].valid    = 0;	
			}
		} /* else, slot not valid.. move along */
	}

	return 0;
}

/* ----------------------------------------------------- HMCSIM_CLOCK_REORG_VAULT_RQST */
/* 
 * HMCSIM_CLOCK_REORG_VAULT_RQST
 * 
 */
static int hmcsim_clock_reorg_vault_rqst( 	struct hmcsim_t *hmc, 
						uint32_t dev, 
						uint32_t quad, 
						uint32_t vault )
{
	/* vars */
	uint32_t i	= 0;
	uint32_t j	= 0;
	uint32_t slot   = 0;
	/* ---- */

	/* 
	 * walk the request queue starting at slot 1 
	 * 
	 */
	for( i=1; i<hmc->queue_depth; i++ )
	{
		/* 
		 * if the slot is valid, look upstream in the queue
		 *
		 */
		if( hmc->devs[dev].quads[quad].vaults[vault].rqst_queue[i].valid == 1 ){

			/*
			 * find the lowest appropriate slot
			 *
			 */
			slot = i;
			for( j=(i-1); j>=0; j-- ){
				if( hmc->devs[dev].quads[quad].vaults[vault].rqst_queue[j].valid == 0 ){
					slot = j;
				}
			}

			/* 
		 	 * check to see if a new slot was found
			 * if so, perform the swap 
			 *
			 */
			if( slot != i ){

				/* 
				 * perform the swap 
				 *
				 */
				for( j=0; j<HMC_MAX_UQ_PACKET; j++ ){ 

					hmc->devs[dev].quads[quad].vaults[vault].rqst_queue[slot].packet[j] = 
						hmc->devs[dev].quads[quad].vaults[vault].rqst_queue[i].packet[j];	

					hmc->devs[dev].quads[quad].vaults[vault].rqst_queue[i].packet[j] =0x00ll;	
					
				}

				hmc->devs[dev].quads[quad].vaults[vault].rqst_queue[slot].valid = 1;	
				hmc->devs[dev].quads[quad].vaults[vault].rqst_queue[i].valid    = 0;	
			}
		} /* else, slot not valid.. move along */
	}

	return 0;
}

/* ----------------------------------------------------- HMCSIM_CLOCK_REORG_VAULT_RSP */
/* 
 * HMCSIM_CLOCK_REORG_VAULT_RSP
 * 
 */
static int hmcsim_clock_reorg_vault_rsp( 	struct hmcsim_t *hmc, 
						uint32_t dev, 
						uint32_t quad, 
						uint32_t vault )
{
	/* vars */
	uint32_t i	= 0;
	uint32_t j	= 0;
	uint32_t slot   = 0;
	/* ---- */

	/* 
	 * walk the response queue starting at slot 1 
	 * 
	 */
	for( i=1; i<hmc->queue_depth; i++ )
	{
		/* 
		 * if the slot is valid, look upstream in the queue
		 *
		 */
		if( hmc->devs[dev].quads[quad].vaults[vault].rsp_queue[i].valid == 1 ){

			/*
			 * find the lowest appropriate slot
			 *
			 */
			slot = i;
			for( j=(i-1); j>=0; j-- ){
				if( hmc->devs[dev].quads[quad].vaults[vault].rsp_queue[j].valid == 0 ){
					slot = j;
				}
			}

			/* 
		 	 * check to see if a new slot was found
			 * if so, perform the swap 
			 *
			 */
			if( slot != i ){

				/* 
				 * perform the swap 
				 *
				 */
				for( j=0; j<HMC_MAX_UQ_PACKET; j++ ){ 

					hmc->devs[dev].quads[quad].vaults[vault].rsp_queue[slot].packet[j] = 
						hmc->devs[dev].quads[quad].vaults[vault].rsp_queue[i].packet[j];	

					hmc->devs[dev].quads[quad].vaults[vault].rsp_queue[i].packet[j] =0x00ll;	
					
				}

				hmc->devs[dev].quads[quad].vaults[vault].rsp_queue[slot].valid = 1;	
				hmc->devs[dev].quads[quad].vaults[vault].rsp_queue[i].valid    = 0;	
			}
		} /* else, slot not valid.. move along */
	}

	return 0;
}

/* ----------------------------------------------------- HMCSIM_CLOCK_QUEUE_REORG */
/* 
 * HMCSIM_CLOCK_QUEUE_REORG
 * 
 */
static int hmcsim_clock_queue_reorg( struct hmcsim_t *hmc )
{
	/* vars */
	uint32_t i	= 0;
	uint32_t j	= 0;
	uint32_t k	= 0;
	/* ---- */

	/* 
	 * crossbar queues 
	 * 
	 */
	for( i=0; i<hmc->num_devs; i++ )
	{
		for( j=0; j<hmc->num_links; j++ )
		{
			/* 
			 * reorder:
			 * hmc->devs[i].xbar[j].xbar_rqst;
			 * hmc->devs[i].xbar[j].xbar_rsp;
			 * 
			 */
			hmcsim_clock_reorg_xbar_rqst( hmc, i, j );
			hmcsim_clock_reorg_xbar_rsp( hmc, i, j );
		}
	}

	/* 
	 * vault queues
	 * 
	 */
	for( i=0; i<hmc->num_devs; i++ )
	{
		for( j=0; j<hmc->num_quads; j++ )
		{
			for( k=0; k<hmc->num_vaults; k++ )
			{
				/* 
				 * reorder: 
				 * hmc->devs[i].quads[j].vaults[k].rqst_queue;
				 * hmc->devs[i].quads[j].vaults[k].rsp_queue;
				 * 
			 	 */
				hmcsim_clock_reorg_vault_rqst( hmc, i, j, k );
				hmcsim_clock_reorg_vault_rsp( hmc, i, j, k );
			}
		}
	}

	return 0;
}

/* ----------------------------------------------------- HMCSIM_CLOCK */
/* 
 * HMCSIM_CLOCK
 * 
 */
extern int	hmcsim_clock( struct hmcsim_t *hmc )
{
	/* 
	 * sanity check 
	 * 
 	 */
	if( hmc == NULL ){ 
		return -1;
	}

	/* 
	 * Overview of the clock handler structure 
	 * 
	 * Stage 1: Walk all the child devices and drain
	 * 	    their xbars
	 * 
	 * Stage 2: Start with the root device(s) and drain
	 * 	    the xbar of any messages
	 * 
	 * Stage 3: Walk each device's vault queues and
	 *          look for bank conflicts
	 * 
	 * Stage 4: Walk each device's vault queues and 
	 * 	    perform the respective operations
	 * 
	 * Stage 5: Register any necessary responses with
	 * 	    the xbar
	 * 
	 * Stage 6: Update the internal clock value
	 * 
	 */

	/* 
	 * Stage 1: Drain the child devices
	 * 
	 */
	if( hmcsim_clock_child_xbar( hmc ) != 0 ){
		return -1;
	}

	/* 
	 * Stage 2: Drain the root devices
	 * 
	 */
	if( hmcsim_clock_root_xbar( hmc ) != 0 ){
		return -1;
	}

	/* 
	 * Stage 3: Walk the vault queues and perform
	 *          any integrated analysis
	 * 
	 */
	if( hmcsim_clock_analysis_phase( hmc ) != 0 ){
		return -1;
	}

	/* 
	 * Stage 4: Walk the vault queues and perform
	 *          read and write operations
	 * 
	 */
	if( hmcsim_clock_rw_ops( hmc ) != 0 ){
		return -1;
	}

	/* 
	 * Stage 5: Register any responses 
	 *          with the crossbar
	 * 
	 */
	if( hmcsim_clock_reg_responses( hmc ) != 0 ){ 
		return -1;
	}

	/* 
	 * Stage 5a: Reorder all the request queues
	 * 
	 */
	if( hmcsim_clock_queue_reorg( hmc ) != 0 ){
		return -1;
	}

	/* 
	 * Stage 6: update the clock value
	 * 
	 */
	hmc->clk++;

	return 0;
}

/* EOF */
