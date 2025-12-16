#include <stdio.h>

#include "HelperFunc.h"
#include "MapGenFunc.h"
#include "mtest.h"
#include "../src/Navigation.h"


TEST_CASE(TestNavigationOneStop,
/* Arrange */
const int mapSize = 10;
int map[] = {
    //0  1  2  3  4  5  6  7  8  9
/*0*/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*1*/ 5, 5, 5, 5, 5, 5, 5, 5, 5, 0,
/*2*/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*3*/ 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, //stop in this row
/*4*/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*5*/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*6*/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*7*/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*8*/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*9*/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
//int startIdx = XYToIdx(0, 0, mapSize);
//int goalIdx = XYToIdx(mapSize-1, mapSize-1, mapSize);
int outlength = 0;
int *stops = malloc(sizeof(int)*mapSize);
int numOfStops = 0;

Destination destination;
destination.startX = 0;
destination.startY = 0;
destination.endX = mapSize-1;
destination.endY = mapSize-1;
const int expectedPath[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 19, 28, 27, 26, 35, 34, 34, 45, 56, 67, 77, 88, 99};
const int expectedNumOfStops = 1;
const int expectedStoplocationIdx = XYToIdx(4, 3, mapSize);
/* Act */
int *path = Navigate(map, mapSize, destination, &outlength, &numOfStops, stops);
/* Assert */
for (int i = 0; i < outlength; i++) {
    printf(" %d,", path[i]);
    //map[path[i]] = ROUTE;
    CHECK_EQ_INT(expectedPath[i], path[i]);
}
printf("\n");
CHECK_EQ_INT(expectedNumOfStops, numOfStops);
CHECK_EQ_INT(expectedStoplocationIdx, stops[0]);

//print map with route for debugging
PrintMap(map, mapSize, path ,outlength);

free(path);
free(stops);
)

TEST_CASE(TestNavigationNoStopsFound,
/* Arrange */
const int mapSize = 10;
int map[] = {
    //0  1  2  3  4  5  6  7  8  9
/*0*/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*1*/ 5, 5, 5, 5, 5, 5, 5, 5, 5, 0,
/*2*/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*3*/ 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, //stop in this row
/*4*/ 0, 0, 5, 5, 5, 0, 0, 0, 0, 0,
/*5*/ 0, 0, 0, 0, 0, 0, 5, 5, 5, 0,
/*6*/ 5, 5, 5, 5, 5, 5, 5, 5, 5, 0,
/*7*/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*8*/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*9*/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
//int startIdx = XYToIdx(0, 0, mapSize);
//int goalIdx = XYToIdx(mapSize-1, mapSize-1, mapSize);
int outlength = 0;
int *stops = malloc(sizeof(int)*mapSize);
int numOfStops = 0;

Destination destination;
destination.startX = 0;
destination.startY = 0;
destination.endX = mapSize-1;
destination.endY = mapSize-1;
const int expectedPathLenght = -1;
const int expectedNumOfStops = -1;
const int expectedStoplocationIdx = -1;
/* Act */
int *path = Navigate(map, mapSize, destination, &outlength, &numOfStops, stops);
/* Assert */

if (path == NULL) {
    CHECK_EQ_INT(expectedPathLenght, outlength);
    CHECK_EQ_INT(expectedNumOfStops, numOfStops);
    CHECK_EQ_INT(expectedStoplocationIdx, stops[0]);
}
printf("\n");

//print map with route for debugging
PrintMap(map, mapSize, path ,outlength);

free(path);
free(stops);
)

TEST_CASE(TestNavigationPathWrapBack,
/* Arrange */
const int mapSize = 10;
int map[] = {
    //0  1  2  3  4  5  6  7  8  9
/*0*/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
/*1*/ 5, 5, 5, 5, 5, 5, 5, 5, 5, 0,
/*2*/ 0, 0, 0, 0, 0, 4, 0, 0, 0, 0,
/*3*/ 0, 5, 5, 5, 5, 5, 5, 5, 5, 5,
/*4*/ 0, 0, 5, 5, 5, 0, 0, 0, 0, 0,
/*5*/ 0, 0, 0, 0, 0, 3, 5, 5, 5, 0,
/*6*/ 5, 5, 5, 5, 5, 5, 5, 5, 5, 0,
/*7*/ 0, 0, 0, 0, 5, 4, 0, 0, 0, 0,
/*8*/ 0, 0, 0, 0, 5, 5, 5, 5, 5, 0,
/*9*/ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
//int startIdx = XYToIdx(0, 0, mapSize);
//int goalIdx = XYToIdx(mapSize-1, mapSize-1, mapSize);
int outlength = 0;
int *stops = malloc(sizeof(int)*mapSize*mapSize);
int numOfStops = 0;

Destination destination;
destination.startX = 0;
destination.startY = 0;
destination.endX = mapSize-1;
destination.endY = mapSize-1;
const int expectedPath[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 19, 28, 27, 26, 25, 24, 23, 22, 21, 30, 41, 52, 53, 54, 55, 46,
    47, 48, 59, 69, 78, 77, 76, 75, 75, 76, 77, 78, 89, 99};
const int expectedPathLenght = sizeof(expectedPath) / sizeof(expectedPath[0]);
const int expectedNumOfStops = 2;
const int expectedStoplocationIdx[] = {XYToIdx(5, 2 ,mapSize), XYToIdx(5, 7, mapSize)};
/* Act */
int *path = Navigate(map, mapSize, destination, &outlength, &numOfStops, stops);
/* Assert */

CHECK_EQ_INT(expectedPathLenght, outlength);
for (int i = 0; i < outlength; i++) {
    printf("%d, ", path[i]);
}
printf("idx value %d ",map[75]);

printf("\n Num Stops : %d\n", numOfStops);
CHECK_EQ_INT(expectedNumOfStops, numOfStops);
for (int j = 0; j < numOfStops; j++) {
    printf("%d ", expectedStoplocationIdx[j]);
    CHECK_EQ_INT(expectedStoplocationIdx[j], stops[j]);
}

printf("\n");

//print map with route for debugging
PrintMap(map, mapSize, path ,outlength);

free(path);
free(stops);
)

