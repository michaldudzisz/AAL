CC=g++
CFLAGS=-I.
DEPS = algo.h
OBJ = algo.o main.o


main: main.cpp algo.cpp
	g++ algo.cpp main.cpp




