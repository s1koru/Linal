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
void testResult(bool condition, const std::string& testName, const linalg::Matrix& resultMatrix = linalg::Matrix(0, 0)) {
    if (condition) {
        std::cout << "Test " << testName << " passed.";
    }
    else {
        std::cout << "Test " << testName << " failed.";
    }

    // Если передана матрица, выводим её через перегруженный оператор <<
    if (resultMatrix.rows() > 0) {
        std::cout << " Resulting matrix:\n" << resultMatrix << std::endl;
    }
    else {
        std::cout << std::endl;  // просто перенос строки если матрицы нет
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

    testResult(result(0, 0) == 5 && result(0, 1) == 5 && result(1, 0) == 5 && result(1, 1) == 5, "Matrix addition", result);

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
    linalg::Matrix m2{ {4, 3}, {2, 1} };
    linalg::Matrix result = m1 * m2;

    testResult(result(0, 0) == 8 && result(0, 1) == 5 && result(1, 0) == 20 && result(1, 1) == 13, "Matrix multiplication", result);

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
        result(0, 1) == 4 && result(1, 1) == 5 && result(2, 1) == 6, "Matrix transpose", result);
}

void testMatrixDeterminant() {
    linalg::Matrix m{ {1, 2}, {3, 4} };
    double det = m.det();

    if (std::fabs(det + 2.0) < 1e-7) {
        std::cout << "Test Matrix determinant passed. Determinant: " << det << "\n";
    }
    else {
        std::cout << "Test Matrix determinant failed. Determinant: " << det << "\n";
    }

    try {
        // Матрица с неверным числом столбцов и строк
        linalg::Matrix m_invalid{ {1, 2, 3}, {4, 5, 6} };
        det = m_invalid.det();
        std::cout << "Test Matrix determinant invalid size failed. Determinant: " << det << "\n";
    }
    catch (const std::invalid_argument&) {  // Ловим std::invalid_argument
        std::cout << "Test Matrix determinant invalid size passed.\n";
    }
}


void testMatrixInverse() {
    linalg::Matrix m{ {4, 7}, {2, 6} };
    linalg::Matrix result = linalg::invert(m);

    testResult(areEqual(result(0, 0), 0.6) && areEqual(result(0, 1), -0.7) &&
        areEqual(result(1, 0), -0.2) && areEqual(result(1, 1), 0.4), "Matrix inversion", result);

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
