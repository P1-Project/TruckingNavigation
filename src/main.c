#include <stdio.h>

#include "AStarPathFinding.h"
#include "CheckCoordinateSetFunc.h"
#include "ConverterFunc.h"
#include "MapGenFunc.h"
#include "GenStopsFunc.h"
#include "GenBlockadeFunc.h"
#include "GetDestinationFunc.h"
#include "GenInterstateFunc.h"
#include "GenStopsFunc.h"
#include "DefineConst.h"
#include "DefineStruct.h"
#include "DivideRouteFunc.h"
#include "Navigation.h"


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
    RunMapGen(map, MAPSIZE, restStops);

    //PrintMap(map, MAPSIZE);

    // Find optimal route between start and end points
    Destination destination;
    GetDestination(&destination,0,MAPSIZE);


    // Find optimal route between found stops of type 3 and display to user
    Navigate(map, MAPSIZE, destination);



    return 0;
}