#include "matrix.h"
#include <iostream>
#include <stdexcept> 
#include <utility>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <limits>

bool linalg::Matrix::empty() const noexcept {
    return m_columns == 0 && m_rows == 0;
}

void linalg::Matrix::reshape(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        throw std::runtime_error("empty matrix");
    }
    m_rows = rows;
    m_columns = cols;
}

//конструктор с одним параметром 
linalg::Matrix::Matrix(size_t rows) : Matrix() {
    m_rows = rows;
    if (rows == 0) {
        m_ptr = nullptr;
        m_columns = m_rows = 0;
        return;
    }
    m_columns = 1;
    m_ptr = new double[rows * 1];
};

//конструктор с двумя параметрами 
linalg::Matrix::Matrix(size_t rows, size_t columns) : Matrix(){
    if (rows == 0 || columns == 0) {
        m_ptr = nullptr;
        m_columns = m_rows = 0;
        return;
    }
    m_rows = rows; 
    m_columns = columns;
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


//функция, которая находит максимальную длину числа из первого столбика 
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
// Вспомогательные функции для вычисления длины чисел (для красивого форматирования)
size_t max_dlina_ch_of_m(const linalg::Matrix& m) {
    double max_value = 0;
    for (size_t i = 0; i < m.rows(); ++i) {
        for (size_t j = 0; j < m.columns(); ++j) {
            double value = std::fabs(m(i, j));
            if (value > max_value) {
                max_value = value;
            }
        }
    }
    return static_cast<size_t>(std::ceil(std::log10(max_value + 1)));  // Максимальное количество цифр в числе
}


// Перегрузка оператора <<
std::ostream& linalg::operator<<(std::ostream& out, const linalg::Matrix& m) {
    if (m.empty()) return out << "| empty matrix |";

    size_t max_number_of_digitals = max_dlina_ch_of_m(m);
    size_t maxim_left = max_dlina_ch_left(m);

    out << std::fixed << std::setprecision(3);  // Фиксированное количество знаков после запятой (3)

    for (size_t i = 0; i < m.rows(); ++i) {
        out << "|";  // Начало строки
        out << std::setw(maxim_left + 3) << m(i, 0);  // Первый элемент строки с отступом

        for (size_t j = 1; j < m.columns(); ++j) {
            out << std::setw(max_number_of_digitals + 6) << m(i, j);  // Остальные элементы с большим отступом
        }

        out << " |\n";  // Конец строки
    }

    return out;
}

//ОПЕРАТОРЫ
//поэлементное сложение матриц Matrix + Matrix = rvalue
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

//поэлементное сложение матриц Matrix += Matrix (lvalue)
linalg::Matrix linalg::Matrix::operator+= (const linalg::Matrix& m) {
    if (m_rows != m.m_rows || m_columns != m.m_columns) {
        throw std::runtime_error("matrix sizes don't match");
    }
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        m_ptr[i] += m.m_ptr[i];
    }
    return *this;
}

//поэлементное вычитание матриц Matrix - Matrix = result (rvalue) 
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

//Поэлементное вычитание матриц Matrix -= Matrix (lvalue) 
linalg::Matrix linalg::Matrix::operator-= (const linalg::Matrix& m) {
    if (m_rows != m.m_rows || m_columns != m.m_columns) {
        throw std::runtime_error("matrix sizes don't match");
    }
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        m_ptr[i] -= m.m_ptr[i];
    }
    return *this;
}

//перемножение совместимых матриц Matrix * Matrix = result (rvalue)
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

//поэлементное перемножение на число double * Matrix = result (rvalue)
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

//поэлементное перемножение на число Matrix * double = result (rvalue) 
const linalg::Matrix linalg::operator* (const double c, const Matrix& m) {
    if (m.empty()) { throw std::runtime_error("empty matric"); }
    linalg::Matrix result = m * c;
    return result;
}

//перемножение совместимых матриц Matrix *= Matrix (lvalue) 
linalg::Matrix linalg::Matrix::operator*= (const Matrix& m) {
    if (m.empty()) { throw std::runtime_error("matrix is empty"); }
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

//поэлементное перемножение на число Matrix *= double (lvalue)
linalg::Matrix linalg::Matrix::operator*= (const double c) {
    if (this->empty()) {
        throw std::runtime_error("empty matrix");
    }

    for (size_t i = 0; i < m_rows; ++i) {
        for (size_t j = 0; j < m_columns; ++j) {
            m_ptr[i * m_columns + j] *= c;  // Изменяем элемент на m_ptr[i][j] *= c
        }
    }

    return *this;
}


bool linalg::operator== (const Matrix& m1, const Matrix& m2) {
    // Проверка на равенство количества строк и столбцов
    if (m1.rows() != m2.rows() || m1.columns() != m2.columns()) return false;

    // Задаём точность сравнения
    double eps = std::numeric_limits<double>::epsilon();

    // Сравнение всех элементов с учётом допустимой погрешности
    for (size_t i = 0; i < m1.rows(); ++i) {
        for (size_t j = 0; j < m1.columns(); ++j) {
            if (std::abs(m1(i, j) - m2(i, j)) > eps * 1e7) {  // Корректируем допустимую погрешность
                return false;
            }
        }
    }

    // Если все элементы совпали в пределах погрешности, матрицы считаются равными
    return true;
}
//проверка матриц на НЕ совпадение Matrix != Matrix (bool)
bool linalg::operator!= (const Matrix& m1, const Matrix& m2) {
    return !(m1 == m2);
}

//Норма (Фробениуса) 
double linalg::Matrix::norm() const noexcept {
    double summa = 0;
    for (size_t i = 0; i < m_rows * m_columns; ++i) {
        summa += m_ptr[i] * m_ptr[i];
    }
    return sqrt(summa);
}

//След
double linalg::Matrix::trace() const {
    if (m_columns != m_rows) { throw std::runtime_error("wrong size of matric"); }
    double result = 0;
    for (size_t i = 0; i < m_rows; ++i) {
        result += (*this)(i, i);
    }
    return result;
}

//вспомогательный метод, который удаляет у матрицы i строку и j столбей 
linalg::Matrix linalg::deleteRowCol(const linalg::Matrix& m, size_t i, size_t j) {
    if (m.empty()) { throw std::runtime_error("matrix is empty"); }
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
//Определитель
double linalg::Matrix::det() const {
    if (m_rows != m_columns) {
        throw std::invalid_argument("Matrix must be square");
    }
    if (m_rows == 1) {
        return (*this)(0, 0);
    }
    if (m_columns == 2) {
        return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
    }
    double determinant = 0;
    for (int i = 0; i < m_columns; ++i) {
        linalg::Matrix newma = deleteRowCol(*this, 0, i);
        determinant += (i % 2 == 0 ? 1 : -1) * (*this)(0, i) * newma.det();
    }
    return determinant;
}


//ФУНКЦИИ
//Соединить правую и левую 
const linalg::Matrix linalg::concatenate (const Matrix & m1, const Matrix& m2){
	size_t rows1 = m1.rows();
	size_t rows2 = m2.rows();
	size_t cols1 = m1.columns();
	size_t cols2 = m2.columns();

	if (rows1 != rows2) {
		throw std::invalid_argument("Matrix1 and Matrix2 should have same number of rows");
	}
	linalg::Matrix newMatrix(rows1, cols1 + cols2);
	for (size_t i = 0; i < rows1;++i) {
		for (size_t j = 0; j < cols1; ++j) {
			newMatrix(i, j) = m1(i, j);
		}
		for (size_t j = 0; j < cols2; ++j) {
			newMatrix(i, j+cols1) = m2(i, j);
		}
	}
	return newMatrix;
}



//Транспонирование
const linalg::Matrix linalg::transpose(const Matrix& m) {
    if (m.empty()) { throw std::runtime_error("matrix is empty"); }
    Matrix result(m.columns(), m.rows());
    for (size_t i = 0; i < m.columns(); ++i) {
        for (size_t j = 0; j < m.rows(); ++j) {
            result(i, j) = m(j, i);
        }
    }
    return result;
}

//Обратная матрица
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

//единичная матрица 
linalg::Matrix linalg::matrix_unit(size_t size) {
    if (size == 0) throw std::runtime_error("matrix is empty");
    linalg::Matrix m(size, size);
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; ++j) {
            if (i == j) m(i, j) = 1;
            else m(i, j) = 0;
        }
    }
    return m;
}

//Возведение в степень
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

void linalg::Matrix::gaussianElimination() {
    for (size_t i = 0; i < m_rows; ++i) {
        // Поиск максимального элемента в текущем столбце
        size_t maxRow = i;
        for (size_t k = i + 1; k < m_rows; ++k) {
            if (std::fabs(m_ptr[k * m_columns + i]) > std::fabs(m_ptr[maxRow * m_columns + i])) {
                maxRow = k;
            }
        }

        // Обмен текущей строкой с максимальной, если maxRow изменился
        if (maxRow != i) {
            for (size_t k = 0; k < m_columns; ++k) {
                // Обмен элементов строк
                std::swap(m_ptr[maxRow * m_columns + k], m_ptr[i * m_columns + k]);
            }
        }

        // Проверка на нулевой элемент на главной диагонали
        //if (std::fabs(m_ptr[i * m_columns + i]) < 1e-10) { // Используем небольшой порог
          //  throw std::runtime_error("Matrix is singular and cannot be solved.");
        //}

        // Приведение строк ниже к 0
        for (size_t k = i + 1; k < m_rows; ++k) {
            double factor = m_ptr[k * m_columns + i] / m_ptr[i * m_columns + i];
            for (size_t j = i; j < m_columns; ++j) {
                m_ptr[k * m_columns + j] -= factor * m_ptr[i * m_columns + j];
            }
        }

        // Вывод состояния матрицы после текущего шага
       // std::cout << "Step " << i + 1 << ":\n" << *this << "\n"; // Предполагается, что оператор вывода << перегружен
    }
}
size_t linalg::Matrix::rank() const {
    // Проверка на пустую матрицу
    if (m_rows == 0 || m_columns == 0) {
        throw std::invalid_argument("Matrix is empty. Rank cannot be determined.");
    }

    // Создание копии матрицы, чтобы не изменять оригинал
    linalg::Matrix temp(*this);

    try {
        temp.gaussianElimination(); // Приведение к ступенчатому виду
    }
    catch (const std::runtime_error& e) {
        throw std::runtime_error("Error during Gaussian elimination: " + std::string(e.what()));
    }

    size_t rank = 0;
    for (size_t i = 0; i < temp.m_rows; ++i) {
        bool isZeroRow = true;

        // Проверка, является ли строка нулевой
        for (size_t j = 0; j < temp.m_columns; ++j) {
            if (std::fabs(temp.m_ptr[i * temp.m_columns + j]) > 1e-9) { // Используем допустимую погрешность
                isZeroRow = false;
                break;
            }
        }

        if (!isZeroRow) {
            rank++; // Увеличиваем ранг, если строка ненулевая
        }
    }

    return rank;
}
