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
#testing files and functions before merge

#Linking all together for main program
target_link_libraries(TruckingNavigation mapGen GenBlockadeFunc GenInterstateFunc GenStopsFunc GetDestinationFunc CheckCoordinateSetFunc)

