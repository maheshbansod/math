#include <iostream>
#include "Matrix.hpp"

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
	int dat2[] = {1,0,0, 0,1,0, 0,0,1};
	Matrix<int> a(dat2, 3,3);


	cout << "Matrix A:\n"<<m << endl;
	cout << "Matrix B:\n"<<a.to_string() << endl;

	cout << "Enter the matrix\n";
	cin >> m;
	
	/*cout << "A+B=\n"<<(m+a).to_string() << endl;
	cout << "A-B=\n"<<(m-a).to_string() << endl;
	cout << "A*B=\n"<<(m*a).to_string() << endl;
	cout << "det(A)="<<m.determinant()<<"\ndet(B)="<<a.determinant()<<endl;*/
	
	cout << "A to row echelon:\n"<<(m.rowEchelon()).to_string()<<endl;
	cout << "A again:\n"<<m.to_string()<<endl;

	return 0;
}
