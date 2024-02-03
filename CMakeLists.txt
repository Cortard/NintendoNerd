cmake_minimum_required(VERSION 3.26)
project(NintendoNerd C)

set(CMAKE_C_STANDARD 11)

add_executable(NintendoNerd HireMe.c
        Solver.h
        Solver.c
)
