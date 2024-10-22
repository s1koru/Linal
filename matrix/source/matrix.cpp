#include <matrix.h>
#include <iostream>

linalg::Matrix::Matrix(size_t rows, size_t columns) {
    m_ptr = new double[rows * columns];
    m_rows = rows;
    m_columns = columns;
};

linalg::Matrix::~Matrix() {
    delete[] m_ptr;
}
