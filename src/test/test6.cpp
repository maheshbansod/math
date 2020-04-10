#include <iostream>
#include <cmath>
#include <NumInt.hpp>

using namespace std;

#ifndef VERBOSE
#define VERBOSE false
#endif

#define real_stringify(s) #s
#define stringify(...) real_stringify(__VA_ARGS__)

#define FX                 \
double f(double x) {       \
	return sqrt(1-x*x);    \
}
FX

#define GX                 \
double g(double x) {       \
	double s = sin(x);     \
	return s*s;            \
}
GX

#define PX                 \
double p(double x) {       \
	return x;              \
}
PX

int main() {

	double a, b;
	int choice, n;
	double (*fun)(double) = 0; // the function to use
	double (*meth)(double, double, double f(double), int) = 0; //the method to use

	do {
		cout << "Which method to use?\n1. Trapezoidal method\n";
		cout << "2. Simpson's 1/3rd rule\n";
		cout << "3. Simpson's 3/8th rule\n> ";
		cin >> choice;
		if(choice == 1) meth = NumInt::trapezoidal;
		else if(choice == 2) meth = NumInt::simpsons_13;
		else if(choice == 3) meth = NumInt::simpsons_38;
		else cout << "Invalid choice. Try again.\n";
	}while(choice <  0 || choice > 3);

	do {
		cout << "Which function to use?\n1. y=f(x): "<<stringify(FX)<<endl;
		cout << "2. y=g(x): "<<stringify(GX)<<endl;
		cout << "3. y=p(x): "<<stringify(PX)<<endl<<"> ";
		cin >> choice;
		if(choice == 1) fun = f;
		else if(choice == 2) fun = g;
		else if(choice == 3) fun = p;
		else cout << "Invalid choice. Try again.\n";
	}while(choice < 0 || choice > 3);

	cout << "Enter lower limit and upper limit\n";
	cin >> a >> b;

	cout << "Enter the number of samples\n";
	cin >> n;
	try {

		double result;
		result = meth(a,b, fun, n );

		cout << "----------output----------\n";
		/**TODO: make superscript and subscript functions?**/
		cout << b<<endl;
		cout << "\u222B y dx \u2248 "<<result<<endl;
		cout << a << endl;

	}catch(const char *msg) {
		cout <<"Exception occurred: "<< msg << endl;
	}

    return 0;
}