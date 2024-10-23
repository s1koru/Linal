#pragma once
#include <cstddef>
#include <initializer_list>
#include <ostream>

namespace linalg {
    class Matrix {
    public:
        //возращение количества строк
        size_t rows() const noexcept { return m_rows; }
        //возращение количество столбцов
        size_t columns() const noexcept { return m_columns; }
        bool empty() const noexcept;
        void reshape(size_t rows, size_t cols);

        //дефолтный конструктор 
        Matrix() = default;

        //конструктор с параметрами: 
        //с одним параметром - rows 
        Matrix(size_t rows);
        //c двумя параметрами 
        Matrix(size_t rows, size_t columns);
        //конструктор копирования 
        Matrix(const Matrix& s);
        //конструктор перемещения 
        Matrix(Matrix&& s) noexcept;
        //унифицированная инициализация 
        Matrix(std::initializer_list<double> s);
        Matrix(std::initializer_list<std::initializer_list<double>> s);
        ~Matrix() { delete[] m_ptr; }

        Matrix& operator= (const Matrix& m);
        Matrix& operator= (Matrix&& m) noexcept;

        double& operator()(const size_t row, const size_t col);
        const double& operator()(const size_t row, const size_t col) const;


        Matrix operator+= (const Matrix& matrica);
        Matrix operator-= (const Matrix& matrica);
        Matrix operator*= (const Matrix& matrica);
        Matrix operator*= (const double c);


        double trace() const;
        double norm() const noexcept;
        double det() const;
    private:
        double* m_ptr = nullptr;
        size_t m_rows = 0;
        size_t m_columns = 0;
    };

    const Matrix transpose(const Matrix& matrica);
    Matrix power(const Matrix& m, const int c);
    Matrix matrix_unit(size_t size);
    const Matrix concatenate(const linalg::Matrix& m1, const linalg::Matrix& m2);
    const Matrix invert(const linalg::Matrix& matr);
    const Matrix operator+ (const Matrix& m1, const Matrix& m2);
    const Matrix operator- (const Matrix& m1, const Matrix& m2);
    const Matrix operator * (double z, const Matrix& matrica);
    bool operator== (const Matrix& m1, const Matrix& m2);
    bool operator!= (const Matrix& m1, const Matrix& m2);
    const Matrix operator* (const Matrix& m1, const Matrix& m2);
    const Matrix operator* (const Matrix& m, double c);
    Matrix deleteRowCol(const linalg::Matrix& m, size_t i, size_t j);
    std::ostream& operator << (std::ostream& out, const Matrix& m);


}
