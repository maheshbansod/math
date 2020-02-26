#include <iostream>

using namespace std;

void jacobiMethod(double coeffs[100][100], double *b, int m, int n, bool verbose = false) {
    //TODO: rearrange equations so that there are no zeroes on the diagonal
    double soln[100] = {0,};
    double oldsoln[100] = {0,};
    int i,j;

    for(int c =0;c<10;c++) {
        if(verbose) cout << "Iteration "<< (c+1) << ":\n";
        for(i=0;i<n;i++) {
            double res = b[i];
            if(verbose) cout << "x" << i << ": ("<<b[i];
            for(j=0;j<m;j++) {
                if(j != i) {
                    res -= coeffs[i][j]*oldsoln[j];
                    if(verbose) cout << "-"<<coeffs[i][j]<< "*" << oldsoln[j];
                }
            }
            if(verbose) cout << ")/"<<coeffs[i][i] <<endl;
            res /= coeffs[i][i];
            if(verbose) cout << ".'.  x"<< i <<" = " <<res << endl;
            soln[i] = res;
        }
        for(i=0;i<m;i++) oldsoln[i]=soln[i];
    }

    for(i=0;i<n;i++) {
        coeffs[i][i]=1;
        for(j=0;j<m;j++) {
            if(j==i) continue;
            coeffs[i][j]=0;
        }
        b[i]=soln[i];
    }
}

void displayEquations(double coeffs[100][100], double *b, int m, int n) {
    int i, j;
    for(i=0;i<n;i++) {
        for(j=0;j<m;j++) {
            if(coeffs[i][j]==0) continue;
            cout << "+";
            if(coeffs[i][j]<0) cout << "(";
            if(coeffs[i][j]!=1) cout << coeffs[i][j];
            if(coeffs[i][j]<0) cout << ")";
            cout << "x" << j;
        }
        cout << "=" << b[i] << endl;
    }
}

int main() {
    double coeffs[100][100],b[100];
    int i,j,m,n;
    cout << "Equations are of the form:\na00x0+a10x1+..+am0xm = b0\na01x0+a11x1+..+am1xm = b1\n .\n .\n";
    cout << "a0nx0+a1nx1+..+amnxm = bn\n";
    cout << "How many equations?(n: ) ";
    cin >> n;
    cout << "How many variables?(m: ) ";
    cin >> m;
    for(i=0;i<n;i++) {
        cout << "For Equation "<<(i+1)<<":\n";
        for(j=0;j<m;j++) {
            cout << "Enter coefficient of x"<<j<<"(a"<<i<<j<<" ): ";
            cin >> coeffs[i][j];
        }
        cout << "Enter constant term(b): ";
        cin >> b[i];
    }

    jacobiMethod(coeffs, b, m, n,false);

    displayEquations(coeffs, b, m, n);
    return 0;
}