CC = gcc
OUT = out/test.o out/alloc.o out/mem_debug.o
OUTPUT = test
DIRS = build out

all: alloc.o mem_debug.o test.o
	$(CC) -o build/$(OUTPUT) $(OUT)

alloc.o: src/alloc.c
	$(CC) -c -o out/alloc.o src/alloc.c

mem_debug.o: src/mem_debug.c
	$(CC) -c -o out/mem_debug.o src/mem_debug.c

test.o: src/test.c
	$(CC) -c -o out/test.o src/test.c

dirs:
	mkdir $(DIRS)

clean:
	rm -rf $(DIRS)
