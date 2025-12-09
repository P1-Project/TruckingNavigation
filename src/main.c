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





    int pathLength = 0;
    int resultPathLength = 0;
    Destination destination;
    // Get start and end points
    GetDestination(&destination,0,MAPSIZE);
    int startIdx = CheckCoordinateSet(map, destination.startX, destination.startY, MAPSIZE);
    int goalIdx = CheckCoordinateSet(map, destination.endX, destination.endY, MAPSIZE);

    // Find optimal route between start and end points
    int *path = runAstarPathFinding(map, MAPSIZE, startIdx, goalIdx, &pathLength);
    printf("\n");
    if (path) {
        for (int i = 0; i < pathLength; i++) {
            // Print route
            printf("%d ", path[i]);
            //map[path[i]] = ROUTE;
        }
        printf("\nPath length : %d\n", pathLength);
        PrintMapWPath(map, MAPSIZE, path, pathLength);
    }
    else {
        printf("No path found\n");
        PrintMap(map, MAPSIZE);
    }
    printf("\n\n");


    /*
    int *searchPointsType3 = malloc(sizeof(int)*MAPSIZE);
    int numSearchPointsType3;
    // Divide route with ~x hour intervals (xxx minutes)
    DivideRoute(map, path, pathLength, searchPointsType3, &numSearchPointsType3,340);
    // LookForNeighbor(type 3) at found points
    int idx[numSearchPointsType3];
    for (int i = 0; i < numSearchPointsType3; i++) {
        idx[i] = LookForNeighbor(map, searchPointsType3[i], MAPSIZE, TYPE3STOP,5);
        printf("index : %d\n",idx[i]);
        if (idx[i] == -1) {
            printf("Failure");
            exit(-1);
        }
    }
    int *newPath = malloc(sizeof(int) * MAPSIZE);
    int newPathLength = 0;
    int *resultPath = malloc(sizeof(int) * MAPSIZE * MAPSIZE);
    newPath = runAstarPathFinding(map, MAPSIZE, startIdx, idx[0], &newPathLength);
    for (int j = 0; j < newPathLength; j++) {
        *resultPath = newPath[j];
        resultPath++;
    }
    resultPathLength +=newPathLength;

    //print resultpath
    for (int i = 0; i < resultPathLength; i++) {
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
    */

    free(path);
    return 0;
}
