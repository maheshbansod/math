#include <iostream>
#include <cstring>
#include "EquationSystem.hpp"
#include "Matrix.hpp"

using namespace std;

int main(int argc, char **argv) {
    double coeff[]={10,-1,2,0, -1,11,-1,3, 2,-1,10,-1, 0,3,-1,8};
    double consts[]={6,25,-11,15};
    Matrix<double> a(coeff, 4, 4);
    Matrix<double> b(consts, 4, 1);
    /**Exact solution of the above system is (1,2,-1,1). Taken from wikipedia. **/
    EquationSystem<double> es(a, b);

    bool verbose = true;
    if(argc>1) {
        if(strcmp(argv[1],"n")==0) verbose = false;
        else {
            std::cout << "Invalid command line argument. Pass `n` to set verbose to false, pass nothing to set it to true.\nsetting verbose to false\n";
            verbose = false;
        }
    }

    cout << "The given system is:\n"<<es;
    
    cout << "Performing GaussJacobi.\n";
    Matrix<double> solution = es.gaussJacobi(verbose);

    cout << "-----\nSolution set:\n"<<solution<<"-----\n";

    if(argc == 1)
        std::cout << "You can pass the command line argument `n` to remove the detailed messages of the gauss jacobi algorithm.\n";

    return 0;
}