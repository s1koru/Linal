#pragma once
#include <cstddef>
namespace linalg {
    class Matrix {
    public:
        Matrix() : m_rows(0), m_columns(0), m_ptr(nullptr) {}; //дефолтный конструктор 
        Matrix(size_t rows); //конструктор с одним параметром
        Matrix(size_t rows, size_t columns); // конструктор с двум€ параметрами
        size_t rows() const { return m_rows; }
        size_t columns() const { return m_columns; }
        ~Matrix();



    private:
        double* m_ptr;
        size_t m_rows;
        size_t m_columns;
    };
}
