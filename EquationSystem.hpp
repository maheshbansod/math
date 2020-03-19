#ifndef EQUATION_SYSTEM_HPP
#define EQUATION_SYSTEM_HPP

#include "Matrix.hpp"

template <class T>
class EquationSystem : private Matrix<T> {
public:
    EquationSystem();
    EquationSystem(const Matrix<T>&);
    //EquationSystem(std::string&);
    //EquationSystem(char*);

    
};

#endif