#include <iostream>
#include <matrix.h>
#include<initializer_list>
#include <variant>

int main() {
    //дефолтный конструктор 
    linalg::Matrix m0;
    linalg::Matrix m1(4);
    linalg::Matrix m2(4, 6);
    linalg::Matrix m3(m1);
    linalg::Matrix m4(std::move(m2));
    linalg::Matrix m5 = { {1, 333, 1, 1, 333}, {22, 1, 1, 333, 333}, {1, 1, 1, 333, 1}, {1, 22, 1, 22, 22} };
    linalg::Matrix m6 = { {10000, 2, 3, 4, 5, 6 } };
    linalg::Matrix m7 = { 1, 2, 3, 4, 5, 6 };
    // linalg::Matrix m8 = {{1}, {2}, {3}, {4}, {5}, {6}};

    // m1 = m2;
    // m1 = linalg::Matrix{1, 2, 3, 4, 5, 6};
    std::cout << m6;

}
