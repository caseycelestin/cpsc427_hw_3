#ifndef __CS427527_MATRIX_HPP
#define __CS427527_MATRIX_HPP

namespace cs427_527
{
	template <typename T>
	class Matrix
	{
	public:	
		// Creates a matrisx of size h by w
		Matrix(int h, int w);
		
		// Creates a deep copy of the given matrix
		Matrix(const Matrix& other);
		
		// Move contructor for Matrix
		Matrix(const Matrix&& other);
		
		// returns height of matrix
		int height();
		// returns width of matrix
		int width();
		
		// returns reference to the element at the given location
		T& at(int r, int c)
	}
}
