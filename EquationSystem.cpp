
#include "EquationSystem.hpp"
#include <sstream>
#include <cmath>

template<class T>
EquationSystem<T>::EquationSystem() : Matrix<T>() {
    symtab = NULL;
}

template<class T>
EquationSystem<T>::EquationSystem(const Matrix<T>& mt) : Matrix<T>(mt) {
    symtab = NULL;
}

template<class T>
EquationSystem<T>::EquationSystem(const Matrix<T>& a, const Matrix<T>& b)
    : Matrix<T>(a.joinMatrices(b)) {
    symtab = NULL;
}

template<class T>
std::string EquationSystem<T>::to_string() const {
    long int m = Matrix<T>::getRows();
    long int n = Matrix<T>::getColumns();
    bool flag=false;
    if(m==0 || n==0) return std::string("<empty>");
    std::ostringstream str;
    long int j;
    for(long int i=0;i<m;i++) {
        flag = false;
        for(j=0;j<n-1;j++) {
            T coeff = Matrix<T>::get(i,j);
            if(coeff != 0) {
                flag = true;
                if(coeff > 0)
                    str << "+";
                if(coeff != 1)
                    str << coeff;
                if(symtab == NULL) {
                    str << char('a'+j);
                }
            }
        }
        if(!flag)
            str << "0";
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


const double tol = 0.00001; //tolerance

template <class T>
Matrix<T> EquationSystem<T>::gaussJacobi(bool verbose, const int iter_limit) {
    long int m = Matrix<T>::getRows();
    long int n = Matrix<T>::getColumns();
    /**it is assumed that the coefficient matrix is already diagonally dominant**/
    if(m != n-1) {
        if(verbose)
            std::cout << "Either the given system is inconsistent of doesn't have a unique solution.\nAborting\n";
        return Matrix<T>();
    }
    T *res = new T[m];
    T *oldres = new T[m];
    for(long int i=0;i<m;i++)
        oldres[i]=0;
    int cnt = 0;
    bool done = false;
    while(!done) {
        done = true;
        cnt++;
        if(verbose)
            std::cout << "Iteration "<<cnt<<std::endl;
        for(long int i=0;i<m;i++) {
            T b = Matrix<T>::get(i, n-1);
            T coeff = Matrix<T>::get(i,i);
            if(coeff==0) {
                if(verbose) std::cout << "Matrix contains zero on diagonal.\nAborting.\n";
                return Matrix<T>();
            }
            if(verbose) if(symtab == NULL) std::cout << char(i+'a')<<" = ("<<b;
            for(long int j=0;j<n-1;j++) {
                T a = Matrix<T>::get(i,j);
                if(j != i) {
                    b-=oldres[j]*a;
                    if(verbose) {
                        if(a != 0) {
                        std::cout << "-";
                        if(a<0) std::cout << "(";
                        std::cout<<a;
                        if(a<0) std::cout << ")";
                        std::cout <<"x";
                        if(oldres[j]<0) std::cout << "(";
                        std::cout<<oldres[j];
                        if(oldres[j]<0) std::cout << ")";
                        }
                    }
                }
            }
            b/=coeff;
            if(verbose)
                std::cout << ")/("<<coeff<<") = "<<b<<std::endl;
            //std::cout << "b="<<b<<"res[i]="<<res[i]<<","<<(fabs(b-res[i]))<<std::endl;
            if(fabs(b-res[i]) > tol) {
            //    std::cout << b << ","<<res[i]<<","<<abs(b-res[i])<<std::endl;
                done = false;
            }
            res[i]=b;
        }
        if(cnt >= iter_limit || done)
            break;
         for(long int i=0;i<m;i++) {
             oldres[i]=res[i];
         }
    }
    if(verbose)
        std::cout << "Solution found after "<<cnt<<" iterations"<<std::endl;
    Matrix<T> *soln = new Matrix<T>(res, m, 1);
    
    return *soln;
}

template <class T>
Matrix<T> EquationSystem<T>::gaussSeidel(bool verbose, const int iter_limit) {
    long int m = Matrix<T>::getRows();
    long int n = Matrix<T>::getColumns();
    /**it is assumed that the coefficient matrix is already diagonally dominant**/
    if(m != n-1) {
        if(verbose)
            std::cout << "Either the given system is inconsistent of doesn't have a unique solution.\nAborting\n";
        return Matrix<T>();
    }
    T *res = new T[m];
    for(long int i=0;i<m;i++)
        res[i]=0;
    int cnt = 0;
    bool done = false;
    while(!done) {
        done = true;
        cnt++;
        if(verbose)
            std::cout << "Iteration "<<cnt<<std::endl;
        for(long int i=0;i<m;i++) {
            T b = Matrix<T>::get(i, n-1);
            T coeff = Matrix<T>::get(i,i);
            if(coeff==0) {
                if(verbose) std::cout << "Matrix contains zero on diagonal.\nAborting.\n";
                return Matrix<T>();
            }
            if(verbose) if(symtab == NULL) std::cout << char(i+'a')<<" = ("<<b;
            for(long int j=0;j<n-1;j++) {
                T a = Matrix<T>::get(i,j);
                if(j != i) {
                    b-=res[j]*a;
                    if(verbose) {
                        if(a != 0) {
                        std::cout << "-";
                        if(a<0) std::cout << "(";
                        std::cout<<a;
                        if(a<0) std::cout << ")";
                        std::cout <<"x";
                        if(res[j]<0) std::cout << "(";
                        std::cout<<res[j];
                        if(res[j]<0) std::cout << ")";
                        }
                    }
                }
            }
            b/=coeff;
            if(verbose)
                std::cout << ")/("<<coeff<<") = "<<b<<std::endl;
            if(fabs(b-res[i]) > tol) {
                done = false;
            }
            res[i]=b;
        }
        if(cnt >= iter_limit)
            break;
    }
    if(verbose)
        std::cout << "Solution found after "<<cnt<<" iterations"<<std::endl;
    Matrix<T> *soln = new Matrix<T>(res, m, 1);
    
    return *soln;
}

template class EquationSystem<double>;