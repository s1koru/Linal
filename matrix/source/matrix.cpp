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
    if (rows == 0 || cols == 0) {
        throw std::runtime_error("Empty matrix");
    }
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
};

linalg::Matrix::Matrix(size_t rows) {
    m_ptr = new double[rows * 1];
    m_rows = rows;
    m_columns = 1;
};

linalg::Matrix::Matrix(const Matrix& s) {
    if (s.m_ptr == nullptr) {
        m_ptr = nullptr;
        m_rows = 0;
        m_columns = 0;
    }
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

// linalg::Matrix::Matrix(std::initializer_list<double> s) { 
//     m_ptr = new double[s.size()];
//     m_rows = s.size(); 
//     m_columns = 1;
//     size_t i = 0; 
//     for (double el:m) { 
//         m_ptr[i++] = el;
//     }
// }


// linalg::Matrix::Matrix(std::initializer_list<std::initializer_list<double>> s) {
//     m_rows = s.size();
//     if (m_rows == 0) {
//         m_columns = 0;
//     } else {
//         m_columns = mm.begin()->size();
//     }

//     m_ptr = new double[m_rows * m_columns];
//     size_t i = 0;
//     for (const std::initializer_list<double>& row : mm) {
//         if (row.size() != m_columns) { 
//             throw std::invalid_argument("all rows should have the same len");
//         }

//         for (const double& el : row) {
//             m_ptr[i++] = el;
//         }
//     }
// };

linalg::Matrix& linalg::Matrix::operator= (const Matrix& m) {
    if (m_columns * m_rows != m_columns * m_rows) {
        delete[] m_ptr;
        m_ptr = new double[m.m_rows * m.m_columns];
        m_rows = m.m_rows;
        m_columns = m.m_columns;
    }

    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        m_ptr[i] = m.m_ptr[i];
    }

    return *this;
};

linalg::Matrix& linalg::Matrix::operator=(Matrix&& m) {
    std::swap(m_ptr, m.m_ptr);
    std::swap(m_rows, m.m_rows);
    std::swap(m_columns, m.m_columns);
    return *this;
};

double& linalg::Matrix::operator()(size_t row, size_t cols) {
    if (row > m_rows || cols > m_columns) {
        throw std::out_of_range("size error");
    }
    return m_ptr[row * m_columns + cols];
}

const double& linalg::Matrix::operator()(size_t row, size_t cols) const {
    if (row > m_rows || cols > m_columns) {
        throw std::out_of_range("size error");
    };
    return m_ptr[row * m_columns + cols];
};


double& linalg::Matrix::operator() (int i, int j) {
    return *(m_ptr + i * m_columns + j);
};

const double& linalg::Matrix::operator()(int i, int j) const {
    return *(m_ptr + i * m_columns + j);
};

void linalg::Matrix::print() const {
    for (int i = 0; i < m_rows; ++i) {
        std::cout << " | ";
        for (int j = 0; j < m_columns; ++j) {
            std::cout.width(3);
            std::cout << *(m_ptr + i * m_rows + j) << " ";
        }
        std::cout << "| \n" << std::endl;
    }
};
linalg::Matrix linalg::Matrix::operator+ (const linalg::Matrix& matrica) const {
    if (m_rows != matrica.m_rows || m_columns != matrica.m_columns) {
        throw std::invalid_argument("matrix sizes don't match");
    }
    Matrix conclusion(m_rows, m_columns);
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        conclusion.m_ptr[i] = m_ptr[i] + matrica.m_ptr[i];
    }
    return conclusion;
};

linalg::Matrix linalg::Matrix::operator+= (const linalg::Matrix& matrica) {
    if (m_rows != matrica.m_rows || m_columns != matrica.m_columns) {
        throw std::invalid_argument("matrix sizes don't match");
    }
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        this->m_ptr[i] += matrica.m_ptr[i];
    }
    return *this;
};

linalg::Matrix linalg::Matrix::operator- (const linalg::Matrix& matrica) const {
    if (m_rows != matrica.m_rows || m_columns != matrica.m_columns) {
        throw std::invalid_argument("matrix sizes don't match");
    }
    Matrix conclusion(m_rows, m_columns);
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        conclusion.m_ptr[i] = m_ptr[i] - matrica.m_ptr[i];
    }
    return conclusion;
};

linalg::Matrix linalg::Matrix::operator-= (const linalg::Matrix& matrica) {
    if (m_rows != matrica.m_rows || m_columns != matrica.m_columns) {
        throw std::invalid_argument("matrix sizes don't match");
    }
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        this->m_ptr[i] -= matrica.m_ptr[i];
    }
    return *this;
};
linalg::Matrix linalg::Matrix::operator* (const linalg::Matrix& matrica) const {
    if (m_columns != matrica.m_rows) {
        throw std::invalid_argument("sizes matrix different");
    }
    Matrix conclusion(m_rows, matrica.m_columns);
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < matrica.m_columns; ++j) {
            conclusion(i, j) = 0;
            for (int l = 0; l < m_columns; ++l) {
                conclusion(i, j) += (*this)(i, l) * matrica(l, j);
            }
        }
    }
    return conclusion;
}

linalg::Matrix linalg::Matrix::operator*= (const linalg::Matrix& matrica) {
    if (m_columns != matrica.m_rows) {
        throw std::invalid_argument("sizes matrix different");
    }
    Matrix conclusion(m_rows, matrica.m_columns);
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < matrica.m_columns; ++j) {
            conclusion(i, j) = 0;
            for (int l = 0; l < m_columns; ++l) {
                conclusion(i, j) += (*this)(i, l) * matrica(l, j);
            }
        }
    }
    *this = std::move(conclusion);
    return *this;
}


