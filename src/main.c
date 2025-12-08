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

    PrintMap(map, MAPSIZE);
    //getDestination();


    //getDestination()

    //Check destination and start Coordinates

    //Navigate to destination

    int pathLength = 0;
    int startIdx = XYToIdx(0, 0, MAPSIZE);
    int goalIdx = XYToIdx(29, 29, MAPSIZE);
    int *path = runAstarPathFinding(map, MAPSIZE, startIdx, goalIdx, &pathLength);

    if (path) {
        for (int i = 0; i < pathLength; i++) {
            printf("%d ", path[i]);
            map[path[i]] = ROUTE;
        }
        free(path);
    }
    else {
        printf("No path found\n");
    }

    PrintMap(map, MAPSIZE);


    //runDestination();

    return 0;
}
