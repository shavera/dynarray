cmake_minimum_required (VERSION 3.0)
project(dynarray)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} dynarray.h main.cpp)