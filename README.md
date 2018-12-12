# cpp-base
Base directory / files for a cpp project

TODO:
  - define layouts and everything, including Makefile. Example: https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/
  - Tests should run with `make test`
  - Example test is 010-TestCase.cpp, based on catch2 library
  - Catch2: https://github.com/catchorg/Catch2
  - catch.hpp probably should end in an include directory, or in the test directory
  - The exampe test now can be run with this command (this should change to `make test`):


	g++ -std=c++11 -Wall -o 010-TestCase 010-TestCase.cpp && ./010-TestCase
