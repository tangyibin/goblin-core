/* 
 * _GC64_MALLOC_C_ 
 * 
 * GC64 USER LIBRARY 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "gc64-usr.h"
#include "gc64-comp.h"


/* 
 * STATIC INT __INTERNAL_SPALLOC( STRUCT GC64SP_T *SP, __SCRATCH VOID **PTR, SIZE_T SZ )
 * 
 */
static int __internal_spalloc( 	struct gc64sp_t *sp, 
				__scratch void **ptr, 
				size_t sz ){ 

	/* vars */
	struct gc64entry_t *ent	= NULL;
	struct gc64entry_t *tmp	= NULL;
	struct gc64entry_t *nxt	= NULL;
	uint64_t newbase	= 0x00ll;
	int found		= 0;
	int done		= 0;
	/* ---- */

	ent	= malloc( sizeof( struct gc64entry_t ) );
	if( ent == NULL ){ 
		return GC64_ERROR;
	}

	/* 
	 * get the tail of the entries 
	 *
	 */
	tmp		= sp->end;	

	if( sp->nentry == 0 ){ 
		/* 
	 	 * we are the first entry 
		 *
		 */
		ent->base_addr	= sp->base_addr;
		ent->size	= sz;
		ent->next	= NULL;

		sp->start	= ent;
		sp->end		= ent;
		sp->nentry++;

		sp->used	+= sz;
		sp->free	-= sz;

	}else if( (tmp->base_addr+tmp->size+1+sz) < (sp->base_addr + sp->tsize) ){ 
		/*
	 	 * we are not the first entry, but we can tack this on the end 
		 *
		 */
		newbase		= tmp->base_addr + tmp->size + 1;	

		ent->base_addr	= newbase;
		ent->size	= sz;
		ent->next	= NULL;

		sp->end		= ent;
		sp->nentry++;
		sp->used	+= sz;
		sp->free	-= sz;

		tmp->next	= ent;
	}else{ 
		/* 
	 	 * we are not the first entry and we need to search for the space
		 *
		 */
		tmp 	= sp->start;
		nxt	= tmp->next;

		while( (found != 1) && (done != 1) ){ 

			/* 
			 * look for a slot where the 
			 * ending address of 'tmp' + sz
			 * is less than the base_address of 
			 * nxt
			 *
			 */
			newbase	= tmp->base_addr+tmp->size+1;
			if( (newbase+sz+1) <= nxt->base_addr ){ 
				/* 
			 	 * we have a valid slot 
				 *
				 */
				found = 1;
	
			}else{ 
				/*	
				 * no valid slot
				 * slide the pointers left
				 *
				 */
				if( nxt->next != NULL ){
					/* we're not at the end of the list */			
					tmp 	= tmp->next;
					nxt	= nxt->next;
				}else{ 
					done = 1;
				}
			}

		}

		if( found == 0 ){ 
			/* 
			 * memory is too fragmented
			 * return an error;
			 *
			 */
			free( ent );
			ent 	= NULL;
			*ptr	= NULL;
			return GC64_NULLPTR;	
		}

		/* 
		 * no error occurred 
		 * init the link structure and the new 
	 	 * allocation 
		 *
		 */
		newbase		= tmp->base_addr + tmp->size + 1;
		
		ent->base_addr	= newbase;
		ent->size	= sz;
		ent->next	= nxt;

		sp->end		= ent;
		sp->nentry++;
		sp->used	+= sz;
		sp->free	-= sz;

		tmp->next	= ent;
	}


	*ptr	= (__scratch void *)(ent->base_addr);

	return GC64_OK;
}

/* 
 * EXTERN INT SP_MALLOC( __SCRATCH VOID **PTR, SIZE_T SZ )
 * 
 */
extern int sp_malloc( __scratch void **ptr, size_t sz ){ 

	/* vars */
	struct gc64sp_t *sp	= NULL;
	/* ---- */

	/* sanity check */
	if( ptr == NULL ){ 
		return GC64_ERROR;
	}

	if( __g_comp == NULL ){ 
		return GC64_ERROR;
	}

	/* 
	 * grab the base structure 
	 * 
	 */
	sp = __g_comp->mem;

	/*
	 * bounds check the size of the request
	 * 
	 */
	if( sz > sp->tsize ){ 
		*ptr	= NULL;
		return GC64_NULLPTR;
	}else if( sz > sp->free ){ 
		*ptr	= NULL;
		return GC64_NULLPTR;
	}

	/* 
	 * the memory has sufficient space 
	 * call the internal function to perform the necessary update
	 * 
	 */
	return __internal_spalloc( sp, ptr, sz );
}

/* 
 * EXTERN INT SP_CALLOC( __SCRATCH VOID **PTR, SIZE_T NMEMB, SIZE_T SZ )
 * 
 */
extern int sp_calloc( __scratch void **ptr, size_t nmemb, size_t sz ){ 
	
	/* vars */
	struct gc64sp_t *sp	= NULL;
	size_t tsize		= nmemb * sz;
	/* ---- */

	/* sanity check */
	if( ptr == NULL ){ 
		return GC64_ERROR;
	}

	if( __g_comp == NULL ){ 
		return GC64_ERROR;
	}

	/* 
	 * grab the base structure 
	 * 
	 */
	sp = __g_comp->mem;

	/*
	 * bounds check the size of the request
	 * 
	 */
	if( tsize > sp->tsize ){ 
		*ptr	= NULL;
		return GC64_NULLPTR;
	}else if( tsize > sp->free ){ 
		*ptr	= NULL;
		return GC64_NULLPTR;
	}

	/* 
	 * the memory has sufficient space 
	 * call the internal function to perform the necessary update
	 * 
	 */
	return __internal_spalloc( sp, ptr, tsize );
}

/* 
 * EXTERN INT SP_REALLOC( __SCRATCH VOID **NEWPTR, __SCRATCH VOID **OLDPTR, 
 * 				SIZE_T SZ )
 * 
 */
extern int sp_realloc( __scratch void **newptr, __scratch void **oldptr, 
			size_t sz ) {
	
	return GC64_OK;
}

/* 
 * EXTERN INT SP_FREE( __SCRATCH VOID **PTR )
 * 
 */
extern int sp_free( __scratch void **ptr )
{
	return GC64_OK;
}
