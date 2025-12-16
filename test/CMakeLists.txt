# Define the test executable
add_executable(testTruckingNavigation
        testMain.c
        testCheckCoordinateSetFunc.c
        testHelperFunc.c
        testDivideRouteFunc.c
        testGenBlockadeFunc.c
        testGenInterstateFunc.c
        testGenStopsFunc.c
        testGetDestinationFunc.c
        testMapGenFunc.c
        testAstarPathFinding.c
        testNavigation.c
)

# Give testTruckingNavigation access to local headers and src headers
target_include_directories(testTruckingNavigation PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
)

# Husk adgang til de forskellige funktioner som der testet
# kan tilføjes som et libary og kaldes fra testMain

# Library for main code
add_library(trucking_src
        ../src/CheckCoordinateSetFunc.c
        ../src/HelperFunc.c
        ../src/DivideRouteFunc.c
        ../src/GenBlockadeFunc.c
        ../src/GenInterstateFunc.c
        ../src/GenStopsFunc.c
        ../src/GetDestinationFunc.c
        ../src/MapGenFunc.c
        ../src/AStarPathFinding.c
        ../src/Navigation.c
)

# Include directories for trucking_src headers
target_include_directories(trucking_src PUBLIC ../src)

# Link test executable with mtest and trucking_src using keyword form
target_link_libraries(testTruckingNavigation PRIVATE mtest trucking_src)

# Discover tests for CTest
discover_tests(testTruckingNavigation)