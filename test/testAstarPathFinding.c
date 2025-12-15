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

TEST_CASE(TestClearMapManhattan,
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

    int expectedPath[] = {0, 5, 10, 15, 20};
    int len = sizeof(expectedPath) / sizeof(expectedPath[0]);
    /* Act */
    int outlength = 0;
    int *path = RunAstarPathFindingManhattan(map, mapSize, startIdx, goalIdx,&outlength);

    /* Assert */

    for (int i = 0; i < outlength; i++) {
        printf("%d ", path[i]);
        map[path[i]] = ROUTE;
        CHECK_EQ_INT(expectedPath[i], path[i]);
    }
    //print map with route for debugging
    PrintMap(map, mapSize, path ,outlength);
)


TEST_CASE(TestSnakeMapManhattan,
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
    int *path = RunAstarPathFindingManhattan(map, mapSize, startIdx, goalIdx,&outlength);

    /* Assert */

    for (int i = 0; i < outlength; i++) {
        printf("%d ", path[i]);
        map[path[i]] = ROUTE;
        CHECK_EQ_INT(expectedPath[i], path[i]);
    }
    //print map with route for debugging
    PrintMap(map, mapSize, path ,outlength);
)