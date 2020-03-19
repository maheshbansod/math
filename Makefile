CXX=g++
CXXFLAGS= -Wall

ass1.exe: ass1.o Matrix_base.o Matrix_basicoperations.o Matrix_functions.o
	$(CXX) $(CXXFLAGS) -o ass1.exe ass1.o Matrix_base.o Matrix_basicoperations.o Matrix_functions.o

ass1.o: Matrix_base.o Matrix_basicoperations.o Matrix_functions.o Matrix.hpp

Matrix_basicoperations.o: Matrix_base.o Matrix.hpp

Matrix_functions.o: Matrix_base.o Matrix.hpp

Matrix_base.o: Matrix.hpp

.PHONY: clean
clean:
	rm *.o *.exe
