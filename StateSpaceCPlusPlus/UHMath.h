/***********************************************************************
FILE UHMATH.H CONTAINS BASIC MATRIX CLASS IMPLEMENTATIONS

FILE UTMOST REVIEW DONE ON (23.12.2019) BY ARTUR K. 
***********************************************************************/

#ifndef UH_MATH_H
#define UH_MATH_H

namespace UH
{
	//-----------------------------------------------------------------------
	//TEMPLATE COLUMN VECTOR 2
	//
	//Basic Implementation of column vector 2 class.
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

	private:
		T m_values[4];
	};

	using ColumnVec2 = TColumnVec2<double>;
	using Matrix2x2 = TMatrix2x2<double>;

} //namespace UH
#endif //!UH_MATH_H
