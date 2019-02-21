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
			public:
				
				// slice constructor
				slice(bool t, int index, Matrix<T> *m);

				// returns refrence to element at index of slice
				T& operator[](int i);

				// return itererator at beginning of slice
				// iterator begin();

				// return iterator at end of slice
				// iterator end();

				// copy constructor
				slice(const slice& other);

			private:
				//  index of beginning
				int start;
				// row (false) or col (true)
				bool type;
				// Matrix of slice
				Matrix<T> *matrix;
				
		};

		// row slice contructor
		slice operator[](int row);

		// col slice constructor
		slice column(int col);



		// const_slice class
		class const_slice
		{
			public:
				
				// slice constructor
				const_slice(bool t, int index, const Matrix<T> *m);

				// returns refrence to element at index of slice
				T& operator[](int i) const;

				// return itererator at beginning of slice
				// iterator begin();

				// return iterator at end of slice
				// iterator end();

				// copy constructor
				const_slice(const const_slice& other);

			private:
				//  index of beginning
				int start;
				// row (false) or col (true)
				bool type;
				// Matrix of slice
				const Matrix<T> *matrix;
		};

		// const row getter
		const_slice operator[](int row) const;

		// const col getter
		const_slice column(int col) const;
		
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
