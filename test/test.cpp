#include <iostream>
#include <cmath>
#include <stdexcept>
#include "matrix.h"  // Заголовочный файл для работы с матрицами
#include "test.h"    // Заголовочный файл с объявлениями тестов

// Функция для проверки равенства действительных чисел с учетом погрешности
bool areEqual(double a, double b, double epsilon = 1e-7) {
    return std::fabs(a - b) < epsilon;
}

// Вспомогательная функция для вывода результата теста
void testResult(bool condition, const std::string& testName) {
    if (condition) {
        std::cout << "Test " << testName << " passed." << std::endl;
    }
    else {
        std::cout << "Test " << testName << " failed." << std::endl;
    }
}

void testMatrixConstructor() {
    linalg::Matrix m1(2, 3);
    testResult(m1.rows() == 2 && m1.columns() == 3, "Matrix constructor (2x3)");

    try {
        linalg::Matrix m2(0, 3);
        testResult(false, "Matrix constructor invalid size");
    }
    catch (const std::runtime_error&) {
        testResult(true, "Matrix constructor invalid size");
    }
}

void testMatrixAddition() {
    linalg::Matrix m1{ {1, 2}, {3, 4} };
    linalg::Matrix m2{ {4, 3}, {2, 1} };
    linalg::Matrix result = m1 + m2;

    testResult(result(0, 0) == 5 && result(0, 1) == 5 && result(1, 0) == 5 && result(1, 1) == 5, "Matrix addition");

    try {
        linalg::Matrix m3{ {1, 2} };
        result = m1 + m3;
        testResult(false, "Matrix addition invalid sizes");
    }
    catch (const std::runtime_error&) {
        testResult(true, "Matrix addition invalid sizes");
    }
}

void testMatrixMultiplication() {
    linalg::Matrix m1{ {1, 2}, {3, 4} };
    linalg::Matrix m2{ {2, 0}, {1, 2} };
    linalg::Matrix result = m1 * m2;

    testResult(result(0, 0) == 4 && result(0, 1) == 4 && result(1, 0) == 10 && result(1, 1) == 8, "Matrix multiplication");

    try {
        linalg::Matrix m3{ {1, 2} };
        result = m1 * m3;
        testResult(false, "Matrix multiplication invalid sizes");
    }
    catch (const std::runtime_error&) {
        testResult(true, "Matrix multiplication invalid sizes");
    }
}

void testMatrixTranspose() {
    linalg::Matrix m{ {1, 2, 3}, {4, 5, 6} };
    linalg::Matrix result = linalg::transpose(m);

    testResult(result(0, 0) == 1 && result(1, 0) == 2 && result(2, 0) == 3 &&
        result(0, 1) == 4 && result(1, 1) == 5 && result(2, 1) == 6, "Matrix transpose");
}

void testMatrixDeterminant() {
    linalg::Matrix m{ {1, 2}, {3, 4} };
    double det = m.det();

    testResult(areEqual(det, -2.0), "Matrix determinant");

    try {
        linalg::Matrix m_invalid{ {1, 2, 3}, {4, 5, 6} };
        det = m_invalid.det();
        testResult(false, "Matrix determinant invalid size");
    }
    catch (const std::runtime_error&) {
        testResult(true, "Matrix determinant invalid size");
    }
}

void testMatrixInverse() {
    linalg::Matrix m{ {4, 7}, {2, 6} };
    linalg::Matrix result = linalg::invert(m);

    testResult(areEqual(result(0, 0), 0.6) && areEqual(result(0, 1), -0.7) &&
        areEqual(result(1, 0), -0.2) && areEqual(result(1, 1), 0.4), "Matrix inversion");

    try {
        linalg::Matrix singular{ {1, 2}, {2, 4} };
        result = linalg::invert(singular);
        testResult(false, "Matrix inversion singular");
    }
    catch (const std::runtime_error&) {
        testResult(true, "Matrix inversion singular");
    }
}

// Функция для запуска всех тестов
void runAllTests() {
    testMatrixConstructor();
    testMatrixAddition();
    testMatrixMultiplication();
    testMatrixTranspose();
    testMatrixDeterminant();
    testMatrixInverse();
}