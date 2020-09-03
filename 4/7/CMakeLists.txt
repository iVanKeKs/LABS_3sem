cmake_minimum_required(VERSION 3.15)
project(7 C)

set(CMAKE_C_STANDARD 11)

add_executable(7 main.c InterpreterWithOptions.c InterpreterWithOptions.h Tree.h Tree.c)