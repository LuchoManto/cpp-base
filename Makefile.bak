BUILDDIR := build
TARGET := bin/runner
TEST := bin/test
CFLAGS := -std=c++11 -Wall
CXX := g++
COO := $(CXX) -c
BIN := bin
DEPS := include/catch.hpp
OBJS := build/010-TestCase.o



test: $(BIN)/test
	@./$(BIN)/test

$(BIN)/test: build/010-TestCase.o
	@#mkdir $(BIN)
	@$(CXX) $(CFLAGS) build/010-TestCase.o -o $(BIN)/test


build/%.o: src/%.cpp $(DEPS)
	@$(COO) -o $@ $< $(CFLAGS)


clean :
	@rm -f build/*
	
.PHONY : clean

