CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++17 -g -DMATRIX

all: Main Unit

Main: main.o 
	${CXX} ${CXXFLAGS} -o Main main.o 

Unit: matrix_unit.o
	${CXX} ${CXXFLAGS} -o Unit matrix_unit.o

main.o: matrix.hpp
matrix_unit.o: matrix.hpp 

