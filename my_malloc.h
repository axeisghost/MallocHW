#ifndef __MY_MALLOC_H__
#define __MY_MALLOC_H__

/* we need this *ONLY* for the size_t typedef */
#include <stdio.h>
/* we need this for uintptr_t */
#include <stdint.h>

/* our metadata structure for use with the buddy system.
 * you *MUST NOT* change this definition unless specified
 * in an official assignment update by the TAs.
 */
typedef struct metadata
{
  short in_use;
  short size;
  struct metadata* next;
  struct metadata* prev;
} metadata_t;
/* This is your error enum. You must return one of these in the
 * case that a call to your functions results in an error. The three
 * different types of errors for this homework are explained below.
 * If ANY function has a case where one of the errors described could
 * occur, it must set ERRNO to the appropriate enum.
 * In the case where a single request is too large and
 * the request results in an out of memory error as well, the
 * SINGLE_REQUEST_TOO_LARGE should take precedence. If any of the three
 * functions complete successfully, the error code should be set to
 * NO_ERROR. */
enum my_malloc_err {
	NO_ERROR,
	OUT_OF_MEMORY,
	SINGLE_REQUEST_TOO_LARGE
};
enum my_malloc_err ERRNO;

/* this function should allocate a block that is big enough to hold the
 * specified size, and that is all. if there is not a block that is able
 * to satisfy the request, then you should attempt to grab more heap
 * space with a call to my_sbrk. if this succeeds, then you should continue
 * as normal. If it fails (by returning NULL), then you should return NULL.
 */
void* my_malloc(size_t);

/* this function should free the block of memory, recursively merging
 * buddies up the freelist until they can be merged no more.
 */
void my_free(void *);

/* this function returns a pointer to an array of num quantity of elements
 * each of size size*/
void* my_calloc( size_t num, size_t size);

/* this copies memory starting at the source, src and copying num_bytes
 * of bytes into the memory pointed to by dest. The source and destination
 * can indeed overlap, so the copy should be done as if the data were put into
 * a temporary buffer first and then copied. */
void* my_memmove(void* dest, const void* src, size_t num_bytes);

/* this function will emulate the system call sbrk(2). if you do not
 * have enough free heap space to satisfy a memory request, then you
 * must call this function to allocate memory to your allocator.
 */
void* my_sbrk(int);

void* my_malloc_splitor(int, size_t);

void my_free_combiner(int, metadata_t*);

metadata_t* givemefreelist(int);

#endif /* __MY_MALLOC_H__ */
