//
// Created by rasmk on 20-11-2025.
//

#include "GenInterstateFunc.h"
#include "HelperFunc.h"
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
 * Ensures that value is between min and max, if outside set as min or max
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
 *The function takes the map, mapsize and the structure interstateRoad and outputs a path length
 * @param map int array of the map
 * @param mapSize The size of the map width
 * @param interstateRoad Struct type of InterStateRoad, containing the start x,y and end x,y
 * @param outPathLength the amount of indexes in path
 * @return Returns a pointer of indexes from the map.
 */
int *DefineInterstatePath(int *map, int mapSize, InterStateRoad interstateRoad, int *outPathLength) {
    //calculate distance absolute distance from startX to endX
    int absDx = abs( interstateRoad.startX - interstateRoad.endX);
    //calculate distance absolute distance from startY to endY
    int absDy = abs(interstateRoad.startY - interstateRoad.endY);
    //these intgers below are assigned as a one line if-statement with return either 1, or -1
    int stepX = (interstateRoad.endX > interstateRoad.startX) ? 1 : -1;

    int stepY = (interstateRoad.endY > interstateRoad.startY) ? 1 : -1;

    int x = interstateRoad.startX;
    int y = interstateRoad.startY;
    int decision; //decision var
    int pathLength = 0;
    int tempIndex;
    int *path = malloc(sizeof(int) * mapSize * mapSize);
    //if the interstate is going North to South or East to West, do this else do North to South,
    if (absDx >= absDy) { //East To west
        decision = 2 * absDy - absDx;
        for (int i = 0; i <= absDx; i++) {
            tempIndex = XYToIdx(x, y, mapSize);
            map[tempIndex] = INTERSTATEROAD; //sets mapIdx as highway
            pathLength++;
            path[i] = tempIndex;
            if (decision > 0) {
                y += stepY; //adds or subtracts depending on the absDy above
                decision -= 2*absDx;
            }
            x += stepX; //adds or subtracts depending on the absDx above
            decision += 2*absDy;
        }
    }
    else { //North To South
        decision = 2 * absDx - absDy;
        for (int i = 0; i <= absDy; i++) {
            tempIndex = XYToIdx(x, y, mapSize);
            map[tempIndex] = INTERSTATEROAD; //sets mapIdx as highway
            pathLength++;
            path[i] = tempIndex;
            if (decision > 0) {
                x += stepX;
                decision -= 2 * absDy;
            }
            y += stepY;
            decision += 2 * absDx;
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
    const int frequencyOfStops, int path[], const int pathLength,
    Stops *restStops,
    StopType stopTypesArray[3],
    int *stopCounter
    ){
    if (!path || !restStops || !stopTypesArray || !stopCounter) {exit(GENSTOPERROR);}
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
 * @param restStops restStop Struct for storage of rest stops
 * @param stopTypesArray Rest stops types, of the 3 types
 * @param stopCounter a counter to keep track of the amount of stops in the array of stops
 */
void SetInterStateRoad(int *map, int mapSize,
    InterStateRoad interStateRoad,
    Stops *restStops,
    StopType stopTypesArray[3],
    int *stopCounter) {
    //defines Interstate,
    int pathLength;
    int *path = DefineInterstatePath(map, mapSize, interStateRoad, &pathLength);
    int frequencyOfStops = 2;
    SetInterstateRestStops(map, mapSize, frequencyOfStops, path, pathLength,
        restStops, stopTypesArray, stopCounter);

    //frees the memory allocated for pointers
    free(path);
}

/**
 * Generate interstat road main run function
 * @param map Map
 * @param mapSize Mapsize
 * @param restStops Array with rest stops
 * @param stopTypesArray types of stops
 */
void GenInterStates(int *map, const int mapSize, Stops *restStops, StopType stopTypesArray[3]) {

    if (!map || !restStops || !stopTypesArray) {exit(GENSTOPERROR);}
    InterStateRoad interStateRoad1;
    InterStateRoad interStateRoad2;
    int wiggle = 7;
    // interStateRoad1 = vertical-ish
    // interStateRoad2 = horizontal-ish
    int baseX = mapSize / 2;          // vertical highway near center
    int baseY = mapSize / 2;          // horizontal highway near center
    // Vertical highway
    interStateRoad1.startX = clamp(baseX + RandomBetween(-wiggle, wiggle), 0 ,mapSize - 1);
    interStateRoad1.startY = 0;           // top edge
    interStateRoad1.endX   = clamp(baseX + RandomBetween(-wiggle, wiggle), 0 ,mapSize - 1);
    interStateRoad1.endY   = mapSize - 1; // bottom edge
    // Horizontal highway
    interStateRoad2.startX = 0;           // left edge
    interStateRoad2.startY = clamp(baseY + RandomBetween(-wiggle, wiggle), 0 ,mapSize - 1);
    interStateRoad2.endX   = mapSize - 1; // right edge
    interStateRoad2.endY   = clamp(baseY + RandomBetween(-wiggle, wiggle), 0 ,mapSize - 1);
    // 2. Ensure they are not too close to each other
    int minSeparation = mapSize / 4;
    while (abs(interStateRoad1.startX - interStateRoad2.startY) < minSeparation)
    {
        interStateRoad1.startX = clamp(baseX + RandomBetween(-wiggle, wiggle), 0 ,mapSize - 1);
        interStateRoad1.endX   = clamp(baseX + RandomBetween(-wiggle, wiggle), 0 ,mapSize - 1);

        interStateRoad2.startY = clamp(baseY + RandomBetween(-wiggle, wiggle), 0 ,mapSize - 1);
        interStateRoad2.endY   = clamp(baseY + RandomBetween(-wiggle, wiggle), 0 ,mapSize - 1);
    }
    // 3. Draw highways
    int stopCounter = abs(NUMBEROFSTOPS - NUMBEROFINTERSTATESTOPS);
    SetInterStateRoad(map, mapSize, interStateRoad1, restStops, stopTypesArray, &stopCounter);
    SetInterStateRoad(map, mapSize, interStateRoad2, restStops, stopTypesArray, &stopCounter);
}