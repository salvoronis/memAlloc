#ifndef ALLOC_H
#define ALLOC_H
#include <stddef.h>
#include <stdbool.h>

#define HEAP_START ((void*)0x04040000)
#define CHUNK 5*1024*1024
#pragma pack(push,1)
struct mem{
	struct mem * next;
	size_t capacity;
	bool is_free;
};
#pragma pack(pop)
void * _malloc(size_t query);
void _free(void *mem);
void *heap_init(size_t initial_size);
#endif
