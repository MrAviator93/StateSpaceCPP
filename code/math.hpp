/***********************************************************************
FILE UHMATH.H CONTAINS BASIC MATRIX CLASS IMPLEMENTATIONS

FILE UTMOST REVIEW DONE ON (26.12.2019) BY ARTUR K. 
***********************************************************************/

#ifndef UH_MATH_HPP__
#define UH_MATH_HPP__

// C++
#include <cmath>
#include <array>
#include <stdexcept>

namespace UH
{

// Forward declarations
template < class T >
class TColumnVec2;
template < class T >
class TMatrix2x2;

//-----------------------------------------------------------------------
// TEMPLATE ROW VECTOR 2
//
// Basic Implementation of row vector 2 class.
//
//  _  _
// |x  y|
//   ͞   ͞
//-----------------------------------------------------------------------
template < class T >
class TRowVec2
{
public:
	constexpr TRowVec2() noexcept
		: m_values{}
	{ }

	constexpr explicit TRowVec2( T value ) noexcept { m_values.fill( value ); }

	constexpr TRowVec2( T a1, T a2 ) noexcept
		: m_values{ a1, a2 }
	{ }

	// In-place vector addition
	constexpr TRowVec2& operator+=( const TRowVec2& vec2 ) noexcept
	{
		m_values[ 0 ] += vec2.m_values[ 0 ];
		m_values[ 1 ] += vec2.m_values[ 1 ];
		return *this;
	}

	// Non-in-place vector addition
	constexpr TRowVec2 operator+( const TRowVec2& vec2 ) const noexcept { return TRowVec2( *this ) += vec2; }

	// In-place scalar multiplication
	constexpr TRowVec2& operator*=( const T& scalar ) noexcept
	{
		m_values[ 0 ] *= scalar;
		m_values[ 1 ] *= scalar;
		return *this;
	}

	// Non-in-place scalar multiplication
	constexpr TRowVec2 operator*( const T& scalar ) const noexcept { return TRowVec2( *this ) *= scalar; }

	// Dot product with a column vector
	constexpr T operator*( const TColumnVec2< T >& vec ) const noexcept
	{
		return m_values[ 0 ] * vec[ 0 ] + m_values[ 1 ] * vec[ 1 ];
	}

	// Multiply a row vector by a 2x2 matrix, returning a new row vector
	constexpr TRowVec2 operator*( const TMatrix2x2< T >& matrix ) const noexcept
	{
		return TRowVec2(
			m_values[ 0 ] * matrix[ 0 ] + m_values[ 1 ] * matrix[ 2 ], // First element of resulting row vector
			m_values[ 0 ] * matrix[ 1 ] + m_values[ 1 ] * matrix[ 3 ] // Second element of resulting row vector
		);
	}

	// Transpose to column vector
	constexpr TColumnVec2< T > transpose() const noexcept { return TColumnVec2< T >( m_values[ 0 ], m_values[ 1 ] ); }

	T& operator[]( int index )
	{
		if( index >= 0 && index <= 1 )
		{
			return m_values[ index ];
		}
		throw std::out_of_range( "Index out of bounds for TRowVec2." );
	}

	const T& operator[]( int index ) const
	{
		if( index >= 0 && index <= 1 )
		{
			return m_values[ index ];
		}
		throw std::out_of_range( "Index out of bounds for TRowVec2." );
	}

private:
	std::array< T, 2 > m_values;
};

//-----------------------------------------------------------------------
// TEMPLATE COLUMN VECTOR 2
//
// Basic Implementation of column vector 2 class.
//
//     _ _
//    |	x |
//    |	  |
//    |	y |
//      ͞  ͞
//-----------------------------------------------------------------------
template < class T >
class TColumnVec2
{
public:
	constexpr TColumnVec2() noexcept
		: m_values{}
	{ }

	constexpr explicit TColumnVec2( T value ) noexcept { m_values.fill( value ); }

	constexpr TColumnVec2( T a1, T a2 ) noexcept
		: m_values{ a1, a2 }
	{ }

	// In-place vector addition
	constexpr TColumnVec2& operator+=( const TColumnVec2& vec2 ) noexcept
	{
		m_values[ 0 ] += vec2.m_values[ 0 ];
		m_values[ 1 ] += vec2.m_values[ 1 ];
		return *this;
	}

	// Non-in-place vector addition
	constexpr TColumnVec2 operator+( const TColumnVec2& vec2 ) const noexcept { return TColumnVec2( *this ) += vec2; }

	// In-place scalar multiplication
	constexpr TColumnVec2& operator*=( const T& scalar ) noexcept
	{
		m_values[ 0 ] *= scalar;
		m_values[ 1 ] *= scalar;
		return *this;
	}

	// Non-in-place scalar multiplication
	constexpr TColumnVec2 operator*( const T& scalar ) const noexcept { return TColumnVec2( *this ) *= scalar; }

	// Dot product with another column vector
	constexpr T operator*( const TColumnVec2& vec ) const noexcept
	{
		return m_values[ 0 ] * vec.m_values[ 0 ] + m_values[ 1 ] * vec.m_values[ 1 ];
	}

	// Outer product with a row vector to produce a 2x2 matrix
	constexpr TMatrix2x2< T > operator*( const TRowVec2< T >& vec ) const noexcept
	{
		return TMatrix2x2< T >(
			m_values[ 0 ] * vec[ 0 ], m_values[ 1 ] * vec[ 0 ], m_values[ 0 ] * vec[ 1 ], m_values[ 1 ] * vec[ 1 ] );
	}

	// Transpose to row vector
	constexpr TRowVec2< T > transpose() const noexcept { return TRowVec2< T >( m_values[ 0 ], m_values[ 1 ] ); }

	T& operator[]( int index )
	{
		if( index >= 0 && index <= 1 )
		{
			return m_values[ index ];
		}
		throw std::out_of_range( "Index out of bounds for TColumnVec2." );
	}

	const T& operator[]( int index ) const
	{
		if( index >= 0 && index <= 1 )
		{
			return m_values[ index ];
		}
		throw std::out_of_range( "Index out of bounds for TColumnVec2." );
	}

private:
	std::array< T, 2 > m_values;
};

//-----------------------------------------------------------------------
// TEMPLATE MATRIX 2 BY 2
//
// Basic Implementation of 2 by 2 matrix class.
//
//     _       _
//    |a11	 a12|
//    |			|
//    |a21	 a22|
//      ͞        ͞
//-----------------------------------------------------------------------
template < class T >
class TMatrix2x2
{
public:
	constexpr TMatrix2x2() noexcept
		: m_values{ 0, 0, 0, 0 }
	{ }

	constexpr explicit TMatrix2x2( T value ) noexcept { m_values.fill( value ); }

	constexpr TMatrix2x2( T a11, T a12, T a21, T a22 ) noexcept
		: m_values{ a11, a12, a21, a22 }
	{ }

	constexpr static TMatrix2x2 identity() noexcept
	{
		TMatrix2x2 matrix;
		matrix.m_values[ 0 ] = 1.0;
		matrix.m_values[ 1 ] = 0.0;
		matrix.m_values[ 2 ] = 0.0;
		matrix.m_values[ 3 ] = 1.0;
		return matrix;
	}

	/// In-place matrix addition
	constexpr TMatrix2x2& operator+=( const TMatrix2x2& other ) noexcept
	{
		m_values[ 0 ] += other.m_values[ 0 ];
		m_values[ 1 ] += other.m_values[ 1 ];
		m_values[ 2 ] += other.m_values[ 2 ];
		m_values[ 3 ] += other.m_values[ 3 ];
		return *this;
	}

	/// Non-in-place matrix addition
	constexpr TMatrix2x2 operator+( const TMatrix2x2& other ) const noexcept { return TMatrix2x2( *this ) += other; }

	/// In-place matrix subtraction
	constexpr TMatrix2x2& operator-=( const TMatrix2x2& other ) noexcept
	{
		m_values[ 0 ] -= other.m_values[ 0 ];
		m_values[ 1 ] -= other.m_values[ 1 ];
		m_values[ 2 ] -= other.m_values[ 2 ];
		m_values[ 3 ] -= other.m_values[ 3 ];
		return *this;
	}

	/// Non-in-place matrix subtraction
	constexpr TMatrix2x2 operator-( const TMatrix2x2& other ) const noexcept { return TMatrix2x2( *this ) -= other; }

	// In-place matrix-scalar multiplication
	TMatrix2x2& operator*=( const T& scalar ) noexcept
	{
		m_values[ 0 ] *= scalar;
		m_values[ 1 ] *= scalar;
		m_values[ 2 ] *= scalar;
		m_values[ 3 ] *= scalar;
		return *this;
	}

	// Non-in-place matrix-scalar multiplication
	TMatrix2x2 operator*( const T& scalar ) const noexcept { return TMatrix2x2( *this ) *= scalar; }

	// Matrix-vector multiplication
	TColumnVec2< T > operator*( const TColumnVec2< T >& columnVec2 ) const noexcept
	{
		TColumnVec2< T > newColumnVec2;
		newColumnVec2[ 0 ] = m_values[ 0 ] * columnVec2[ 0 ] + m_values[ 1 ] * columnVec2[ 1 ];
		newColumnVec2[ 1 ] = m_values[ 2 ] * columnVec2[ 0 ] + m_values[ 3 ] * columnVec2[ 1 ];
		return newColumnVec2;
	}

	// In-place matrix-matrix multiplication
	TMatrix2x2& operator*=( const TMatrix2x2& other ) noexcept
	{
		const T a11 = m_values[ 0 ] * other.m_values[ 0 ] + m_values[ 1 ] * other.m_values[ 2 ];
		const T a12 = m_values[ 0 ] * other.m_values[ 1 ] + m_values[ 1 ] * other.m_values[ 3 ];
		const T a21 = m_values[ 2 ] * other.m_values[ 0 ] + m_values[ 3 ] * other.m_values[ 2 ];
		const T a22 = m_values[ 2 ] * other.m_values[ 1 ] + m_values[ 3 ] * other.m_values[ 3 ];

		m_values[ 0 ] = a11;
		m_values[ 1 ] = a12;
		m_values[ 2 ] = a21;
		m_values[ 3 ] = a22;

		return *this;
	}

	// Non-in-place matrix-matrix multiplication
	TMatrix2x2 operator*( const TMatrix2x2& other ) const noexcept { return TMatrix2x2( *this ) *= other; }

	// Frobenius norm of the matrix
	T norm() const noexcept
	{
		return std::sqrt( m_values[ 0 ] * m_values[ 0 ] + m_values[ 1 ] * m_values[ 1 ] +
						  m_values[ 2 ] * m_values[ 2 ] + m_values[ 3 ] * m_values[ 3 ] );
	}

	/// Returns a transposed version of the original Matrix.
	TMatrix2x2 transpose() const noexcept
	{
		return TMatrix2x2{ m_values[ 0 ], m_values[ 2 ], m_values[ 1 ], m_values[ 3 ] };
	}

	T& operator[]( int index )
	{
		if( index < 0 || index >= 4 )
		{
			throw std::out_of_range( "Index out of bounds for TMatrix2x2." );
		}
		return m_values[ index ];
	}

	const T& operator[]( int index ) const
	{
		if( index < 0 || index >= 4 )
		{
			throw std::out_of_range( "Index out of bounds for TMatrix2x2." );
		}
		return m_values[ index ];
	}

private:
	std::array< T, 4 > m_values;
};

template < class T >
constexpr TRowVec2< T > operator*( const T& scalar, const TRowVec2< T >& vec ) noexcept
{
	return TRowVec2< T >( vec[ 0 ] * scalar, vec[ 1 ] * scalar );
}

template < class T >
constexpr TRowVec2< T > operator*( const TRowVec2< T >& rowVec, const TMatrix2x2< T >& matrix ) noexcept
{
	return TRowVec2< T >( rowVec[ 0 ] * matrix[ 0 ] + rowVec[ 1 ] * matrix[ 2 ],
						  rowVec[ 0 ] * matrix[ 1 ] + rowVec[ 1 ] * matrix[ 3 ] );
}

using RowVec2 = TRowVec2< double >;
using ColumnVec2 = TColumnVec2< double >;
using Matrix2x2 = TMatrix2x2< double >;

} //namespace UH
#endif //!UH_MATH_HPP__
