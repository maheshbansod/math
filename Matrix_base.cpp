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
void Matrix<T>::set(T x, long int i, long int j) {
	mat[i][j]=x;
}

template<class T>
void Matrix<T>::setAllElements(T x) {
	for(long int i=0;i<m;i++)
		for(long int j=0;j<n;j++)
			mat[i][j]=x;
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
    //TODO: use stringstream instead
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
