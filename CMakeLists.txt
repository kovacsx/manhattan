cmake_minimum_required(VERSION 3.5)

project(manhattan LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(manhattan main.cpp manhattan.cpp)

add_executable(manhattan_test test.cpp manhattan.cpp)
