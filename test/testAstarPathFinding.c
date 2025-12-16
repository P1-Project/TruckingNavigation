#include <stdio.h>

#include "HelperFunc.h"
#include "DefineConst.h"
#include "MapGenFunc.h"
#include "mtest.h"
#include "../src/AStarPathFinding.h"


TEST_CASE(format8,
    /* Arrange */

    /* Act */

    /* Assert */

)

TEST_CASE(TestClearMapChebyshev,
    /* Arrange */
    int mapSize = 5;
    int map[] = {
    //    0  1  2  3  4
    /*0*/ 0, 0, 0, 0, 0,
    /*1*/ 0, 0, 0, 0, 0,
    /*2*/ 0, 0, 0, 0, 0,
    /*3*/ 0, 0, 0, 0, 0,
    /*4*/ 0, 0, 0, 0, 0,
    };
    int startIdx = XYToIdx(0, 0, mapSize);
    int goalIdx = XYToIdx(0, mapSize-1, mapSize);

    int expectedPath[] = {0, 6, 12, 16, 20};
    int len = sizeof(expectedPath) / sizeof(expectedPath[0]);
    /* Act */
    int outlength = 0;
    int *path = RunAstarPathFindingChebyshev(map, mapSize, startIdx, goalIdx,&outlength);

    /* Assert */

    for (int i = 0; i < outlength; i++) {
        printf("%d ", path[i]);
        map[path[i]] = ROUTE;
        CHECK_EQ_INT(expectedPath[i], path[i]);
    }
    //print map with route for debugging
    PrintMap(map, mapSize, path ,outlength);
)


TEST_CASE(TestSnakeMapChebyshev,
    /* Arrange */
    int mapSize = 5;
    int map[] = {
    //    0  1  2  3  4
    /*0*/ 0, 0, 0, 0, 0,
    /*1*/ 5, 5, 5, 5, 0,
    /*2*/ 0, 0, 0, 0, 0,
    /*3*/ 0, 5, 5, 5, 5,
    /*4*/ 0, 0, 0, 0, 0,
    };
    int startIdx = XYToIdx(0, 0, mapSize);
    int goalIdx = XYToIdx(mapSize-1, mapSize-1, mapSize);

    int expectedPath[] = {0, 1, 2, 3, 9, 13, 12, 11, 15, 21, 22, 23, 24};
    /* Act */
    int outlength = 0;
    int *path = RunAstarPathFindingChebyshev(map, mapSize, startIdx, goalIdx,&outlength);

    /* Assert */

    for (int i = 0; i < outlength; i++) {
        printf("%d ", path[i]);
        map[path[i]] = ROUTE;
        CHECK_EQ_INT(expectedPath[i], path[i]);
    }
    //print map with route for debugging
    PrintMap(map, mapSize, path ,outlength);
)

TEST_CASE(TestNavigationBiggerMap,
    /* Arrange */
    int mapSize = 10;
    int map[] = {
    //0  1  2  3  4  5  6  7  8  9
/*0*/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*1*/ 5, 5, 5, 5, 5, 5, 5, 5, 5, 0,
/*2*/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*3*/ 0, 5, 5, 5, 5, 5, 5, 5, 5, 5,
/*4*/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*5*/ 5, 5, 5, 5, 5, 5, 5, 5, 5, 0,
/*6*/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*7*/ 0, 5, 5, 5, 5, 5, 5, 5, 5, 5,
/*8*/ 0, 5, 5, 5, 5, 5, 5, 5, 5, 5,
/*9*/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    int startIdx = XYToIdx(0, 0, mapSize);
    int goalIdx = XYToIdx(mapSize-1, mapSize-1, mapSize);
    int outlength = 0;
    int *stops;
    int numOfStops = 0;
    int expectedPath[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 19, 28, 27, 26, 25, 24, 23, 22, 21, 30, 41, 42, 43, 44, 45, 46,
        47, 48, 59, 68, 67, 66, 65, 64, 63, 62, 61, 70, 80, 91, 92, 93, 94, 95, 96, 97, 98, 99};
    /* Act */
    int *path = RunAstarPathFindingChebyshev(map, mapSize, startIdx, goalIdx, &outlength);
    /* Assert */
    for (int i = 0; i < outlength; i++) {
        printf(" %d,", path[i]);
        map[path[i]] = ROUTE;
        CHECK_EQ_INT(expectedPath[i], path[i]);
    }
    printf("\n");
    //print map with route for debugging
    PrintMap(map, mapSize, path ,outlength);
)
