#include "Matrix.hpp"

void LUDecompose(Matrix<double> &m, Matrix<double> &l, Matrix<double> &u) {
	/**Using Doolittle method**/
	//assume l and u have appropriate size. all matrices square
	l.setAllElements(0);
	u.setAllElements(0);
	
	for(long int i=0;i<m.m;i++) {
		for(long int k=i;k<m.n;k++) {
			double sum = 0;
			for(long int j=0;j<i;j++) {
				sum += l.mat[i][j]*u.mat[j][k];
			}
			u.mat[i][k]=m.mat[i][k]-sum;
		}
		l.mat[i][i]=1;
		for(long int k=i+1;k<m.n;k++) {
			double sum;
			for(long int j=0;j<i;j++) {
				sum += l.mat[k][j]*u.mat[j][i];
			}
			l.mat[k][i]=(m.mat[k][i]-sum)/u.mat[i][i];
		}
	}
}

template <class T>
Matrix<T> Matrix<T>::rowEchelon(bool verbose) const {
	Matrix<T> *res=new Matrix<T>();
	res->clone(*this);
	res->toRowEchelon(verbose);
	return *res;
}

template <class T>
void Matrix<T>::swapRow(long int x, long int y) {
	for(long int i=0;i<n;i++) {
		T t = mat[x][i];
		mat[x][i]=mat[y][i];
		mat[y][i]=t;
	}
}

template <class T>
void Matrix<T>::toRowEchelon(bool verbose) {
	
	long int r=0;
	for(long int i=0;i<n;i++) {
		for(long int j=r;j<m;j++) {
			if(mat[j][i]!=0) {
				if(r != j) {
					swapRow(j,r);
					if(verbose) std::cout << "swapping row "<< j <<" and row "<<r<<"\n"<<to_string();
				}
				if(mat[r][i]!=1) {
					//dividing row r by first nonzero element of that row
					for(long int k=i+1;k<n;k++) {
						mat[r][k]/=mat[r][i];
					}
				
					if(verbose) std::cout << "R"<<r<<"=R"<<r<<"/"<<mat[r][i]<<std::endl;
					mat[r][i]=1;
					if(verbose) std::cout << to_string();
				}
				
				//make all elements below element at r,i 0
				for(long int k=r+1;k<m;k++) {
					if(mat[k][i]!=0) {
						for(long int l=i+1;l<n;l++) {
							mat[k][l]-=mat[k][i]*mat[r][l];
						}
						if(verbose) std::cout << "R"<<k<<"=R"<<k<<"-"<<mat[k][i]<<"*R"<<r<<std::endl;
						mat[k][i]=0;
						if(verbose) std::cout << to_string();
					}
				}
				r++;
				break;
			}
		}
	}
	
}

template <class T>
T Matrix<T>::determinant() const {
	/**Change code later for determining determinant for matrix size n **/
	if(m != n || n>3) {
		//throw Exception
		return -1;
	}
	if(n==1) return mat[0][0];
	else if(n==2) return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
	else return  mat[0][0]*(mat[1][1]*mat[2][2]-mat[1][2]*mat[2][1])
							-mat[0][1]*(mat[1][0]*mat[2][2]-mat[1][2]*mat[0][2])
							+mat[0][2]*(mat[1][0]*mat[2][1]-mat[1][1]*mat[2][0]);
}

template class Matrix<int>;
template class Matrix<double>;