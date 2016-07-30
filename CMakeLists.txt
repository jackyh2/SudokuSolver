cmake_minimum_required(VERSION 3.5.0)
set (CMAKE_CXX_STANDARD 11)
project (SudokuSolver)
add_executable(SudokuSolver main.cpp grid.cpp node.cpp DLX.cpp)
