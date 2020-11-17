CC = gcc
SRC = src/test.c src/alloc.c src/mem_debug.c
OUT = test

all:
	$(CC) -o build/$(OUT) $(SRC)
