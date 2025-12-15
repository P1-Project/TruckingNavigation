#include <stdio.h>

#include "../src/DefineConst.h"
#include "mtest.h"
#include "../src/HelperFunc.h"

TEST_CASE(testXYToIdx,
    /* Arrange */
    int mapsize = 10;
    int expectedResult[7];
    int actualResult[7];
    int x[7] = {4, 0, 0, 8, 9, 2, 9};
    int y[7] = {6, 0, 3, 0, 9, 9, 4};

    for (int i = 0; i < 7; i++) {
        expectedResult[i] = (y[i] * mapsize) + x[i];

        /* Act */
        actualResult[i] = XYToIdx(x[i], y[i], mapsize);

        /* Assert */
        CHECK_EQ_INT(expectedResult[i], actualResult[i]);
    }
)

TEST_CASE(testIdxToCoords,
    /* Arrange */
    int mapsize = 10;
    int index[4] = {0, 18, 24, 99};

    int x[4], y[4];
    int expectedResultX[4];
    int expectedResultY[4];
    int actualResultX[4];
    int actualResultY[4];


    for (int i = 0; i < 4; i++) {
        expectedResultX[i] = index[i] % mapsize;
        expectedResultY[i] = index[i] / mapsize;

        /* Act */
        IdxToCoords(index[i], mapsize, &x[i], &y[i]);

        actualResultX[i] = x[i];
        actualResultY[i] = y[i];

        /* Assert */
        CHECK_EQ_INT(expectedResultX[i], actualResultX[i]);
        CHECK_EQ_INT(expectedResultY[i], actualResultY[i]);
    }
)

TEST_CASE(testRandomBetween,
    /* Arrange */
    int a[5] = {1, 3, 100, 23, 14};
    int b[5] = {1, 7, 3456, 24, 40};

    int actualResult[5];

    for (int i = 0; i < 5; i++) {
        /* Act */
        actualResult[i] = RandomBetween(a[i], b[i]);

        /* Assert */
        CHECK_TRUE((a[i] <= actualResult[i]) && (actualResult[i] <= b[i]));
    }
)

TEST_CASE(testLookForNeighbor1,
    /* Arrange */
    int mapsize = 5;
    int maxRadius = mapsize;
    int map[25] = {
        5, 0, 0, 1, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 2, 0, 0,
        3, 0, 0, 0, 0
    };

    /* as index
    00, 01, 02, 03, 04,
    05, 06, 07, 08, 09,
    10, 11, 12, 13, 14,
    15, 16, 17, 18, 19,
    20, 21, 22, 23, 24
    */

    int index[5] = {12, 04, 00, 16, 19}; // start indexes
    int neighbor[5] = {INTERSTATEROAD, INTERSTATESTOP, TYPE2STOP, TYPE3STOP, BLOCKADE}; // {1, 2, 3, 4, 5}

    int expectedResult[5] = {3, 17, 20, -1, 0};
    int actualResult[5];

    for (int i = 0; i < 5; i++) {
        /* Act */
        actualResult[i] = LookForNeighbor(map, index[i], mapsize, neighbor[i], maxRadius);

        /* Assert */
        CHECK_EQ_INT(actualResult[i], expectedResult[i]);
    }
)

TEST_CASE(testLookForNeighbor2,
    /* Arrange */
    int mapsize = 5;
    int maxRadius = mapsize;
    int map[25] = {
        5, 0, 0, 0, 0,
        0, 0, 0, 0, 5,
        0, 0, 0, 0, 0,
        0, 0, 0, 5, 0,
        0, 5, 0, 0, 0
    };

    /* as index
    00, 01, 02, 03, 04,
    05, 06, 07, 08, 09,
    10, 11, 12, 13, 14,
    15, 16, 17, 18, 19,
    20, 21, 22, 23, 24
    */

    int index = 12; // start index
    int neighbor = BLOCKADE; // 5

    int expectedResult = 18;

    /* Act */
    int actualResult = LookForNeighbor(map, index, mapsize, neighbor, maxRadius);

    /* Assert */
    CHECK_EQ_INT(actualResult, expectedResult);
)

TEST_CASE(CalculatePathTime1,
    /* Arrange */
    int map[25] = {
        0, 0, 0, 1, 0,
        0, 0, 0, 1, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0
    };

    int pathLength1 = 6;
    int path1[6] = {1, 6, 12, 17, 22, 23};

    int pathLength2 = 9;
    int path2[9] = {4, 9, 14, 19, 18, 17, 12, 8, 3};

    /* as index
    00, 01, 02, 03, 04,
    05, 06, 07, 08, 09,
    10, 11, 12, 13, 14,
    15, 16, 17, 18, 19,
    20, 21, 22, 23, 24
    */

    int expectedTime1 = 168;
    int expectedTime2 = 272;

    /* Act */
    int actualTime1 = CalculatePathTime(map, path1, pathLength1);
    int actualTime2 = CalculatePathTime(map, path2, pathLength2);

    /* Assert */
    CHECK_EQ_INT(actualTime1, expectedTime1);
    CHECK_EQ_INT(actualTime2, expectedTime2);
)

TEST_CASE(testLookForNeighbor3,
    /* Arrange */
    int mapsize = 5;
    int maxRadius = mapsize;
    int map[25] = {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 3, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0
    };

    /* as index
    00, 01, 02, 03, 04,
    05, 06, 07, 08, 09,
    10, 11, 12, 13, 14,
    15, 16, 17, 18, 19,
    20, 21, 22, 23, 24
    */

    int index = 12; // start index
    int neighbor = TYPE2STOP; // 3
    printf("%d \n", TYPE2STOP);
    printf("%d \n", neighbor);
    int expectedResult = 12;

    /* Act */
    int actualResult = LookForNeighbor(map, index, mapsize, neighbor, maxRadius);
    printf("%d \n", actualResult);
    /* Assert */
    CHECK_EQ_INT(actualResult, expectedResult);
)