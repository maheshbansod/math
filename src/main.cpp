#include <iostream>
#include <fstream>
#include <cmath>

#include "Matrix.hpp"
#include "EquationSystem.hpp"
#include "NumInt.hpp"

#define real_stringify(s) #s
#define stringify(...) real_stringify(__VA_ARGS__)

#ifndef VERBOSE
#define VERBOSE false
#endif

using namespace std;

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void displayUsage(const char*);

int main(int argc, char **argv) {
    if(argc < 2) {
        displayUsage(argv[0]);
        return -1;
    }
    int tn = atoi(argv[1]);
    if(tn == 0) {
        displayUsage(argv[0]);
        return -1;
    }
    switch(tn) {
    case 1:
        test1();
        break;
    case 2:
        test2();
        break;
	case 3:
		test3();
		break;
	case 4:
		test4();
		break;
	case 5:
		test5();
		break;
	case 6:
		test6();
		break;
    default:
        displayUsage(argv[0]);
        return -1;
    }
    return 0;
}

#define FX            \
double f(double x) {  \
	double s = sin(x);\
	return s*s;       \
}
FX

void test6() {

	double a, b;
	cout << "The function f(x) is\n"<<stringify(FX)<<endl;
	cout << "Enter lower limit and upper limit\n";
	cin >> a >> b;
	double result = NumInt::trapezoidal(a,b, f );

	cout << "Result: "<<result<<endl;
}

void test5() {
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
		return;
	}
	cout <<"Matrix L:\n"<< l;
	cout <<"Matrix U:\n"<< u;
	cout <<"LxU:\n"<< l*u;
	cout << "Using crout's method.\n";
	a.luDecompose_crout(l, u);
	cout <<"Matrix L:\n"<< l;
	cout <<"Matrix U:\n"<< u;
	cout <<"LxU:\n"<< l*u;
}

void test4() {	
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
				return;
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
			return;
		}
		Matrix<double> l(a.getRows(),a.getRows());
		Matrix<double> u(a.getRows(), a.getRows());
		cout << "Performing matrix decomposition.\n";
		if(!a.luDecompose_cholesky(l, u)) {
			cout << "ERROR: couldn't perform decomposition.\nDeterminant is prolly close to 0\n";
			return;
		}
		cout << "A=LU (U = transpose(L))\nL = \n"<<l;
		cout << "U=\n"<<u;
		cout << "LxU = \n" << l*u;
	}
}

void test3() {
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
			return;
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

}

void test2() {
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
}

void test1() {
    ifstream fin1, fin2;
	std::string str;

	cout << "Enter filename for input for matrix A: ";
	cin >> str;
	fin1.open(str);
	Matrix<double> m;
	fin1 >> m;
	cout << "Enter filename for input for matrix B: ";
	cin >> str;
	fin2.open(str);
	Matrix<double> a;
	fin2 >> a;

	cout << "Matrix A:\n" << m << endl;
	cout << "Matrix B:\n" << a << endl;
	
	Matrix<double> c;
	c = m+a;
	if(c.getRows() == 0) cout << "error while performing addition.\n";
	else cout << "A+B=\n"<< c << endl;
	c = m-a;
	if(c.getRows() == 0) cout << "error while performing subtraction.\n";
	else cout << "A-B=\n"<< c << endl;
	c = m*a;
	if(c.getRows() == 0) cout << "error while performing multiplication.\n";
	else cout << "A*B=\n"<< c << endl;
	
	cout << "det(A)="<< m.determinant()<< "\ndet(B)="<<a.determinant()<<endl;

	cout << "is A identity? " << std::boolalpha << m.isIdentity() << endl;
	cout << "is A symmetric? " << m.isSymmetric() << endl;
}

void displayUsage(const char *pname) {
    cout << "Usage: "<<pname<< " testnumber"<<endl;
    cout << "\twhere test number can be\n\t\t1: addition, multiplication, subtraction, determinant, is the matrix symmetric, is the matrix identity.\n";
    cout << "\t\t2: diagonally dominant and gaussian elimination\n";
	cout << "\t\t3: gauss jacobi method\n";
	cout << "\t\t4: gauss seidel root finding method and cholesky method for matrix decomposition\n";
	cout << "\t\t5: doolittle's and crout's method for matrix decomposition\n";
}