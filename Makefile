BUILDDIR := build
TARGET := bin/runner


test: bin/test

bin/test: build/010-TestCase.o
	@g++ -std=c++11 -Wall build/010-TestCase.o -o test

build/010-TestCase.o: src/010-TestCase.cpp include/catch.hpp
	@g++ -c -std=c++11 -Wall src/010-TestCase.cpp -o build/010-TestCase.o

clean :
	rm -f *.o 
	
.PHONY : clean