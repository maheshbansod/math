#include <iostream>
#include "EquationSystem.hpp"

using namespace std;

int main() {
	double **dat;
	dat = new double*[3];
	
	for(int i=0;i<3;i++) {
		dat[i] = new double[3];
		for(int j=0;j<3;j++) {
			dat[i][j]=i+j;
		}
	}
	
	Matrix<double> m(dat, 3,3);
	double dat2[] = {1,1,1, 6,1,2, 10,2,1};
	Matrix<double> a(dat2, 3,3);
	//Matrix<double> a(m);


	cout << "Matrix A:\n"<< m << endl;
	cout << "Matrix B:\n"<< a << endl;

	cout << "Enter the matrix A(row, col, then elements. Everything seperated by space)\n";
	cin >> m;

	/*Matrix<double> l(3,3), u(3,3);

	LUDecompose(m,l,u);
	cout << "LU Decomposition of m:\nL:\n"<<l<<endl<<"U:\n"<<u<<endl;*/
	
	cout << "A+B=\n"<<(m+a).to_string() << endl;
	cout << "A-B=\n"<<(m-a).to_string() << endl;
	cout << "A*B=\n"<<(m*a).to_string() << endl;
	cout << "det(A)="<<m.determinant()<<"\ndet(B)="<<a.determinant()<<endl;

	//cout << "is A identity? " << m.isIdentity() << endl;
	//cout << "is A symmetric? " << m.isSymmetric() << endl;

	return 0;
}
