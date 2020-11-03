CC=g++
CFLAGS=-I.
DEPS = algo.h
OBJ = algo.o main.o

main: main.o algo.o
	$(CC) -o main main.o algo.o

.PHONY: clean
clean:
	rm *.o main


