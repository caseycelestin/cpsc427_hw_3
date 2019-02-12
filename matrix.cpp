#include "matrix.hpp"


namespace cs427_527
{
	template<typename T>
	Matrix<T>::Matrix(int h, int w):row(h), col(w)
	{

		row_col = (T**)(::operator new(h * sizeof(T*)));

		for (int i=0; i < w; i++)
		{
			row_col[i] = (T*)(::operator new(w * sizeof(T)));
		}
	}

	template<typename T>
	Matrix<T>::~Matrix()
	{
		deallocate();
	}


	template<typename T>
	void Matrix<T>::deallocate()
	{
		for (int i=0; i < row; i++)
		{
			for (int j=0; j < col; j++)
			{
				row_col[i][j].~T();
			}
			::operator delete(row_col[i]);
		}
		::operator delete(row_col);
	}
}



