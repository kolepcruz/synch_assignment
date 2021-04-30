cmake_minimum_required(VERSION 3.20)

project(synch_assignment)

include_directories(frontend)
set(CMAKE_CXX_FLAGS "-pthread -lncurses")
add_executable(synch_assignment main.cpp frontend/ss_view.cpp)
target_link_libraries(synch_assignment ncurses)
