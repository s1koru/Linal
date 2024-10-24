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
    testMatrixReshape();

    linalg::Matrix check = { {1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10}, {1,2,3,4,5,6,7,8,9,10}, {1,2,3,4,5,6,7,8,9,10}, {1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10}, {1,2,3,4,5,6,7,8,9,10}, {1,2,3,4,5,6,7,8,9,10}, {1,2,3,4,5,6,7,8,9,10}, {1,2,3,4,5,6,7,8,9,10} };
    std::cout << check.det();
    linalg::Matrix check1 = { {1,1},{0,1} };
    std::cout << check1.det();
    return 0;
}