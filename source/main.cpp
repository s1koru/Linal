#include <iostream>
#include <matrix.h>


int main() {
    //стандартный конструктор
    linalg::Matrix m0;
    linalg::Matrix m1(2, 2);
    linalg::Matrix m2(2, 2);
    m1(0, 0) = 5; m1(0, 1) = 6; m1(1, 0) = 7; m1(1, 1) = 8;
    m2(0, 0) = 4; m2(0, 1) = 6; m2(1, 0) = 6; m2(1, 1) = 7;
    m1 -= m2;
    linalg::Matrix m3(m1);
    linalg::Matrix m4(std::move(m2));
    // linalg::Matrix m7 = {1, 2, 3, 4, 5, 6};

    std::cout << "Count rows (m1): " << m1.rows() << std::endl;
    std::cout << "Count columns (m1): " << m1.columns() << std::endl;
    std::cout << "Count rows (m2): " << m2.rows() << std::endl;
    std::cout << "Count columns (m2): " << m2.columns() << std::endl;
    std::cout << "Count rows (m3): " << m3.rows() << std::endl;
    std::cout << "Count columns (m3): " << m3.columns() << std::endl;
    std::cout << "Count rows (m4): " << m4.rows() << std::endl;
    std::cout << "Count columns (m4): " << m4.columns() << std::endl;

    //try {
      //  m2.reshape(10, 0);
        //std::cout << "New size: " << m2.columns() << std::endl;
    //}
    //catch (const std::runtime_error& e) {
    //    std::cerr << "ERROR: " << e.what() << std::endl;
    //}

    m1.print();

}

