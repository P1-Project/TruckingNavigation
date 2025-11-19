add_library(
        projectLib utils.c

)
add_library(programFuntions programFuntions.c)

target_include_directories(projectLib PUBLIC .)
target_include_directories(programFuntions PUBLIC .)

add_executable(
        TruckingNavigation
        main.c
)

target_link_libraries(TruckingNavigation projectLib programFuntions)
