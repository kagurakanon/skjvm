cmake_minimum_required(VERSION 3.20)

project(ShinkaiJvm)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_compile_options(-nostdinc++)

add_executable(java src/java/main.cpp)