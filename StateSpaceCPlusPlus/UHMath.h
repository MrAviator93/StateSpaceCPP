/***********************************************************************
FILE UHMATH.H CONTAINS BASIC MATRIX CLASS IMPLEMENTATIONS

FILE UTMOST REVIEW DONE ON (25.12.2019) BY ARTUR K. 
***********************************************************************/

#ifndef UH_MATH_H
#define UH_MATH_H

namespace UH
{
	//Forward declarations
	template<class T> class TColumnVec2;
	template<class T> class TMatrix2x2;

	//-----------------------------------------------------------------------
	//TEMPLATE ROW VECTOR 2
	//
	//Basic Implementation of row vector 2 class.
	//
	//  _  _
	// |x  y|
	//  ͞   ͞  
	//-----------------------------------------------------------------------

	template<class T>
	class TRowVec2
	{
	public:
		TRowVec2()
		{
			memset(&m_values, 0 , sizeof(T) * 2);
		}

		TRowVec2(T value)
		{
			m_values[0] = m_values[1] = value;
		}

		TRowVec2(T a1, T a2)
		{
			m_values[0] = a1;
			m_values[1] = a2;
		}

		~TRowVec2() = default;

		TRowVec2 operator= (TRowVec2 const& vec2)
		{
			m_values[0] = vec2.m_values[0];
			m_values[1] = vec2.m_values[1];
			return *this;
		}

		TRowVec2 operator+ (TRowVec2 const& vec2)
		{
			m_values[0] += vec2.m_values[0];
			m_values[1] += vec2.m_values[1];
			return *this;
		}

		TRowVec2 operator* (T const& scalar)
		{
			m_values[0] *= scalar;
			m_values[1] *= scalar;
			return *this;
		}

		T operator* (TColumnVec2<T> const& columnVector2)
		{
			T scalar = m_values[0] * columnVector2[0] + m_values[1] * columnVector2[1];
			return scalar;
		}

		//Access by copy.
		T operator[](int index) const
		{
			if (index >= 0 && index <= 1)
			{
				return m_values[index];
			}
			//if index out of range return the 0 element
			return m_values[0];
		}

		//Access by reference.
		T& operator[](int index)
		{
			if (index >= 0 && index <= 1)
			{
				return m_values[index];
			}
			//if index out of range return the 0 element
			return m_values[0];
		}

	private:
		T m_values[2];
	};

	//-----------------------------------------------------------------------
	//TEMPLATE COLUMN VECTOR 2
	//
	//Basic Implementation of column vector 2 class.
	//
	// _ _
	//|	x |
	//|	  |
	//|	y |
	// ͞  ͞
	//-----------------------------------------------------------------------

	template<class T>
	class TColumnVec2
	{
	public:
		TColumnVec2()
		{
			memset(&m_values, 0, sizeof(T) * 2);
		}

		TColumnVec2(T value)
		{
			m_values[0] = m_values[1] = value;
		}

		TColumnVec2(T a1, T a2)
		{
			m_values[0] = a1;
			m_values[1] = a2;
		}

		~TColumnVec2() = default;

		TColumnVec2 operator= (TColumnVec2 const& vec2) 
		{
			m_values[0] = vec2.m_values[0];
			m_values[1] = vec2.m_values[1];
			return *this;
		}

		TColumnVec2 operator+ (TColumnVec2 const& vec2)
		{
			m_values[0] += vec2.m_values[0];
			m_values[1] += vec2.m_values[1];
			return *this;
		}

		TColumnVec2 operator* (T const& scalar)
		{
			m_values[0] *= scalar;
			m_values[1] *= scalar;
			return *this;
		}

		TMatrix2x2<T> operator* (TRowVec2<T> const& rowVector2)
		{
			T a11 = m_values[0] * rowVector2[0];
			T a12 = m_values[1] * rowVector2[0]; 
			T a21 = m_values[0] * rowVector2[1];
			T a22 = m_values[1] * rowVector2[1];
			TMatrix2x2<T> mat2x2(a11, a12, a21, a22);		
			return mat2x2;
		}

		//Access by copy.
		T operator[](int index) const
		{
			if (index >= 0 && index <= 1)
			{
				return m_values[index];
			}
			//if index out of range return the 0 element
			return m_values[0];
		}

		//Access by reference.
		T& operator[](int index)
		{
			if (index >= 0 && index <= 1)
			{
				return m_values[index];
			}
			//if index out of range return the 0 element
			return m_values[0];
		}

	private:
		T m_values[2];
	};

	//-----------------------------------------------------------------------
	//TEMPLATE MATRIX 2 BY 2
	//
	//Basic Implementation of 2 by 2 matrix class.
	//-----------------------------------------------------------------------

	template<class T>
	class TMatrix2x2
	{
	public:
		TMatrix2x2()
		{
			memset(&m_values, 0, sizeof(T) * 4);
		}

		TMatrix2x2(T value)
		{
			m_values[0] = m_values[1] = m_values[2] = m_values[3] = value;
		}

		TMatrix2x2(T a11, T a12, T a21, T a22)
		{
			m_values[0] = a11;
			m_values[1] = a12;
			m_values[2] = a21;
			m_values[3] = a22;
		}

		~TMatrix2x2() = default;

		TColumnVec2<T> operator* (TColumnVec2<T> const& columnVec2)
		{
			TColumnVec2<T> newColumnVec2;
			newColumnVec2[0] = m_values[0] * columnVec2[0] + m_values[1] * columnVec2[1];
			newColumnVec2[1] = m_values[2] * columnVec2[0] + m_values[3] * columnVec2[1];
			return newColumnVec2;
		}

		//Access by copy.
		T operator[](int index) const
		{
			if (index >= 0 && index <= 3)
			{
				return m_values[index];
			}
			//if index out of range return the 0 element
			return m_values[0];
		}

		//Access by reference.
		T& operator[](int index)
		{
			if (index >= 0 && index <= 3)
			{
				return m_values[index];
			}
			//if index out of range return the 0 element
			return m_values[0];
		}

	private:
		T m_values[4];
	};

	using RowVec2 = TRowVec2<double>;
	using ColumnVec2 = TColumnVec2<double>;
	using Matrix2x2 = TMatrix2x2<double>;

} //namespace UH
#endif //!UH_MATH_H
