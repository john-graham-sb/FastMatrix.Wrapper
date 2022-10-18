# FastMatrix.Wrapper

Matrix library written in C++ and wrapped in a C# class. It also performs linear regression and computes predictions (See unit tests).

Performing linear regression where,

- X: a 20 x 2 matrix 
- y: a 20 by 1 matrix
- (theta: a 2 x 1 matrix)

- Number of iterations: 1,000,000

This library takes about 2/3 of the time a pure C# implementation does.

\*Note that ComplexConjugateTranspose() treats each entry as a real number.
