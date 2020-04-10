
#include <iostream>
#include <Matrix.hpp>
#include <EquationSystem.hpp>

using namespace std;

int main() {
	Matrix<double> a;
	Matrix<double> b;

	std::string fname;
	cout << "File containing a matrix should be as follows:\n<number of rows> <number of columns>\n<elements>\n(See example matrices testmat1.matrix and testmat2.matrix)\n";
	cout << "Enter file name for coefficient matrix: ";
	cin >> fname;
	ifstream f1(fname);
	f1 >> a;
	cout << "Enter file name for matrix of constants: ";
	cin >> fname;
	ifstream f2(fname);
	f2 >> b;

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