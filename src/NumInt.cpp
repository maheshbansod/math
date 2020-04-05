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

double NumInt::simpsons_13(double a, double b, double f(double), int n) {
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

double NumInt::simpsons_38(double a, double b, double f(double), int n) {
    checkExceptions(a,b,n);
    double dx = (b-a)/n, dx2 = 2*dx, dx3 = 3*dx;
    double x = a+dx;
    int i=1;
    double sum1 = 0; //sum of terms not divisible by 3
    double sum2 = 0; //sum of terms divisible by 3
    while(x<b) {
        if(i%3==0) {
            sum2+=f(x);
        } else {
            sum1+=f(x);
        }
        i++;
        x+=dx;
    }
    return 3*dx*(f(a)+f(b)+3*sum1+2*sum2)/8;
}

void NumInt::checkExceptions(double a, double b, int n) {
    if(n==0)
        throw ": `n=0`\n\t`n` is the number of divisions to make. `n` can't be 0";
    if(a >= b)
        throw ": Lower limit can't be greater than or equal to upper limit.";
}