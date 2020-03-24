CXX=g++
CXXFLAGS= -Wall

main: main.o Matrix_base.o Matrix_basicoperations.o Matrix_functions.o
	$(CXX) $(CXXFLAGS) -o main main.o Matrix_base.o Matrix_basicoperations.o Matrix_functions.o EquationSystem.o

main.o: EquationSystem.o Matrix_base.o Matrix_basicoperations.o Matrix_functions.o Matrix.hpp

EquationSystem.o: Matrix_functions.o Matrix_base.o EquationSystem.hpp

Matrix_basicoperations.o: Matrix_base.o Matrix.hpp

Matrix_functions.o: Matrix_base.o Matrix.hpp

Matrix_base.o: Matrix.hpp

.PHONY: clean
clean:
	rm -f *.o *.exe main a.out
