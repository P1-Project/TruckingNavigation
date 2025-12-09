#include <stdio.h>

#include "CheckCoordinateSetFunc.h"
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

    int map[MAPSIZE*MAPSIZE];
    Stops restStops[NUMBEROFSTOPS];

    //runMapGen()
    runMapGen(map, MAPSIZE, restStops);

    PrintMap(map, MAPSIZE);

    // Get start and end points

    // Find optimal route between start and end points

    // Divide route with ~7 hour intervals (420 minutes)

    // LookForNeighbor(type 3) at found points

    // Find optimal route between found stops of type 3

    // Divide route with ~2.5 hour intervals (150 minutes)

    // LookForNeighbor(type 2) at found points

    // Find optimal route between found stops of type 2, 3 and start and end points

    // Print route

    return 0;
}
