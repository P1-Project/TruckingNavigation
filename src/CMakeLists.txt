add_library(projectLib
        utils.c
)

target_include_directories(projectLib PUBLIC .)

add_executable(
        TruckingNavigation
        main.c
)

target_link_libraries(TruckingNavigation projectLib)
