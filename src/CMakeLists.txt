cmake_minimum_required(VERSION 3.20)

project(synch_assignment)


set(CMAKE_CXX_FLAGS "-pthread")
add_executable(synch_assignment main.cpp)
