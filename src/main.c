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
    //int *path = 0;
    //PrintMap(map, MAPSIZE, path);
    //getDestination();

    // Get start and end points

    // Find optimal route between start and end points

    // Divide route with ~7 hour intervals (420 minutes)

    // LookForNeighbor(type 3) at found points

    // Find optimal route between found stops of type 3

    // Divide route with ~2.5 hour intervals (150 minutes)

    //Navigate to destination
    int pathLength = 0;
    Destination pointA;

    GetDestination(&pointA,0,MAPSIZE);
    int startIdx = CheckCoordinateSet(map, pointA.startX, pointA.startY, MAPSIZE);
    int goalIdx = CheckCoordinateSet(map, pointA.endX, pointA.endY, MAPSIZE);

    int *path = runAstarPathFinding(map, MAPSIZE, startIdx, goalIdx, &pathLength);
    printf("\n");
    if (path) {
        for (int i = 0; i < pathLength; i++) {
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
    free(path);
    // LookForNeighbor(type 2) at found points

    // Find optimal route between found stops of type 2, 3 and start and end points

    // Print route

    return 0;
}
