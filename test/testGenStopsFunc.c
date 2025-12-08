#include <stdio.h>
#include "mtest.h"
#include "../src/GenStopsFunc.h"

TEST_CASE(TestConnectionGenStops,
    /* Arrange */
    int i = 3;
    int j = 3;

    /* Act */
    int k = i + j;

    /* Assert */
    CHECK_EQ_INT(k,6);
)

TEST_CASE(TestInitializeTypes,
    /* Arrange */
    StopType stopTypesArray[3];

    /* Act */
    InitializeTypes(stopTypesArray);

    /* Assert */
    // Check for: Type, Toilet, Fuel, Hotel, Food, Parking
    // Type
    CHECK_EQ_INT(stopTypesArray[0].Type, INTERSTATESTOP);
    CHECK_EQ_INT(stopTypesArray[1].Type, TYPE2STOP);
    CHECK_EQ_INT(stopTypesArray[2].Type, TYPE3STOP);

    // Toilet
    CHECK_EQ_INT(stopTypesArray[0].Toilet, 1);
    CHECK_EQ_INT(stopTypesArray[1].Toilet, 1);
    CHECK_EQ_INT(stopTypesArray[2].Toilet, 1);

    // Fuel
    CHECK_EQ_INT(stopTypesArray[0].Fuel, 0);
    CHECK_EQ_INT(stopTypesArray[1].Fuel, 1);
    CHECK_EQ_INT(stopTypesArray[2].Fuel, 1);

    // Hotel
    CHECK_EQ_INT(stopTypesArray[0].Hotel, 0);
    CHECK_EQ_INT(stopTypesArray[1].Hotel, 0);
    CHECK_EQ_INT(stopTypesArray[2].Hotel, 1);

    // Food
    CHECK_EQ_INT(stopTypesArray[0].Food, 0);
    CHECK_EQ_INT(stopTypesArray[1].Food, 1);
    CHECK_EQ_INT(stopTypesArray[2].Food, 1);

    // Parking
    CHECK_EQ_INT(stopTypesArray[0].Parking, 1);
    CHECK_EQ_INT(stopTypesArray[1].Parking, 1);
    CHECK_EQ_INT(stopTypesArray[2].Parking, 1);
)

TEST_CASE(TestInitializeStopsType,
    /* Arrange */
    StopType stopTypesArray[3];

    stopTypesArray[0].Type = INTERSTATESTOP;
    stopTypesArray[1].Type = TYPE2STOP;
    stopTypesArray[2].Type = TYPE3STOP;

    Stops restStops[NUMBEROFSTOPS];

    /* Act */
    InitializeStopsType(restStops, stopTypesArray);

    /* Assert */
    int countType1 = 0, countType2 = 0, countType3 = 0;
    for (int i = 0; i < NUMBEROFSTOPS; i++) {
        if (restStops[i].Type.Type == INTERSTATESTOP) countType1++;
        else if (restStops[i].Type.Type == TYPE2STOP) countType2++;
        else if (restStops[i].Type.Type == TYPE3STOP) countType3++;
    }

    int expectedType1 = NUMBEROFSTOPS-NUMBEROFSTOPS23;
    int expectedType2 = ((int)floor(NUMBEROFSTOPS23*0.86));
    int expectedType3 = NUMBEROFSTOPS23-expectedType2;

    CHECK_EQ_INT(countType1, expectedType1);
    CHECK_EQ_INT(countType2, expectedType2);
    CHECK_EQ_INT(countType3, expectedType3);
)

TEST_CASE(TestInitializeStopsLocation,
    /* Arrange */

    int map[MAPSIZE*MAPSIZE] = {0}; // 0 = not occupied
    Stops restStops[NUMBEROFSTOPS23];

    map[5 * MAPSIZE + 5] = 5; // 5 = occupied
    map[2 * MAPSIZE + 3] = 5;

    /* Act */
    InitializeStopsLocation(map, restStops);

    /* Assert */
    // Check that all coordinates in bounds
    for (int i = 0; i < NUMBEROFSTOPS23; i++) {
        CHECK_TRUE(restStops[i].locationX >= 0);
        CHECK_TRUE(restStops[i].locationX < MAPSIZE);
        CHECK_TRUE(restStops[i].locationY >= 0);
        CHECK_TRUE(restStops[i].locationY < MAPSIZE);
    }

    // Check that there is no overlap with the occupied spots
    for (int i = 0; i < NUMBEROFSTOPS23; i++) {
        CHECK_FALSE((restStops[i].locationX == 5) && (restStops[i].locationY == 5));
        CHECK_FALSE((restStops[i].locationX == 3) && (restStops[i].locationY == 2));
    }
)

TEST_CASE(TestSpotOccupied,
    /* Arrange */
    int miniMap[4] = {NORMALROAD,NORMALROAD,NORMALROAD,NORMALROAD};
    miniMap[2] = BLOCKADE;

    unsigned int x1 = 2 % 4;
    unsigned int y1 = 2 / 4;
    unsigned int x2 = 1 % 4;
    unsigned int y2 = 1 / 4;

    /* Act */
    int result1 = SpotOccupied(miniMap, x1, y1);
    int result2 = SpotOccupied(miniMap, x2, y2);

    /* Assert */
    CHECK_EQ_INT(result1, 1);
    CHECK_EQ_INT(result2, 0);
)

TEST_CASE(TestGenStops,
    /* Arrange */
    int map[MAPSIZE*MAPSIZE] = {0};
    Stops restStops[NUMBEROFSTOPS23];
    int numberOfType2 = NUMBEROFSTOPS23/2;

    // Assign some type 2's
    for (int i = 0; i < numberOfType2; i++) {
        restStops[i].Type.Type = TYPE2STOP;
    }

    // Assign some type 3's
    for (int i = numberOfType2; i < NUMBEROFSTOPS23; i++) {
    restStops[i].Type.Type = TYPE3STOP;
    }

    // Assign coordinates
    for (int x = 0, y = MAPSIZE-1, count = 0; count < NUMBEROFSTOPS23; x++, y--, count ++) {
        restStops[count].locationX = x;
        restStops[count].locationY = y;
    }

    /* Act */
    for (int i = 0; i < NUMBEROFSTOPS23; i++) {
        GenStop(map, restStops, i);
    }

    /* Assert */
    // Check that type 2 stops were written as 3
    for (int i = 0; i < numberOfType2; i++) {
        int idx = restStops[i].locationY * MAPSIZE + restStops[i].locationX;
        CHECK_TRUE(map[idx] == TYPE2STOP);
    }

    // Check that type 3 stops were written as 4
    for (int i = numberOfType2; i < NUMBEROFSTOPS23; i++) {
        int idx = restStops[i].locationY * MAPSIZE + restStops[i].locationX;
        CHECK_TRUE(map[idx] == TYPE3STOP);
    }
)