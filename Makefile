CXX=g++
CXXFLAGS= -Wall

ass1.exe: ass1.o Matrix_base.o Matrix_basicoperations.o Matrix_functions.o
	$(CXX) $(CXXFLAGS) -o ass1.exe ass1.o Matrix_base.o Matrix_basicoperations.o Matrix_functions.o

ass2.exe: ass2.o Matrix_base.o Matrix_basicoperations.o Matrix_functions.o
	$(CXX) $(CXXFLAGS) -o ass2.exe ass2.o Matrix_base.o Matrix_basicoperations.o Matrix_functions.o EquationSystem.o

ass1.o: Matrix_base.o Matrix_basicoperations.o Matrix_functions.o Matrix.hpp

ass2.o: EquationSystem.o

EquationSystem.o: Matrix_functions.o Matrix_base.o EquationSystem.hpp

Matrix_basicoperations.o: Matrix_base.o Matrix.hpp

Matrix_functions.o: Matrix_base.o Matrix.hpp

Matrix_base.o: Matrix.hpp

.PHONY: clean
clean:
	rm *.o *.exe
