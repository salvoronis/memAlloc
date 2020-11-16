CC = gcc
SRC = src/test.c src/alloc.c
OUT = test

all:
	$(CC) -o build/$(OUT) $(SRC)
