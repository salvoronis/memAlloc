CC = gcc
SRC = src/test.c src/alloc.c src/mem_debug.c
OUT = test

all: build
	$(CC) -o build/$(OUT) $(SRC)

build:
	mkdir $@

clean:
	rm -rf build
