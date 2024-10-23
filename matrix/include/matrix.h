#pragma once
#include <cstddef>
#include <initializer_list>


namespace linalg {
    class Matrix {
    public:
        //дефолтный конструктор 
        Matrix() : m_rows(0), m_columns(0), m_ptr(nullptr) {};

        //конструктор с параметрами: 
        //с одним параметром - rows 
        Matrix(size_t rows);
        //c двумя параметрами 
        Matrix(size_t rows, size_t columns);

        size_t rows() const { return m_rows; }
        size_t columns() const { return m_columns; }
        bool empty() const;
        void reshape(int rows, int cols);
        //конструктор копирования 
        Matrix(const Matrix& s);
        //конструктор перемещения 
        Matrix(Matrix&& s);
        Matrix(std::initializer_list<double> s);
        Matrix(std::initializer_list<std::initializer_list<double>> s);
        ~Matrix() { delete[] m_ptr; }

        Matrix& operator= (const Matrix& m);
        Matrix& operator= (Matrix&& m);

        double& operator()(size_t row, size_t col);
        const double& operator()(size_t row, size_t col) const;

        double& operator()(int i, int j);
        const double& operator()(int i, int j) const;
        void print() const;

        Matrix operator+ (const Matrix& matrica) const;
        Matrix operator+= (const Matrix& matrica);
        Matrix operator- (const Matrix& matrica) const;
        Matrix operator-= (const Matrix& matrica);
        Matrix operator* (const Matrix& matrica) const;
        Matrix operator*= (const Matrix& matrica);
        Matrix operator* (const double c) const;


        double trace() const;
        double norm() const;
        Matrix deleteRowCol(const linalg::Matrix& m, size_t i, size_t j) const;
        double det() const;


        Matrix transpose();

        Matrix power(const Matrix& m, int c);

        bool operator== (const Matrix& matrica) const;
        bool operator!= (const Matrix& matrica) const;
    private:
        double* m_ptr;
        size_t m_rows;
        size_t m_columns;
    };
}
