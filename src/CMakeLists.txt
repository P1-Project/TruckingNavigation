add_library(mapGen mapGen.c)
add_library(pathfinding pathfinding.c)

add_library(GenBlockadeFunc GenBlockadeFunc.c)
add_library(GenInterstateFunc GenInterstateFunc.c)
add_library(GetDestinationFunc GetDestinationFunc.c)
add_library(GenStopsFunc GenStopsFunc.c)
add_library(CheckCoordinateSetFunc CheckCoordinateSetFunc.c)

target_include_directories(GenBlockadeFunc PUBLIC .)
target_include_directories(GenInterstateFunc PUBLIC .)
target_include_directories(GetDestinationFunc PUBLIC .)
target_include_directories(GenStopsFunc PUBLIC .)
target_include_directories(CheckCoordinateSetFunc PUBLIC .)

target_include_directories(mapGen PUBLIC .)
target_include_directories(pathfinding PUBLIC .)


add_executable(
        TruckingNavigation
        main.c
)

add_executable(GenStopsExec GenStopsFunc.c mapGen.c)

#testing files and functions before merge
#add_executable(MapGen mapGen.c)

#Linking all togehter for main program
target_link_libraries(TruckingNavigation mapGen GenBlockadeFunc GenInterstateFunc GenStopsFunc GetDestinationFunc CheckCoordinateSetFunc)

