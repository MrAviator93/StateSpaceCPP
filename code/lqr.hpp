#ifndef UH_LQR_HPP__
#define UH_LQR_HPP__

#include "math.hpp"

// C++
#include <cmath>

namespace UH
{

ColumnVec2 lqr( const Matrix2x2& A, const ColumnVec2& B, const Matrix2x2& Q, double R )
{
	// Initialize P with Q as a starting approximation
	Matrix2x2 P = Q;
	Matrix2x2 AT = A.transpose();
	Matrix2x2 BTB = B * B.transpose() * ( 1.0 / R ); // B * (1/R) * B^T

	// Tolerance and maximum iterations for convergence
	const double tolerance = 1e-6;
	const int maxIterations = 1000;

	for( int i = 0; i < maxIterations; ++i )
	{
		// Update Riccati equation iteratively
		Matrix2x2 P_next = AT * P + P * A - ( P * BTB * P ) + Q;

		// Check for convergence
		if( ( P_next - P ).norm() < tolerance )
		{
			P = P_next;
			break;
		}
		P = P_next;
	}

	// Compute the optimal gain matrix K = R^{-1} * B^T * P
	// ColumnVec2 K = ( 1 / R ) * ( B.transpose() * P );
	TRowVec2< double > rowResult = B.transpose() * P; // Step 1: Get Row Vector result
	TRowVec2< double > scaledRowResult = rowResult * ( 1 / R ); // Step 2: Scale it
	ColumnVec2 K = scaledRowResult.transpose(); // Step 3: Convert to ColumnVec2

	return K;
}

} // namespace UH
#endif // UH_LQR_HPP__
