#include <iostream>

#include "matrix.hpp"

using IMatrix = cs427_527::Matrix<int>;


int main(int argc, char **argv)
{
	IMatrix test{5,1};
	IMatrix copy = test;

	std::cout << test.height() << "," << test.width() << std::endl;
	
	std::cout << copy.height() << "," << copy.width() << std::endl;

}
