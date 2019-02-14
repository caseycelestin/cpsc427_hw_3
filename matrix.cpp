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

	// Destructor for Matrix
	template<typename T>
	Matrix<T>::~Matrix()
	{
		deallocate();
	}

	template<typename T>	
	int Matrix<T>::height() const
	{
		return row;
	}


	template<typename T>	
	int Matrix<T>::width() const
	{
		return col;
	}

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
}



