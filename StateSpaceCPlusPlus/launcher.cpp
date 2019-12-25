/***********************************************************************
FILE LAUNCHER.CPP CONTAINS SIMPLE MODEL OF STATE SPACE

FILE UTMOST REVIEW DONE ON (25.12.2019) BY ARTUR K. 
***********************************************************************/

#include "pch.h"
#include <iostream>
#include <fstream>

#include "UHMath.h"
#include "Timer/CTimer.h"

using namespace UH;

// ****** TODO: Consider implementing ss(...) method.
//double ss(const Matrix2x2& A, const ColumnVec2& B, const RowVec2& C, const double simulationTimeS, const double dt = 0.01);

int main()
{
    std::cout << "Welcome!\n"; 

	CTimer timer1;

	//State space model
	Matrix2x2 A(0, 1, -3, -2);
	ColumnVec2 B(0, 1);
	RowVec2 C(1, 0);
	//D matrix doesn't exist in this example D = 0;

	//Initial conditions
	ColumnVec2 X0(0, 0);

	//u is desired condition for 2 by 2 A matrix,
	//we have only a single controllable variable.
	double u = 1; 

	double initialTime = 0.0;                       
	double dt = 0.01; //Step size
	double simulationTimeS = 160.0; //Simulation time in seconds
	int n = round((simulationTimeS - initialTime) / dt); //Number of iterations

	//Allocate arrays
	ColumnVec2* X = new ColumnVec2[n];
	double* Y = new double[n];

	//Set initial value
	X[0] = X0;

	timer1.start();

	//Simulation of the response of the system for the period of simulationTimeS.
	for (auto i = 1; i < n; i++)
	{
		X[i] = X[i - 1] + (A * X[i - 1] + B * u) * dt;
	}

	for (auto j = 0; j < n; j++)
	{
		//Y is the output
		Y[j] = C * X[j];
	}

	auto timeElapsed = timer1.getElapsedTimeUs();

	//Control law
	//Matrix2x2 Q(1,0,0,2);
	//double R = 1;
	//auto K = lqr(A,B,Q,R);
	// ****** TODO: Implement lqr method.

	//Closed loop system then look like this
	//ss((A-B*K),B,C,D);

	std::ofstream outFile;
	outFile.open("outputs.txt");
	outFile << "Time(s) Column1 Column2 Y";
	for (auto i = 0; i < n; i++)
	{
		outFile << "\n" << i * dt << " " << X[i][0] << " " << X[i][1] << " " << Y[i];
	}
	outFile.close();

	//Clean-up after ourselves
	delete[] X;
	delete[] Y;

	std::cout << "Done, see output.txt file.\n";
	std::cout << "Time elapsed: " << timeElapsed << "us\n";
	std::cin.get();
}
