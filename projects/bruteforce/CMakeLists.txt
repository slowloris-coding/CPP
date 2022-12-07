cmake_minimum_required(VERSION 3.24)
project(bruteforce)

set(CMAKE_CXX_STANDARD 20)

add_executable(bruteforce main.cpp lib/bruteforce/bruteforce.cpp lib/bruteforce/bruteforce.h)
