
#include "EquationSystem.hpp"

template<class T>
EquationSystem<T>::EquationSystem() : Matrix<T>() {
}

template<class T>
EquationSystem<T>::EquationSystem(const Matrix<T>& mt) : Matrix<T>(mt) {
    
}

template class EquationSystem<double>;