#include <stdio.h>
#include <stdlib.h>
#include "Navigation.h"
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
 * @param fullPathLength
 * @param numSections
 * @param stops
 */
int *Navigate(int *map, const int mapSize, const Destination destination,
    int *fullPathLength, int *numSections, int *stops) {
    int pathLength = 0;
    int *fullPath = malloc(sizeof(int) * (mapSize * mapSize));
    int time = 0;

    // Get start and end points
    int startIdx = CheckCoordinateSet(map, destination.startX, destination.startY, mapSize);
    int goalIdx = CheckCoordinateSet(map, destination.endX, destination.endY, mapSize);
    //print map with start and end
    map[startIdx] = ROUTE;
    map[goalIdx] = ROUTE;
    printf("Chebyshev Heuristic\n");
    int *originalPath = RunAstarPathFindingChebyshev(map, mapSize, startIdx, goalIdx, &pathLength);
    if (originalPath) {
        PrintMap(map, mapSize, originalPath, pathLength);
        printf("\nPath length : %d\n", pathLength);
        for (int i = 0; i < pathLength; i++) {
            // Print route
            printf("%d ", originalPath[i]);
        }
    }
    else {
        PrintMap(map, mapSize, originalPath, pathLength);
        printf("No path found\n");
    }
    printf("\n\n");

    time = CalculatePathTime(map, originalPath, pathLength);
    printf("Path time in minutes : %d\n", time);
    free(originalPath);
/////////////////////////////////
    //variables in use
    int numSearchPoints = 0;
    int currentIdx = startIdx;
    int localFullPathLength = 0;
    int localNumSections = 0;
    int restStopIdx = 0;
    const int baseSearchRadius = 5;
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
        //printf("numSearchPoints = %d\n", numSearchPoints);
        // Time spent driving aka section size = 13 tiles before first rest stop
        //if the path is too short the program returns the full path from start to end
        if (numSearchPoints == 0) {
            for (int i = 0; i < pathLength; i++)
                fullPath[localFullPathLength++] = path[i];
            free(path);
            break;
        }
        //The route must be divided for the driver to follow regulations
        if (localNumSections == 0) {
            desiredType = 0; //Stop type can be both.
        }
        else {//numSections % 2 == 0 chose type 3 otherwise type 2
            desiredType = (localNumSections % 2 != 0) ? TYPE3STOP : TYPE2STOP;
        }
        //Find the nearest TYPE3STOP to the next section break
        int targetSection = searchPoints[0]; // next section point
        int t2 = LookForNeighbor(map, targetSection, mapSize, TYPE2STOP, baseSearchRadius);
        int t3 = LookForNeighbor(map, targetSection, mapSize, TYPE3STOP, baseSearchRadius);
        //if no rest stop found
        if (t2 == -1 && t3 == -1) {
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
        /*
        //debugging print and checks
        int maxNodes = mapSize * mapSize;
        if (currentIdx < 0 || currentIdx >= maxNodes) { fprintf(stderr,"BAD current=%d\n", currentIdx); abort(); }
        if (targetSection < 0 || targetSection >= maxNodes) { fprintf(stderr,"BAD targetSection=%d\n", targetSection); abort(); }
        if (t2 < -1 || t2 >= maxNodes || t3 < -1 || t3 >= maxNodes) { fprintf(stderr,"BAD neighbor t2=%d t3=%d\n", t2, t3); abort(); }
        */
        //Divide path into sections (this fills searchPointsType3)
        // Recalculate A* to the rest stop
        int *pathToStop = RunAstarPathFindingChebyshev(map, mapSize,
            currentIdx, restStopIdx, &pathLength);

        // Append subsection to fullPath
        for (int i = 0; i < pathLength; i++) {
            // avoid duplicate node when paths connect
            if (localFullPathLength == 0 || fullPath[localFullPathLength - 1] != pathToStop[i]) {
                fullPath[localFullPathLength++] = pathToStop[i];
            }
        }
        numberStops[localNumSections++] = restStopIdx;
        // Update current position to rest stop
        currentIdx = restStopIdx;
        // Loop continues and A* now runs from rest stop to goal
        free(pathToStop);
        free(path);
    }
    //return
    //full path, FullPathLenght, numberstops, numsections,
    *fullPathLength = localFullPathLength;
    *numSections = localNumSections;
    *stops = *numberStops;
    return fullPath;

}

