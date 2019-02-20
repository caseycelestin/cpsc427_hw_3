#ifndef __CS427527_MATRIX_HPP
#define __CS427527_MATRIX_HPP

namespace cs427527
{
	template <typename T>
	class Matrix
	{
	public:	
		// Creates a matris of size h by w
		Matrix(int h, int w);
		
		// Creates a deep copy of the given matrix
		Matrix(const Matrix&);
		
		// copy assignment operator
		Matrix& operator=(const Matrix &rhs);

		// Move contructor for Matrix
		Matrix(Matrix&& other);

		// move assignment operator
		Matrix& operator=(Matrix &&rhs);

		// Destructor
		~Matrix();
		
		// returns height of matrix
		int height() const;
		// returns width of matrix
		int width() const;
		
		// returns reference to the element at the given location
		T& at(int r, int c) const;

		// slice class
		class slice 
		{
		};

		// const_slice class
		class const_slice
		{
		};
		
		// iterator class
		class iterator
		{
		};

		// const_iterator class
		class const_iterator
		{
		};

		void toPrint();
	private:
		const int row;
		const int col;

		// helper function to deallocate row_col
		void deallocate();
		// helper function to copy
		void copy(const Matrix& other);
		// helper function to move
		void move(Matrix& other);
		

		T **row_col;	
	};
}
#include "matrix.cpp"

#endif
