#include <stdio.h>
#include "mtest.h"
#include "../src/GenBlockadeFunc.h"

TEST_CASE(format4,
    /* Arrange */

    /* Act */

    /* Assert */

)


TEST_CASE(TestGenBlockade,
    /* Arrange */
    int mapSize = 3;
    int map[mapSize*mapSize];

    int numBlockades = mapSize*mapSize;
    int expectedMap[] =
            {5, 5, 5,
             5, 5, 5,
             5, 5, 5};
    /* Act */
    GenBlockadeFunc(map, mapSize, numBlockades);

    /* Assert */
    for (int i = 0; i < mapSize*mapSize; i++) {
        CHECK_EQ_INT(map[i], expectedMap[i]);
    }
)