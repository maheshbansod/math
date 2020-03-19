#include <iostream>
#include "EquationSystem.hpp"

using namespace std;

int main() {
	
	Matrix<double> m;
	double dat2[] = {1,1,1, 6,1,2, 10,2,1};
	Matrix<double> a(dat2, 3,3); //constructor init

	cout << "Matrix B:\n"<< a << endl;

	cout << "Enter the matrix A(nrow, ncol, then elements. Everything seperated by space)\n";
	cin >> m; //init through user input
	
	cout << "A+B=\n"<<(m+a).to_string() << endl;
	cout << "A-B=\n"<<(m-a).to_string() << endl;
	cout << "A*B=\n"<<(m*a).to_string() << endl;
	cout << "det(A)="<<m.determinant()<<"\ndet(B)="<<a.determinant()<<endl;

	cout << "is A identity? " << std::boolalpha << m.isIdentity() << endl;
	cout << "is A symmetric? " << m.isSymmetric() << endl;

	return 0;
}
