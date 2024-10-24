#include "test.h"  
#include "matrix.h"
#include <iostream>
#include <initializer_list>


int main() {

    testMatrixAddition();
    testMatrixMultiplication();
    testMatrixTranspose();
    testMatrixDeterminant();
    testMatrixInverse();
    testMatrixTrace();
    testMatrixNorm();
    testMatrixGaussianElimination();
    testMatrixRank();
    testMatrixPower();
    testMatrixTransposeInverse();
    testMatrixInverseProduct(); 
    testMatrixInversePower(); 
    testMatrixConcatenate();
    linalg::Matrix a = { {2,4},{1,11} };
    std::cout << a;
    linalg::Matrix i(std::move(a));
    std::cout << i;


    return 0;
}