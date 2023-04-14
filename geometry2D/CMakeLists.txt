cmake_minimum_required(VERSION 3.2)

project(geometry2D)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} consts.hpp graham.hpp graham.cpp objects_2D.hpp GJK.hpp GJK.cpp)