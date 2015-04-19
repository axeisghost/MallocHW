#include "my_malloc.h"
size_t size = 16;
void* heap;
int main() {
	metadata_t* fuck;
	// metadata_t* newMeta;
	heap = (void*)((uintptr_t)fuck - 96);
	fuck->size = 32;
	fuck->in_use = 0;
	fuck->next = NULL;
	fuck->prev = NULL;
	// printf("%lu\n", sizeof(metadata_t));
	// printf("%lu\n",(uintptr_t) heap);
	// newMeta = (metadata_t*)(((((uintptr_t) fuck) - (uintptr_t) heap) ^ (fuck->size >> 1)) + (uintptr_t) heap);
	// printf("%lu\n",(uintptr_t) fuck);
	// printf("%lu\n",(uintptr_t) newMeta);
	metadata_t* buddy = (metadata_t*)(((((uintptr_t) fuck) - (uintptr_t) heap) ^ fuck->size) + (uintptr_t) heap);
	printf("%lu\n",(uintptr_t) fuck);
	printf("%lu\n",(uintptr_t) buddy);
}