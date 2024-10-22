#include <iostream>
#include <matrix.h>


int main() {
    //стандартный конструктор
    linalg::Matrix m0;
    linalg::Matrix m1(4);
    linalg::Matrix m2(4, 6);

    std::cout << "Count rows (m1): " << m1.rows() << std::endl;
    std::cout << "Count columns (m1): " << m1.columns() << std::endl;
    std::cout << "Count rows (m2): " << m2.rows() << std::endl;
    std::cout << "Count columns (m2): " << m2.columns() << std::endl;
}
