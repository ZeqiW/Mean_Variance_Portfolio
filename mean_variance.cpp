#include <iostream>
#include <eigen3/Eigen/Dense>
using namespace Eigen;
using namespace std;


RowVectorXf minrisk_weights(MatrixXf C, int n, RowVectorXf u){
  //n is the number of securities
  //C is the convariance matrix
  //u is the identity row vector with length n
  MatrixXf inverse_C(n,n);
  inverse_C=C.inverse();
  RowVectorXf w(n);
  //w is the weight that we want to calcalate
  w=(u*inverse_C)/(u*inverse_C*u.transpose());
  return w;
}

RowVectorXf minriskwithexpectedreturn_weights(float exp_return, MatrixXf C,
  int n, RowVectorXf m, RowVectorXf u){
  //exp_return is the expected return
  //C is the convariance matrix
  //n is the number of securities
  //m is the expected return of each individual securities
  //u is the identity row vector with length n
    MatrixXf inverse_C(n,n);
    inverse_C=C.inverse();
    RowVector2f v_row;
    v_row(0)=exp_return;
    v_row(1)=1;
    MatrixXf v_column(2,n);
    v_column<<m*inverse_C,u*inverse_C;
    MatrixXf M(2,2);
    M(0,0)=m*inverse_C*m.transpose();
    M(0,1)=m*inverse_C*u.transpose();
    M(1,0)=M(0,1);
    M(1,1)=u*inverse_C*u.transpose();
    RowVectorXf w(n);
    //w is the weight that we want to calcalate
    w=v_row*M.inverse()*v_column;
    return w;
  }

int main(){
  int n;
  //the number of securities in our portfolio
  cin>>n;
  MatrixXf C(n,n);//convariance matrix
  RowVectorXf w1(n),w2(n),u(n),m(n);
  //vetcor w is the weight, and vector u is an identity vector;
  //vector m is the expected return of each stock
  //Here, we first choose three stocks to check our program
  C<<0.1,0,0,0,0.5,0.3,0,0.3,0.2;
  u<<1,1,1;
  m<<0.3,0.5,0.7;

  float return1, return2;
  w1=minrisk_weights(C, n, u);
  //w1 is the minimal risk portfolio
  cout<<"The portfolio with minimal risk: "<<w1<<endl;
  return1=w1*m.transpose();
  cout<<"The expected return is: "<<return1<<endl;

  //Now, we calcalate the minimal variance portfolio for given expected return
  cout<<"Please type the expected return of the portfolio: "<<endl;
  cin>>return2;
  w2=minriskwithexpectedreturn_weights(return2, C, n, m, u);
  cout<<"The portfolio with expected return "<<return2<<" and minimal risk is: "<<endl;
  cout<<w2<<endl;
  return 0;
}
