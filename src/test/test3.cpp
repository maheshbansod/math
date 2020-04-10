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

	std::string fname;
    if(verbose)
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
    
    cout << "Performing GaussJacobi.\n";
    Matrix<double> solution = es.gaussJacobi(verbose);

    cout << "-----\nSolution set:\n"<<solution<<"-----\n";

    if (verbose)
        std::cout << "Set the verbose variable to false in the source code to disable detailed output.\n";

    return 0;
}