# --- Libraries -------------------------------------------------------

add_library(MapGenFunc            MapGenFunc.c)
add_library(pathfinding           pathfinding.c)
add_library(ConverterFunc         ConverterFunc.c)
add_library(GenBlockadeFunc       GenBlockadeFunc.c)
add_library(GenInterstateFunc     GenInterstateFunc.c)
add_library(GetDestinationFunc    GetDestinationFunc.c)
add_library(GenStopsFunc          GenStopsFunc.c)
add_library(CheckCoordinateSetFunc CheckCoordinateSetFunc.c)
#add_library(DijkstraAlgorithm     DijkstraAlgorithm.c)


# --- Include directories (all libraries use the same include dir) ---
set(PROJECT_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(MapGenFunc            PUBLIC ${PROJECT_INCLUDES})
target_include_directories(pathfinding           PUBLIC ${PROJECT_INCLUDES})
target_include_directories(ConverterFunc         PUBLIC ${PROJECT_INCLUDES})
target_include_directories(GenBlockadeFunc       PUBLIC ${PROJECT_INCLUDES})
target_include_directories(GenInterstateFunc     PUBLIC ${PROJECT_INCLUDES})
target_include_directories(GetDestinationFunc    PUBLIC ${PROJECT_INCLUDES})
target_include_directories(GenStopsFunc          PUBLIC ${PROJECT_INCLUDES})
target_include_directories(CheckCoordinateSetFunc PUBLIC ${PROJECT_INCLUDES})
#target_include_directories(DijkstraAlgorithm     PUBLIC ${PROJECT_INCLUDES})



# --- Library Dependencies -------------------------------------------

# ConverterFunc is a common utility
target_link_libraries(GenInterstateFunc  PUBLIC ConverterFunc)
target_link_libraries(CheckCoordinateSetFunc PUBLIC ConverterFunc)
target_link_libraries(GenStopsFunc       PUBLIC ConverterFunc)

# Two-way or multiple dependencies
target_link_libraries(MapGenFunc PUBLIC
        GenBlockadeFunc
        ConverterFunc
        CheckCoordinateSetFunc
)

target_link_libraries(GenBlockadeFunc PUBLIC
        ConverterFunc
        MapGenFunc
)


# --- Executable ------------------------------------------------------

add_executable(TruckingNavigation main.c)

target_link_libraries(TruckingNavigation
        MapGenFunc
        ConverterFunc
        GenBlockadeFunc
        GenInterstateFunc
        GenStopsFunc
        GetDestinationFunc
        CheckCoordinateSetFunc
)