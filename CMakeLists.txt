cmake_minimum_required(VERSION 3.16)
project(TruckingNavigation C)

set(CMAKE_C_STANDARD 11)

#add_executable(TruckingNavigation src/main.c)

include(cmake/mtest.cmake)

add_subdirectory(src)

#enables testing using mtest from
enable_testing()
add_subdirectory(test)
