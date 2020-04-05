#include "NumInt.hpp"

double NumInt::trapezoidal(double a, double b, double f(double), int n) {
    double dx = (b-a)/n;
    double x = a+dx;
    double sum = 0;
    while(x < b) {
        sum += f(x);
        x+=dx;
    }
    return dx*(f(a)+f(b)+2*sum)/2;
}