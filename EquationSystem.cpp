
#include "EquationSystem.hpp"

template<class T>
EquationSystem<T>::EquationSystem() : Matrix<T>() {
}

template<class T>
EquationSystem<T>::EquationSystem(Matrix<T> m) : Matrix<T>(m) {
    
}

template class EquationSystem<double>;