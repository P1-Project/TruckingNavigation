#include <stdio.h>
#include "mtest.h"
#include "../src/CheckCoordinateSetFunc.h"

TEST_CASE(IdxEDGE,
    /* Arrange */
    int Map[] = {5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,0,5};

    int mapSize = 8;

    /* Act */
    int result = CheckCoordinateSet(Map, 2, 2, mapSize);

    /* Assert */
    CHECK_EQ_INT(result, 62);
)

TEST_CASE(Idx63,
    /* Arrange */
    int Map[] = {5,0,5,5,5,0,0,5,
                 0,0,5,5,5,0,0,0,
                 0,0,0,0,0,0,0,0,
                 5,0,0,5,5,0,0,0,
                 5,0,0,5,5,5,0,0,
                 0,0,0,5,5,5,0,0,
                 0,0,0,0,0,0,0,5,
                 5,0,0,0,0,0,5,5};

    int mapSize = 8;

    /* Act */
    int result = CheckCoordinateSet(Map, 7, 7, mapSize);

    /* Assert */
    CHECK_EQ_INT(result, 54);
)

TEST_CASE(Idx0,
    /* Arrange */
    int Map[] = {5,0,5,5,5,0,0,5,
                 0,0,5,5,5,0,0,0,
                 0,0,0,0,0,0,0,0,
                 5,0,0,5,5,0,0,0,
                 5,0,0,5,5,5,0,0,
                 0,0,0,5,5,5,0,0,
                 0,0,0,0,0,0,0,5,
                 5,0,0,0,0,0,5,5};

    int mapSize = 8;

    /* Act */
    int result = CheckCoordinateSet(Map, 0, 0, mapSize);

    /* Assert */
    CHECK_EQ_INT(result, 8);
)

TEST_CASE(Idx3,
    /* Arrange */
    int Map[] = {5,0,5,5,5,0,0,5,
                 0,0,5,5,5,0,0,0,
                 0,0,0,0,0,0,0,0,
                 5,0,0,5,5,0,0,0,
                 5,0,0,5,5,5,0,0,
                 0,0,0,5,5,5,0,0,
                 0,0,0,0,0,0,0,5,
                 5,0,0,0,0,0,5,5};

    int mapSize = 8;

    /* Act */
    int result = CheckCoordinateSet(Map, 3, 0, mapSize);

    /* Assert */
    CHECK_EQ_INT(result, 1);
)

TEST_CASE(Idx7,
    /* Arrange */
    int Map[] = {5,0,5,5,5,0,0,5,
                 0,0,5,5,5,0,0,0,
                 0,0,0,0,0,0,0,0,
                 5,0,0,5,5,0,0,0,
                 5,0,0,5,5,5,0,0,
                 0,0,0,5,5,5,0,0,
                 0,0,0,0,0,0,0,5,
                 5,0,0,0,0,0,5,5};

    int mapSize = 8;

    /* Act */
    int result = CheckCoordinateSet(Map, 7, 0, mapSize);

    /* Assert */
    CHECK_EQ_INT(result, 6);
)

TEST_CASE(Idx56,
    /* Arrange */
    int Map[] = {5,0,5,5,5,0,0,5,
                 0,0,5,5,5,0,0,0,
                 0,0,0,0,0,0,0,0,
                 5,0,0,5,5,0,0,0,
                 5,0,0,5,5,5,0,0,
                 0,0,0,5,5,5,0,0,
                 0,0,0,0,0,0,0,5,
                 5,0,0,0,0,0,5,5};

    int mapSize = 8;

    /* Act */
    int result = CheckCoordinateSet(Map, 0, 7, mapSize);

    /* Assert */
    CHECK_EQ_INT(result, 48);
)

TEST_CASE(Idx24,
    /* Arrange */
    int Map[] = {5,0,5,5,5,0,0,5,
                 0,0,5,5,5,0,0,0,
                 0,0,0,0,0,0,0,0,
                 5,0,0,5,5,0,0,0,
                 5,0,0,5,5,5,0,0,
                 0,0,0,5,5,5,0,0,
                 0,0,0,0,0,0,0,5,
                 5,0,0,0,0,0,5,5};

    int mapSize = 8;

    /* Act */
    int result = CheckCoordinateSet(Map, 0, 3, mapSize);

    /* Assert */
    CHECK_EQ_INT(result, 16);
)

TEST_CASE(Idx36,
    /* Arrange */
    int Map[] = {5,0,5,5,5,0,0,5,
                 0,0,5,5,5,0,0,0,
                 0,0,0,0,0,0,0,0,
                 5,0,0,5,5,0,0,0,
                 5,0,0,5,5,5,0,0,
                 0,0,0,5,5,5,0,0,
                 0,0,0,0,0,0,0,5,
                 5,0,0,0,0,0,5,5};

    int mapSize = 8;

    /* Act */
    int result = CheckCoordinateSet(Map, 4, 4, mapSize);

    /* Assert */
    CHECK_EQ_INT(result, 29);
)

TEST_CASE(Idx70,
    /* Arrange */
    int Map[] = {5,0,5,5,5,0,0,5,
                 0,0,5,5,5,0,0,0,
                 0,0,0,0,0,0,0,0,
                 5,0,0,5,5,0,0,0,
                 5,0,0,5,5,5,0,0,
                 0,0,0,5,5,5,0,0,
                 0,0,0,0,0,0,0,5,
                 5,0,0,0,0,0,5,5};

    int mapSize = 8;

    /* Act */
    int result = CheckCoordinateSet(Map, 6, 8, mapSize);

    /* Assert */
    CHECK_EQ_INT(result, -1);
)

TEST_CASE(IdxNOSPACE,
    /* Arrange */
    int Map[] = {5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,5,5};

    int mapSize = 8;

    /* Act */
    int result = CheckCoordinateSet(Map, 4, 4, mapSize);

    /* Assert */
    CHECK_EQ_INT(result, -2);
)

