cmake_minimum_required(VERSION 3.10)
project(warcaby)

set(CMAKE_CXX_STANDARD 11)

add_executable(warcaby main.cpp board.cpp board.h field.cpp field.h pionek.cpp pionek.h needed.h)