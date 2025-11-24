add_library(MapGenFunc MapGenFunc.c)
add_library(pathfinding pathfinding.c)

add_library(ConverterFunc ConverterFunc.c)

add_library(GenBlockadeFunc GenBlockadeFunc.c)
add_library(GenInterstateFunc GenInterstateFunc.c)
#add_library(DijkstraAlgorithm DijkstraAlgorithm.c)
add_library(GetDestinationFunc GetDestinationFunc.c)
add_library(GenStopsFunc GenStopsFunc.c)
add_library(CheckCoordinateSetFunc CheckCoordinateSetFunc.c)

target_include_directories(GenBlockadeFunc PUBLIC .)
target_include_directories(GenInterstateFunc PUBLIC .)
#target_include_directories(DijkstraAlgorithm PUBLIC .)
target_include_directories(GetDestinationFunc PUBLIC .)
target_include_directories(GenStopsFunc PUBLIC .)
target_include_directories(CheckCoordinateSetFunc PUBLIC .)
target_include_directories(ConverterFunc PUBLIC .)

target_include_directories(MapGenFunc PUBLIC .)
target_include_directories(pathfinding PUBLIC .)

target_link_libraries(GenInterstateFunc PUBLIC ConverterFunc)
target_link_libraries(CheckCoordinateSetFunc PUBLIC ConverterFunc)
target_link_libraries(MapGenFunc PUBLIC CheckCoordinateSetFunc)


add_executable(
        TruckingNavigation
        main.c
)
#testing files and functions before merge




#Linking all libraries to main program
target_link_libraries(
        TruckingNavigation MapGenFunc ConverterFunc
        GenBlockadeFunc GenInterstateFunc
        #DijkstraAlgorithm
        GenStopsFunc GetDestinationFunc CheckCoordinateSetFunc
)

