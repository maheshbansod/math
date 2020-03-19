
#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <iostream>

template <class T>
class Matrix {
private:
	T **mat;
	long int m,n; //no. of rows and columns
public:
	Matrix();
	Matrix(T**, long int, long int);
	Matrix(long int, long int); //creates an mxn zero matrix
	Matrix(const T*, long int, long int);
	Matrix(const Matrix&);

	void clone(const Matrix&);

	Matrix<T> operator+(Matrix&);
	Matrix<T> operator-(Matrix&);
	Matrix<T> operator-(); //unary minus
	Matrix<T> operator*(double); //const*mat
	Matrix<T> operator*(Matrix&);

	void set(T, long int, long int);
	void setAllElements(T );
	
	friend std::ostream &operator<<(std::ostream &output, const Matrix<T> &m2) {
		output << m2.to_string();
		return output;
	}
	friend std::istream &operator>>(std::istream &input, Matrix<T> &m2) {
		m2.freeMemory();
		input >> m2.m >> m2.n;
		m2.mat = new T*[m2.m];
		for(long int i=0;i<m2.m;i++) {
			m2.mat[i]=new T[m2.n];
			for(long int j=0;j<m2.n;j++) {
				input >> m2.mat[i][j];
			}
		}
		return input;
	}

	//template<class Y>
	friend void LUDecompose(Matrix<double> &m,Matrix<double> &l, Matrix<double> &u);
	
	Matrix<T> rowEchelon(bool verbose=false) const;
	void swapRow(long int, long int);
	void toRowEchelon(bool verbose=false);
	
	T determinant() const;

	T get(long int, long int) const; //get M(i,j)
	long int getRows() const;
	long int getColumns() const;
	std::string to_string() const;

	void freeMemory();
	~Matrix();
};
#endif
