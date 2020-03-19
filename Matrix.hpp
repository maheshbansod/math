
#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <iostream>

template <class T>
class Matrix {
private:
	T **mat;
	long int m,n; //no. of rows and columns
public:
	//matrix_base
	//constructors
	Matrix();
	/**
	 * @brief Takes a 2D array of type T and creates an mxn matrix with that data.
	 * 
	 * @param dat the data i.e. the 2D array
	 * @param m the number of rows of matrix
	 * @param n the number of columns of matrix
	 * 
	 */
	Matrix(T** dat, long int m, long int n);
	/**
	 * @brief Creates an mxn zero matrix
	 * 
	 * @param m the number of rows of matrix
	 * @param n the number of columns of matrix
	 * 
	 */
	Matrix(long int m, long int n);
	/**
	 * @brief Creates an mxn matrix using the plain array dat provided
	 * 
	 * @param dat the array containing data
	 * @param m the number of rows of matrix
	 * @param n the number of columns of matrix
	 * 
	 */
	Matrix(const T* dat, long int, long int);
	/**
	 * @brief Copy constructor(uses the clone function)
	 * 
	 * @param mat Matrix to copy from
	 * 
	 */
	Matrix(const Matrix& mat);
	
	/**
	 * @brief Copies a matrix to the current matrix
	 * 
	 * @param mat Matrix to copy from
	 * 
	 */
	void clone(const Matrix& mat);

	/**
	 * @brief Sets element at (i,j) to x
	 * 
	 * @param x the element to set
	 * @param i row index
	 * @param j column index
	 * 
	 */
	void set(T x, long int i, long int j);
	/**
	 * @brief Sets all elements in the matrix to x
	 * 
	 * @param x the element to set
	 * 
	 */
	void setAllElements(T x);

	/**
	 * @brief Getter for element (i,j) of the matrix
	 * 
	 * @param i row index
	 * @param j column index
	 * 
	 */
	T get(long int, long int) const;
	long int getRows() const;
	long int getColumns() const;
	std::string to_string() const;

	void freeMemory();
	~Matrix();
	
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

	//matrix_basicoperations
	Matrix<T> operator+(Matrix&);
	Matrix<T> operator-(Matrix&);
	Matrix<T> operator-(); //unary minus
	Matrix<T> operator*(double); //const*mat
	Matrix<T> operator*(Matrix&);
	Matrix<T> joinMatrices(const Matrix&) const;
	int makeDiagonallyDominant(bool verbose=false, Matrix<T> *b=NULL);
	bool isIdentity() const;
	bool isSymmetric() const;
	bool isDiagonallyDominant() const;

	//matrix_functions
	friend void LUDecompose(Matrix<double> &m,Matrix<double> &l, Matrix<double> &u);
	
	Matrix<T> rowEchelon(bool verbose=false) const;
	void swapRow(long int, long int);
	void toRowEchelon(bool verbose=false);
	
	T determinant() const;
};
#endif
