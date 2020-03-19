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

template <class T>
Matrix<T> Matrix<T>::joinMatrices(const Matrix<T> &m2) const {
	Matrix<T> *res;
	if(m != m2.m)
		return Matrix<T>();
	res = new Matrix<T>(m, n+m2.n);
	for(long int i=0;i<m;i++) {
		long int j;
		for(j=0;j<n;j++) {
			res->mat[i][j]=mat[i][j];
		}
		for(long int k=0;k<m2.n;k++) {
			res->mat[i][j++] = m2.mat[i][k];
		}
	}

	return *res;
}

template <class T>
bool Matrix<T>::isIdentity() const {
    if(m != n)
        return false;
    for(long int i=0;i<m;i++)
        for(long int j=0;j<n;j++)
            if(i==j) {
                if(mat[i][i]!=1)
                    return false;
            } else if(mat[i][j]!=0)
                return false;
    return true;
}

template <class T>
bool Matrix<T>::isSymmetric() const {
    if(m != n)
        return false;
    for(long int i=1;i<m;i++)
        for(long int j=0;j<i;j++)
            if(mat[i][j] != mat[j][i])
                return false;
    return true;
}

template <class T>
bool Matrix<T>::isDiagonallyDominant() const {
	for(long int i=0;i<m;i++) {
		T sum = 0;
		for(long int j=0;j<n;j++) {
			if(i != j)
				sum+=abs(mat[i][j]);
		}
		if(sum > abs(mat[i][i]))
			return false;
	}
	return true;
}

template <class T>
int Matrix<T>::makeDiagonallyDominant(bool verbose, Matrix<T> *b) {
	/* b: matrix of constants <- to swap wlwmentswhenever there's a row swap */
	//uses naive algorithm - swaps the rows if possible
	long int mi;
	for(long int i=0;i<m;i++) {
		T max = abs(mat[i][0]);
		T sum = 0;
		mi = 0;
		for(long int j=1;j<n;j++) {
			if(max < abs(mat[i][j])) {
				sum += max;
				max = abs(mat[i][j]);
				mi = j;
			} else sum+= abs(mat[i][j]);
		}
		if(sum > max){
			if(verbose)
				std::cout << "Can't make the matrix diagonally dominant :(\n";
			return -1;
		}
		if(verbose)
			std::cout << "Suitable element on row "<<i+1<< " is "<<max<<" at position "<<mi<<std::endl;
		if(mi != i) {
			if(verbose)
				std::cout << "Swapping row "<<mi+1 << " and row "<<i+1<<"\n";
			swapRow(mi, i);
			if(b != NULL)
				b->swapRow(mi, i);
		}
	}
	return 1;
}

template class Matrix<int>;
template class Matrix<double>;