#include <iostream>
#include "EquationSystem.hpp"
#include "Matrix.hpp"

using namespace std;

int main() {
    double coeff[]={10,-1,2,0, -1,11,-1,3, 2,-1,10,-1, 0,3,-1,8};
    double consts[]={6,25,-11,15};
    Matrix<double> a(coeff, 4, 4);
    Matrix<double> b(consts, 4, 1);
    /**Exact solution of the above system is (1,2,-1,1). Taken from wikipedia. **/
    EquationSystem<double> es(a, b);

    cout << "The given system is:\n"<<es;
    
    cout << "Performing GaussJacobi.\n";
    Matrix<double> solution = es.gaussJacobi(true);

    cout << "Solution set:\n"<<solution;

    return 0;
}