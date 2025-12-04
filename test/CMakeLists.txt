# Define the test executable
add_executable(testTruckingNavigation
        testMain.c
        testGenStopsFunc.c
)

# Husk adgang til de forskellige funktioner som der testet
# kan tilføjes som et libary og kaldes fra testMain

# Library for main code
add_library(trucking_src
        ../src/ConverterFunc.c
        ../src/GenStopsFunc.c
)

# Include directories for trucking_src headers
target_include_directories(trucking_src PUBLIC ../src)

# Link test executable with mtest and trucking_src using keyword form
target_link_libraries(testTruckingNavigation PRIVATE mtest trucking_src)

# Discover tests for CTest
discover_tests(testTruckingNavigation)