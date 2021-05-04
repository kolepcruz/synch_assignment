cmake_minimum_required(VERSION 3.20)

project(synch_assignment)
set (CMAKE_CXX_STANDARD 11)


set(CMAKE_CXX_FLAGS "-pthread -Wall -g -lncurses ")

FILE(GLOB_RECURSE project_srcs CONFIGURE_DEPENDS src  "*.cpp") 
add_executable(synch_assignment ${project_srcs})
target_link_libraries(synch_assignment ncurses)

