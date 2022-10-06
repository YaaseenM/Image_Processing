cmake_minimum_required(VERSION 3.21)
project(Image_Processing)

set(CMAKE_CXX_STANDARD 14)

add_executable(Image_Processing main.cpp Image.cpp Image.h)
