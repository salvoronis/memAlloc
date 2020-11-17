CC = gcc
SRC = src/test.c src/alloc.c
OUT = test

all: build
	$(CC) -o build/$(OUT) $(SRC)

build:
	mkdir $@

clean:
	rm -rf build
