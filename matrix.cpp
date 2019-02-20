#include <stdexcept>

#include "matrix.hpp"

namespace cs427_527
{
	template<typename T>
	Matrix<T>::Matrix(int h, int w):row(h), col(w)
	{
		// Creates space for rows, which are pointers to array of data
		row_col = (T**)(::operator new(row * sizeof(T*)));

		for (int i=0; i < row; i++)
		{
			// Creates space for coulums, which are pointers to data
			row_col[i] = (T*)(::operator new(col * sizeof(T)));
		}
	}

	// Creates a deep copy of the given matrix
	template<typename T>
	Matrix<T>::Matrix(const Matrix& other):row(other.row), col(other.col)
	{
		copy(other);
	}
	
	// copy assignment operator
	template<typename T>
	Matrix<T>& Matrix<T>::operator=(const Matrix &rhs)
	{
		// checks to see if set to itself
		if(&rhs != this)
		{
			deallocate();
			copy(rhs);
		}

		return *this;
	}

	// Moves data from one matrix to another
	template <typename T>
	Matrix<T>::Matrix(const Matrix&& other) : row(other.row), col(other.col)
	{
		move(other);	
	}

	// move assignment operator
	template<typename T>
	Matrix<T>& Matrix<T>::operator=(Matrix &&rhs)
	{
		// checks to see if set to itself
		if(&rhs != this)
		{
			// deallocates row_col
			deallocate();
			move(rhs);
		}

		return *this;

	}

	// Destructor for Matrix
	template<typename T>
	Matrix<T>::~Matrix()
	{
		deallocate();
	}

	// returns height of matrix
	template<typename T>	
	int Matrix<T>::height() const
	{
		return row;
	}

	// returns  width of matrix
	template<typename T>	
	int Matrix<T>::width() const
	{
		return col;
	}

	// returns data at a specific location in matrix
	template<typename T>
	T& Matrix<T>::at(int r, int c)
	{
		// Check to see if t and c are in range
		if( r < 0 || r > row || c < 0 || c > col)
		{
			// throws error if out of range
			throw std::out_of_range("");
		} else {
			// returns data at matrix location
			return row_col[r][c];
		}
	}
	
	// helper function to deallocate row_col data
	template<typename T>
	void Matrix<T>::deallocate()
	{
		for (int i=0; i < row; i++)
		{
			for (int j=0; j < col; j++)
			{
				// Calls destructor on given type
				row_col[i][j].~T();
			}
			// Calls destructor on column
			::operator delete(row_col[i]);
		}
		// Calls destructor on rows
		::operator delete(row_col);
	}

	// helper function to copy a matrix
	template<typename T>
	void Matrix<T>::copy(const Matrix& other)	
	{
		// Creates space for row
		row_col =  (T**)(::operator new(row * sizeof(T*)));

		for (int i=0; i < row; i++)
		{
			// Create space for col
			row_col[i] = (T*)(::operator new(col * sizeof(T)));

			for (int j=0; j < col; j++)
			{
				// Copy elements at each matrix space
				row_col[i][j] = other.row_col[i][j];
			}
		}
	}

	// helper function to move a matrix
	template<typename T>
	void Matrix<T>::move(Matrix& other)
	{
		// shallow copy
		row_col = other.row_col;

		// set pointers to NULL
		for (int i=0; i < row; i++)
		{
			row_col[i] = NULL;
		}

		row_col = NULL;
	}
}



