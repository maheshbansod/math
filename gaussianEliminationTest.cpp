#include <iostream>
#include "EquationSystem.hpp"

using namespace std;

int main() {
	double dat2[] = {1,1,1, 6, 2,1,2, 10, 3,2,1, 10};
	Matrix<double> a(dat2, 3,4);
	EquationSystem<double> eq(a);
	cout << eq;
	cout << "Performing gaussian elimination...\n";
	eq.gaussianElimination();
    cout << eq;
    cout << "Attempting to back substitute...\n";
    eq.backSubstitution(true);
	cout << eq;
	return 0;
}
