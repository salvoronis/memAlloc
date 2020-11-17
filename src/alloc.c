#include "./alloc.h"
#include <stddef.h>
#include <sys/mman.h>
#include <stdio.h>

static void * find_free_mem(size_t query);
static void align_mem(void);
static void * find_last(void);

static void * start;

void *heap_init(size_t initial_size){
	void * mem_pointer = mmap(HEAP_START,
		initial_size/* + sizeof(struct mem)*/,
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
	if ((pointer = (struct mem *)find_free_mem(query + sizeof(struct mem))) != NULL) {
		new_end = (struct mem*)pointer + sizeof(struct mem) + query;
		new_end->capacity = pointer->capacity - query - sizeof(struct mem);
		new_end->is_free = 1;
		new_end->next = NULL;

		pointer->is_free = 0;
		pointer->next = new_end;
		pointer->capacity = query;
	
		return pointer + sizeof(struct mem);
	}
	if (start) {
		struct mem * tmp = find_last();

		pointer = heap_init(query+sizeof(struct mem) > CHUNK ? query+sizeof(struct mem) : CHUNK);
		tmp->next = pointer;

		pointer->is_free = 0;
		pointer->next = NULL;
		pointer->capacity = query;
		return pointer + sizeof(struct mem);
	}
	pointer = heap_init(query+sizeof(struct mem) > CHUNK ? query+sizeof(struct mem) : CHUNK);
	pointer->is_free = 0;
	return pointer + sizeof(struct mem);
}


void _free(void * memory){
	struct mem * delete = (struct mem *)memory;
	delete->is_free = 1;
	align_mem();
}


void align_mem(){
	struct mem * head = (struct mem *) start;
	while (head->next != NULL) {
		if (head->is_free && head->next->is_free && head+head->capacity+sizeof(struct mem) == head->next) {
			head->capacity = head->capacity + sizeof(struct mem) + head->next->capacity;
			head->next = head->next->next;
		}
		head = head->next;
	}
}


void * find_last(){
	struct mem * head = (struct mem *)start;
	while (head->next) {
		head = head->next;
	}
	return head;
}


void * find_free_mem(size_t query){
	struct mem * head = (struct mem *)start;
	while (head){
		if (head->is_free && head->capacity >= query) {
			return head;
		}
		head = head->next;
	}
	
	return NULL;
}
