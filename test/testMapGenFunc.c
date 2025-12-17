#include <stdio.h>
#include "mtest.h"
#include "../src/MapGenFunc.h"
TEST_CASE(TestInitMap,
    /* Arrange */
    const int mapSize = 3;
    const int expectedResult[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int actualMap[mapSize*mapSize];
    /* Act */
    InitMap(actualMap, mapSize);
    /* Assert */
    for (int i = 0; i < mapSize*mapSize; i++) {
        CHECK_EQ_INT(expectedResult[i], actualMap[i]);
    }
)