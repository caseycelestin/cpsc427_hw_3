#ifndef __CS427527_MATRIX_HPP
#define __CS427527_MATRIX_HPP

namespace cs427_527
{
	template <typename T>
	class Matrix
	{
	public:	
		// Creates a matris of size h by w
		Matrix(int h, int w);
		
		// Creates a deep copy of the given matrix
		Matrix(const Matrix&);
		
		// Move contructor for Matrix
		Matrix(const Matrix&& other);

		// Destructor
		~Matrix();
		
		// returns height of matrix
		int height() const;
		// returns width of matrix
		int width() const;
		
		// returns reference to the element at the given location
		T& at(int r, int c);
		
	private:
		const int row;
		const int col;

		void deallocate();
		void copy(const Matrix& other);
		
		T **row_col;	
	};
}
#include "matrix.cpp"

#endif
