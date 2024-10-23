cmake_minimum_required(VERSION 3.10)
project(test_matrix)
set(CMAKE_CXX_STANDARD 17)
add_subdirectory(matrix)
add_executable(proga "source/main.cpp")

target_link_libraries(proga PUBLIC matrix)
