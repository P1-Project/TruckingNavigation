cmake_minimum_required(VERSION 3.16)
project(TruckingNavigation C)

# Prefer our local headers over external deps
include_directories(BEFORE ${CMAKE_SOURCE_DIR}/include)

set(CMAKE_C_STANDARD 11)

#add_executable(TruckingNavigation src/main.c)

include(cmake/mtest.cmake)

add_subdirectory(src)

#enables testing using mtest from
enable_testing()
add_subdirectory(test)
