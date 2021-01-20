CFLAGS = -L./lib -lyaml-cpp -I ./lib/include/ -std=c++17
OBJECTS = test-generator # b bruteforce 
CC = g++

all: $(OBJECTS)
	

test-generator: test-generator.cpp
	$(CC) $@.cpp -o $@ $(CFLAGS)

#bruteforce: bruteforce.cpp
#	$(CC) $@.cpp -o $@ $(CFLAGS)

#b: b.cpp
#	$(CC) $@.cpp -o $@ $(CFLAGS)

clean:
	@rm *.o

delete-executables:
	@rm $(OBJECTS)