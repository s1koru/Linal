cmake_minimum_required(VERSION 3.10)
project(test_matrix)
add_subdirectory(matrix)
add_executable(proga "source/main.cpp")

target_link_libraries(proga PUBLIC matrix)
