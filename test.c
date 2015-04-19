#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my_malloc.h"
typedef struct testcase {
	long a1;
	long a2;
	long a3;
	long a4;
	long a5;
	long a6;
	long a7;
	long a8;
} testcase_t;

typedef struct hugetestcase {
	testcase_t b1;
	testcase_t b2;
	testcase_t b3;
	testcase_t b4;
	testcase_t b5;
	testcase_t b6;
	testcase_t b7;
	testcase_t b8;
} hugetestcase_t;

typedef struct oversize {
	hugetestcase_t c1;
	hugetestcase_t c2;
	hugetestcase_t c3;
	hugetestcase_t c4;
} oversize_t;

typedef struct fnewheap {
	hugetestcase_t d1;
	hugetestcase_t d2;
	hugetestcase_t d3;
} fnewheap_t;

int main() {
	int ind = 0;
	// fnewheap_t* errornow = (fnewheap_t*)my_malloc(sizeof(fnewheap_t));
	testcase_t* abc = (testcase_t*)my_malloc(sizeof(testcase_t));
	testcase_t* abc1 = (testcase_t*)my_malloc(sizeof(testcase_t));
	// testcase_t* abc2 = (testcase_t*)my_malloc(sizeof(testcase_t));
	abc->a1 = 100;
	abc1->a2 = 100;
	printf("size of testcase_t: %lu\n", sizeof(testcase_t));
	printf("%lu\n", (uintptr_t) abc);
	printf("%lu\n", (uintptr_t) abc1);
	// for (ind = 0; ind < 8; ind++) {
	// 	printf("freelist[%d]: %lu\n", ind, (uintptr_t)givemefreelist(ind));
	// 	if (givemefreelist(ind) != NULL) {
	// 		printf("freelist[%d]->next: %d\n", ind, givemefreelist(ind)->next != NULL);
	// 	}
	// }
	// printf("%lu\n", (uintptr_t) abc1);
	// printf("%lu\n", (uintptr_t) abc2);
	// printf("%lu\n", (uintptr_t) errornow);
	// metadata_t* metaee = (metadata_t*)((uintptr_t) errornow - sizeof(metadata_t));
	// printf("%lu\n", (uintptr_t)metaee);
	// printf("%d\n", metaee->size);
	// fnewheap_t* errornow1 = (fnewheap_t*)my_malloc(sizeof(fnewheap_t));
	// fnewheap_t* errornow2 = (fnewheap_t*)my_malloc(sizeof(fnewheap_t));
	// fnewheap_t* errornow3 = (fnewheap_t*)my_malloc(sizeof(fnewheap_t));
	// printf("Out of memory1: %d\n", errornow1 == NULL);
	// printf("Out of memory2: %d\n", errornow2 == NULL);
	// printf("Out of memory3: %d\n", errornow3 == NULL);
	// my_free(errornow2);
	// printf("freelist[7]->size: %d\n", givemefreelist(7)->size);
	// my_free(errornow1);
	// printf("freelist[7]->next->size: %d\n", givemefreelist(7)->next->size);
	my_free(abc1);
	// for (ind = 0; ind < 8; ind++) {
	// 	printf("freelist[%d]: %lu\n", ind, (uintptr_t)givemefreelist(ind));
	// 	if (givemefreelist(ind) != NULL) {
	// 		printf("freelist[%d]->size: %d\n", ind, givemefreelist(ind)->size);
	// 	} else {
	// 		printf("freelist[%d]->size: NULL\n", ind);
	// 	}
	// }
	char* cha1 = (char*)my_malloc(sizeof(char));
	char* cha2 = (char*)my_malloc(sizeof(char));
	char* cha3 = (char*)my_malloc(sizeof(char));
	char* cha4 = (char*)my_malloc(sizeof(char));
	printf("cha1: %lu\n", (uintptr_t) cha1);
	printf("cha2: %lu\n", (uintptr_t) cha2);
	printf("cha3: %lu\n", (uintptr_t) cha3);
	printf("cha4: %lu\n", (uintptr_t) cha4);
	metadata_t* curr = givemefreelist(1);
	while (curr != NULL) {
		printf("freelist[1]: %lu->", (uintptr_t)curr);
		curr = curr->next;
	}
	// metadata_t* curr = givemefreelist(1);
	// while (curr != NULL) {
	// 	printf("freelist[1]: %lu->", (uintptr_t)curr);
	// 	curr = curr->next;
	// }
	// printf("\n");
	my_free(cha2);
	my_free(cha3);
	curr = givemefreelist(1);
	while (curr != NULL) {
		printf("freelist[1]: %lu->", (uintptr_t)curr);
		curr = curr->next;
	}
	printf("\n");
	my_free(cha1);
	my_free(cha4);
	my_free(abc);
	fnewheap_t* errornow = (fnewheap_t*)my_malloc(sizeof(fnewheap_t));
	cha1 = (char*)my_malloc(sizeof(char));
	my_free(errornow);
	my_free(cha1);
	for (ind = 0; ind < 8; ind++) {
		printf("freelist[%d]: %lu\n", ind, (uintptr_t)givemefreelist(ind));
	}
	curr = givemefreelist(7);
	while (curr != NULL) {
		printf("freelist[1]: %lu->", (uintptr_t)curr);
		curr = curr->next;
	}
	printf("\n");
	long* array1;
	array1 = (long*) my_calloc(100, sizeof(long));
	printf("array address: %lu\n", (uintptr_t)array1);
	for (ind = 0; ind < 8; ind++) {
		printf("freelist[%d]: %lu\n", ind, (uintptr_t)givemefreelist(ind));
	}
	my_free(array1);
	printf("Size of long: %lu\n", sizeof(long));
	printf("Size of int: %lu\n", sizeof(int));
	printf("Size of char: %lu\n", sizeof(char));
	int testint = 1449;
	int* movetest = &testint;
	int* destptr;
	destptr = (int*)((uintptr_t)(movetest) + 1);
	printf("src: %lu\n", (uintptr_t)movetest);
	printf("dst: %lu\n", (uintptr_t)destptr);
	my_memmove(destptr, movetest, 2);
	printf("result of my_memmove: %d\n", *movetest);
	/*
	 * Test code goes here
	 */

	return 0;
}
