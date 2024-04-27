cmake_minimum_required(VERSION 3.23)
project(C__Code)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(C__Code main.cpp array_generators.h array_sorters.h)
