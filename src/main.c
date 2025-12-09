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


    //getDestination()

    //Check destination and start Coordinates

    //Navigate to destination

    int pathLength = 0;
    int startIdx = CheckCoordinateSet(map, 0, 0, MAPSIZE);
    int goalIdx = CheckCoordinateSet(map, 29, 29, MAPSIZE);
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
    return 0;
}
