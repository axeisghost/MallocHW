#include "my_malloc.h"

/* You *MUST* use this macro when calling my_sbrk to allocate the 
 * appropriate size. Failure to do so may result in an incorrect
 * grading!
 */
#define SBRK_SIZE 2048

/* If you want to use debugging printouts, it is HIGHLY recommended
 * to use this macro or something similar. If you produce output from
 * your code then you will receive a 20 point deduction. You have been
 * warned.
 */
#ifdef DEBUG
#define DEBUG_PRINT(x) printf(x)
#else
#define DEBUG_PRINT(x)
#endif


/* make sure this always points to the beginning of your current
 * heap space! if it does not, then the grader will not be able
 * to run correctly and you will receive 0 credit. remember that
 * only the _first_ call to my_malloc() returns the beginning of
 * the heap. sequential calls will return a pointer to the newly
 * added space!
 * Technically this should be declared static because we do not
 * want any program outside of this file to be able to access it
 * however, DO NOT CHANGE the way this variable is declared or
 * it will break the autograder.
 */
void* heap;

/* our freelist structure - this is where the current freelist of
 * blocks will be maintained. failure to maintain the list inside
 * of this structure will result in no credit, as the grader will
 * expect it to be maintained here.
 * Technically this should be declared static for the same reasons
 * as above, but DO NOT CHANGE the way this structure is declared
 * or it will break the autograder.
 */
metadata_t* freelist[8];
/**** SIZES FOR THE FREE LIST ****
 * freelist[0] -> 16
 * freelist[1] -> 32
 * freelist[2] -> 64
 * freelist[3] -> 128
 * freelist[4] -> 256
 * freelist[5] -> 512
 * freelist[6] -> 1024
 * freelist[7] -> 2048
 */


void* my_malloc(size_t size)
{
	int ii = 4;
	size += sizeof(metadata_t);
	DEBUG_PRINT("First flag\n");
	if (size > SBRK_SIZE) {
		ERRNO = SINGLE_REQUEST_TOO_LARGE;
		return NULL;
	} else {
		while (((long)size - (1 << ii)) > 0) {
			ii++;
		}
		DEBUG_PRINT("1 flag\n");
		ii -= 4;
		while ((freelist[ii] == NULL) && ii < 7) {
			ii++;
		}
		DEBUG_PRINT("2 flag\n");
		if (freelist[ii] == NULL) {
			void* temp = my_sbrk(SBRK_SIZE);
			if (temp == NULL) {
				ERRNO = OUT_OF_MEMORY;
				return NULL;
			}
			freelist[ii] = (metadata_t*) temp;
			freelist[ii]->size = SBRK_SIZE;
			freelist[ii]->in_use = 0;
			freelist[ii]->next = NULL;
			freelist[ii]->prev = NULL;
			if (heap == NULL)
				heap = temp;
		}
		DEBUG_PRINT("3 flag\n");
		ERRNO = NO_ERROR;
		return my_malloc_splitor(ii, size);
	}
  	return NULL;
}

void* my_calloc(size_t num, size_t size)
{
	size_t realsize = size * num + sizeof(metadata_t); 
	if (realsize > SBRK_SIZE) {
		ERRNO = SINGLE_REQUEST_TOO_LARGE;
		return NULL;
	} else {
		int ind;
		void* ret = my_malloc(realsize);
		realsize = realsize - sizeof(metadata_t);
		for (ind = 0; ind < (long)realsize; ind++) {
			*((char*) (((uintptr_t) ret) + (unsigned int)ind)) = 0;
		}
		return ret;
	}
}

void my_free(void* ptr)
{
	metadata_t* metaptr = (metadata_t*)((uintptr_t) ptr - sizeof(metadata_t));
	metaptr->in_use = 0;
	short calcsize = metaptr->size;
	int ii = 0;
	while (calcsize > 16) {
		calcsize = calcsize >> 1;
		ii++;
	}
	my_free_combiner(ii, metaptr);
}

void* my_memmove(void* dest, const void* src, size_t num_bytes)
{
  	char temp[num_bytes];
  	int ind;
  	for (ind = 0; ind < num_bytes; ind++) {
  		temp[ind] = ((char*)src)[ind];
  	}
  	for (ind = 0; ind < num_bytes; ind++) {
  		((char*) dest)[ind] = temp[ind];
  	}
  	return dest;
}

void* my_malloc_splitor(int ii, size_t size) 
{
	if (((unsigned short) (freelist[ii]->size) >> 1) < size) {
		//allocate
		DEBUG_PRINT("right flag\n");
		void* ret = freelist[ii];
		freelist[ii]->in_use = 1;
		freelist[ii] = freelist[ii]->next;
		if (freelist[ii] != NULL) {
			freelist[ii]->prev = NULL;
		}
		ret = (void*)((uintptr_t) ret + sizeof(metadata_t));
		DEBUG_PRINT("end flag\n");
		return ret;
	} else {
		//split
		metadata_t* newMeta = (metadata_t*)(((((uintptr_t) freelist[ii]) - (uintptr_t) heap) ^ (freelist[ii]->size >> 1)) + (uintptr_t) heap);
		metadata_t* curr = freelist[ii];
		freelist[ii] = freelist[ii]->next;
		if (freelist[ii] != NULL) {
			freelist[ii]->prev = NULL;
		}
		curr->size = curr->size >> 1;
		curr->next = newMeta;
	    newMeta->size = curr->size;
	    newMeta->in_use = 0;
	    newMeta->next = NULL;
	    newMeta->prev = curr;
	    freelist[ii - 1] = curr;
	    ii--;
	    DEBUG_PRINT("loop flag\n");
	    return my_malloc_splitor(ii, size);
	}
}

void my_free_combiner(int ii, metadata_t* metaptr) 
{
	metadata_t* buddy = (metadata_t*)(((((uintptr_t) metaptr) - (uintptr_t) heap) ^ metaptr->size) + (uintptr_t) heap);
	if (ii < 7) {
		if ((buddy->size == metaptr->size) && (buddy->in_use == 0)) {
			if (buddy->prev == NULL) {
				freelist[ii] = buddy->next;
				if (freelist[ii] != NULL)
					freelist[ii]->prev = NULL;
			} else {
				buddy->prev->next = buddy->next;
				if (buddy->next != NULL)
					buddy->next->prev = buddy->prev;
			}
			ii++;
			if ((uintptr_t)(buddy) > (uintptr_t)(metaptr)) {
				metaptr->size = metaptr->size << 1;
				my_free_combiner(ii, metaptr);
				return;
			} else {
				buddy->size = buddy->size << 1;
				my_free_combiner(ii, buddy);
				return;
			}
		}
	}
	metaptr->next = freelist[ii];
	if (freelist[ii] != NULL)
		freelist[ii]->prev = metaptr;
	metaptr->prev = NULL;
	freelist[ii] = metaptr;
}

metadata_t* givemefreelist(int ii)
{
	return freelist[ii];
}
