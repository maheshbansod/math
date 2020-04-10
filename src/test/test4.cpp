#include <iostream>
#include <Matrix.hpp>
#include <EquationSystem.hpp>

#ifndef VERBOSE
#define VERBOSE false
#endif

using namespace std;

int main() {	
	Matrix<double> a;
	Matrix<double> b;

    bool verbose = VERBOSE; /**make this to false to disable detailed output**/

	string fname;
    if(verbose)
	    cout << "File containing a matrix should be as follows:\n<number of rows> <number of columns>\n<elements>\n(See example matrices testmat1.matrix and testmat2.matrix)\n";

	int ti;
	cout << "Enter 1 for gauss seidel method. any other number for cholesky decomposition\n";
	cin >> ti;

	if(ti == 1) {
		cout << "Enter file name for coefficient matrix: ";
		cin >> fname;
		ifstream f1(fname);
		f1 >> a;
		f1.close();
		cout << "Enter file name for matrix of constants: ";
		cin >> fname;
		ifstream f2(fname);
		f2 >> b;
		f2.close();

		cout << "Coefficient matrix:\n";
		cout << a;
		cout << "Constant matrix:\n";
		cout << b;

		if(verbose)
			cout << "Checking if coeffecient matrix is diagonally dominant...";
		if(a.isDiagonallyDominant()) {
			if(verbose)  cout << "yes\n";
		} else {
			if(verbose) cout << "no\nAttempting to make it diagonally dominant...\n";
			a.makeDiagonallyDominant(verbose, &b);
			if(!a.isDiagonallyDominant()) {
				cout << "Couldn't make the matrix diagonally dominant. Exiting\n";
				return -1;
			}
			if(verbose) cout << a;
		}

		EquationSystem<double> es(a, b);

		cout << "The given system is:\n"<<es;
		
		cout << "Performing GaussSeidel.\n";
		Matrix<double> solution = es.gaussSeidel(verbose);

		cout << "-----\nSolution set:\n"<<solution<<"-----\n";

		if (verbose) {
			std::cout << "Set the verbose variable to false in the source code to disable detailed output.\n";
		}
	} else {

		cout << "\nMatrix Decomposition\nEnter filename where matrix is stored: ";
		cin>>fname;
		ifstream f1(fname);
		f1 >> a;
		if(!a.isSymmetric()) {
			cout << "Matrix not symmetric. Can't perform cholesky decomposition\n";
			return -1;
		}
		Matrix<double> l(a.getRows(),a.getRows());
		Matrix<double> u(a.getRows(), a.getRows());
		cout << "Performing matrix decomposition.\n";
		if(!a.luDecompose_cholesky(l, u)) {
			cout << "ERROR: couldn't perform decomposition.\nDeterminant is prolly close to 0\n";
			return -1;
		}
		cout << "A=LU (U = transpose(L))\nL = \n"<<l;
		cout << "U=\n"<<u;
		cout << "LxU = \n" << l*u;
	}
    return 0;
}