#include <stdexcept>

#include "matrix.hpp"

namespace cs427527
{
	/** Matrix implementation *************************************/

	// Creates a matrix of size h by w
	template<typename T>
	Matrix<T>::Matrix(int h, int w):row(h), col(w)
	{
		// Creates space for rows, which are pointers to array of data
		row_col = (T**)(::operator new(row * sizeof(T*)));

		for (int i=0; i < row; i++)
		{
			// Creates space for coulums, which are pointers to data
			row_col[i] = (T*)(::operator new(col * sizeof(T)));

			for (int j=0; j < col; j++)
			{
				row_col[i][j] = (T)NULL;
			}
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

	// move constructor
	template <typename T>
	Matrix<T>::Matrix(Matrix&& other) : row(other.row), col(other.col)
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
	T& Matrix<T>::at(int r, int c) const
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

	
	/** slice implementation **************************************/

	// slice constructor
	template<typename T>
	Matrix<T>::slice::slice(bool t, int s, Matrix<T> *m) : matrix(m)
	{
		type = t;
		start = s;
		// matrix = m;
	}

	// returns referece to element at index of slice
	template<typename T>
	T& Matrix<T>::slice::operator[](int i) 
	{	
		// type == true then col
		if(type)
		{
			return (*matrix).at(i, start);
		}
		// type != true then row
		else
		{
			return (*matrix).at(start, i);
		}
	}

	// copy constructor
	template<typename T>
	Matrix<T>::slice::slice(const slice& other)
	{
		start = other.start;
		type = other.type;
		matrix = other.matrix;	
	}


	// row slice constructor
	template<typename T>
	typename Matrix<T>::slice Matrix<T>::operator[](int row) 
	{
		Matrix<T>::slice s{0, row, this};
		return s;
	}


	// col slice creator
	template<typename T>
	typename Matrix<T>::slice Matrix<T>::column(int col) 
	{
		Matrix<T>::slice s{1, col, this};
		return s;
	}

	
	/** const_slice implementation ********************************/

	// const_slice constructor
	template<typename T>
	Matrix<T>::const_slice::const_slice(bool t, int s, const Matrix<T> *m) : matrix(m)
	{
		type = t;
		start = s;
	}

	// returns referece to element at index of slice
	template<typename T>
	T& Matrix<T>::const_slice::operator[](int i) const
	{	
		// type == true then col
		if(type)
		{
			return (*matrix).at(i, start);
		}
		// type != true then row
		else
		{
			return (*matrix).at(start, i);
		}
	}

	template <typename T>
	Matrix<T>::const_slice::const_slice(const const_slice& other)
	{
		start = other.start;
		type = other.type;
		matrix = other.matrix;
	}

	// const row creator
	template<typename T>
	typename Matrix<T>::const_slice Matrix<T>::operator[](int row) const
	{
		Matrix<T>::const_slice s{0, row, this};
		return s;
	}

	// const col creator
	template<typename T>
	typename Matrix<T>::const_slice Matrix<T>::column(int col) const
	{
		Matrix<T>::const_slice s{1, col, this};
		return s;
	}


	/** helper functions ******************************************/

	template<typename T>
	void Matrix<T>::toPrint()
	{
		std::cout << row << " " << col << std::endl;
		for(int i=0; i < row; i++)
		{
			for(int j=0; j < col; j++)
			{
				std::cout << at(i,j) << " ";
			}
			std::cout << std::endl;
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



