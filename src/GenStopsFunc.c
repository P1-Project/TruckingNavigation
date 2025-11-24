#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "GenStopsFunc.h"
#include "ConverterFunc.h"
#include "GetDestinationFunc.h"
#include "MapGenFunc.h"

void TestConGenStopsFunc() {
    printf("Hello, World from GenStopsFunc!");

}

/**
 * This function takes three stop types from an array, and assigns which facilities it has.
 * @param stopTypesArray An array of the 3 stop types
 */
void InitializeTypes(StopType stopTypesArray[3]) {
    stopTypesArray[0] = (StopType){INTERSTATESTOP, 1, 0, 0, 0, 1}; //49 is 1
    stopTypesArray[1] = (StopType){TYPE2STOP, 1, 1, 0, 1, 1}; //50 is 2
    stopTypesArray[2] = (StopType){TYPE3STOP, 1, 1, 1, 1, 1}; //51 is 3
}

/**
 * This function creates type 2 and type 3 stops by percentage, storing them with type and coordinates in an array
 * @param mapSize The size of the map (int)
 * @param restStops An array of all the existing restStops
 * @param stopTypesArray An array of the 3 stop types
 */
void InitializeStops(int *map, int mapSize, Stops restStops[NUMBEROFSTOPS], StopType stopTypesArray[3]) {
    double Type2Percentage = 0.75;
    double Type3Percentage = 1.00-Type2Percentage;

    int numberOfType2 = ((int)floor(NUMBEROFSTOPS*Type2Percentage));
    int numberOfType3 = ((int)ceil(NUMBEROFSTOPS*Type3Percentage));

    int randomX, randomY;

    printf("Creating %d rest stops of type 2 and %d rest stops of type 3.\n", numberOfType2, numberOfType3);

    for (int i = 0; i < NUMBEROFSTOPS; ++i) {
        if (i < numberOfType2) restStops[i].Type = stopTypesArray[1];
        else restStops[i].Type = stopTypesArray[2];

        do {
            randomX = rand() % mapSize;
            randomY = rand() % mapSize;
            printf("Trying to assign rest stop at (%d, %d)\n", randomX, randomY);
        } while (SpotOccupied(map, mapSize, randomX, randomY));
        printf("Successfully assigned rest stop at (%d, %d)\n", randomX, randomY);

        restStops[i].locationX = randomX;
        restStops[i].locationY = randomY;
    }
}

/**
 * This function checks whether the rest stop you're trying to initialize, is being placed on top of an existing rest stop
 * @param X The x-coordinate of the given stop
 * @param Y The y-coordinate of the given stop
 * @param restStops An array of all the existing restStops
 * @param stopsPlaced The amount of rest stops which have already been initialized
 * @return 1 if the stop is occupied, 0 if not
 */
int SpotOccupied(int *map, int mapSize, int X, int Y) {
    if (map[XYToIdx(X, Y, mapSize)] == NORMALROAD) {
        return 0;
    }
    if ((map[XYToIdx(X, Y, mapSize)] == BLOCKADE) || (map[XYToIdx(X, Y, mapSize)] == INTERSTATEROAD) || (map[XYToIdx(X, Y, mapSize)] == INTERSTATESTOP)) {
        return 1;
    }
    return 1;
}

/**
 * This function places the rest stops in their coordinates on the map
 * @param map Pointer to the map array
 * @param mapSize The size of the map (int)
 * @param restStops An array of all the existing restStops
 */
void GenStops(int *map, unsigned int mapSize, Stops restStops[NUMBEROFSTOPS]) {
    for (int i = 0; i < NUMBEROFSTOPS; ++i) {
        //printf("Setting (%d, %d) to stop type %d\n", restStops[i].locationX, restStops[i].locationY, restStops[i].Type.Type);
        int index = XYToIdx(restStops[i].locationX, restStops[i].locationY, mapSize);
        map[index] = restStops[i].Type.Type;
    }
}

/*
int main(void) {
    srand(time(NULL));

    const unsigned int mapSize = 30;
    int map[mapSize*mapSize];
    GenRandomMap(map,mapSize*mapSize);

    StopType stopTypesArray[3];
    InitializeTypes(stopTypesArray);

    Stops restStops[NUMBEROFSTOPS];
    InitializeStops(mapSize, restStops, stopTypesArray);
    GenStops(map, mapSize, restStops);

    PrintMap(map, mapSize*mapSize);

    return 0;
}*/