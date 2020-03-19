
#include "EquationSystem.hpp"
#include <sstream>

template<class T>
EquationSystem<T>::EquationSystem() : Matrix<T>() {
    symtab = NULL;
}

template<class T>
EquationSystem<T>::EquationSystem(const Matrix<T>& mt) : Matrix<T>(mt) {
    symtab = NULL;
}

template<class T>
std::string EquationSystem<T>::to_string() const {
    long int m = Matrix<T>::getRows();
    long int n = Matrix<T>::getColumns();
    if(m==0 || n==0) return std::string("<empty>");
    //std::string str = "";
    std::ostringstream str;
    long int j;
    for(long int i=0;i<m;i++) {
        for(j=0;j<n-1;j++) {
            if(Matrix<T>::get(i,j) != 0) {
                str << "+";
                if(Matrix<T>::get(i,j) != 1)
                    str << Matrix<T>::get(i,j);
                if(symtab == NULL) {
                    str << char('a'+j);
                }
            }
        }
        str << "=" << Matrix<T>::get(i,j) << "\n";
    }
    return str.str();
}

template <class T>
void EquationSystem<T>::gaussianElimination(bool verbose) {
    Matrix<T>::toRowEchelon(verbose);
}

template <class T>
int EquationSystem<T>::backSubstitution(bool verbose) {
    //backsubstitution
    long int n = Matrix<T>::getColumns(); //no of cols/(no. of var+1)
    long int m = Matrix<T>::getRows(); //no of eqs
    if(m != n-1) {
        if(verbose)
            std::cout << "No. of variables should be equal to no. of equations for back substitution.\n";
        return -1;
    }
    /* it is assummed that the diagonal MUST have non-zero elements 
        if backsubstitution is to be applied - verify this*/
    for(long int i=m-1;i>=0;i--) {
        T b = Matrix<T>::get(i, n-1); //constant term of eqn i
        T lc = Matrix<T>::get(i,i); //leading coefficient
        if(lc == 0) {
            if(b) { //non-zero constant term
                //inconsistent system. do nothing
                if(verbose)
                    std::cout << "Inconsistent system.\n";
                return -1;
            }
            if(verbose)
                std::cout << "Try different set of equations.\n(atleast a pair of equations was same; found a zero row)";
            return -2;
        }
        for(long int j=n-2;j>i;j--) {
            T coeff = Matrix<T>::get(i, j);
            if(coeff != 0) {
                b -= coeff*Matrix<T>::get(j, n-1);
                Matrix<T>::set(T(0), i, j);
            }
        }
        b /= lc;
        Matrix<T>::set(b,i,n-1);
    }
    return 0;
}

template class EquationSystem<double>;