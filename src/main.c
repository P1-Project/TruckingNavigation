#include <stdio.h>

#include "CheckCoordinateSetFunc.h"
#include "pathFinding.h"
#include "mapGen.h"
#include "GenStopsFunc.h"
#include "GenBlockadeFunc.h"
#include "GetDestinationFunc.h"
#include "GenInterstateFunc.h"


//DEFINES OF CONSTANTS
#define DRIVINGTIMEMAX 4.5 //hours
#define DRIVINGSPEED 100 //KM per hour

int main(void) {
    //GenMap

    //GetDestination (start, end)

    //GenTruckStops

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
    TestMapGenConcetion();

    return 0;
}
