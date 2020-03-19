#ifndef EQUATION_SYSTEM_HPP
#define EQUATION_SYSTEM_HPP

#include "Matrix.hpp"

template <class T>
class EquationSystem : public Matrix<T> {
    char *symtab;
public:
    EquationSystem();
    EquationSystem(const Matrix<T>&);
    //EquationSystem(std::string&);
    //EquationSystem(char*);

    friend std::ostream &operator<<(std::ostream &output, const EquationSystem<T> &es) {
		output << es.to_string();
		return output;
	}

    std::string to_string() const;
};

#endif