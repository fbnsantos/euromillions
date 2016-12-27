cmake_minimum_required(VERSION 2.8.9)
project (EUROS)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

add_executable(eurorun eurorun.cpp)