#include <iostream>

#include "matrix.hpp"

using IMatrix = cs427527::Matrix<int>;


int main(int argc, char **argv)
{
	IMatrix test{2, 2};

	test.toPrint();	

}
