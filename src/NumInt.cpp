#include "NumInt.hpp"

double NumInt::trapezoidal(double a, double b, double f(double), int n) {
    checkExceptions(a,b,n);
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
    checkExceptions(a,b,n);
    double dx = (b-a)/n,tdx=2*dx;
    double x = a+dx;
    double sumo = 0;
    //sum of odd terms
    while(x<b) {
        sumo += f(x);
        x+=tdx;
    }
    x = a+tdx;
    double sume = 0;
    //sum of even terms
    while(x<b) {
        sume += f(x);
        x += tdx;
    }
    
    return dx*(f(a)+f(b) +2*sume +4*sumo)/3;
}

void NumInt::checkExceptions(double a, double b, int n) {
    if(n==0)
        throw ": `n=0`\n\t`n` is the number of divisions to make. `n` can't be 0";
    if(a >= b)
        throw ": Lower limit can't be greater than or equal to upper limit.";
}