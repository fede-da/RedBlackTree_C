
CC=gcc
CFLAGS=-I.
DEPS = functions.h
OBJ = Red_black_tree.o functions.o

run: main
	./main

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


