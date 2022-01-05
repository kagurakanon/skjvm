cmake_minimum_required(VERSION 3.20)

project(ShinkaiJvm)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_compile_options(-nostdinc++)

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)
