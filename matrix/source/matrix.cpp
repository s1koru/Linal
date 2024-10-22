#include <matrix.h>
#include <iostream>

linalg::Matrix::Matrix(size_t rows, size_t columns) {
    m_ptr = new double[rows * columns];
    m_rows = rows;
    m_columns = columns;
};

linalg::Matrix::Matrix(size_t rows) {
    m_ptr = new double[rows * 1];
    m_rows = rows;
    m_columns = 1;
};

linalg::Matrix::Matrix(const Matrix& s) {
    m_ptr = new double[s.m_rows * s.m_columns];
    m_rows = s.m_rows;
    m_columns = s.m_columns;
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        m_ptr[i] = s.m_ptr[i];
    }
};

linalg::Matrix::Matrix(Matrix&& s) {
    std::swap(m_ptr, s.m_ptr);
    std::swap(m_rows, s.m_rows);
    std::swap(m_columns, s.m_columns);

    s.m_ptr = nullptr;
    s.m_rows = 0;
    s.m_columns = 0;
}


linalg::Matrix::~Matrix() {
    if (m_ptr != NULL) {
        delete[] m_ptr;
    };
};
