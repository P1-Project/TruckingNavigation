#include <stdio.h>

#include "../src/DefineConst.h"
#include "mtest.h"
#include "../src/DivideRouteFunc.h"

TEST_CASE(testDivideRouteFunc1,
    /* Arrange */
    int mapSize = 5;
    int map[25] = {
        0, 1, 0, 0, 0,
        0, 1, 0, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0
    };

    /*
    00, 01, 02, 03, 04,
    05, 06, 07, 08, 09,
    10, 11, 12, 13, 14,
    15, 16, 17, 18, 19,
    20, 21, 22, 23, 24
    */

    int route[] = {1, 6, 12, 17, 23};
    int routeLength = 5;
    int numberOfPoints = 0;

    int *searchPoints = malloc(sizeof(int)*mapSize*mapSize);

    /* Act */
    searchPoints = DivideRoute(map, route, routeLength, searchPoints, &numberOfPoints, 50);

    printf("Number of points: %d\n", numberOfPoints);

    for (int i = 0; i < numberOfPoints; ++i) {
        printf("Point number %d is: %d\n", i, searchPoints[i]);
    }

    /* Assert */
    CHECK_EQ_INT(searchPoints[0], 12);

    free(searchPoints);
)

TEST_CASE(testDivideRouteFunc2,
    /* Arrange */
    int mapSize = 5;
    int map[25] = {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 1, 1, 1,
        1, 1, 0, 0, 0,
        0, 0, 0, 0, 0
    };

    /*
    00, 01, 02, 03, 04,
    05, 06, 07, 08, 09,
    10, 11, 12, 13, 14,
    15, 16, 17, 18, 19,
    20, 21, 22, 23, 24
    */

    int route[] = {3, 8, 12, 16, 21};
    int routeLength = 5;
    int numberOfPoints = 0;

    int *searchPoints = malloc(sizeof(int)*mapSize*mapSize);

    /* Act */
    searchPoints = DivideRoute(map, route, routeLength, searchPoints, &numberOfPoints, 70);

    printf("Number of points: %d\n", numberOfPoints);

    for (int i = 0; i < numberOfPoints; ++i) {
        printf("Point number %d is: %d\n", i, searchPoints[i]);
    }

    /* Assert */
    CHECK_EQ_INT(searchPoints[0], 8);
    CHECK_EQ_INT(searchPoints[1], 16);

    free(searchPoints);
)

TEST_CASE(testDivideRouteFunc3,
    /* Arrange */
    int mapSize = 6;
    int map[36] = {
    0, 1, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0,
    0, 0, 1, 0, 0, 0,
    0, 0, 0, 1, 0, 0,
    0, 0, 0, 1, 0, 0,
    };

    /*
    00, 01, 02, 03, 04, 05,
    06, 07, 08, 09, 10, 11,
    12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29,
    30, 31, 32, 33, 34, 35,
    */

    int route[] = {2, 8, 14, 20, 25, 31, 32, 33};
    int routeLength = 8;
    int numberOfPoints = 0;

    int *searchPoints = malloc(sizeof(int)*mapSize*mapSize);

    /* Act */
    searchPoints = DivideRoute(map, route, routeLength, searchPoints, &numberOfPoints, 90);

    printf("Number of points: %d\n", numberOfPoints);

    for (int i = 0; i < numberOfPoints; ++i) {
    printf("Point number %d is: %d\n", i, searchPoints[i]);
    }

    /* Assert */
    CHECK_EQ_INT(searchPoints[0], 14);
    CHECK_EQ_INT(searchPoints[1], 25);
    CHECK_EQ_INT(searchPoints[2], 32);

    free(searchPoints);
)