#include <matrix.h>
#include <iostream>
#include <stdexcept> 
#include <cmath>
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

    s.m_ptr = nullptr; //обнуляем ресурсы у объекта s 
    s.m_rows = 0;
    s.m_columns = 0;
};

linalg::Matrix::Matrix(std::initializer_list<double> s) {
    m_ptr = new double[s.size()];
    m_rows = s.size();
    m_columns = 1;
    size_t i = 0;
    for (double el : s) {
        m_ptr[i++] = el;
    }
};

linalg::Matrix::Matrix(std::initializer_list<std::initializer_list<double>> s) {
    m_rows = s.size();
    if (m_rows == 0) {
        m_columns = 0;
    }
    else {
        m_columns = s.begin()->size();
    }

    m_ptr = new double[m_rows * m_columns];
    size_t i = 0;
    for (const std::initializer_list<double>& row : s) {
        if (row.size() != m_columns) {
            throw std::invalid_argument("all rows should have the same len");
        }
        for (const double& el : row) {
            m_ptr[i++] = el;
        }
    }
};

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
    std::cout << std::fixed;  //      ( )
    std::cout.precision(3);   //      (3 ,  )

    for (int i = 0; i < m_rows; ++i) {
        std::cout << " | ";
        for (int j = 0; j < m_columns; ++j) {
            std::cout.width(6);  //      (   )
            std::cout << *(m_ptr + i * m_columns + j) << " ";
        }
        std::cout << "| \n" << std::endl;
    }
}


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

linalg::Matrix linalg::Matrix::operator* (const double c) const {
    if (empty()) { throw std::invalid_argument("empty matric"); }

    linalg::Matrix result(m_rows, m_columns);
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        result.m_ptr[i] = c * m_ptr[i];
    }
    return result;
};

bool linalg::Matrix::operator== (const linalg::Matrix& matrica) const {
    if (m_rows != matrica.m_rows || m_columns != matrica.m_columns) {
        return false;
    }
    for (size_t i = 0; i < matrica.m_rows * matrica.m_columns; ++i) {
        if (m_ptr[i] != matrica.m_ptr[i]) {
            return false;
        }
    }
    return true;
}

bool linalg::Matrix::operator!= (const linalg::Matrix& matrica) const {
    if (m_rows != matrica.m_rows || m_columns != matrica.m_columns) {
        return true;
    }
    for (size_t i = 0; i < matrica.m_rows * matrica.m_columns; ++i) {
        if (m_ptr[i] != matrica.m_ptr[i]) {
            return true;
        }
    }
    return false;
}

double linalg::Matrix::trace() const {
    if (m_columns != m_rows) {
        throw std::invalid_argument("wrong size of matric");
    }
    double result = 0;
    for (size_t i = 0; i < m_rows; ++i) {
        result += *(m_ptr + i * m_columns + i);
    }
    return result;
};

double linalg::Matrix::norm() const {
    double summa = 0;
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        summa += m_ptr[i] * m_ptr[i];
    }
    return sqrt(summa);
};

linalg::Matrix linalg::Matrix::deleteRowCol(const linalg::Matrix& m, size_t i, size_t j) const {
    Matrix newmatrix(m.m_rows - 1, m.m_columns - 1);
    size_t new_row = 0;
    for (size_t q = 0; q < m.m_rows; ++q) {
        if (q == i) continue;
        size_t new_col = 0;
        for (size_t z = 0; z < m.m_columns; ++z) {
            if (z == j) continue;
            newmatrix(new_row, new_col) = m(q, z);
            ++new_col;
        }
        ++new_row;
    }
    return newmatrix;
};

double linalg::Matrix::det() const {
    if (m_rows != m_columns) {
        throw std::invalid_argument("wrong size matrix");
    }

    if (m_rows == 1) { return (*this)(0, 0); }
    if (m_columns == 2) {
        return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
    }
    double determinant = 0;
    for (int i = 0; i < m_columns; ++i) {
        linalg::Matrix newma = deleteRowCol(*this, 0, i);
        determinant += (i % 2 == 0 ? 1 : -1) * (*this)(0, i) * newma.det();
    };
    return determinant;
};


linalg::Matrix linalg::Matrix::transpose() {
    Matrix result(m_columns, m_rows);
    for (size_t i = 0; i < m_columns; ++i) {
        for (size_t j = 0; j < m_rows; ++j) {
            result(i, j) = (*this)(j, i);
        }
    }
    return result;
};

linalg::Matrix linalg::Matrix::concatenate(const Matrix& m1, const Matrix& m2) {
    if (m1.m_rows != m2.m_rows) {
        throw std::invalid_argument("different m_rows");
    }
    Matrix result(m1.m_rows, m1.m_columns + m2.m_columns);
    for (size_t i = 0; i < m1.m_rows; ++i) {
        for (size_t j = 0; j < m1.m_columns; ++j) {
            result(i, j) = m1(i, j);
        }
    }
    for (size_t i = 0; i < m2.m_rows; ++i) {
        for (size_t j = 0; j < m2.m_columns; ++j) {
            result(i, m1.m_columns + j) = m2(i, j);
        }
    }
    return result;
};

linalg::Matrix linalg::Matrix::invert(const Matrix& matr) {
    if (matr.m_rows != matr.m_columns) {
        throw std::invalid_argument("size matrix is wrong");
    }
    Matrix result(matr.m_rows, matr.m_columns);
    double determinant = matr.det();
    if (determinant == 0) {
        throw std::invalid_argument("determinant == 0");
    }
    for (size_t i = 0; i < matr.m_rows; ++i) {
        for (size_t j = 0; j < matr.m_columns; ++j) {
            linalg::Matrix spd = matr.deleteRowCol(matr, i, j);
            result(i, j) = std::pow(-1, i + j) * spd.det() / determinant;
        }
    }

    return result.transpose();
}


linalg::Matrix linalg::Matrix::power(const linalg::Matrix& m, int c) {
    Matrix result(m.m_columns, m.m_rows);
    for (size_t i = 0; i < m.m_rows; ++i) {
        for (size_t j = 0; j < m.m_columns; ++j) {
            result.m_ptr[i * m.m_columns + j] = (i == j) ? 1 : 0;
        }
    }

    for (int i = 0; i < c; ++i) {
        result = result * m;
    }
    return result;
};

