CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++17 -g

Main: main.o 
	${CXX} ${CXXFLAGS} -o Main main.o 

main.o: matrix.hpp matrix.cpp

