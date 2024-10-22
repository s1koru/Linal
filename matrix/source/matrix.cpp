#include <matrix.h>
#include <iostream>
#include <initializer_list>

linalg::Matrix::Matrix(size_t rows, size_t columns) {
    m_ptr = new double[rows * columns];
    m_rows = rows;
    m_columns = columns;
};

bool linalg::Matrix::empty() const {
    return m_columns == 0 && m_rows == 0;
}

void linalg::Matrix::reshape(int rows, int cols) {
    if (m_rows != rows || m_columns != cols) {
        delete[] m_ptr;
        m_ptr = new double[rows * cols];
        m_columns = cols;
        m_rows = rows;

        bool change = true;
        //скопируем элементы из старой матрицы в новую 
        size_t j = 0;
        for (size_t i = 0; i < m_rows * m_columns; i++) {
            if (m_ptr[i] != 0.0) { m_ptr[j++] = m_ptr[i]; }
            if (j >= m_rows * m_columns) {
                change = false;
                break;
            }
        }

        if (!change) {
            throw std::runtime_error("impossible reshape");
        }

    }
}

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
};

// linalg::Matrix::Matrix(std::initializer_list<std::initializer_list<double>> mm) {
//     m_rows = mm.size();
//     if (m_rows == 0) {
//         m_columns = 0;
//     } else {
//         m_columns = mm.begin()->size();
//     }

//     m_ptr = new double[m_rows * m_columns];
//     size_t i = 0;
//     for (const std::initializer_list<double>& row : mm) {
//         for (const double& el : row) {
//             m_ptr[i++] = el;
//         }
//     }
// };


