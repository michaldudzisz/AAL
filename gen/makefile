CFLAGS = -L./yaml-cpp-master/build -lyaml-cpp -I ./yaml-cpp-master/include/ -std=c++17
OBJECTS = test-generator 
CC = g++

all: $(OBJECTS)

test-generator: test-generator.h test-generator.cpp
	$(CC) $@.cpp -o $@ $(CFLAGS)

clean:
	@rm *.o

delete-executables:
	@rm $(OBJECTS)
