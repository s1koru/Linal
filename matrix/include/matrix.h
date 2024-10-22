#pragma once
#include <cstddef>



namespace linalg {
    class Matrix {
    public:
        Matrix() : m_rows(0), m_columns(0), m_ptr(nullptr) {}; //��������� ����������� 
        
        Matrix(size_t rows); //����������� � ����� ����������
        
        Matrix(size_t rows, size_t columns); // ����������� � ����� �����������
        
        size_t rows() const { return m_rows; }
        
        size_t columns() const { return m_columns; }
       
        bool empty() const;

        void reshape(int rows, int cols);


        ~Matrix();
        Matrix(const Matrix& s); //����������� ����������� 
        Matrix(Matrix&& s);//����������� ����������� 
        double operator[](size_t i) { return m_ptr[i]; }


    private:
        double* m_ptr;
        size_t m_rows;
        size_t m_columns;
    };
}
