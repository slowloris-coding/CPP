cmake_minimum_required(VERSION 3.24)
project(pip_algo)

set(CMAKE_CXX_STANDARD 17)
add_executable(pip_algo main.cpp libs/point_in_polygon/point_in_polygon.h libs/point_in_polygon/point_in_polygon.cpp)
