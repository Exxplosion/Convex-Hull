cmake_minimum_required(VERSION 3.2)

project(main)

set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# cmake -DCMAKE_BUILD_TYPE=Debug ..
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")                # common
#set(CMAKE_CXX_FLAGS_DEBUG "-Og -g -DDEBUG")                   # debug only
#set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -pedantic -DNDEBUG")  # release only
set(CMAKE_CXX_FLAGS " -Wall -Wextra -pedantic -Ofast ")

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/geometry2D ${PROJECT_SOURCE_DIR}/parse_read)
add_subdirectory(geometry2D)
add_subdirectory(parse_read)

target_link_libraries(${PROJECT_NAME} geometry2D parse_read)