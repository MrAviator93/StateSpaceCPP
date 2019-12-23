/***********************************************************************
FILE LAUNCHER.CPP CONTAINS SIMPLE MODEL OF STATE SPACE

FILE UTMOST REVIEW DONE ON (23.12.2019) BY ARTUR K. 
***********************************************************************/

#include "pch.h"
#include <iostream>
#include <fstream>

#include "UHMath.h"

using namespace UH;

int main()
{
    std::cout << "Welcome!\n"; 

	//State space model
	Matrix2x2 A(0, 1, -3, -2);
	ColumnVec2 B(0, 1);

	//Initial conditions
	ColumnVec2 X0(0, 0);

	//u is desired condition for 2 by 2 A matrix,
	//we have only a single controllable variable.
	double u = 1; 

	double initialTime = 0.0;                       
	double dt = 0.01; //Step size
	double simulationTimeS = 160.0; //Simulation time in seconds
	int n = round((simulationTimeS - initialTime) / dt); //Number of iterations

	ColumnVec2* X = new ColumnVec2[n];
	memset(X, 0, sizeof(ColumnVec2));

	//Set initial value
	X[0] = X0;

	for (auto i = 1; i < n; i++)
	{
		X[i] = X[i - 1] + (A * X[i - 1] + B * u) * dt;
	}

	std::ofstream outFile;
	outFile.open("outputs.txt");
	outFile << "Time(s) Column1 Column2";
	for (auto i = 0; i < n; i++)
	{
		outFile << "\n" << i * dt << " " << X[i][0] << " " << X[i][1];
	}
	outFile.close();

	//Clean-up after ourselves
	delete[] X;

	std::cout << "Done, see output.txt file.\n";
	std::cin.get();
}


