//
// Created by rasmk on 11-12-2025.
//

#include "Navigation.h"

#include <stdio.h>
#include <stdlib.h>

#include "AStarPathFinding.h"
#include "CheckCoordinateSetFunc.h"
#include "HelperFunc.h"
#include "DefineConst.h"
#include "DivideRouteFunc.h"
#include "MapGenFunc.h"


/**
 * This function takes the map and calculates the most optimal path from Start to End Goal.
 * The function then splits the path into sections and for each section navigating to a nearby rest stop.
 * @param map The map the program runs on
 * @param mapSize The Size of the map needed
 * @param destination Contains start and end coordinates in a struct for easy handling
 */
void Navigate(int *map, const int mapSize, const Destination destination) {
    int pathLength = 0;
    int *fullPath = malloc(sizeof(int) * (mapSize * mapSize));
    int fullPathLength = 0;

    // Get start and end points
    int startIdx = CheckCoordinateSet(map, destination.startX, destination.startY, mapSize);
    int goalIdx = CheckCoordinateSet(map, destination.endX, destination.endY, mapSize);

    //Use these for these lines for debugging
    /*startIdx = CheckCoordinateSet(map, 0, 0, mapSize);
    goalIdx = CheckCoordinateSet(map, 29, 29, mapSize);*/

    //print map with start and end
    map[startIdx] = ROUTE;
    map[goalIdx] = ROUTE;

    /*
    //Original path saved
    printf("Manhattan Heuristic");
    int *originalPath = RunAstarPathFindingManhattan(map, mapSize, startIdx, goalIdx, &pathLength);
    printf("\n");
    if (originalPath) {
        for (int i = 0; i < pathLength; i++) {
            // Print route
            printf("%d ", originalPath[i]);
        }
        printf("\nPath length : %d\n", pathLength);
        PrintMapWPath(map, mapSize, originalPath, pathLength);
    }
    else {
        printf("No path found\n");
        PrintMap(map, mapSize);
    }
    printf("\n\n");
    */

    /*
    printf("Euclidean Heuristic");
    originalPath = RunAstarPathFindingEuclidean(map, mapSize, startIdx, goalIdx, &pathLength);
    printf("\n");
    if (originalPath) {
        for (int i = 0; i < pathLength; i++) {
            // Print route
            printf("%d ", originalPath[i]);
        }
        printf("\nPath length : %d\n", pathLength);
        PrintMapWPath(map, mapSize, originalPath, pathLength);
    }
    else {
        printf("No path found\n");
        PrintMap(map, mapSize);
    }
    printf("\n\n");*/

    printf("Chebyshev Heuristic");
    int *originalPath = RunAstarPathFindingChebyshev(map, mapSize, startIdx, goalIdx, &pathLength);
    printf("\n");
    if (originalPath) {
        for (int i = 0; i < pathLength; i++) {
            // Print route
            printf("%d ", originalPath[i]);
        }
        printf("\nPath length : %d\n", pathLength);
        PrintMap(map, mapSize, originalPath, pathLength);
    }
    else {
        printf("No path found\n");
        PrintMap(map, mapSize, originalPath, pathLength);
    }
    printf("\n\n");


    free(originalPath);


/////////////////////////////////

    //vaiables in use
    int numSearchPoints = 0;
    int currentIdx = startIdx;
    int numSections = 0;
    int restStopIdx = 0;
    int baseSearchRadius = 5;
    int desiredType;

    int *numberStops = malloc(sizeof(int) * (mapSize));
    int *searchPoints = malloc(sizeof(int)* (mapSize));

    while (currentIdx != goalIdx) {
        //First Run should equal the original path,
        int *path = RunAstarPathFindingChebyshev(map, mapSize, currentIdx, goalIdx, &pathLength);
        if (!path || pathLength <= 1) break;

        numSearchPoints = 0;
        DivideRoute(map, path, pathLength,
                    searchPoints,
                    &numSearchPoints,
                    DRIVINGTIMEMAX);
        printf("numSearchPoints = %d\n", numSearchPoints);
        // Time spent driving aka section size = 13 tiles before first rest stop
        //if the path is too short the program returns the full path from start to end
        if (numSearchPoints == 0) {
            for (int i = 0; i < pathLength; i++)
                fullPath[fullPathLength++] = path[i];
            free(path);
            break;
        }

        //The route must be divided for the driver to follow regulations
        if (numSections == 0) {
            desiredType = 0; //Stop type can be both.
        }
        else {//numSections % 2 == 0 chose type 3 otherwise type 2
            desiredType = (numSections % 2 != 0) ? TYPE3STOP : TYPE2STOP;
        }

        //Find the nearest TYPE3STOP to the next section break
        int targetSection = searchPoints[0]; // next section point
        int t2 = LookForNeighbor(map, targetSection, mapSize, TYPE2STOP, baseSearchRadius);
        int t3 = LookForNeighbor(map, targetSection, mapSize, TYPE3STOP, baseSearchRadius);

        if (t2 ==-1 && t3 == -1) { //widedens scope
            t2 = LookForNeighbor(map, targetSection, mapSize, TYPE2STOP, ++baseSearchRadius);
            t3 = LookForNeighbor(map, targetSection, mapSize, TYPE3STOP, ++baseSearchRadius);
        }
        //if still no reststop found
        if (t2 <= -1 && t3 <= -1) {
            printf("No path found\n");
            free(path);
            break;
        }

        if (desiredType == 0) { //pick type closest
            if (t2 == -1 ) restStopIdx = t3;
            else if (t3 == -1 ) restStopIdx = t2;
            else {
                int distance2 = HeuristicChebyshev(targetSection, t2 , mapSize);
                int distance3 = HeuristicChebyshev(targetSection, t3 , mapSize);
                if (distance2 == distance3) {
                    int goalDistance2 = HeuristicChebyshev(t2, goalIdx, mapSize);
                    int goalDistance3 = HeuristicChebyshev(t3, goalIdx, mapSize);
                    restStopIdx = (goalDistance2 < goalDistance3) ? t2 : t3;
                }
                else {
                    restStopIdx = (distance2 < distance3 ? t2 : t3);
                }
            }
        } else if (desiredType == TYPE3STOP) {
            restStopIdx = (t3 != -1) ? t3 : t2;
        } else { // TYPE2STOP
            restStopIdx = (t2 != -1) ? t2 : t3;
        }

        if (restStopIdx == -1) {
            printf("Could not find rest stop of type 3 at target section %d", targetSection);
            free(path);
            break;
        }
        //frees path for next loop,

        //debugging print and checks
        int maxNodes = mapSize * mapSize;
        if (currentIdx < 0 || currentIdx >= maxNodes) { fprintf(stderr,"BAD current=%d\n", currentIdx); abort(); }
        if (targetSection < 0 || targetSection >= maxNodes) { fprintf(stderr,"BAD targetSection=%d\n", targetSection); abort(); }
        if (t2 < -1 || t2 >= maxNodes || t3 < -1 || t3 >= maxNodes) { fprintf(stderr,"BAD neighbor t2=%d t3=%d\n", t2, t3); abort(); }


        //Divide path into sections (this fills searchPointsType3)
        // Recalculate A* to the rest stop
        int *pathToStop = RunAstarPathFindingChebyshev(map, mapSize,
            currentIdx, restStopIdx, &pathLength);

        // Append subsection to fullPath
        for (int i = 0; i < pathLength; i++) {
            // avoid duplicate node when paths connect
            if (fullPathLength == 0 || fullPath[fullPathLength - 1] != pathToStop[i]) {
                fullPath[fullPathLength++] = pathToStop[i];
            }
        }
        numberStops[numSections] = restStopIdx;
        numSections++;
        // Update current position to rest stop
        currentIdx = restStopIdx;

        // Loop continues and A* now runs from rest stop to goal
        free(pathToStop);
        free(path);
    }

    //print map with full complete path
    PrintPath(fullPath, fullPathLength);
    PrintMap(map, mapSize, fullPath, fullPathLength);

    printf("\n");
    printf("number of stops : %d\n", numSections);

    for (int i = 0; i < numSections; i++) {
        printf("stop at index : %d of type %d ", numberStops[i], map[numberStops[i]]);
        int tempX, tempY;
        IdxToCoords(numberStops[i], mapSize, &tempX, &tempY);
        printf("coordinates: (%d, %d)\n", tempX, tempY);
    }

    //free memory
    free(fullPath);
    free(numberStops);
}

