cmake_minimum_required(VERSION 3.2)

project(parse_read)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} parse_arguments.cpp parse_arguments.hpp read_points.cpp read_points.hpp)