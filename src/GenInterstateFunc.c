//
// Created by rasmk on 20-11-2025.
//

#include "GenInterstateFunc.h"
#include "ConverterFunc.h"
#include "DefineStruct.h"
#include "DefineConst.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>




void printInterStateRoad(const InterStateRoad interStateRoad) {
    printf("in start (X, Y) : (%d , %d) ", interStateRoad.startX , interStateRoad.startY);
    printf("Start Index : %d\n", XYToIdx(interStateRoad.startX, interStateRoad.startY, 30));

    printf("in end (X, Y) : (%d , %d) ", interStateRoad.endX, interStateRoad.endY);
    printf("End Index : %d\n", XYToIdx(interStateRoad.endX, interStateRoad.endY, 30));
}


/**
 *
 * @param v input value
 * @param min min value always equal to 0
 * @param max Max value
 * @return //checks if the value is outside the map array if it does then it returns the max or min value
 */
static int clamp(const int v, const int min, const int max) {
    if (v < min) return min;
    if (v > max) return max;
    return v;
}


/**
 *
 * @param map int array of the map
 * @param mapSize The size of the map width
 * @param interStateRoad Struct type of InterStateRoad, containing the start x,y and end x,y
 * @param outPathLength the amount of indexes in path
 * @return Returns a pointer of indexes from the map.
 */
int *DefineInterstatePath(int *map, int mapSize, InterStateRoad interStateRoad, int *outPathLength) {
    //calculate distance absolute distance from startX to endX
    int absDx = abs( interStateRoad.startX - interStateRoad.endX);
    //calculate distance absolute distance from startY to endY
    int absDy = abs(interStateRoad.startY - interStateRoad.endY);

    //these intgers below are assigned as a one line if-statement with return either 1, 0 or -1
    int stepX = (interStateRoad.endX > interStateRoad.startX) ? 1 :
            (interStateRoad.endX < interStateRoad.startX) ? -1 : 0;

    int stepY = (interStateRoad.endY > interStateRoad.startY) ? 1 :
                (interStateRoad.endY < interStateRoad.startY) ? -1 : 0;


    int x = interStateRoad.startX;
    int y = interStateRoad.startY;
    int D; //decision var
    int pathLength = 0;
    int tempIndex;
    int *path = malloc(sizeof(int) * mapSize * mapSize);

    //printf("tempIndex = %d\n", tempIndex);
    //map[tempIndex-1] = INTERSTATEROAD;
    //printf("map[tempIndex] = %d\n", map[tempIndex]);

    //if the interstate is going North to South or East to West, do this else do East West,
    if (absDx >= absDy) { //East To west
        D = 2 * absDy - absDx;
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
    else { //North To South
        D = 2 * absDy - absDx;
        for (int i = 0; i <= absDy; i++) {
            tempIndex = XYToIdx(x, y, mapSize);
            map[tempIndex] = INTERSTATEROAD; //sets mapIdx as highway
            pathLength++;
            path[i] = tempIndex;
            if (D > 0) {
                x += stepX;
                D -= 2 * absDy;
            }
            y += stepY;
            D += 2 * absDx;
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
 * @param restStops
 * @param stopTypesArray
 * @param stopCounter
 * @return An array of TruckInterstate stops related to the amout of stops, and their respective location on the map.
 * The number of stops and the updated map itself
 */
void SetInterstateRestStops(int *map, int mapSize,
    int frequencyOfStops, int *path, int pathLength,
    Stops *restStops,
    StopType stopTypesArray[3],
    int *stopCounter
    ){
    if (!path || !restStops || !stopTypesArray || !stopCounter) {return;}
    int counter = *stopCounter;

    //add interstate rest stops matching length of the path
    for (int i = 0; i < pathLength; i++) {
        //sorting in frequency and the start and end stop.
        if (i % frequencyOfStops != 0 /*|| i == pathLength - 1 || i == 0*/) {
            continue;
        }
        //sets the type of truckstop to match interstate type
        restStops[counter].Type = stopTypesArray[0];
        //Calls IdxToCoords from Converter.c and gets the value for x and y in return
        IdxToCoords(path[i], mapSize,
                    &restStops[counter].locationX,
                    &restStops[counter].locationY);

        //displaying debugging informaiton
        /*printf("TruckStop # %d at path[%d] = %d\n", counter, i, path[i]);
        printf("Location (x,y): %d, %d\n",
                restStops[counter].locationX,
                restStops[counter].locationY);*/

        map[path[i]] = INTERSTATESTOP; //value for an interstate truck stop on the map
        counter++; //post increments the counter for the amount of stops to keep track.
    }
    *stopCounter += (pathLength / frequencyOfStops - 2);
}

/**
 * SetInterStateRoad defines the interstate going across the map. It takes the most direct route  from start to end
 * using the points declared in the InterStateRoad Struct
 * @param map Takes a blank map filled with 0's and "returns" an updated version with interstate going across
 * @param mapSize mapSize
 * @param interStateRoad Struct type of InterStateRoad, containing the start x,y and end x,y
 * @param restStops
 * @param stopTypesArray
 * @param stopCounter
 *
 */
void SetInterStateRoad(int *map, int mapSize,
    InterStateRoad interStateRoad,
    Stops *restStops,
    StopType stopTypesArray[3],
    int *stopCounter) {
    //defines Interstate,
    int pathLength;
    int *path = DefineInterstatePath(map, mapSize, interStateRoad, &pathLength);
    int frequencyOfStops = 1;
    SetInterstateRestStops(map, MAPSIZE, frequencyOfStops, path, pathLength,
        restStops, stopTypesArray, stopCounter);

    //frees the memory allocated for pointers
    free(path);
}


void GenInterStates(int *map, const int mapSize, Stops *restStops, StopType stopTypesArray[3]) {
    srand(time(NULL));

    InterStateRoad interStateRoad1;
    InterStateRoad interStateRoad2;

    int wiggle = 5;


    // interStateRoad1 = vertical-ish
    // interStateRoad2 = horizontal-ish
    int baseX = mapSize / 2;          // vertical highway near center
    int baseY = mapSize / 2;          // horizontal highway near center

    // Vertical highway
    interStateRoad1.startX = clamp(baseX + randomBetween(-wiggle, wiggle), 0, mapSize - 1);
    interStateRoad1.startY = 0;           // top edge
    interStateRoad1.endX   = clamp(baseX + randomBetween(-wiggle, wiggle), 0, mapSize - 1);
    interStateRoad1.endY   = mapSize - 1; // bottom edge

    // Horizontal highway
    interStateRoad2.startX = 0;           // left edge
    interStateRoad2.startY = clamp(baseY + randomBetween(-wiggle, wiggle), 0, mapSize - 1);
    interStateRoad2.endX   = mapSize - 1; // right edge
    interStateRoad2.endY   = clamp(baseY + randomBetween(-wiggle, wiggle), 0, mapSize - 1);

    // 2. Ensure they are not too close to each other
    int minSeparation = mapSize / 4;

    while (abs(interStateRoad1.startX - interStateRoad2.startY) < minSeparation)
    {
        interStateRoad1.startX = clamp(baseX + randomBetween(-wiggle, wiggle), 0, mapSize - 1);
        interStateRoad1.endX   = clamp(baseX + randomBetween(-wiggle, wiggle), 0, mapSize - 1);

        interStateRoad2.startY = clamp(baseY + randomBetween(-wiggle, wiggle), 0, mapSize - 1);
        interStateRoad2.endY   = clamp(baseY + randomBetween(-wiggle, wiggle), 0, mapSize - 1);
    }

    // 3. Draw highways
    int stopCounter = abs(NUMBEROFSTOPS - NUMBEROFINTERSTATESTOPS);
    printf("stopCounter value : %d\n", stopCounter);
    SetInterStateRoad(map, mapSize, interStateRoad1, restStops, stopTypesArray, &stopCounter);
    printf("stopCounter value : %d\n", stopCounter);
    SetInterStateRoad(map, mapSize, interStateRoad2, restStops, stopTypesArray, &stopCounter);
    printf("stopCounter value : %d\n", stopCounter);

}