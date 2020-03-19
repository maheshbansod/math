#include <string>
#include <iostream>
#include "Matrix.hpp"

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

template class Matrix<int>;
template class Matrix<double>;