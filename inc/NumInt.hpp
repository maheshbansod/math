
#ifndef NUMINT_HPP
#define NUMINT_HPP

//Static class for Numerical Integration functions
class NumInt {
public:
    /**
     * @brief Uses the trapezoidal method for numerical integration
     * 
     * @param a lower limit for integration
     * @param b upper limit for integration
     * @param f the function to integrate
     * @param n (optional)the number of trazepoids to divide the area under the curve into.
     * 
     * @returns the definite integral of f on [a,b]
     */
    static double trapezoidal(double a, double b, double f(double), int n=10);

private:
    //disallow creating instances of this class
    NumInt() {}
};
#endif