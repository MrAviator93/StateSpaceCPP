/***********************************************************************
FILE LAUNCHER.CPP CONTAINS SIMPLE MODEL OF STATE SPACE

FILE UTMOST REVIEW DONE ON (26.12.2019) BY ARTUR K. 
***********************************************************************/

#include "lqr.hpp"
#include "timer.hpp"

// C++
#include <vector>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace UH;

struct SysCharacteristics
{
	double timeToMax;
	double ymax;
	double overshoot;
	double yss;
	double ess;
	std::vector<double> yArray; // or just ys ?
};

// ****** TODO: Consider implementing ss(...) method.
// SysCharacteristics ss(const Matrix2x2& A, const ColumnVec2& B, const RowVec2& C, const double simulationTimeS, const double dt = 0.01);

int main()
{
	std::cout << "Welcome!\n";

	CTimer timer1;

	// State space model
	Matrix2x2 A( 0, 1, -3, -2 );
	ColumnVec2 B( 0, 1 );
	RowVec2 C( 1, 0 );
	// D matrix doesn't exist in this example D = 0;

	// Initial conditions
	ColumnVec2 X0( 0, 0 );

	// u is desired condition for 2 by 2 A matrix,
	// we have only a single controllable variable.
	double u = 1;

	double initialTime = 0.0;
	double dt = 0.01; // Step size
	double simulationTimeS = 160.0; // Simulation time in seconds
	int n = std::round( ( simulationTimeS - initialTime ) / dt ); // Number of iterations

	// Allocate arrays
	std::vector<ColumnVec2> xArray; // X
	xArray.resize(n);

	std::vector<double> yArray; // Y
	yArray.resize(n);

	// Set initial value
	xArray[ 0 ] = X0;

	timer1.start();

	// Simulation of the response of the system for the period of simulationTimeS.
	for( auto i = 1; i < n; i++ )
	{
		xArray[ i ] = xArray[ i - 1 ] + ( A * xArray[ i - 1 ] + B * u ) * dt;
	}

	for( auto j = 0; j < n; j++ )
	{
		// Y is the output
		yArray[ j ] = C * xArray[ j ];
	}

	auto timeElapsed = timer1.elapsedTimeUs();

	// Control law
	// Matrix2x2 Q(1,0,0,2);
	// double R = 1;
	// auto K = lqr(A,B,Q,R);
	//  ****** TODO: Implement lqr method.

	// Closed loop system then look like this
	// ss((A-B*K),B,C,D);

	std::ofstream outFile;
	outFile.open( "outputs.txt" );
	outFile << "Time(s) Column1 Column2 Y";
	for( auto i = 0; i < n; i++ )
	{
		outFile << "\n" << i * dt << " " << xArray[ i ][ 0 ] << " " << xArray[ i ][ 1 ] << " " << yArray[ i ];
	}
	outFile.close();

	xArray.clear();
	yArray.clear();

	std::cout << "Done, see output.txt file.\n";
	std::cout << "Time elapsed: " << timeElapsed << "us\n";
	return 0;
}
