cmake_minimum_required(VERSION 3.15)
project(dynarray)

include_directories(.)

add_executable(${PROJECT_NAME}
        dynarray.h
        main.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)