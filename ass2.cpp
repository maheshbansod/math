#include <iostream>
#include "EquationSystem.hpp"

using namespace std;

int main() {
	double coeffs[] = {3, -2, 1,  1, -3, 2,  -1, 2, 4};
	double consts[] = {2, 1, 15};
	Matrix<double> a(coeffs, 3,3);
	Matrix<double> b(consts,3, 1);

	a.swapRow(0,1);
	b.swapRow(0,1);

	cout << "Coefficient matrix:\n";
	cout << a;
	cout << "Constant matrix:\n";
	cout << b;

	cout << "Checking if coeffecient matrix is diagonally dominant...";
	if(a.isDiagonallyDominant())
		cout << "yes\n";
	else {
		cout << "no\nAttempting to make it diagonally dominant...\n";
		a.makeDiagonallyDominant(false, &b);
		cout << a;
	}
	EquationSystem<double> eq(a,b);
	cout << "Given system of equations: \n";
	cout << eq;
	
	cout << "Performing gaussian elimination...\n";
	eq.gaussianElimination();
    cout << eq;
    cout << "Attempting to back substitute...\n";
    eq.backSubstitution(true);
	cout << eq;
	return 0;
}
