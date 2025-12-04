add_executable(testTruckingNavigation testMain.c)
target_link_libraries(testTruckingNavigation mtest)
#Husk adgang til de forskellige funtioner som der testet
#kan tilføjes som et libary og kaldes fra testMain

discover_tests(testTruckingNavigation)