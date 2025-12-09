#include <stdio.h>

#include "AStarPathFinding.h"
#include "CheckCoordinateSetFunc.h"
#include "ConverterFunc.h"
#include "pathFinding.h"
#include "MapGenFunc.h"
#include "GenStopsFunc.h"
#include "GenBlockadeFunc.h"
#include "GetDestinationFunc.h"
#include "GenInterstateFunc.h"
#include "GenStopsFunc.h"
#include "DefineConst.h"
#include "DefineStruct.h"
#include "DivideRouteFunc.h"


int main(void) {
    //GenMap

    //GetDestination (start, end)

    //GetPreferences

    //Navigate

    //DisplayRoute

    //FilterTruckStops

    printf("Hello, World!\n");

    //connection testing
    TestConGenStopsFunc();
    TestConGetDestinationFunc();
    TestConCheckCoordinateSetFunc();
    TestConGenBlockadeFunc();

    //TestPathfindingConcetion();
    TestMapGenConnection();
    TestAstarPathFindingConnection();

    int map[MAPSIZE*MAPSIZE];
    Stops restStops[NUMBEROFSTOPS];

    //runMapGen()
    runMapGen(map, MAPSIZE, restStops);

    //PrintMap(map, MAPSIZE);

    // Find optimal route between start and end points




    int pathLength = 0;
    int *fullPath = malloc(MAPSIZE * MAPSIZE * sizeof(int));
    int fullPathLength = 0;
    Destination destination;
    // Get start and end points
    /*GetDestination(&destination,0,MAPSIZE);
    int startIdx = CheckCoordinateSet(map, destination.startX, destination.startY, MAPSIZE);
    int goalIdx = CheckCoordinateSet(map, destination.endX, destination.endY, MAPSIZE);*/
    int startIdx = CheckCoordinateSet(map, 0, 0, MAPSIZE);
    int goalIdx = CheckCoordinateSet(map, 29, 29, MAPSIZE);

    //print map with start and end
    map[startIdx] = ROUTE;
    map[goalIdx] = ROUTE;


    int *path1 = runAstarPathFinding(map, MAPSIZE, startIdx, goalIdx, &pathLength);
    printf("\n");
    if (path1) {
        for (int i = 0; i < pathLength; i++) {
            // Print route
            printf("%d ", path1[i]);
            //map[path[i]] = ROUTE;
        }
        printf("\nPath length : %d\n", pathLength);
        PrintMapWPath(map, MAPSIZE, path1, pathLength);
    }
    else {
        printf("No path found\n");
        PrintMap(map, MAPSIZE);
    }
    printf("\n\n");


/////////////////////////////////

    /*int currentIdx = startIdx;
    while (currentIdx != goalIdx) {
        int *path = runAstarPathFinding(map, MAPSIZE, currentIdx, goalIdx, &pathLength);
        if (!path || pathLength <= 1) {break;} //Error og no movement possible
        //printing the hole path
        printPath(path, pathLength);
    }*/
    int *searchPointsType3 = malloc(sizeof(int)*MAPSIZE);
    int numSearchPointsType3;
    int *numberStops = malloc(sizeof(int)* MAPSIZE);
    int current = startIdx;
    int numSections = 0;

    while (current != goalIdx) {

        int *path = runAstarPathFinding(map, MAPSIZE, current, goalIdx, &pathLength);
        if (!path || pathLength <= 1) break;

        // 1. Divide path into sections (this fills searchPointsType3)
        numSearchPointsType3 = 0;
        DivideRoute(map, path, pathLength,
                    searchPointsType3,
                    &numSearchPointsType3,
                    340);   // Time spendt drining aka section size = 13 tiles before first reststop

        if (numSearchPointsType3 == 0) {
            for (int i = 0; i < pathLength; i++)
                fullPath[fullPathLength++] = path[i];

            current = goalIdx;
            free(path);
            break;
        }

        // 2. Find the nearest TYPE3STOP to the next section break
        int targetSection = searchPointsType3[0];     // next section point
        int restStopIdx = LookForNeighbor(map, targetSection,
            MAPSIZE, TYPE3STOP, 5);

        free(path);

        // 3. Recalculate A* to the rest stop
        int *pathToStop = runAstarPathFinding(map, MAPSIZE,
            current, restStopIdx, &pathLength);
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
        current = restStopIdx;
        free(pathToStop);
        // Loop continues and A* now runs from rest stop → goal
    }
    printPath(fullPath, fullPathLength);
    PrintMapWPath(map, MAPSIZE, fullPath, fullPathLength);

    printf("\n");
    printf("number of stops : %d\n", numSections);

    for (int i = 0; i < numSections; i++) {
        printf("stop at index : %d ", numberStops[i]);
    }


    free(fullPath);
    free(numberStops);
    /*




    // Divide route with ~x hour intervals (xxx minutes)
    DivideRoute(map, path, pathLength, searchPointsType3, &numSearchPointsType3,340);
    // LookForNeighbor(type 3) at found points
    int idx[numSearchPointsType3];
    for (int i = 0; i < numSearchPointsType3; i++) {
        idx[i] = LookForNeighbor(map, searchPointsType3[i], MAPSIZE, TYPE3STOP,5);
        printf("index : %d\n",idx[i]);
        int x,y;
        IdxToCoords(idx[i], MAPSIZE, &x, &y);

        printf("Coordinatess are : %d %d\n", x, y);
        if (idx[i] == -1) {
            printf("Failure");
            exit(-1);
        }
    }

    //Reroute for first rest stop
    int newPathLength = 0;
    int *newPath = runAstarPathFinding(map, MAPSIZE, startIdx, idx[0], &newPathLength);
    for (int i = 0; i < newPathLength; i++) {
        printf("%d ", newPath[i]);
        resultPath[i] = newPath[i];
        resultPathLength++;
    }
    //Calculate route from last point in newPath to goal and divide it again:
    newPath = runAstarPathFinding(map, MAPSIZE, resultPath[resultPathLength],goalIdx, &newPathLength);


    DivideRoute(map, newPath, newPathLength, searchPointsType3, &numSearchPointsType3,340);


    for (int i = 0; i < numSearchPointsType3; i++) {
        idx[i] = LookForNeighbor(map, searchPointsType3[i], MAPSIZE, TYPE3STOP,5);
        printf("index : %d\n",idx[i]);
        int x,y;
        IdxToCoords(idx[i], MAPSIZE, &x, &y);

        printf("Coordinatess are : %d %d\n", x, y);
        if (idx[i] == -1) {
            printf("Failure");
            exit(-1);
        }
    }


    for (int i = 0; i < newPathLength; i++) {
        printf("%d ", newPath[i]);
        resultPath[i] = newPath[i];
        resultPathLength++;
    }
    */






    /*
    int *resultPath = malloc(sizeof(int) * MAPSIZE * MAPSIZE);
    for (int j = 0; j < newPathLength; j++) {
        *resultPath = *newPath;
        newPath++;
        resultPath++;
    }
    resultPathLength +=newPathLength;

    //print resultpath
    for (int i = 0; i < resultPathLength; i++) {
        printf("%d ", resultPath[i]);
    }
    */

    /*
    printf("\nResult Path :\n");
    for (int i = 0; i <resultPathLength; i++) {
        printf("%d ", resultPath[i]);
    }
    */


    // Find optimal route between found stops of type 3



    // Divide route with ~2.5 hour intervals (150 minutes)

    //Navigate to destination

    // LookForNeighbor(type 2) at found points

    // Find optimal route between found stops of type 2, 3 and start and end points







    /*
    free(newPath);
    free(resultPath);
    free(path);*/
    return 0;
}