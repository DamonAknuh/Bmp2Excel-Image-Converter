cmake_minimum_required(VERSION 3.5.1)
project(BMP2Excel)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pedantic -Wall -Wextra")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++14")

set(binary Byte2Int)

add_executable(${binary} ${binary}.cpp main.cpp)

target_compile_features(${binary} PRIVATE cxx_decltype_auto cxx_auto_type)
