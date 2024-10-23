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
    m_rows = rows;
    m_columns = cols;
    if (rows * cols != m_rows * m_columns) {
        throw std::runtime_error("impossilbe to change size");
    }
}

//конструктор с одним параметром 
linalg::Matrix::Matrix(size_t rows) : Matrix() {
    m_rows = rows;
    if (rows < 0) {
        throw std::runtime_error("impossible number of lines");
    }
    m_columns = 1;
    m_ptr = new double[rows * 1];
};

//конструктор с двумя параметрами 
linalg::Matrix::Matrix(size_t rows, size_t columns) : Matrix() {
    m_rows = rows;
    m_columns = columns;
    if (rows < 0 || columns < 0) {
        throw std::runtime_error("impossible number of lines or columns");
    }
    m_ptr = new double[rows * columns];
}

//конструктор копирования
linalg::Matrix::Matrix(const Matrix& s) {
    m_rows = s.m_rows;
    m_columns = s.m_columns;
    m_ptr = new double[s.m_rows * s.m_columns];
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        m_ptr[i] = s.m_ptr[i];
    }
}

//конструктор перемещения
linalg::Matrix::Matrix(Matrix&& s) noexcept {
    std::swap(m_ptr, s.m_ptr);
    std::swap(m_rows, s.m_rows);
    std::swap(m_columns, s.m_columns);
}

//унифицированная инициализация 
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

//копирующее присваивание
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

//перемещающее присваивание
linalg::Matrix& linalg::Matrix::operator= (Matrix&& m) noexcept {
    std::swap(m_ptr, m.m_ptr);
    std::swap(m_rows, m.m_rows);
    std::swap(m_columns, m.m_columns);
    return *this;
}

//операторы вызова функции 
double& linalg::Matrix::operator() (const size_t row, const size_t cols) {
    if (row > m_rows || cols > m_columns) {
        throw std::out_of_range("out of range");
    }
    return m_ptr[row * m_columns + cols];
}

//оператор вызова функции для константной матрицы 
const double& linalg::Matrix::operator()(size_t row, size_t cols) const {
    if (row > m_rows || cols > m_columns) {
        throw std::out_of_range("size error");
    };
    return m_ptr[row * m_columns + cols];
}

//функция, которая будет находить максимальное по длине число из всей матрицы 
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
//форматированный вывод 
std::ostream& linalg::operator << (std::ostream& out, const linalg::Matrix& m) {
    if (m.empty()) return out << "| empty matrix |";
    size_t max_number_of_digitals = max_dlina_ch_of_m(m);
    size_t maxim_left = max_dlina_ch_left(m);
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


// linalg::Matrix linalg::Matrix::operator+ (const linalg::Matrix &matrica) const {
//     if (m_rows != matrica.m_rows || m_columns != matrica.m_columns) { 
//         throw std::invalid_argument("matrix sizes don't match");
//     }
//     Matrix conclusion(m_rows, m_columns); 
//     for (size_t i = 0; i < m_rows * m_columns; ++i) { 
//         conclusion.m_ptr[i] = m_ptr[i] + matrica.m_ptr[i];
//     }
//     return conclusion; 
// };

// linalg::Matrix linalg::Matrix::operator+= (const linalg::Matrix &matrica) { 
//     if (m_rows != matrica.m_rows || m_columns != matrica.m_columns) { 
//         throw std::invalid_argument("matrix sizes don't match");
//     }
//     for (size_t i = 0; i < m_rows * m_columns; ++i) { 
//         this->m_ptr[i] += matrica.m_ptr[i];
//     }
//     return *this;
// };

// linalg::Matrix linalg::Matrix::operator- (const linalg::Matrix &matrica) const {
//     if (m_rows != matrica.m_rows || m_columns != matrica.m_columns) { 
//         throw std::invalid_argument("matrix sizes don't match");
//     }
//     Matrix conclusion(m_rows, m_columns); 
//     for (size_t i = 0; i < m_rows * m_columns; ++i) { 
//         conclusion.m_ptr[i] = m_ptr[i] - matrica.m_ptr[i];
//     }
//     return conclusion; 
// };

// linalg::Matrix linalg::Matrix::operator-= (const linalg::Matrix &matrica) { 
//     if (m_rows != matrica.m_rows || m_columns != matrica.m_columns) { 
//         throw std::invalid_argument("matrix sizes don't match");
//     }
//     for (size_t i = 0; i < m_rows * m_columns; ++i) { 
//         this->m_ptr[i] -= matrica.m_ptr[i];
//     }
//     return *this;
// };

// linalg::Matrix linalg::Matrix::operator* (const linalg::Matrix &matrica) const { 
//     if (m_columns != matrica.m_rows) { 
//         throw std::invalid_argument("sizes matrix different");
//     }
//     Matrix conclusion(m_rows, matrica.m_columns);
//     for (int i = 0; i < m_rows; ++i) { 
//         for (int j = 0; j < matrica.m_columns; ++j) { 
//             conclusion(i, j) = 0; 
//             for (int l = 0; l < m_columns; ++l) { 
//                 conclusion(i, j) += (*this)(i, l) * matrica(l, j);
//             }
//         }
//     }
//     return conclusion;
// }

// linalg::Matrix linalg::Matrix::operator*= (const linalg::Matrix &matrica) { 
//     if (m_columns != matrica.m_rows) { 
//         throw std::invalid_argument("sizes matrix different");
//     }
//     Matrix conclusion(m_rows, matrica.m_columns);
//     for (int i = 0; i < m_rows; ++i) { 
//         for (int j = 0; j < matrica.m_columns; ++j) { 
//             conclusion(i, j) = 0; 
//             for (int l = 0; l < m_columns; ++l) { 
//                 conclusion(i, j) += (*this)(i, l) * matrica(l, j);
//             }
//         }
//     }
//     *this = std::move(conclusion);
//     return *this;
// }

// linalg::Matrix linalg::Matrix::operator* (const double c){ 
//     if (empty()) {throw std::invalid_argument("empty matric");}

//     linalg::Matrix result(m_rows, m_columns); 
//     for (size_t i = 0; i < m_rows*m_columns; ++i) { 
//         result.m_ptr[i] = c * m_ptr[i]; 
//     }
//     return result;
// }; 

// linalg::Matrix operator* (const linalg::Matrix& matrica, double c) { 
//     linalg::Matrix result = matrica * c;
// };

// bool linalg::Matrix::operator== (const linalg::Matrix &matrica) const { 
//     if (m_rows != matrica.m_rows || m_columns != matrica.m_columns) { 
//         return false;
//     }
//     for (size_t i = 0; i < matrica.m_rows*matrica.m_columns; ++i) { 
//         if (m_ptr[i] != matrica.m_ptr[i]) { 
//             return false;
//         }
//     }
//     return true;
// };

// double& linalg::Matrix::operator() (int i, int j) { 
//     return *(m_ptr + i * m_columns + j);
// };

// const double& linalg::Matrix::operator()(int i, int j) const { 
//     return *(m_ptr + i * m_columns + j);
// };


// bool linalg::Matrix::operator!= (const linalg::Matrix &matrica) const { 
//     if (m_rows != matrica.m_rows || m_columns != matrica.m_columns) { 
//         return true;
//     }
//     for (size_t i = 0; i < matrica.m_rows*matrica.m_columns; ++i) { 
//         if (m_ptr[i] != matrica.m_ptr[i]) { 
//             return true;
//         }
//     }
//     return false;
// }

// double linalg::Matrix::trace() const { 
//     if (m_columns != m_rows) { 
//         throw std::invalid_argument("wrong size of matric");
//     }
//     double result = 0;
//     for (size_t i = 0; i < m_rows; ++i) { 
//         result += *(m_ptr + i*m_columns + i);}
//     return result;
// };

// double linalg::Matrix::norm() const { 
//     double summa = 0; 
//     for (size_t i = 0; i < m_rows * m_columns; ++i) { 
//         summa += m_ptr[i]*m_ptr[i]; 
//     }
//     return sqrt(summa);
// };

// linalg::Matrix linalg::Matrix::deleteRowCol(const linalg::Matrix& m, size_t i, size_t j) const{ 
//     Matrix newmatrix(m.m_rows-1, m.m_columns -1);
//     size_t new_row = 0; 
//     for (size_t q = 0; q < m.m_rows; ++q) { 
//         if (q == i) continue;
//         size_t new_col = 0;
//         for (size_t z = 0; z < m.m_columns; ++z) { 
//             if (z == j) continue;
//             newmatrix(new_row, new_col) = m(q, z);
//             ++new_col;
//         }
//         ++new_row;
//     }
//     return newmatrix;
// };

// double linalg::Matrix::det() const { 
//     if (m_rows != m_columns) { 
//         throw std::invalid_argument("wrong size matrix");
//     }

//     if (m_rows == 1) {return (*this)(0, 0);}
//     if (m_columns == 2) {
//         return (*this)(0, 0)*(*this)(1, 1) - (*this)(0, 1)*(*this)(1,0);}
//     double determinant = 0;
//     for (int i = 0; i < m_columns; ++i) { 
//         linalg::Matrix newma = deleteRowCol(*this, 0, i); 
//         determinant += (i % 2 == 0 ? 1 : -1) * (*this)(0, i) * newma.det();
//     };
//     return determinant;
// }; 

// linalg::Matrix linalg::Matrix::concatenate(const Matrix& m1, const Matrix& m2) { 
//     if (m1.m_rows != m2.m_rows) { 
//         throw std::invalid_argument("different m_rows");
//     }
//     Matrix result(m1.m_rows, m1.m_columns + m2.m_columns);
//     for (size_t i = 0; i < m1.m_rows; ++i) { 
//         for (size_t j = 0; j < m1.m_columns; ++j) { 
//             result(i, j) = m1(i, j); 
//         }
//     }
//     for (size_t i = 0; i < m2.m_rows; ++i) { 
//         for (size_t j = 0; j < m2.m_columns; ++j) { 
//             result(i, m1.m_columns + j) =  m2(i, j);
//         }
//     }
//     return result; 
// }; 

// linalg::Matrix linalg::Matrix::transpose() { 
//     Matrix result(m_columns, m_rows); 
//     for (size_t i = 0; i < m_columns; ++i) { 
//         for (size_t j = 0; j < m_rows; ++j) { 
//             result(i, j) = (*this)(j, i);
//         }
//     }
//     return result; 
// }; 

// linalg::Matrix linalg::Matrix::invert(const Matrix& matr) { 
//     if (matr.m_rows != matr.m_columns) { 
//         throw std::invalid_argument("size matrix is wrong");
//     }
//     Matrix result(matr.m_rows, matr.m_columns);
//     double determinant = matr.det();
//     if (determinant == 0) { 
//         throw std::invalid_argument("determinant == 0");
//     }
//     for (size_t i = 0; i < matr.m_rows; ++i) { 
//         for (size_t j = 0; j < matr.m_columns; ++j) { 
//             linalg::Matrix spd = matr.deleteRowCol(matr,i, j);
//             result(i, j) = std::pow(-1,i+j) * spd.det() / determinant;
//         }
//     }

//     return result.transpose();
// }

// linalg::Matrix linalg::Matrix::power(const linalg::Matrix& m, int c) { 
//     Matrix result(m.m_columns, m.m_rows); 
//     for (size_t i = 0; i < m.m_rows; ++i) {
//         for (size_t j = 0; j < m.m_columns; ++j) {
//             result.m_ptr[i * m.m_columns + j] = (i == j) ? 1 : 0;
//         }
//     }

//     for (int i = 0; i < c; ++i) { 
//         result = result * m;
//     }
//     return result; 
// };

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
