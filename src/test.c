#include "./alloc.h"
#include <stdio.h>
#include <stdint.h>

struct anime{
	uint32_t id, series, seasons;
};

int main(int argc, char * argv[]){
	struct anime * oregairu = _malloc(sizeof(struct anime));
	oregairu->id = 123123;
	oregairu->series = 12;
	oregairu->seasons = 3;

	printf("id - %u S - %u E- %u\n",oregairu->id, oregairu->seasons, oregairu->series);
	
	struct anime * naruto = _malloc(sizeof(struct anime));
	naruto->id = 123;
	naruto->series = 500;
	naruto->seasons = 2;

	printf("id - %u S - %u E- %u\n",naruto->id, naruto->seasons, naruto->series);

	struct anime * naruto1 = _malloc(sizeof(struct anime));
	naruto1->id = 123;
	naruto1->series = 500;
	naruto1->seasons = 2;

	printf("id - %u S - %u E- %u\n",naruto1->id, naruto1->seasons, naruto1->series);	
}
