#include <iostream>
#include <matrix.h>
#include <initializer_list>


int main() {
    //стандартный конструктор
    linalg::Matrix m0;
    linalg::Matrix m1(4);
    linalg::Matrix m2(4, 6);
    linalg::Matrix m3(m1);
    linalg::Matrix m4(std::move(m2));
    linalg::Matrix m5 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    linalg::Matrix m6 = { {1, 2, 3, 4, 5, 6} };
    linalg::Matrix m7 = { 1, 2, 3, 4, 5, 6 };
    //linalg::Matrix m9 = m5.power(4);
    // linalg::Matrix m8 = {{1}, {2}, {3}, {4}, {5}, {6}};

    // m1 = m2;
    // m1 = linalg::Matrix{1, 2, 3, 4, 5, 6};


    //std::cout << "Count rows (m1): " << m1.rows() << std::endl;
    //std::cout << "Count columns (m1): " << m1.columns() << std::endl;
    //std::cout << "Count rows (m2): " << m2.rows() << std::endl;
    //std::cout << "Count columns (m2): " << m2.columns() << std::endl;
    //std::cout << "Count rows (m3): " << m3.rows() << std::endl;
    //std::cout << "Count columns (m3): " << m3.columns() << std::endl;
    //std::cout << "Count rows (m4): " << m4.rows() << std::endl;
    //std::cout << "Count columns (m4): " << m4.columns() << std::endl;

    //try {
      //  m2.reshape(10, 0);
        //std::cout << "New size: " << m2.columns() << std::endl;
    //}
    //catch (const std::runtime_error& e) {
    //    std::cerr << "ERROR: " << e.what() << std::endl;
    //}

    m5.print();
    linalg::Matrix m8 = m5 * 3.6;
    m8.print();
    std::cout << m8.trace() << "\n";
    std::cout << m5.norm() << "\n";
    //m9.print();
}
