cmake_minimum_required(VERSION 3.20)

project(synch_assignment)
set (CMAKE_CXX_STANDARD 11)


set(CMAKE_CXX_FLAGS "-pthread -Wall -g -lncurses ")
add_executable(synch_assignment main.cpp frontend/ss_view.cpp backend/Saiyan.cpp backend/Infirmary.cpp backend/Arena.cpp backend/Pit.cpp backend/Updater.cpp)
target_link_libraries(synch_assignment ncurses)
