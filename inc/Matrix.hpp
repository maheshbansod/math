
#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <iostream>
#include <fstream>

template <class T>
class Matrix {
private:
	T **mat;
	long int m,n; //no. of rows and columns
public:
	//matrix_base
	//constructors
	/**
	 * @brief default constructor. Sets matrix to null and number of rows and columns to 0
	 * 
	*/
	Matrix();
	/**
	 * @brief Takes a 2D array of type T and creates an mxn matrix with that data.
	 * 
	 * @param T** the data i.e. the 2D array
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
	 * @brief overloading = operator(uses the clone function)
	 * 
	 * @param mat Matrix to copy from
	 * 
	 */
	void operator=(const Matrix& mat);
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
	 * @return Returns element at location (i,j) in the matrix
	 */
	T get(long int i, long int j) const;
	/**
	 * @brief gets number of rows of matrix
	 * 
	 * @return Returns number of rows of the matrix
	 */
	long int getRows() const;
	/**
	 * @brief gets number of columns of matrix
	 * 
	 * @return Returns number of columns of the matrix
	 */
	long int getColumns() const;
	/**
	 * @brief Creates a string which is more suitable to be displayed on the screen
	 * 
	 * @return Returns stringified version of the matrix
	 */
	std::string to_string() const;
	/**
	 * @brief Destructor
	 */
	~Matrix();
private:
	/**
	 * @brief Copies a matrix to the current matrix
	 * 
	 * @param mat Matrix to copy from
	 * 
	 */
	void clone(const Matrix& mat);
	/**
	 * @brief frees the memory allocated by matrix and resets the matrix
	*/
	void freeMemory();

public:
	/**
	 * @brief overloads << operator for output
	 * 
	 * @param output Output stream which is the left operand of `<<`
	 * @param m2     Matrix to output
	 * 
	 * @return Returns the stream with the stringified version of the matrix.
	 */
	friend std::ostream &operator<<(std::ostream &output, const Matrix<T> &m2) {
		output << m2.to_string();
		return output;
	}
	/**
	 * @brief overloads >> operator for input
	 * 
	 * @param input Input stream which is the left operand
	 * @param m2 Matrix which would store the input
	 * 
	 * @return Returns an input stream
	 */
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
	/**
	 * @brief overloads >> operator for file input stream(taking input from a file)
	 * 
	 * @param fin Input stream which is the left operand
	 * @param m2 Matrix which would store the input
	 * 
	 * @return Returns a file input stream
	 */
	friend std::ifstream &operator>>(std::ifstream &fin, Matrix<T> &m2) {
		//TODO: EOF exception handling
		long int m, n;
		m2.freeMemory();
		fin >> m >> n;
		m2.mat = new T*[m];
		for(long int i=0;i<m;i++) {
			m2.mat[i]=new T[n];
			for(long int j=0;j<n;j++) {
				fin >> m2.mat[i][j];
			}
		}
		m2.m = m;
		m2.n = n;
		return fin;
	}

	//matrix_basicoperations
	/**
	 * @brief Overloaded addition operator to perform matrix addition
	 * 
	 * @param m The right hand side operand
	 * 
	 * @returns a matrix which is the result of addition of `this` and `m`
	 */
	Matrix<T> operator+(Matrix& m);
	/**
	 * @brief Overloaded minus operator to perform matrix subtraction
	 * 
	 * @param m The right hand side operand
	 * 
	 * @returns a matrix which is the result of subtraction of `this` and `m`
	 */
	Matrix<T> operator-(Matrix& m);
	/**
	 * @brief overload unary - operator performs unary minus/multiplies the matrix by -1
	 * 
	 * @returns a matrix which is -`this`
	 */
	Matrix<T> operator-();
	/**
	 * @brief Overloaded asterisk operator to perform matrix multiplication with a constant/matrix scaling
	 * 
	 * @param k A scalar - right hand side operand
	 * 
	 * @returns a matrix which is the result of scaling the matrix by `k`
	 */
	Matrix<T> operator*(double k); //const*mat
	/**
	 * @brief Overloaded asterisk operator to perform matrix multiplication
	 * 
	 * @param m The right hand side matrix operand
	 * 
	 * @returns a matrix which is the result of multiplication of `this` and `m`
	 */
	Matrix<T> operator*(Matrix& m);
	/**
	 * @brief joins two matrices horizontally
	 * 
	 * @param m the rhs matrix operand
	 * 
	 * @returns a matrix which is obtained by joining the rhs matrix to the right of lhs matrix
	 */
	Matrix<T> joinMatrices(const Matrix& m) const;
	/**
	 * @brief attempts to make the matrix diagonally dominant
	 * 
	 * @param verbose shows detailed output if set to true
	 * @param[out] b pointer to the matrix of constants which is also appropriately changed
	 * 
	 * @returns 1 if it was successful, -3 if the dimensions are not good, -1 if failed to make the matrix diagonally dominant
	 */
	int makeDiagonallyDominant(bool verbose=false, Matrix<T> *b=NULL);
	/**
	 * @brief checks if the matrix is identity matrix
	 * 
	 * @returns true if the matrix is identity matrix, false otherwise
	*/
	bool isIdentity() const;
	/**
	 * @brief checks if the matrix is symmetric
	 * 
	 * @returns true if the matrix is symmetric, false otherwise
	 */
	bool isSymmetric() const;
	/**
	 * @brief checks if matrix is triangular(upper or lower)
	 * 
	 * @returns true if the matrix is triangular, false otherwise
	 */
	bool isTriangular() const;
	/**
	 * 
	 * @brief checks if the matrix is diagonally dominant
	 * 
	 * @returns true if the matrix is diagonally dominant, false otherwise
	 */
	bool isDiagonallyDominant() const;

	//matrix_functions
	/**
	 * @brief Perform LU Decomposition using Doolittle's method
	 * 
	 * @param[out] l The lower triangular matrix
	 * @param[out] u The upper triangular matrix
	 * 
	 * @returns 1 if the decomposition was successful, 0 otherwise
	 */
	int luDecompose_doolittle(Matrix<T> &l, Matrix<T> &u) const;
	/**
	 * @brief Perform LU Decomposition using Crout's method
	 * 
	 * @param[out] l The lower triangular matrix
	 * @param[out] u The upper triangular matrix
	 * 
	 * @returns 1 if the decomposition was successful, 0 otherwise
	 */
	int luDecompose_crout(Matrix<T> &l, Matrix<T> &u) const;
	/**
	 * @brief Perform LU Decomposition using Cholesky's method
	 * 
	 * @param[out] l The lower triangular matrix
	 * @param[out] u The upper triangular matrix
	 * 
	 * @returns 1 if the decomposition was successful, 0 otherwise
	 */
	int luDecompose_cholesky(Matrix<T> &l, Matrix<T> &u) const;
	
	/**
	 * @brief performs Gaussian elimination
	 * 
	 * @param verbose shows detailed output if true
	 * 
	 * @returns a matrix which is row echelon form of `this`
	 */
	Matrix<T> rowEchelon(bool verbose=false) const;
	/**
	 * @brief swaps two rows
	 * 
	 * @param x,y the row indices to swap. 
	 * 
	 */
	void swapRow(long int x, long int y);
	/**
	 * @brief performs Gaussian elimination
	 * 
	 * @param verbose shows detailed output if true
	 */
	void toRowEchelon(bool verbose=false);
	
	/**
	 * @brief Calculates the determinant of a square matrix using LU decomposition
	 * 
	 * @returns the determinant of the matrix
	 */
	T determinant() const;
};
#endif
