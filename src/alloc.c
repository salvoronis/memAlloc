#include "./alloc.h"
#include <stddef.h>
#include <sys/mman.h>
#include <stdio.h>

static void * find_free_mem(size_t query);

static void * start;

void *heap_init(size_t initial_size){
	void * mem_pointer = mmap(HEAP_START,
		initial_size,
		PROT_READ|PROT_WRITE,
		MAP_PRIVATE|MAP_ANONYMOUS,
		-1, 0);
	//it checks do we have heap start or not
	if (!start){
		start = mem_pointer;
	}
	struct mem * head = (struct mem*) mem_pointer;
	head->next = NULL;
	head->capacity = initial_size - sizeof(struct mem);
	head->is_free = 1;
	return mem_pointer;
}

void * _malloc(size_t query){
	struct mem * pointer;;
	struct mem * new_end;
	if ((pointer = (struct mem *)find_free_mem(query + sizeof(struct mem))) == NULL) {
		return NULL;
	}
	new_end = (struct mem*)pointer + sizeof(struct mem) + query;
	new_end->capacity = pointer->capacity - query - sizeof(struct mem);
	new_end->is_free = 1;
	new_end->next = NULL;

	pointer->is_free = 0;
	pointer->next = new_end;
	pointer->capacity = query;
	
	return pointer + sizeof(struct mem);
}

void * find_free_mem(size_t query){
	struct mem * head = (struct mem *)start;
	if (!start) {
		size_t heap = query > CHUNK ? query : CHUNK;
		return heap_init(heap);
	}
	while (head){
		if (head->is_free && head->capacity >= query) {
			return head;
		}
		head = head->next;
	}
	if (!head || head->capacity < query) {
		size_t new_heap = query > CHUNK ? query : CHUNK;
		return heap_init(new_heap);
	}
	
	return NULL;
}
