#include "./alloc.h"
#include <stdio.h>
#include <stdint.h>

struct anime{
	uint32_t id, series, seasons;
};

int main(int argc, char * argv[]){
	void * test = _malloc(CHUNK * 3);
	struct anime * oregairu = _malloc(sizeof(struct anime));
	oregairu->id = 123123;
	oregairu->series = 12;
	oregairu->seasons = 3;

	struct anime * naruto = _malloc(sizeof(struct anime));
	naruto->id = 123;
	naruto->series = 500;
	naruto->seasons = 2;

	memalloc_debug_heap(stdout, HEAP_START);

	struct anime * naruto1 = _malloc(sizeof(struct anime));
	naruto1->id = 1234;
	naruto1->series = 550;
	naruto1->seasons = 5;

	_free(naruto1);
	_free(naruto);
	_free(oregairu);

	struct anime * hsdxd = _malloc(sizeof(struct anime)-1);
	hsdxd->id = 123;

	struct anime * one_peace = _malloc(6*1024);
	one_peace->id = 124124;
}
