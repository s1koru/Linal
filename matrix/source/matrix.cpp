#include "matrix.h"
#include <iostream>
#include <stdexcept> 
#include <utility>
#include <cmath>
#include <sstream>
#include <iomanip>
bool linalg::Matrix::empty() const noexcept {
    return m_columns == 0 && m_rows == 0;
}

void linalg::Matrix::reshape(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        throw std::runtime_error("empty matrix");
    }
    if (rows * cols != m_rows * m_columns) {
        throw std::runtime_error("impossilbe to change size");
    }

    m_rows = rows;
    m_columns = cols;
}

//����������� � ����� ���������� 
linalg::Matrix::Matrix(size_t rows) : Matrix() {
    m_rows = rows;
    if (rows < 0) {
        throw std::runtime_error("impossible number of lines");
    }
    m_columns = 1;
    m_ptr = new double[rows * 1];
};

//����������� � ����� ����������� 
linalg::Matrix::Matrix(size_t rows, size_t columns) : Matrix() {
    m_rows = rows;
    m_columns = columns;
    if (rows < 0 || columns < 0) {
        throw std::runtime_error("impossible number of lines or columns");
    }
    m_ptr = new double[rows * columns];
}

//����������� �����������
linalg::Matrix::Matrix(const Matrix& s) {
    m_rows = s.m_rows;
    m_columns = s.m_columns;
    m_ptr = new double[s.m_rows * s.m_columns];
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        m_ptr[i] = s.m_ptr[i];
    }
}

//����������� �����������
linalg::Matrix::Matrix(Matrix&& s) noexcept {
    std::swap(m_ptr, s.m_ptr);
    std::swap(m_rows, s.m_rows);
    std::swap(m_columns, s.m_columns);
}

//��������������� ������������� 
linalg::Matrix::Matrix(std::initializer_list<double> s) {
    if (s.size() == 0) {
        throw std::runtime_error("initializer_list can't be empty");
    }
    m_ptr = new double[s.size()];
    m_rows = s.size();
    m_columns = 1;
    size_t i = 0;
    for (const double& el : s) {
        m_ptr[i++] = el;
    }
}

linalg::Matrix::Matrix(std::initializer_list<std::initializer_list<double>> s) {
    if (s.size() == 0 || s.begin()->size() == 0) {
        throw std::runtime_error("intilizer_list can't be empty");
    }
    m_columns = s.begin()->size();
    m_rows = s.size();
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
}

//���������� ������������
linalg::Matrix& linalg::Matrix::operator= (const Matrix& m) {
    if (this == &m) { //check m1 = m1
        return *this;
    }
    if (m.empty()) {
        throw std::runtime_error("empty matrix");
    }
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
}

//������������ ������������
linalg::Matrix& linalg::Matrix::operator= (Matrix&& m) noexcept {
    std::swap(m_ptr, m.m_ptr);
    std::swap(m_rows, m.m_rows);
    std::swap(m_columns, m.m_columns);
    return *this;
}

//��������� ������ ������� 
double& linalg::Matrix::operator() (const size_t row, const size_t cols) {
    if (row > m_rows || cols > m_columns) {
        throw std::out_of_range("out of range");
    }
    return m_ptr[row * m_columns + cols];
}

//�������� ������ ������� ��� ����������� ������� 
const double& linalg::Matrix::operator()(size_t row, size_t cols) const {
    if (row > m_rows || cols > m_columns) {
        throw std::out_of_range("size error");
    };
    return m_ptr[row * m_columns + cols];
}

//�������, ������� ����� �������� ������������ �� ����� ����� �� ���� ������� 
static size_t max_dlina_ch_of_m(const linalg::Matrix& m) {
    size_t max_number_of_digitals = 0;
    size_t cols = m.columns();
    size_t rows = m.rows();
    for (size_t i = 0; i < cols; ++i) {
        for (size_t j = 0; j < rows; ++j) {
            std::stringstream sout;
            sout << m(j, i);
            size_t dlina = sout.str().size();
            if (max_number_of_digitals < dlina) {
                max_number_of_digitals = dlina;
            }
        }
    }
    return max_number_of_digitals;
}

//�������, ������� ������� ������������ ����� ����� �� ������� �������� 
static size_t max_dlina_ch_left(const linalg::Matrix& m) {
    size_t maxim_dl_left = 0;
    size_t rows = m.rows();
    for (size_t i = 0; i < rows; ++i) {
        std::stringstream sout;
        sout << m(i, 0);
        size_t dlina = sout.str().size();
        if (maxim_dl_left < dlina) {
            maxim_dl_left = dlina;
        }
    }
    return maxim_dl_left;
}

//��������������� ����� 
std::ostream& linalg::operator << (std::ostream& out, const linalg::Matrix& m) {
    if (m.empty()) return out << "| empty matrix |";
    size_t max_number_of_digitals = max_dlina_ch_of_m(m);
    size_t maxim_left = max_dlina_ch_left(m);
    // out << std::fixed << std::setprecision(15); //������������� ����� ����� ������� 
    for (size_t i = 0; i < m.rows(); ++i) {
        out << "|";
        out << std::setw(maxim_left) << m(i, 0);
        for (size_t j = 1; j < m.columns(); ++j) {
            out << std::setw(max_number_of_digitals + 1) << m(i, j);
        }
        out << "|\n";
    }
    return out;
}

//���������
//������������ �������� ������ Matrix + Matrix = rvalue
const linalg::Matrix linalg::operator+ (const linalg::Matrix& m1, const linalg::Matrix& m2) {
    if (m1.rows() != m2.rows() || m1.columns() != m2.columns()) {
        throw std::runtime_error("matrix sizes don't match");
    }
    size_t row = m1.rows();
    size_t col = m1.columns();
    Matrix result(row, col);
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            result(i, j) = m1(i, j) + m2(i, j);
        }
    }
    return result;
}

//������������ �������� ������ Matrix += Matrix (lvalue)
linalg::Matrix linalg::Matrix::operator+= (const linalg::Matrix& m) {
    if (m_rows != m.m_rows || m_columns != m.m_columns) {
        throw std::runtime_error("matrix sizes don't match");
    }
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        m_ptr[i] += m.m_ptr[i];
    }
    return *this;
}

//������������ ��������� ������ Matrix - Matrix = result (rvalue) 
const linalg::Matrix linalg::operator- (const linalg::Matrix& m1, const linalg::Matrix& m2) {
    if (m1.rows() != m2.rows() || m1.columns() != m2.columns()) {
        throw std::runtime_error("matrix sizes don't match");
    }
    size_t row = m1.rows();
    size_t col = m1.columns();
    Matrix result(row, col);
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            result(i, j) = m1(i, j) - m2(i, j);
        }
    }
    return result;
};

//������������ ��������� ������ Matrix -= Matrix (lvalue) 
linalg::Matrix linalg::Matrix::operator-= (const linalg::Matrix& m) {
    if (m_rows != m.m_rows || m_columns != m.m_columns) {
        throw std::runtime_error("matrix sizes don't match");
    }
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        m_ptr[i] -= m.m_ptr[i];
    }
    return *this;
}

//������������ ����������� ������ Matrix * Matrix = result (rvalue)
const linalg::Matrix linalg::operator* (const Matrix& m1, const Matrix& m2) {
    if (m1.columns() != m2.rows()) {
        throw std::runtime_error("sizes matrix different");
    }
    Matrix result(m1.rows(), m2.columns());
    for (size_t i = 0; i < m1.rows(); ++i) {
        for (size_t j = 0; j < m2.columns(); ++j) {
            result(i, j) = 0;
            for (size_t l = 0; l < m2.rows(); ++l) {
                result(i, j) += m1(i, l) * m2(l, j);
            }
        }
    }
    return result;
}

//������������ ������������ �� ����� double * Matrix = result (rvalue)
const linalg::Matrix linalg::operator* (const Matrix& m, double c) {
    if (m.empty()) { throw std::runtime_error("empty matric"); }
    linalg::Matrix result(m.rows(), m.columns());
    for (size_t i = 0; i < m.rows(); ++i) {
        for (size_t j = 0; j < m.columns(); ++j) {
            result(i, j) = c * m(i, j);
        }
    }
    return result;
}

//������������ ������������ �� ����� Matrix * double = result (rvalue) 
const linalg::Matrix linalg::operator* (const double c, const Matrix& m) {
    if (m.empty()) { throw std::runtime_error("empty matric"); }
    linalg::Matrix result = m * c;
    return result;
}

//������������ ����������� ������ Matrix *= Matrix (lvalue) 
linalg::Matrix linalg::Matrix::operator*= (const Matrix& m) {
    if (m_columns != m.m_rows) { throw std::runtime_error("sizes matrix different"); }
    Matrix result(m_rows, m.m_columns);
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m.m_columns; ++j) {
            result(i, j) = 0;
            for (int l = 0; l < m_columns; ++l) {
                result(i, j) += (*this)(i, l) * m(l, j);
            }
        }
    }
    *this = std::move(result);
    return *this;
}

//������������ ������������ �� ����� Matrix *= double (lvalue)
linalg::Matrix linalg::Matrix::operator*= (const double c) {
    if (this->empty()) { throw std::runtime_error("empty matric"); }
    for (size_t i = 0; i < m_rows, m_columns; ++i) {
        m_ptr[i] = m_ptr[i] * c;
    }
    return *this;
}

//�������� ������ �� ���������� bool (Matrix == Matrix)
bool linalg::operator== (const Matrix& m1, const Matrix& m2) {
    if (m1.rows() != m2.rows() || m1.columns() != m2.columns()) return false;
    double eps = std::numeric_limits<double>::epsilon();
    for (size_t i = 0; i < m1.rows(); ++i) {
        for (size_t j = 0; j < m1.columns(); ++j) {
            if (std::abs(m1(i, j) - m2(i, j)) > eps * 1000) return false;
        }
    }
    return true;
}

//�������� ������ �� �� ���������� Matrix != Matrix (bool)
bool linalg::operator!= (const Matrix& m1, const Matrix& m2) {
    return !(m1 == m2);
}

//����� (����������) 
double linalg::Matrix::norm() const noexcept {
    double summa = 0;
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        summa += m_ptr[i] * m_ptr[i];
    }
    return sqrt(summa);
}

//����
double linalg::Matrix::trace() const {
    if (m_columns != m_rows) { throw std::runtime_error("wrong size of matric"); }
    double result = 0;
    for (size_t i = 0; i < m_rows; ++i) {
        result += (*this)(i, i);
    }
    return result;
}

//��������������� �����, ������� ������� � ������� i ������ � j ������� 
linalg::Matrix linalg::deleteRowCol(const linalg::Matrix& m, size_t i, size_t j) {
    Matrix newmatrix(m.rows() - 1, m.columns() - 1);
    size_t new_row = 0;
    for (size_t q = 0; q < m.rows(); ++q) {
        if (q == i) continue;
        size_t new_col = 0;
        for (size_t z = 0; z < m.columns(); ++z) {
            if (z == j) continue;
            newmatrix(new_row, new_col) = m(q, z);
            ++new_col;
        }
        ++new_row;
    }
    return newmatrix;
}
//������������
double linalg::Matrix::det() const {
    if (m_rows != m_columns) { throw std::invalid_argument("wrong size matrix"); }
    if (m_rows == 1) { return (*this)(0, 0); }
    if (m_columns == 2) { return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0); }
    double determinant = 0;
    for (int i = 0; i < m_columns; ++i) {
        linalg::Matrix newma = deleteRowCol(*this, 0, i);
        determinant += (i % 2 == 0 ? 1 : -1) * (*this)(0, i) * newma.det();
    };
    return determinant;
}

//�������
//��������� ������ � ����� 
const linalg::Matrix linalg::concatenate(const Matrix& m1, const Matrix& m2) {
    if (m1.empty() && m2.empty()) throw std::runtime_error("two matrixs are empty");
    if (m1.empty()) return m2;
    if (m2.empty()) return m1;

    Matrix result(m1.rows(), m1.columns() + m2.columns());
    for (size_t i = 0; i < m1.rows(); ++i) {
        for (size_t j = 0; j < m1.columns() + m2.columns(); ++j) {
            if (j < m1.columns()) result(i, j) = m1(i, j);
            else result(i, j) = m2(i, j - m1.columns());
        }
    }
    return result;
}

//����������������
const linalg::Matrix linalg::transpose(const Matrix& m) {
    Matrix result(m.columns(), m.rows());
    for (size_t i = 0; i < m.columns(); ++i) {
        for (size_t j = 0; j < m.rows(); ++j) {
            result(i, j) = m(j, i);
        }
    }
    return result;
}

//�������� �������
const linalg::Matrix linalg::invert(const Matrix& m) {
    if (m.empty()) throw std::runtime_error("empty matrix");
    if (m.rows() != m.columns()) throw std::runtime_error("m_rows != m_columns");
    double eps = std::numeric_limits<double>::epsilon();
    double determinant = m.det();
    if (std::abs(determinant - 0) < eps * 1000) throw std::runtime_error("determinant == 0");
    Matrix result(m.rows(), m.columns());
    for (size_t i = 0; i < m.rows(); ++i) {
        for (size_t j = 0; j < m.columns(); ++j) {
            linalg::Matrix spd = deleteRowCol(m, i, j);
            result(i, j) = std::pow(-1, i + j) * spd.det() / determinant;
        }
    }
    return transpose(result);
}

//��������� ������� 
linalg::Matrix linalg::matrix_unit(size_t size) {
    if (size == 0) throw std::runtime_error("matrix is empty");
    linalg::Matrix m(size, size);
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; ++j) {
            if (i == j) m(i, j) = 1;
            else m(i, j) == 0;
        }
    }
    return m;
}

//���������� � �������
linalg::Matrix linalg::power(const Matrix& m, const int c) {
    if (m.empty()) { throw std::runtime_error("matrix is empty"); }
    if (m.rows() != m.columns()) { throw std::runtime_error("size is wrong"); }
    linalg::Matrix result(m);
    if (c == 0) { result = matrix_unit(m.rows()); }
    else if (c < 0) { result = invert(m); }
    else { result = m; }
    linalg::Matrix result2 = result;
    for (int i = 1; i < abs(c); i++) {
        result = result * result2;
    }
    return result;
}


// linalg::Matrix linalg::Matrix::U(const Matrix& m) { 
//     Matrix u(m);
//     for (size_t i = 0; i < m.m_rows; ++i) { 
//         for (size_t j = 0; j < m.m_columns; ++j) { 
//             u(i, j) = m(i, j);
//         }
//     }

//     for (size_t col = 0; col < m.m_columns; ++col) { 
//         for (size_t row = col+1; row < m.m_rows; ++row) { 
//             double value = u(row, col) / u(col, col);
//             double prom = round(value*10)/10.0;
//             for (size_t col2 = col; col2 < m.m_columns; ++col2) { 
//                 double el =  u(row, col2)- u(col, col2)*prom;
//                 u(row, col2) = el;
//             }
//         }
//     }
//     return u;
// };

