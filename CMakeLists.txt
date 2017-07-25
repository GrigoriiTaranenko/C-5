cmake_minimum_required(VERSION 3.7)
project(list)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES library.c library.h)
add_library(list ${SOURCE_FILES})