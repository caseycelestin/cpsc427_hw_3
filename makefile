CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++17 -g -DFINAL

Unit: matrix_unit.o
	${CXX} ${CXXFLAGS} -o Unit matrix_unit.o

matrix_unit.o: matrix.hpp 

