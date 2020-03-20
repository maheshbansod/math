#ifndef EQUATION_SYSTEM_HPP
#define EQUATION_SYSTEM_HPP

#include "Matrix.hpp"

template <class T>
class EquationSystem : public Matrix<T> {
    char *symtab;
public:
    EquationSystem();
    EquationSystem(const Matrix<T>&);
    EquationSystem(const Matrix<T>&, const Matrix<T>&);
    //EquationSystem(std::string&);
    //EquationSystem(char*);

    friend std::ostream &operator<<(std::ostream &output, const EquationSystem<T> &es) {
		output << es.to_string();
		return output;
	}

    void gaussianElimination(bool verbose=false);
    int backSubstitution(bool verbose=false);
    /**
     * @brief Performs Gauss Jacobi algorithm to find out solution of the system
     * 
     * @param bool Optional. if set to true, also prints information on stdout. It's set to false by default.
     * @param const Optional. Default value=25. Defines the number of iterations to perform.
     * 
     * @return Matrix<T> Returns a matrix of size mx1 containing the solution of the system
     */
    Matrix<T> gaussJacobi(bool verbose=false, const int iter_limit=25);

    std::string to_string() const;
};

#endif