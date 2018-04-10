cmake_minimum_required(VERSION 3.5.1)
project(Bmp2Excel-Image-Converter)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pedantic -Wall -Wextra")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++14")

set(binary1 Byte2Int)

set(binary2 BMP2EXCEL)

add_executable(Image_Procs ${binary1}.hpp ${binary1}.cpp ${binary2}.hpp ${binary2}.cpp  main.cpp)
