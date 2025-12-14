#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "GenStopsFunc.h"
#include "ConverterFunc.h"
#include "GetDestinationFunc.h"
#include "MapGenFunc.h"
#include "DefineConst.h"
#include "DefineStruct.h"

void TestConGenStopsFunc() {
    printf("Hello, World from GenStopsFunc!");

}

/**
 * This function takes three stop types from an array, and assigns which facilities it has.
 * @param stopTypesArray An array of the 3 stop types
 */
void InitializeTypes(StopType stopTypesArray[3]) {
    // Set-up: {Type, Toilet, Fuel, Hotel, Food, Parking}
    stopTypesArray[0] = (StopType){INTERSTATESTOP, 1, 0, 0, 0, 1};
    stopTypesArray[1] = (StopType){TYPE2STOP, 1, 1, 0, 1, 1};
    stopTypesArray[2] = (StopType){TYPE3STOP, 1, 1, 1, 1, 1};
}

/**
 * This function creates stops of type 1, type 2 and type 3 stops by percentage
 * @param restStops An array of all the existing restStops
 * @param stopTypesArray An array of the 3 stop types
 */
void InitializeStopsType(Stops restStops[], StopType stopTypesArray[3]) {
    double Type2Percentage = 0.86; // Set percentage of type 2 rest stops
    int numberOfType2 = ((int)floor(NUMBEROFSTOPS23*Type2Percentage)); // Calculate number of type 2 rest stops

    //printf("Creating %d rest stops of type 2 and %d rest stops of type 3.\n", numberOfType2, NUMBEROFSTOPS23-numberOfType2);
    for (int i = 0; i < NUMBEROFSTOPS23; ++i) { // Assign every rest stop a type up until the total number of type 2 and 3 stops
        if (i < numberOfType2) {
            restStops[i].Type = stopTypesArray[1]; // Assign type 2 if i is below number of type 2
        } else {
            restStops[i].Type = stopTypesArray[2]; // Assign type 3 if i is above number of type 3
        }
    }

    for (int i = NUMBEROFSTOPS23; i < NUMBEROFSTOPS; ++i) { // Assign the rest of the number of stops the type 1
        restStops[i].Type = stopTypesArray[0];
    }
}

/**
 * This function defines stop 2 and 3's coordinates in an array
 * @param map Pointer to the map array
 * @param restStops An array of all the existing restStops
 */
void InitializeStopsLocation(int *map, Stops restStops[]) {
    int randomIdx, newX, newY;

    for (int i = 0; i < NUMBEROFSTOPS23; ++i) { // Assign a location to every rest stop of type 2 and 3
        int attempts = 0;
        do {
            randomIdx = rand() % (MAPSIZE*MAPSIZE); // Get a random index
            attempts++;
            if(attempts > (MAPSIZE * 10)) {
                printf("Could not place stop after %d attempts!\n", (MAPSIZE * 10));
                exit(EXIT_FAILURE);
            }

            // If the chosen spot is occupied or there is another stop close by, try again.
            } while (SpotOccupied(map, randomIdx) ||
                LookForNeighbor(map, randomIdx, MAPSIZE, TYPE2STOP, 1) != -1 ||
                LookForNeighbor(map, randomIdx, MAPSIZE, TYPE3STOP, 3) != -1);

        IdxToCoords(randomIdx, MAPSIZE, &newX, &newY);
        //printf("Successfully assigned rest stop at (%d, %d)\n", randomX, randomY);
        restStops[i].locationX = newX; // Assign the given rest stop's x coordinate
        restStops[i].locationY = newY; // Assign the given rest stop's x coordinate

        GenStop(map, restStops, i);
    }
}

/**
 * This function checks whether the rest stop you're trying to initialize, is being placed on top of an existing rest stop
 * @param map Pointer to the map array
 * @param index The index of the given spot
 * @return 1 if the stop is occupied, 0 if not
 */
int SpotOccupied(int *map, int index) {
    if (map[index] == NORMALROAD) { // Check what type of road the given index is on the map
        return 0; // If it is a normal road, return false
    }
    return 1; // Else return false
}

/**
 * This function places the rest stops in their coordinates on the map
 * @param map Pointer to the map array
 * @param restStops An array of all the existing restStops
 */
void GenStop(int *map, Stops restStops[], int i) {
    //printf("Setting (%d, %d) to stop type %d\n", restStops[i].locationX, restStops[i].locationY, restStops[i].Type.Type);
    int index = XYToIdx(restStops[i].locationX, restStops[i].locationY, MAPSIZE); // Find the index of the given rest stop's coordinates
    map[index] = restStops[i].Type.Type; // Set the map value of that index to the rest stops type equivalent
    //printf("Printing stop number %d\n", i);
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