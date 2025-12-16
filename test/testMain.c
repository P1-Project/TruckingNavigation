#include <stdio.h>
#include "mtest.h"

int TestConnectionGenStops(void);

// GenStopsFunc Tests
int TestSpotOccupied(void);
int TestInitializeTypes(void);
int TestInitializeStopsType(void);
int TestInitializeStopsLocation(void);
int TestGenStops(void);

// ConverterFunc Tests
int testXYToIdx(void);
int testIdxToCoords(void);
int testRandomBetween(void);
int testLookForNeighbor1(void);
int testLookForNeighbor2(void);
int testLookForNeighbor3(void);
int CalculatePathTime1(void);

//MAPGEN Tests
int TestInitMap(void);

//GenBlockade Tests
int TestGenBlockade(void);

//GenInterstate Tests
int TestDefineInterstateStraightEastWest(void);
int TestDefineInterstateStraightNorthSouth(void);
int TestDefineInterstateDiagonalNS(void);
int TestDefineInterstateNSTwoTiles(void);

//CheckCoordinateSet Tests
int IdxGO(void);
int IdxEDGE(void);
int Idx63(void);
int Idx0(void);
int Idx7(void);
int Idx3(void);
int Idx56(void);
int Idx24(void);
int Idx36(void);
int Idx70(void);
int IdxNOSPACE(void);

//DivideRouteFunc Tests
int testDivideRouteFunc1(void);
int testDivideRouteFunc2(void);
int testDivideRouteFunc3(void);


//Test AstarPathFinding
int TestClearMapManhattan(void);
int TestSnakeMapManhattan(void);

// Test GetDestination
int IsDestinationInBound (void);

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
    Idx63, Idx0, Idx3, Idx7, Idx56, Idx24, Idx36, Idx70, IdxNOSPACE,IdxEDGE, IdxGO,
    /* ConverterFunc tests */
    testXYToIdx, testIdxToCoords, testRandomBetween,
    CalculatePathTime1,
    testLookForNeighbor1, testLookForNeighbor2, testLookForNeighbor3,
    /* DivideFunction */
    testDivideRouteFunc1, testDivideRouteFunc2, testDivideRouteFunc3,
    /* GenBlockade tests */
    TestGenBlockade,
    /* GenInterstateFunc tests */
    TestDefineInterstateStraightEastWest, TestDefineInterstateStraightNorthSouth,
    TestDefineInterstateDiagonalNS, TestDefineInterstateNSTwoTiles,
    /* GenStopsFunc tests */
    TestInitializeTypes, TestInitializeStopsType,
    TestInitializeStopsLocation, TestSpotOccupied, TestGenStops,
    /* GetDestinationFunc tests */
    IsDestinationInBound,
    /* MapGenFunc tests */
    TestInitMap,
    /* pathFinding tests */
    TestClearMapManhattan, TestSnakeMapManhattan
    )

