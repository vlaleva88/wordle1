cmake_minimum_required(VERSION 4.0)
project(wordle)

set(CMAKE_CXX_STANDARD 20)

add_executable(wordle main.cpp
        wordle.cpp)
