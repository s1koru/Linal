#include <iostream>
#include <matrix.h>


int main() {

    linalg::Matrix m0;
    linalg::Matrix m1(4, 1);
    int rows;
    int columns;

    std::cout << "Enter count row: ";
    std::cin >> rows;
    std::cout << "Enter count columns: ";
    std::cin >> columns;

    linalg::Matrix matrix(rows, columns);

    std::cout << "Count rows: " << matrix.rows() << std::endl;
    std::cout << "Count columns: " << matrix.columns() << std::endl;
}
