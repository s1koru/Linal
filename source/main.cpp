#include <iostream>
#include <matrix.h>
#include<initializer_list>
#include <variant>

int main() {
    //  
    linalg::Matrix m0;
    linalg::Matrix m1(4);
    linalg::Matrix m2(4, 6);
    linalg::Matrix m3(m1);
    linalg::Matrix m4(std::move(m2));
    linalg::Matrix m5 = { {1, 333, 1, 1, 333}, {22, 1, 1, 333, 333}, {1, 1, 1, 333, 1}, {1, 22, 1, 22, 22} };
    linalg::Matrix m6 = { {10000, 2, 3, 4, 5, 6 } };
    linalg::Matrix m7 = { 1, 2, 3, 4, 5, 6 };
    // linalg::Matrix m8 = {{1}, {2}, {3}, {4}, {5}, {6}};
    linalg::Matrix m11 = { {0.3, 2}, {3, 4} };
    // linalg::Matrix m8 = {{1}, {2}, {3}, {4}, {5}, {6}};
    linalg::Matrix m12 = { {4, 6, 9}, {34, 65, 456}, {4.678, 2, 0} };
    linalg::Matrix m13 = { {23, 5, 9}, {2, 5, 8}, {4, 7, 8} };
    linalg::Matrix m14 = power(m11, -2);

    // m1 = m2;
    // m1 = linalg::Matrix{1, 2, 3, 4, 5, 6};
    linalg::Matrix m(2, 2); // 3 строки, 4 столбца
    m(0, 0) = 1; m(0, 1) = 2; 
    m(1, 0) = 2; m(1, 1) = 4; 
    

    std::cout << m << std::endl;

    m.gaussianElimination();

    //try {
      //  m.gaussianElimination();
    //}
    //catch (const std::runtime_error& e) {
      //  std::cerr << "Error: " << e.what() << std::endl;
    //}
        
    std::cout << m;
    //std::cout << m << std::endl;
    //try {
     std::cout <<   m.rank();
    //}
    //catch (const std::exception& e) {
      //  std::cerr << "Error: " << e.what() << std::endl;
    //}

}

