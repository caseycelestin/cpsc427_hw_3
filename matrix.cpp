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
	Matrix<T>::slice::slice(bool t, int s, int stp,Matrix<T> *m) : matrix(m)
	{
		type = t;
		start = s;
		stop = stp;
	}

	// returns referece to element at index of slice
	template<typename T>
	T& Matrix<T>::slice::operator[](int i) const
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

	// iterator to beginning of slice
	template<typename T>
	typename Matrix<T>::iterator Matrix<T>::slice::begin() 
	{
		Matrix<T>::iterator i{this, 0}; 
		return i;
	}

	// iterator to beginning of slice
	template<typename T>
	typename Matrix<T>::iterator Matrix<T>::slice::begin() const
	{
		Matrix<T>::iterator i{this, 0}; 
		return i;
	}

	// iterator to end of slice
	template<typename T>
	typename Matrix<T>::iterator Matrix<T>::slice::end() 
	{
		Matrix<T>::iterator i{this, stop};
		return i;
	}

	// iterator to end of slice
	template<typename T>
	typename Matrix<T>::iterator Matrix<T>::slice::end() const
	{
		Matrix<T>::iterator i{this, stop};
		return i;
	}

	// copy constructor
	template<typename T>
	Matrix<T>::slice::slice(const slice& other)
	{
		start = other.start;
		type = other.type;
		matrix = other.matrix;	
	}

	template<typename T>
	bool Matrix<T>::slice::operator==(const slice& rhs) const
	{
		if(matrix == rhs.matrix && start == rhs.start)
			return true;
		else
			return false;
	}


	// row slice constructor
	template<typename T>
	typename Matrix<T>::slice Matrix<T>::operator[](int row) 
	{
		Matrix<T>::slice s{0, row, col, this};
		return s;
	}


	// col slice creator
	template<typename T>
	typename Matrix<T>::slice Matrix<T>::column(int col) 
	{
		Matrix<T>::slice s{1, col, row, this};
		return s;
	}

	
	/** const_slice implementation ********************************/

	// const_slice constructor
	template<typename T>
	Matrix<T>::const_slice::const_slice(bool t, int s, int stp, const Matrix<T> *m) : matrix(m)
	{
		type = t;
		start = s;
		stop = stp;
	}

	// returns referece to element at index of const_slice
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

	// const_iterator to beginning of const_slice
	template<typename T>
	typename Matrix<T>::const_iterator Matrix<T>::const_slice::begin() const
	{
		Matrix<T>::const_iterator i{this, 0}; 
		return i;
	}

	// const_iterator to end of const_slice
	template<typename T>
	typename Matrix<T>::const_iterator Matrix<T>::const_slice::end() const
	{
		Matrix<T>::const_iterator i{this, stop};
		return i;
	}
	// copy constructor
	template <typename T>
	Matrix<T>::const_slice::const_slice(const const_slice& other)
	{
		start = other.start;
		type = other.type;
		matrix = other.matrix;
	}

	// const_slice comparator
	template<typename T>
	bool Matrix<T>::const_slice::operator==(const const_slice& rhs) const
	{
		if(matrix == rhs.matrix && start == rhs.start)
			return true;
		else
			return false;
	}

	// const row creator
	template<typename T>
	typename Matrix<T>::const_slice Matrix<T>::operator[](int row) const
	{
		Matrix<T>::const_slice s{0, row, col, this};
		return s;
	}

	// const col creator
	template<typename T>
	typename Matrix<T>::const_slice Matrix<T>::column(int col) const
	{
		Matrix<T>::const_slice s{1, col, row, this};
		return s;
	}

	/** iterator implementation ***********************************/
	
	// constructor
	template <typename T>
	Matrix<T>::iterator::iterator(const Matrix<T>::slice *s, int i):slice(s)
	{
		index = i;
	}

	// returns element iterator is at
	template <typename T>
	T& Matrix<T>::iterator::operator*()
	{
		return (*slice)[index];
	}
	
	// advance iterator
	template <typename T>
	typename Matrix<T>::iterator& Matrix<T>::iterator::operator++()
	{
		index++;
		return *this;
	}

	// equality comparator
	template <typename T>
	bool Matrix<T>::iterator::operator==(const iterator& rhs) const
	{
		if(index == rhs.index && *slice == *rhs.slice)
			return true;
		else 
			return false;	
	}

	// inequality comparator
	template <typename T>
	bool Matrix<T>::iterator::operator!=(const iterator& rhs) const
	{
		if(*this == rhs)
			return false;
		else
			return true;
	}


	/** const_iterator implementation ***********************************/
	
	// constructor
	template <typename T>
	Matrix<T>::const_iterator::const_iterator(const Matrix<T>::const_slice *s, int i):const_slice(s)
	{	
		index = i;
	}

	// returns element const_iterator is at
	template <typename T>
	T& Matrix<T>::const_iterator::operator*() const
	{
		return (*const_slice)[index];
	}
	
	// advance const_iterator
	template <typename T>
	typename Matrix<T>::const_iterator& Matrix<T>::const_iterator::operator++() 
	{
		index++;
		return *this;
	}

	// equality comparator
	template <typename T>
	bool Matrix<T>::const_iterator::operator==(const const_iterator& rhs) const
	{
		if(index == rhs.index && *const_slice == *rhs.const_slice)
			return true;
		else 
			return false;	
	}

	// inequality comparator
	template <typename T>
	bool Matrix<T>::const_iterator::operator!=(const const_iterator& rhs) const
	{
		if(*this == rhs)
			return false;
		else
			return true;
	}

	/** helper functions ******************************************/

	template<typename T>
	void Matrix<T>::toPrint()
	{
		std::cout << row << "x" << col << std::endl;
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



