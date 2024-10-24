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

    return 0;
}