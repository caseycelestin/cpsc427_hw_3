#include <iostream>

#include "matrix.hpp"

using IMatrix = cs427527::Matrix<int>;


int main(int argc, char **argv)
{
	IMatrix test{2, 2};

	test[0][0] = 25;
	test.at(1,0) = 22;
	test.toPrint();
	IMatrix::slice s = test[1];

	std::cout << test[1][0] << std::endl;
}
