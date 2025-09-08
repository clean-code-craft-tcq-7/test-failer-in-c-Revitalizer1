CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra
CXXFLAGS = -Wall -Wextra -std=c++11

# Default target
all: c_tests cmake_tests

# Traditional C tests
c_tests: test_tshirts_c test_misaligned_c test_weatherreport_c

test_tshirts_c: src/tshirts.c test/test_tshirts.c
	$(CC) $(CFLAGS) -o $@ $^

test_misaligned_c: src/misaligned.c test/test_misaligned.c
	$(CC) $(CFLAGS) -o $@ $^

test_weatherreport_c: src/weatherreport.c test/test_weatherreport.c
	$(CC) $(CFLAGS) -o $@ $^

# Run C tests
test_c: c_tests
	./test_tshirts_c
	./test_misaligned_c
	./test_weatherreport_c

# CMake tests (GoogleTest)
build:
	cmake -S . -B build

cmake_tests: build
	cmake --build build

# Run GoogleTest tests
test_gtest: cmake_tests
	cd build && ctest --verbose

# Run all tests
test: test_c test_gtest

clean:
	rm -f test_tshirts_c test_misaligned_c test_weatherreport_c
	rm -rf build

.PHONY: all c_tests cmake_tests test_c test_gtest test clean