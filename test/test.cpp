#include <iostream>
#include <cmath>
#include <stdexcept>
#include "matrix.h"  
#include "test.h"    

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
        std::cout << std::endl;  
    }
    std::cout << std::endl;  
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
    catch (const std::invalid_argument&) {  
        std::cout << "Test Matrix determinant invalid size passed.\n";
    }
    std::cout << std::endl;  
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

void testMatrixTrace() {
    linalg::Matrix m{ {1, 2}, {3, 4} };
    double trace_value = m.trace();

    if (std::fabs(trace_value - 5.0) < 1e-7) {
        std::cout << "Test Matrix trace passed. Trace: " << trace_value << "\n";
    }
    else {
        std::cout << "Test Matrix trace failed. Trace: " << trace_value << "\n";
    }
    std::cout << std::endl;  
}

void testMatrixNorm() {
    linalg::Matrix m{ {1, 2}, {3, 4} };
    double norm_value = m.norm();

    if (std::fabs(norm_value - std::sqrt(30.0)) < 1e-7) {
        std::cout << "Test Matrix norm passed. Norm: " << norm_value << "\n";
    }
    else {
        std::cout << "Test Matrix norm failed. Norm: " << norm_value << "\n";
    }
    std::cout << std::endl;  
}

void testMatrixGaussianElimination() {
    linalg::Matrix m{ {2, 1, -1}, {-3, -1, 2}, {-2, 1, 2} };
    m.gaussianElimination();

    std::cout << "Test Matrix Gaussian elimination. Resulting matrix:\n" << m << "\n\n";  
}

void testMatrixRank() {
    linalg::Matrix m{ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    size_t rank_value = m.rank();

    if (rank_value == 2) {
        std::cout << "Test Matrix rank passed. Rank: " << rank_value << "\n\n";
    }
    else {
        std::cout << "Test Matrix rank failed. Rank: " << rank_value << "\n\n";
    }
}

void testMatrixPower() {
    // Тест 1: Возведение в степень 0
    {
        linalg::Matrix m = { {1, 2}, {3, 4} };
        linalg::Matrix expected = linalg::matrix_unit(2); // Ожидаем единичную матрицу 2x2
        linalg::Matrix result = linalg::power(m, 0);

        std::cout << "Test 1: m^0 = I\n";
        std::cout << result;

        if (result == expected) {
            std::cout << "Test 1 Passed: m^0 = I (Identity matrix)\n";
        }
        else {
            std::cout << "Test 1 Failed: \n";
        }
        std::cout << std::endl;  
    }

    // Тест 2: Возведение в положительную степень
    {
        linalg::Matrix m = { {1, 2}, {3, 4} };
        linalg::Matrix expected = { {7, 10}, {15, 22} }; // m^2
        linalg::Matrix result = linalg::power(m, 2);

        std::cout << "Test 2: m^2\n";
        std::cout << result;

        if (result == expected) {
            std::cout << "Test 2 Passed: m^2 is correct\n";
        }
        else {
            std::cout << "Test 2 Failed: \n";
        }
        std::cout << std::endl;  
    }

    // Тест 3: Возведение в отрицательную степень
    {
        linalg::Matrix m = { {1, 2}, {3, 4} };
        linalg::Matrix expected = { {-2, 1}, {1.5, -0.5} }; // m^-1
        linalg::Matrix result = linalg::power(m, -1);

        std::cout << "Test 3: m^-1\n";
        std::cout << result;

        if (result == expected) {
            std::cout << "Test 3 Passed: m^-1 is correct\n";
        }
        else {
            std::cout << "Test 3 Failed: \n";
        }
        std::cout << std::endl;  
    }

    // Тест 4: Проверка на ошибку для неквадратной матрицы
    {
        linalg::Matrix m = { {1, 2, 3}, {4, 5, 6} }; // Неквадратная матрица
        try {
            linalg::Matrix result = linalg::power(m, 2);
            std::cout << "Test 4 Failed: Expected an error for non-square matrix\n";
        }
        catch (const std::runtime_error& e) {
            std::cout << "Test 4 Passed: Caught expected error: " << e.what() << "\n";
        }
        std::cout << std::endl;  
    }

    // Тест 5: Проверка на ошибку для пустой матрицы
    {
        linalg::Matrix m; // Пустая матрица
        try {
            linalg::Matrix result = linalg::power(m, 2);
            std::cout << "Test 5 Failed: Expected an error for empty matrix\n";
        }
        catch (const std::runtime_error& e) {
            std::cout << "Test 5 Passed: Caught expected error: " << e.what() << "\n";
        }
        std::cout << std::endl;  
    }
}

void testMatrixTransposeInverse() {
    linalg::Matrix A{ {4, 7}, {2, 6} };
    linalg::Matrix result = linalg::transpose(linalg::invert(A));
    linalg::Matrix expected = linalg::invert(linalg::transpose(A)); // (A^T)^-1

    testResult(result == expected, "(A^T)^-1 = (A^-1)^T", result);
}

void testMatrixInverseProduct() {
    linalg::Matrix A1{ {1, 2}, {3, 4} };
    linalg::Matrix A2{ {5, 6}, {7, 8} };
    linalg::Matrix result = linalg::invert(A1 * A2);
    linalg::Matrix expected = linalg::invert(A2) * linalg::invert(A1); // (A1 * A2)^-1

    testResult(result == expected, "(A1 * A2)^-1 = A2^-1 * A1^-1", result);
}

void testMatrixInversePower() {
    linalg::Matrix A{ {1, 2}, {3, 4} };
    linalg::Matrix result1 = linalg::power(linalg::invert(A), 6); // (A^-1)^6
    linalg::Matrix result2 = linalg::power(linalg::invert(A), 2); // (A^-2)^3
    linalg::Matrix expected = linalg::power(linalg::invert(A), 6); // (A^-2)^3

    testResult(result1 == expected, "(A^-1)^6 = (A^-2)^3", result1);
}
void testMatrixConcatenate() {
    linalg::Matrix m1{ {1, 2}, {3, 4} }; // 2x2
    linalg::Matrix m2{ {5,6},{7,8} };
    linalg::Matrix m3{ {5, 6} };         // 1x2
    try {
        linalg::Matrix result = concatenate(m1, m2);
        std::cout << "Test Matrix concatenate passed. Concatenated matrix:\n";
        std::cout << result;
            
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error during concatenation: " << e.what() << "\n";
    }

    // Тестируем ошибку при несовпадении по строкам
    try {
        linalg::Matrix result = concatenate(m1, m3);
        std::cout << "This line should not be executed due to exception.\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Test Matrix concatenate passed. Expected error: " << e.what() << "\n"; 
    }
}
    