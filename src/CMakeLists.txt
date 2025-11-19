add_library(projectLib utils.c)
add_library(programFuntions programFuntions.c)
add_library(mapGen mapGen.c)
add_library(pathfinding pathfinding.c)
add_library(truckstops truckStops.c)

target_include_directories(projectLib PUBLIC .)
target_include_directories(programFuntions PUBLIC .)
target_include_directories(mapGen PUBLIC .)
target_include_directories(pathfinding PUBLIC .)
target_include_directories(truckstops PUBLIC .)


add_executable(
        TruckingNavigation
        main.c
)

target_link_libraries(TruckingNavigation projectLib programFuntions mapGen pathfinding truckstops)
