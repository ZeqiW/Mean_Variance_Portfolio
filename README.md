# Mean_Variance Portfolio
OpenMP, Monte-Carlo Simulation, Eigen to realize Mean-Variance Portfolio Strategy.

In mean_variance.cpp, I realize mean_variance strategy by using its own formula.
The formula succeeds in solving two differenct situations:
    1. The minimal risk portfolio among all possible portfolio
    2. The minimal risk portfolio with given expected return.
We use Eigen library to do the matrix multiplication, which is super fast.
For the result, the negative weights mean we are going to sell the underlying security.

In mean_var_monte.cpp, I consider the situation without selling securities. 
It is pretty common for individual investor. 
Most of time, they can just buy and hold their securities.
To realize this situation, I use Monte-Carlo Simulation.
Set experiement time N=10000, find the portfolio with minimal risk( or variance var=sqrt(w*C*w.transpose))

In mean_var_parallel_monte.cpp, I use parallel programming to improve our Monte-Carlo code.
Generally speaking, the computer has 4 threads. Usually, the computer just use one thread to execute your code.
Here, instead of using one, we use 4 threads together to do the Simulation Part.
We also set N=10000. However, in our new code, the computer has finished 4*N times simulation with almost the same time.
