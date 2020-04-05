#include "NumInt.hpp"

double NumInt::trapezoidal(double a, double b, double f(double), int n) {
    if(n==0)
        throw "NumInt::trapezoidal: `n=0`\n\t`n` is the number of divisions to make. `n` can't be 0";
    if(a > b)
        throw "NumInt::trapezoidal: Lower limit can't be greater than or equal to upper limit.";
    double dx = (b-a)/n;
    double x = a+dx;
    double sum = 0;
    while(x < b) {
        sum += f(x);
        x+=dx;
    }
    return dx*(f(a)+f(b)+2*sum)/2;
}

double NumInt::simpsons_onethird(double a, double b, double f(double), int n) {
    ;
}