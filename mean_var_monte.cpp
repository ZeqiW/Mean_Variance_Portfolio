#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <eigen3/Eigen/Dense>
using namespace Eigen;
using namespace std;

 // Here, we use Monte_Carlo simulation to realize portfolio optimization

float uniformRandom()
{
  return ( (float)(rand()))/( (float)(RAND_MAX));
}
//Here, the generator will create random in closed interval [0,1]
//We create uniform random generator

RowVectorXf RandomW(int n){
  //n is the number of securities
  RowVectorXf weight(n);
  float total=0.0;
  for(int i=0;i<n;++i){
    weight(i) = uniformRandom();
  }
  weight=weight/weight.sum();
  return weight;
  }
//Here, we create a random row vector, [0,1] of each element, sum is 1

RowVectorXf mean_var_monte(MatrixXf C, int n, RowVectorXf m){
  //C is the convariance matrix
  //n is the number of securities
  //m is the expected return of each individual securities
  RowVectorXf w(n);
  srand(time(NULL));
  w=RandomW(n);
  float variance;
  variance=w*C*w.transpose();
  int N=10000;
  //Here, N is the simulation time
  for(int i=0; i<N; ++i){
    RowVectorXf temp(n);
    temp=RandomW(n);
    float temp_variance=temp*C*temp.transpose();
    if(temp_variance<variance){
      w=temp;
      variance=temp_variance;
    }
  }
  return w;
}

int main(){
  int n;
  //the number of securities in our portfolio
  cin>>n;
  MatrixXf C(n,n);//convariance matrix
  RowVectorXf w(n),m(n);
  //vetcor w is the weight, and vector u is an identity vector;
  //vector m is the expected return of each stock
  //Here, we first choose three stocks to check our program
  C<<0.1,0,0,0,0.5,0.3,0,0.3,0.2;
  m<<0.3,0.5,0.7;
  w=mean_var_monte(C,n,m);
  cout<<"The weight(without selling) of minimal variance is: "<<w<<endl;
  float port_return=w*m.transpose();
  cout<<"The expected return is: "<<port_return<<endl;
  //Here, if it has the transaction cost, just subtract -n*cost
  }
