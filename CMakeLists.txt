cmake_minimum_required(VERSION 2.8)
project(GameOfLife)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(app)
add_subdirectory(lib)
add_subdirectory(googletest)
add_subdirectory(tests)
add_subdirectory(benchmark)
