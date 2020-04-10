#include <iostream>
#include <fstream>
#include "Matrix.hpp"

using namespace std;

int main() {
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
	cout << "is A triangular? " << m.isTriangular() << endl;

    return 0;
}