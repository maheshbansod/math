#include <string>
#include <iostream>
#include "Matrix.hpp"

template <class T>
Matrix<T>::Matrix() {
	mat = NULL;
	m = n = 0;
}

template <class T>
Matrix<T>::Matrix(T** dat, long int rows, long int cols) {
	/* Copies elements from dat to our mat */
	mat = new T*[rows];
	for(long int i=0; i<rows; i++) {
		mat[i] = new T[cols];
		for(long int j=0;j<cols;j++) {
			mat[i][j]=dat[i][j];
		}
	}
	m = rows; n = cols;
}

template <class T>
Matrix<T>::Matrix(long int rows, long int cols) {
	mat = new T*[rows];
	for(long int i=0;i<rows;i++) {
		mat[i]=new T[cols];
		for(long int j=0;j<cols;j++)
			mat[i][j]=0;
	}
	m = rows;n = cols;
}

template <class T>
Matrix<T>::Matrix(const T* dat, long int rows, long int cols) {
	mat = new T*[rows];
	for(long int i=0;i<rows;i++) {
		mat[i] = new T[cols];
		for(long int j=0;j<cols;j++)
			mat[i][j]=dat[i*cols+j];
	}
	m = rows;n = cols;
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& m2) {
	m = n = 0;
	this->clone(m2);
}

template <class T>
void Matrix<T>::clone(const Matrix<T>& m2) {
	if(m > 0) {
		for(long int i=0;i<m;i++)
			delete[] mat[i];
		delete[] mat;
		m = n=0;
	}
	m = m2.m;
	n = m2.n;
	mat = new T*[m];
	for(long int i=0;i<m;i++) {
		mat[i]=new T[n];
		for(long int j=0;j<n;j++)
			mat[i][j]=m2.mat[i][j];
	}
}

template <class T>
Matrix<T> Matrix<T>::operator+(Matrix<T> &m2) {
	if(m != m2.m || n != m2.n) {
		//throw Exception
		return Matrix<T>();
	}
	Matrix<T> *res=new Matrix<T>(m, n);
	for(long int i=0;i<m;i++) {
		for(long int j=0;j<n;j++) {
			res->mat[i][j] = mat[i][j]+m2.mat[i][j];
		}
	}
	return *res;
}

template <class T>
Matrix<T> Matrix<T>::operator-(Matrix<T> &m2) {
	return (-m2)+(*this);
}

template <class T>
Matrix<T> Matrix<T>::operator-() {
	return (*this)*(-1);
}

template <class T>
Matrix<T> Matrix<T>::operator*(double k) {
	Matrix<T> *res;
	res = new Matrix<T>(this->m, this->n);
	for(long int i=0;i<m;i++) {
		for(long int j=0;j<n;j++) {
			res->mat[i][j]=mat[i][j]*k;
		}
	}
	return *res;
}

template <class T>
Matrix<T> Matrix<T>::operator*(Matrix<T> &m2) {
	/**Maybe use a parallel algorithm later**/
	Matrix<T> *res;
	if(n != m2.m) {
		//throw Exception
		return Matrix<T>();
	}
	res = new Matrix<T>(m, m2.n);
	for(int i=0;i<m;i++) {
		for(int j=0;j<m2.n;j++) {
			res->mat[i][j]=0;
			for(int k=0;k<n;k++) {
				res->mat[i][j]+=mat[i][k]*m2.mat[k][j];
			}
		}
	}
	return *res;
}

template<class T>
void Matrix<T>::setAllElements(T x) {
	for(long int i=0;i<m;i++)
		for(long int j=0;j<n;j++)
			mat[i][j]=x;
}

void LUDecompose(Matrix<double> &m, Matrix<double> &l, Matrix<double> &u) {
	/**Using Doolittle method**/
	//assume l and u have appropriate size. all matrices square
	l.setAllElements(0);
	u.setAllElements(0);
	
	for(long int i=0;i<m.m;i++) {
		for(long int k=i;k<m.n;k++) {
			double sum = 0;
			for(long int j=0;j<i;j++) {
				sum += l.mat[i][j]*u.mat[j][k];
			}
			u.mat[i][k]=m.mat[i][k]-sum;
		}
		l.mat[i][i]=1;
		for(long int k=i+1;k<m.n;k++) {
			double sum;
			for(long int j=0;j<i;j++) {
				sum += l.mat[k][j]*u.mat[j][i];
			}
			l.mat[k][i]=(m.mat[k][i]-sum)/u.mat[i][i];
		}
	}
}

template <class T>
Matrix<T> Matrix<T>::rowEchelon(bool verbose) const {
	Matrix<T> *res=new Matrix<T>();
	res->clone(*this);
	res->toRowEchelon(verbose);
	return *res;
}

template <class T>
void Matrix<T>::swapRow(long int x, long int y) {
	for(long int i=0;i<n;i++) {
		T t = mat[x][i];
		mat[x][i]=mat[y][i];
		mat[y][i]=t;
	}
}

template <class T>
void Matrix<T>::toRowEchelon(bool verbose) {
	
	long int r=0;
	for(long int i=0;i<n;i++) {
		for(long int j=r;j<m;j++) {
			if(mat[j][i]!=0) {
				if(r != j) {
					swapRow(j,r);
					if(verbose) std::cout << "swapping row "<< j <<" and row "<<r<<"\n"<<to_string();
				}
				if(mat[r][i]!=1) {
					//dividing row r by first nonzero element of that row
					for(long int k=i+1;k<n;k++) {
						mat[r][k]/=mat[r][i];
					}
				
					if(verbose) std::cout << "R"<<r<<"=R"<<r<<"/"<<mat[r][i]<<std::endl;
					mat[r][i]=1;
					if(verbose) std::cout << to_string();
				}
				
				//make all elements below element at r,i 0
				for(long int k=r+1;k<m;k++) {
					if(mat[k][i]!=0) {
						for(long int l=i+1;l<n;l++) {
							mat[k][l]-=mat[k][i]*mat[r][l];
						}
						if(verbose) std::cout << "R"<<k<<"=R"<<k<<"-"<<mat[k][i]<<"*R"<<r<<std::endl;
						mat[k][i]=0;
						if(verbose) std::cout << to_string();
					}
				}
				r++;
				break;
			}
		}
	}
	
}

template <class T>
T Matrix<T>::determinant() const {
	/**Change code later for determining determinant for matrix size n **/
	if(m != n || n>3) {
		//throw Exception
		return -1;
	}
	if(n==1) return mat[0][0];
	else if(n==2) return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
	else return  mat[0][0]*(mat[1][1]*mat[2][2]-mat[1][2]*mat[2][1])
							-mat[0][1]*(mat[1][0]*mat[2][2]-mat[1][2]*mat[0][2])
							+mat[0][2]*(mat[1][0]*mat[2][1]-mat[1][1]*mat[2][0]);
}

template <class T>
T Matrix<T>::get(long int i, long int j) const {
	if(i > m || j > n) {
		//throw Exception
		return -1;
	}
	return mat[i][j];
}

template <class T>
long int Matrix<T>::getRows() const {
	return m;
}

template <class T>
long int Matrix<T>::getColumns() const {
	return n;
}

template <class T>
std::string Matrix<T>::to_string() const {
	std::string str="";
	if(n==0 || m ==0) return std::string("<empty>");

	for(int i=0;i<m;i++) {
		for(int j=0;j<n;j++) {
			str+=std::to_string(mat[i][j])+", ";
		}
		str+="\n";
	}
	return str;
}

template <class T>
void Matrix<T>::freeMemory() {
	if(m==0) return;

	for(int i=0;i<m;i++) {
		delete[] mat[i];
	}
	delete[] mat;
	mat = NULL;
	m = n = 0;
}

template <class T>
Matrix<T>::~Matrix() {
	freeMemory();
}

template class Matrix<int>;
template class Matrix<double>;
