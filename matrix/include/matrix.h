#pragma once
#include <cstddef>
#include <initializer_list>



namespace linalg {
    class Matrix {
    public:
        Matrix() : m_rows(0), m_columns(0), m_ptr(nullptr) {}; //дефолтный конструктор
        Matrix(size_t rows); //конструктор с одним параметром
        Matrix(size_t rows, size_t columns); // конструктор с двумя параметрами
        
        bool empty() const;

        void reshape(int rows, int cols);

        size_t rows() const { return m_rows; }
        
        size_t columns() const { return m_columns; }
       

        Matrix(std::initializer_list<double> s);
        Matrix(std::initializer_list<std::initializer_list<double>> s);

        ~Matrix() { 
            delete[] m_ptr; 
        }

        Matrix& operator= (const Matrix& m);
        Matrix& operator= (Matrix&& m);

        double& operator()(size_t row, size_t col);
        const double& operator()(size_t row, size_t col) const;


        Matrix(const Matrix& s); //конструктор копирования 
        Matrix(Matrix&& s);//конструктор перемещения 
        double& operator()(int i, int j);
        const double& operator()(int i, int j) const;
        void print() const;

        Matrix operator+ (const Matrix& matrica) const;
        Matrix operator- (const Matrix& matrica) const;
        Matrix operator+= (const Matrix& matrica);
        Matrix operator-= (const Matrix& matrica);
        Matrix operator*= (const Matrix& matrica);
        Matrix operator* (const double c) const;


        double trace() const;
        double norm() const;

        

        bool operator== (const Matrix& matrica) const;
        bool operator!= (const Matrix& matrica) const;

    private:
        double* m_ptr;
        size_t m_rows;
        size_t m_columns;
    };
}
