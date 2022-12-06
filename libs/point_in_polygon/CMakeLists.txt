cmake_minimum_required(VERSION 3.24)
project(point_in_polygon)

set(CMAKE_CXX_STANDARD 17)

add_library(point_in_polygon SHARED point_in_polygon.cpp)
