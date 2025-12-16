#include <stdio.h>
#include "mtest.h"
#include "../src/GenInterstateFunc.h"

TEST_CASE(format5,
    /* Arrange */

    /* Act */

    /* Assert */

)

TEST_CASE(TestDefineInterstateStraightEastWest,
    /* Arrange */
    const int mapSize = 5;
    InterStateRoad interStateRoad;
    interStateRoad.startX = 0;
    interStateRoad.startY = 2;
    interStateRoad.endX = mapSize-1;
    interStateRoad.endY = 2;
    int pathLength = 0;
    int *path = malloc(sizeof(int) * mapSize);
    int map[25] = {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0
    };
    int expetedMap[25] = {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0
    };
    /* Act */
    path = DefineInterstatePath(map, mapSize, interStateRoad, &pathLength);

    /* Assert */
    for (int i = 0; i < pathLength; i++) {
        CHECK_EQ_INT(map[path[i]],expetedMap[path[i]]);
    }
    free(path);
)

TEST_CASE(TestDefineInterstateStraightNorthSouth,
    /* Arrange */
    const int mapSize = 5;
    InterStateRoad interStateRoad;
    interStateRoad.startX = 2;
    interStateRoad.startY = 0;
    interStateRoad.endX = 2;
    interStateRoad.endY = mapSize-1;
    int pathLength = 0;
    int *path = malloc(sizeof(int) * mapSize);
    int map[25] = {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0
    };
    int expetedMap[25] = {
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0
    };
    /* Act */
    path = DefineInterstatePath(map, mapSize, interStateRoad, &pathLength);

    /* Assert */
    for (int i = 0; i < pathLength; i++) {
        CHECK_EQ_INT(map[path[i]],expetedMap[path[i]]);
    }
    free(path);
)

TEST_CASE(TestDefineInterstateDiagonalNS,
    /* Arrange */
    const int mapSize = 5;
    InterStateRoad interStateRoad;
    interStateRoad.startX = 0;
    interStateRoad.startY = 0;
    interStateRoad.endX = mapSize-1;
    interStateRoad.endY = mapSize-1;
    int pathLength = 0;
    int *path = malloc(sizeof(int) * mapSize);
    int map[25] = {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0
    };
    int expetedMap[25] = {
        1, 0, 0, 0, 0,
        0, 1, 0, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 0, 1, 0,
        0, 0, 0, 0, 1
    };
    /* Act */
    path = DefineInterstatePath(map, mapSize, interStateRoad, &pathLength);

    /* Assert */
    for (int i = 0; i < pathLength; i++) {
        CHECK_EQ_INT(map[path[i]],expetedMap[path[i]]);
    }
    free(path);
)

TEST_CASE(TestDefineInterstateNSTwoTiles,
    /* Arrange */
    const int mapSize = 5;
    InterStateRoad interStateRoad;
    interStateRoad.startX = 1; interStateRoad.startY = 0;
    interStateRoad.endX = 3; interStateRoad.endY = mapSize-1;
    int pathLength = 0; int *path = malloc(sizeof(int) * mapSize);
    int map[25] = {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0};
    int expetedMap[25] = {
        0, 1, 0, 0, 0,
        0, 1, 0, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 0, 1, 0};
    /* Act */
    path = DefineInterstatePath(map, mapSize, interStateRoad, &pathLength);
    /* Assert */
    for (int i = 0; i < pathLength; i++) {
        printf("%d, %d", map[path[i]], expetedMap[path[i]]);
        printf("%d\n", path[i]);
        CHECK_EQ_INT(map[path[i]],expetedMap[path[i]]);
    }
    free(path);
)

