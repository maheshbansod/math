
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
     * @param n (optional)the number of trazepoids to divide the area under the curve into. accuracy depends on n.
     * 
     * @returns the definite integral of f on [a,b]
     */
    static double trapezoidal(double a, double b, double f(double), int n=10);

    /**
     * @brief Uses Simpson's one third rule for numerical integration
     * 
     * @param a lower limit for integration
     * @param b upper limit for integration
     * @param f the function to integrate
     * @param n (optional)the number of divisions of the area under the curve. accuracy depends on n.
     * 
     * @returns the definite integral of f on [a,b]
     */
    static double simpsons_13(double a, double b, double f(double), int n=10);

    /**
     * @brief Uses Simpson's three eighth rule for numerical integration
     * 
     * @param a lower limit for integration
     * @param b upper limit for integration
     * @param f the function to integrate
     * @param n (optional)the number of divisions of the area under the curve. accuracy depends on n.
     * 
     * @returns the definite integral of f on [a,b]
     */
    static double simpsons_38(double a, double b, double f(double), int n=10);
    
private:
    //disallow creating instances of this class
    NumInt() {}

    /**
     * @brief checks for and throws common exceptions
     * 
     * @param a lower limit for integration
     * @param b upper limit for integration
     * @param n the number of divisions of the area under the curve. accuracy depends on n.
     * 
    */
   static void checkExceptions(double a, double b, int n);
};
#endif