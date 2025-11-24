//
// Created by rasmk on 20-11-2025.
//

#include "GenInterstateFunc.h"
#include "DijkstraAlgorithm.h"
#include "ConverterFunc.h"
#include "MapGenFunc.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/**
 *
 *  @param map int array of the map
 * @param mapSize The size of the map width
 * @param interStateRoad Struct type of InterStateRoad, containing the start x,y and end x,y
 * @param outPathLength the amount of indexes in path
 * @return Returns an array of indexes from the map.
 */
int *DefineHighwayPath(int *map, signed int mapSize, InterStateRoad interStateRoad, int *outPathLength) {
    //calculate distance absolute distance from startX to endX
    int absDx = abs( interStateRoad.startX - interStateRoad.endX);
    //calculate distance absolute distance from startY to endY
    int absDy = abs(interStateRoad.startY - interStateRoad.endY);

    //these intgers below are assigned as an oneline if-statement with return either 1 or -1
    int stepX = (interStateRoad.endX > interStateRoad.startX) ? 1 : -1;
    int stepY = (interStateRoad.endY > interStateRoad.startY) ? 1 : -1;

    int x = interStateRoad.startX;
    int y = interStateRoad.startY;
    int D; //decision var
    int pathLength = 0;
    int *path = malloc(sizeof(int)* mapSize * mapSize);
    int tempIndex = XYToIdx(x,y, mapSize);
    //printf("tempIndex = %d\n", tempIndex);
    map[tempIndex] = INTERSTATEROAD;

    //if the highway is going North to South or East to West, do this else do East West,
    if (absDx >= absDy) { //North to South
        D = 2*absDy - absDx;
        for (int i = 0; i <= absDx; i++) {
            tempIndex = XYToIdx(x, y, mapSize);
            map[tempIndex] = INTERSTATEROAD; //sets mapIdx as highway
            pathLength++;
            path[i] = tempIndex;

            if (D > 0) {
                y += stepY; //adds or subtracts depending on the absDy above
                D -= 2*absDx;
            }
            x += stepX; //adds or subtracts depending on the absDx above
            D += 2*absDy;
        }
    }
    else { //East to West
        D = 2*absDy- absDx;
        for (int i = 0; i <= absDy; i++) {
            tempIndex = XYToIdx(x, y, mapSize);
            map[tempIndex] = INTERSTATEROAD; //sets mapIdx as highway
            pathLength++;
            path[i] = tempIndex;
            if (D > 0) {
                x += stepX;
                D -= 2*absDy;
            }
            y += stepY;
            D += 2*absDx;
        }
    }
    *outPathLength = pathLength;
    return path;
}

/**
 * This function when called upon places Interstate truck Stops on the highway route,
 * @param map int array of the map
 * @param mapSize The size of the map width
 * @param frequencyOfStops the frequency of stops need by law fx 3 per 100 km
 * @param path The array of indexes the highway is following on the map
 * @param pathLength The amount of indexes in the path,
 * @param startIndex start index for highway
 * @param goalIndex End index for highway
 * @param outNumStops outputs the number of stops
 * @return An array of TruckInterstate stops related to the amout of stops, and their respective location on the map.
 * The number of stops and the updated map itself
 */
TruckStopInterstate *SetInterstateRestStops(int *map, signed int mapSize, int frequencyOfStops,
                                            int *path, int pathLength,
                                            int startIndex, int goalIndex,
                                            int *outNumStops) {
    if (path == NULL) {exit(ERROR_PATH);}

    int maxStops = pathLength / frequencyOfStops;
    int counter = 0;
    TruckStopInterstate *truckStops =
        malloc(maxStops * sizeof(TruckStopInterstate));

    if (!truckStops) {return NULL;}

    //add interstate rest stops matching length of the path
    for (int i = 0; i < pathLength; i++) {
        //sorting in frequency and the start and end stop.
        if (i % frequencyOfStops != 0 || path[i] == startIndex || path[i] == goalIndex) {
            continue;
        }
        //sets the type of truckstop to match interstate type
        truckStops[counter].type = INTERSTATESTOP;
        //Calls IdxToCoords from Converter.c and gets the value for x and y in return
        IdxToCoords(path[i], mapSize,
                    &truckStops[counter].locationX,
                    &truckStops[counter].locationY);

        //displaying debugging informaiton
        /*printf("TruckStop # %d at path[%d] = %d\n", counter, i, path[i]);
        printf("Location (x,y): %d, %d\n",
                truckStops[counter].locationX,
                truckStops[counter].locationY);*/

        map[path[i]] = INTERSTATESTOP; //value for an interstate truck stop on the map
        counter++; //post increments the counter for the amount of stops to keep track.
    }
    *outNumStops = counter; //assigns the pointer a value that are equal counter.
    return truckStops;
}

/**
 * SetInterStateRoad defines the interstate going across the map. It takes the most direct route  from start to end
 * using the points declared in the InterStateRoad Struct
 * @param map Takes a blank map filled with 0's and "returns" an updated version with interstate going across
 * @param mapSize mapSize
 * @param interStateRoad Struct type of InterStateRoad, containing the start x,y and end x,y
 *
 */
void SetInterStateRoad(int *map, signed int mapSize, InterStateRoad interStateRoad) {
    //from point (x,y) on map, to (x,y)
    //start point
    const int startIndex = XYToIdx(interStateRoad.startX,interStateRoad.startY, mapSize);
    //value for map start index
    //printf("Start index : %d\n", startIndex);
    //endpoint
    const int goalIndex = XYToIdx(interStateRoad.endX, interStateRoad.endY, mapSize);
    //value for map end index
    //printf("Goal index : %d\n", goalIndex);

    //defines highway with the use of rules,
    int pathLength;
    int *path = DefineHighwayPath(map, mapSize, interStateRoad, &pathLength);

    printf("PathLength : %d\n", pathLength);

    /*for (int i = 0; i < pathLength; i++) {
        printf("%d, ", path[i]);
    }
    printf("\n");*/
    int frequencyOfStops = 5;
    int numStops;
    TruckStopInterstate *truckStops = SetInterstateRestStops(map, mapSize, frequencyOfStops, path, pathLength, startIndex, goalIndex, &numStops);

    //do something with truck stops if needed
    printf("Number of stops: %d\n", numStops);

    //frees the memorey allocated for pointers
    free(truckStops);
    free(path);
}
void printInterStateRoad(InterStateRoad interStateRoad) {
    printf("in start X :%d\n", interStateRoad.startX);
    printf("in start Y :%d\n", interStateRoad.startY);
    printf("in end X :%d\n", interStateRoad.endX);
    printf("in end Y :%d\n", interStateRoad.endY);
}



void SetInterStates(int *map, int mapSize) {
    srand(time(NULL));
    InterStateRoad interStateRoad1;
    InterStateRoad interStateRoad2;
    int minDistance = mapSize / 2 - 5;

    //find firsts x value with y value = 0
    interStateRoad1.startX = rand() % mapSize-1;
    interStateRoad1.startY = 0; //sets the start to be in the first 0 - 29 indexes

    interStateRoad1.endX = rand() % mapSize-1;
    interStateRoad1.endY = mapSize - 1;

    printInterStateRoad(interStateRoad1);

    // -------------------------
    // SAFELY PICK startY FOR HIGHWAY 2
    // -------------------------
    // If H1 starts on LEFT side, place H2 start on LOWER half
    // If H1 starts on RIGHT side, place H2 start on UPPER half
    if (interStateRoad1.startX < mapSize / 2) {
        // H1 on left → H2 start must be far down
        interStateRoad2.startY = randomBetween(mapSize / 2 + minDistance - mapSize, mapSize - 1);
        // This simplifies to:
        // randomBetween( min(15+15-30=0), 29 ) → randomBetween(0,29)
        // But we ensure the distance condition explicitly:
        do {
            interStateRoad2.startY = randomBetween(mapSize/2, mapSize-1); // 15–29
        } while (abs(interStateRoad1.startX - interStateRoad2.startY) < minDistance);
    } else {
        // H1 on right → H2 start must be high up
        do {
            interStateRoad2.startY = randomBetween(0, mapSize/2); // 0–15
        } while (abs(interStateRoad1.startX - interStateRoad2.startY) < minDistance);
    }

    interStateRoad2.startX = 0;
    interStateRoad2.endX = mapSize - 1;

    // -------------------------
    // END Y WITH SAME GUARANTEES
    // -------------------------
    if (interStateRoad1.endX >= mapSize/2) {
        do {
            interStateRoad2.endY = randomBetween(mapSize/2, mapSize - 1);
        } while (abs(interStateRoad1.endX - interStateRoad2.endY) < minDistance);
    } else {
        do {
            interStateRoad2.endY = randomBetween(0, mapSize/2);
        } while (abs(interStateRoad1.endX - interStateRoad2.endY) < minDistance);
    }




    printInterStateRoad(interStateRoad2);


    SetInterStateRoad(map, mapSize, interStateRoad1);
    SetInterStateRoad(map, mapSize, interStateRoad2);
}
