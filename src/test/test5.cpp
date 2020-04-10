#include <iostream>
#include <Matrix.hpp>

#ifndef VERBOSE
#define VERBOSE false
#endif

using namespace std;

int main() {
	Matrix<double> a;

    bool verbose = VERBOSE; /**make this to false to disable detailed output**/

	string fname;
    if(verbose)
	    cout << "File containing a matrix should be as follows:\n<number of rows> <number of columns>\n<elements>\n(See example matrices testmat1.matrix and testmat2.matrix)\n";
	
	cout << "Enter file name where matrix is stored: ";
	cin >> fname;
	ifstream f1(fname);
	f1 >> a;
	f1.close();
	if(verbose) {
		cout << "The given matrix:\n";
		cout << a;
		cout << "Performing LU decomposition.\n";
	}
	Matrix<double> l(a.getRows(), a.getRows());
	Matrix<double> u(a.getRows(), a.getRows());
	cout << "A = LU\n";
	cout << "Using doolittle's method.\n";
	if(!a.luDecompose_doolittle(l, u)) {
		cout << "ERROR: couldn't decompos matrix.\nDeterminant of the matrix is prolly close to 0\n";
		return -1;
	}
	cout <<"Matrix L:\n"<< l;
	cout <<"Matrix U:\n"<< u;
	cout <<"LxU:\n"<< l*u;
	cout << "Using crout's method.\n";
	a.luDecompose_crout(l, u);
	cout <<"Matrix L:\n"<< l;
	cout <<"Matrix U:\n"<< u;
	cout <<"LxU:\n"<< l*u;

    return 0;
}