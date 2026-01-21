#include <stdio.h>
#include <stdlib.h>
#include "Navigation.h"
#include "AStarPathFinding.h"
#include "CheckCoordinateSetFunc.h"
#include "HelperFunc.h"
#include "DefineConst.h"
#include "DivideRouteFunc.h"
#include "MapGenFunc.h"

int* OriginalPath(int *map, const int mapSize, const Destination destination,
    int *outPathLength){
    int pathLength = 0;
    int time = 0;

    // Get start and end points
    const int startIdx = CheckCoordinateSet(map, destination.startX, destination.startY, mapSize);
    const int goalIdx = CheckCoordinateSet(map, destination.endX, destination.endY, mapSize);
    //print map with start and end
    //map[startIdx] = ROUTE;
    //map[goalIdx] = ROUTE;
    printf("Chebyshev Heuristic\n");
    int *originalPath = RunAstarPathFinding(map, mapSize, startIdx, goalIdx, &pathLength);
    if (originalPath) {
        PrintMap(map, mapSize, originalPath, pathLength);
        printf("Path length : %d\n", pathLength);
        for (int i = 0; i < pathLength; i++) {
            // Print route
            printf("%d ", originalPath[i]);
        }
    }
    else {
        PrintMap(map, mapSize, originalPath, pathLength);
        printf("No path found\n");
    }
    printf("\n");

    time = CalculatePathTime(map, originalPath, pathLength);
    printf("Path time in minutes : %d\n", time);
    printf("_____________________________________________________________________________________________\n");
    *outPathLength = pathLength;
    return originalPath;
}

/**
 * This function takes the map and calculates the most optimal path from Start to End Goal.
 * The function then splits the path into sections and for each section navigating to a nearby rest stop.
 * @param map The map the program runs on
 * @param mapSize The Size of the map needed
 * @param destination Contains start and end coordinates in a struct for easy handling
 * @param fullPathLength length of full path
 * @param numSections Number of sections aka number of stops needed
 * @param stops an array of the indexes where a stop is located
 */
int *Navigate(int *map, const int mapSize, const Destination destination,
    int *fullPathLength, int *numSections, int *stops) {
    int *fullPath = malloc(sizeof(int) * (mapSize * mapSize));
    int pathLength = 0;
    // Get start and end points
    const int startIdx = CheckCoordinateSet(map, destination.startX, destination.startY, mapSize);
    const int goalIdx = CheckCoordinateSet(map, destination.endX, destination.endY, mapSize);
/////////////////////////////////
    //variables in use
    int numSearchPoints = 0;
    int currentIdx = startIdx;
    int localFullPathLength = 0;
    int localNumSections = 0;
    int localStopCount = 0;
    int restStopIdx = 0;
    const int baseSearchRadius = 5;
    int desiredType;
    int *numberStops = malloc(sizeof(int) * (mapSize * mapSize));
    int *searchPoints = malloc(sizeof(int)* (mapSize * mapSize));

    while (currentIdx != goalIdx) {
        //First Run should equal the original path,
        int *path = RunAstarPathFinding(map, mapSize, currentIdx, goalIdx, &pathLength);
        if (!path || pathLength == 0) break;

        numSearchPoints = 0;
        DivideRoute(map, path, pathLength,
                    searchPoints,
                    &numSearchPoints,
                    DRIVINGTIMEMAX);
        // Time spent driving aka section size = 13 tiles before first rest stop
        //if the path is too short the program returns the full path from start to end
        if (numSearchPoints == 0) {
            for (int i = 0; i < pathLength; i++) {
                int start = 0;
                if (localFullPathLength > 0 && fullPath[localFullPathLength-1] == path[0]) {
                    start = 1; // skip the first node of pathToStop
                }
                for (i = start; i <= pathLength-1; i++) {
                    fullPath[localFullPathLength++] = path[i];
                }
            }
            free(path);
            break;
        }
        //The route must be divided for the driver to follow regulations
        if (localNumSections++ == 0) {
            desiredType = 0; //Stop type can be both.
        }
        else {//numSections % 2 == 0 chose type 3 otherwise type 2
            desiredType = (localStopCount % 2 != 0) ? TYPE3STOP : TYPE2STOP;
        }
        //Find the nearest TYPE3STOP to the next section break
        int targetSection = searchPoints[0]; // next section point
        int t2 = LookForNeighbor(map, targetSection, mapSize, TYPE2STOP, baseSearchRadius);
        int t3 = LookForNeighbor(map, targetSection, mapSize, TYPE3STOP, baseSearchRadius);
        //if no rest stop found
        if (t2 == -1 && t3 == -1) {
            printf("No path found\n");
            free(path);
            *numSections = -1;
            *stops = -1;
            *fullPathLength = -1;
            free(numberStops);
            free(searchPoints);
            return NULL;
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
        //Divide path into sections (this fills searchPointsType3)
        // Recalculate A* to the rest stop
        int *pathToStop = RunAstarPathFinding(map, mapSize,
            currentIdx, restStopIdx, &pathLength);
        // Append subsection to fullPath
        for (int i = 0; i < pathLength; i++) {
            // avoid duplicate node when paths connect
            if (localFullPathLength == 0 || fullPath[localFullPathLength - 1] != pathToStop[i]) {
                fullPath[localFullPathLength++] = pathToStop[i];
            }
        }
        stops[localStopCount++] = restStopIdx;
        // Update current position to rest stop
        currentIdx = restStopIdx;
        // Loop continues and A* now runs from rest stop to goal
        free(pathToStop);
        free(path);
    }
    //return
    //full path, FullPathLength, numberStops, numSections,
    *fullPathLength = localFullPathLength;
    *numSections = localStopCount;
    //*stops = numberStops;
    free(numberStops);
    free(searchPoints);
    return fullPath;
}

void NavigateWrapper(int *map, int mapSize, int *path, int pathLength, int *stops, const int numOfStops) {
    //print map with full complete path
    PrintMap(map, mapSize, path, pathLength);
    PrintPath(mapSize, path, pathLength, stops);
    printf("\n");
    printf("Number of stops: %d\n", numOfStops);
    for (int i = 0; i < numOfStops; i++) {
        printf("Stop at index %d of type %d. ", stops[i], map[stops[i]]);
        int tempX, tempY;
        IdxToCoords(stops[i], mapSize, &tempX, &tempY);
        printf("Coordinates: (%d, %d)\n", tempX, tempY);
    }
    int time;
    //printf("New path time in minutes : %d\n", time);
    //printf("Section based time\n");
    int tempIdx[numOfStops];
    int j = 0;
    int i = 0;
    for (i, j; i < pathLength; i++) {
        if (path[i] == stops[j]) {
            tempIdx[j] = i;
            //printf("%d | %d\n", tempIdx[j], path[tempIdx[j]]);
            j++;
        }
    }
    printf("\nSection based time\n");

    int sectionStart = 0;
    int *newSection = malloc(sizeof(int) * pathLength);

    for (int s = 0; s < numOfStops; s++) {
        int sectionEnd = tempIdx[s];
        int sectionLength = 0;

        for (i = sectionStart; i < sectionEnd; i++) {
            newSection[sectionLength++] = path[i];
        }

        time = CalculatePathTime(map, newSection, sectionLength);
        printf("Section %d time: %d minutes\n", s + 1, time);

        if (time > 270) {
            printf("    WARNING: This section is above the legal limit of 270 minutes ! This route is illegal\n");
        } else {
            printf("\n");
        }

        sectionStart = sectionEnd;
    }
    /* final section after last stop                      */
    if (sectionStart < pathLength - 1) {
        int sectionLength = 0;
        for (i = sectionStart; i < pathLength; i++) {
            newSection[sectionLength++] = path[i];
        }
        time = CalculatePathTime(map, newSection, sectionLength);
        printf("Final section time: %d minutes\n", time);
    }

    free(newSection);
}