#include <stdio.h>
#include "mtest.h"

int TestConnectionGenStops(void);

// GenStopsFunc tests
int TestSpotOccupied(void);
int TestInitializeTypes(void);
int TestInitializeStopsType(void);
int TestInitializeStopsLocation(void);
int TestGenStops(void);

TEST_CASE(TestConnection,
    /* Arrange */
    int i = 1;
    int j = 1;

    /* Act */
    int k = i + j;

    /* Assert */
    CHECK_EQ_INT(k,2);
)

MAIN_RUN_TESTS(
    TestConnection, TestConnectionGenStops,
    /* CheckCoordinateSetFunc tests */
    /* ConverterFunc tests */
    /* DijkstraAlgorithm tests */
    /* GenBlockade tests */
    /* GenInterstateFunc tests */
    /* GenStopsFunc tests */ TestInitializeTypes, TestInitializeStopsType, TestInitializeStopsLocation, TestSpotOccupied, TestGenStops
    /* GetDestinationFunc tests */
    /* MapGenFunc tests */
    /* pathFinding tests */
    )