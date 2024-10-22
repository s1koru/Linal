cmake_minimum_required(VERSION 3.10)
project(matrix)
add_library(matrix "source/matrix.cpp")
target_include_directories(matrix PUBLIC include/)
