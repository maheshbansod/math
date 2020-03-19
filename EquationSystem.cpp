
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
    //perform pivoting?
    Matrix<T>::toRowEchelon(verbose);
    //perform back substitution
}

template class EquationSystem<double>;