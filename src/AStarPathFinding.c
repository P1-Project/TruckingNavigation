#include "AStarPathFinding.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "CheckCoordinateSetFunc.h"
#include "ConverterFunc.h"
#include "DefineConst.h"
#include "DefineStruct.h"
#include "DivideRouteFunc.h"
#include "MapGenFunc.h"

void TestAstarPathFindingConnection(void) {
    printf("TestAstarPathFindingConnection\n");
}

#define INF 999999999
// Heuristic (Euclidean Distance)
int heuristic(const int a, const int b, const int mapSize) {
    int ax, ay, bx, by;
    IdxToCoords(a, mapSize, &ax, &ay);
    IdxToCoords(b, mapSize, &bx, &by);
    const int deltaX = ax - bx;
    const int deltaY = ay - by;

    return (int)sqrt(deltaX * deltaX + deltaY * deltaY);
}

// Heuristic (Manhattan)
int heuristicManhattan(int a, int b, int mapSize) {
    int ax, ay, bx, by;
    IdxToCoords(a, mapSize, &ax, &ay);
    IdxToCoords(b, mapSize, &bx, &by);
    return abs(ax - bx) + abs(ay - by);
}


// Movement cost
int movementCost(int cellType) {
    if (cellType == BLOCKADE)
        return INF;  // not passable
    if (cellType == INTERSTATEROAD || cellType == INTERSTATESTOP) return 24;

    return 50;
}


MinHeap* heapCreate(int capacity) {
    MinHeap *h = malloc(sizeof(MinHeap));
    h->data = malloc(sizeof(HeapNode) * capacity);
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void heapSwap(HeapNode *a, HeapNode *b) {
    HeapNode t = *a; *a = *b; *b = t;
}

void heapPush(MinHeap *h, int node, int fScore) {
    int i = h->size++;
    h->data[i].node = node;
    h->data[i].fScore = fScore;

    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->data[p].fScore <= h->data[i].fScore) break;
        heapSwap(&h->data[p], &h->data[i]);
        i = p;
    }
}

int heapPop(MinHeap *h) {
    int result = h->data[0].node;

    h->size--;
    h->data[0] = h->data[h->size];

    int i = 0;
    while (1) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int smallest = i;

        if (left < h->size && h->data[left].fScore < h->data[smallest].fScore)
            smallest = left;
        if (right < h->size && h->data[right].fScore < h->data[smallest].fScore)
            smallest = right;

        if (smallest == i) break;
        heapSwap(&h->data[i], &h->data[smallest]);
        i = smallest;
    }

    return result;
}

bool heapEmpty(MinHeap *h) {
    return h->size == 0;
}

// Path reconstruction

int* reconstruct(const int *cameFrom, int current, int *outLength) {
    int buffer[2000];
    int count = 0;
    if (cameFrom == NULL) return NULL;

    while (current != -1) {
        buffer[count++] = current;
        current = cameFrom[current];
    }

    // reverse the buffer
    int *path = malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++)
        path[i] = buffer[count - 1 - i];

    *outLength = count;
    return path;
}


// A* main algorithm
int* RunAstarPathFinding(const int *map, const int mapSize, const int pointA, const int pointB, int *outLength){
    const int total = mapSize * mapSize;

    int *cameFrom = malloc(sizeof(int) * total);
    int *gScore = malloc(sizeof(int) * total);
    int *fScore = malloc(sizeof(int) * total);

    for (int i = 0; i < total; i++) {
        cameFrom[i] = -1;
        gScore[i] = INF;
        fScore[i] = INF;
    }

    gScore[pointA] = 0;
    fScore[pointA] = heuristic(pointA, pointB, mapSize);

    MinHeap *openSet = heapCreate(total);
    heapPush(openSet, pointA, fScore[pointA]);

    while (!heapEmpty(openSet)) {

        int current = heapPop(openSet);

        //checks if current == goal of pointB if true then free memory and return the path
        if (current == pointB) {
            int *path = reconstruct(cameFrom, current, outLength);
            free(cameFrom); free(gScore); free(fScore);
            free(openSet->data); free(openSet);
            return path;
        }

        int cx, cy;
        IdxToCoords(current, mapSize, &cx, &cy);

        int neighbors[8];
        int ncount = 0;

        //Getting N,S,E,W neighbors to array
        if (cx > 0) neighbors[ncount++] = XYToIdx(cx-1, cy, mapSize);
        if (cx < mapSize-1) neighbors[ncount++] = XYToIdx(cx+1, cy, mapSize);
        if (cy > 0) neighbors[ncount++] = XYToIdx(cx, cy-1, mapSize);
        if (cy < mapSize-1) neighbors[ncount++] = XYToIdx(cx, cy+1, mapSize);

        //Getting NE, NW, SE, SW to neighbors array
        if (cx > 0 && cy > 0)
            neighbors[ncount++] = XYToIdx(cx-1, cy-1, mapSize);
        if (cx < mapSize-1 && cy > 0)
            neighbors[ncount++] = XYToIdx(cx+1, cy-1, mapSize);
        if (cx > 0 && cy < mapSize-1)
            neighbors[ncount++] = XYToIdx(cx-1, cy+1, mapSize);
        if (cx < mapSize-1 && cy < mapSize-1)
            neighbors[ncount++] = XYToIdx(cx+1, cy+1, mapSize);

        for (int i = 0; i < ncount; i++) {

            int nb = neighbors[i];

            int cost = movementCost(map[nb]);
            if (cost == INF) continue; // blocked road

            int tentative_g = gScore[current] + cost;

            if (tentative_g < gScore[nb]) {
                cameFrom[nb] = current;
                gScore[nb] = tentative_g;
                fScore[nb] = tentative_g + heuristicManhattan(nb, pointB, mapSize);

                heapPush(openSet, nb, fScore[nb]);
            }
        }
    }

    // no path found
    *outLength = 0;
    free(cameFrom); free(gScore); free(fScore);
    free(openSet->data); free(openSet);
    return NULL;
}


/**
 * This function takes the map and calculates the most optimal path from Start to End Goal.
 * The function then splits the path into sections and for each section navigating to a nearby rest stop.
 * @param map The map the program runs on
 * @param mapSize The Size of the map needed
 */
void Navigate(int *map, const int mapSize, const Destination destination) {
    int pathLength = 0;
    int *fullPath = malloc(sizeof(int) * (mapSize * mapSize));
    int fullPathLength = 0;

    // Get start and end points
    int startIdx = CheckCoordinateSet(map, destination.startX, destination.startY, mapSize);
    int goalIdx = CheckCoordinateSet(map, destination.endX, destination.endY, mapSize);


    //Use these for these lines for debugging
    startIdx = CheckCoordinateSet(map, 0, 0, mapSize);
    goalIdx = CheckCoordinateSet(map, 29, 29, mapSize);

    //print map with start and end
    map[startIdx] = ROUTE;
    map[goalIdx] = ROUTE;

    //Original path saved
    int *originalPath = RunAstarPathFinding(map, mapSize, startIdx, goalIdx, &pathLength);
    printf("\n");
    if (originalPath) {
        for (int i = 0; i < pathLength; i++) {
            // Print route
            printf("%d ", originalPath[i]);
            //map[path[i]] = ROUTE;
        }
        printf("\nPath length : %d\n", pathLength);
        PrintMapWPath(map, mapSize, originalPath, pathLength);
    }
    else {
        printf("No path found\n");
        PrintMap(map, mapSize);
    }
    printf("\n\n");

    free(originalPath);


/////////////////////////////////

    //vaiables in use

    int numSearchPoints = 0;
    int current = startIdx;
    int numSections = 0;
    int restStopIdx = 0;

    int baseSearchRadius = 5;
    const int drivingTime = 340; //equal to 13 tiles;
    int desiredType;

    int *numberStops = malloc(sizeof(int) * (mapSize * mapSize));
    int *searchPoints = malloc(sizeof(int)* (mapSize * mapSize));

    while (current != goalIdx) {
        //First Run should equal the original path,
        int *path = RunAstarPathFinding(map, mapSize, current, goalIdx, &pathLength);
        if (!path || pathLength <= 1) break;

        numSearchPoints = 0;
        DivideRoute(map, path, pathLength,
                    searchPoints,
                    &numSearchPoints,
                    drivingTime * 2/3);
        printf("numSearchPoints = %d\n", numSearchPoints);
        // Time spent driving aka section size = 13 tiles before first rest stop
        //if the path is too short the program returns the full path from start to end
        if (numSearchPoints == 0) {
            for (int i = 0; i < pathLength; i++)
                fullPath[fullPathLength++] = path[i];
            free(path);
            break;
        }

        //The route must be divided for the driver to follow regulations
        if (numSections == 0) {
            desiredType = 0; //Stop type can be both.
        }
        else {//numSections % 2 == 0 chose type 3 otherwise type 2
            desiredType = (numSections % 2 != 0) ? TYPE3STOP : TYPE2STOP;
        }

        //Find the nearest TYPE3STOP to the next section break
        int targetSection = searchPoints[0]; // next section point
        int t2 = LookForNeighbor(map, targetSection, mapSize, TYPE2STOP, baseSearchRadius);
        int t3 = LookForNeighbor(map, targetSection, mapSize, TYPE3STOP, baseSearchRadius);

        if (t2 ==-1 && t3 == -1) { //widedens scope
            t2 = LookForNeighbor(map, targetSection, mapSize, TYPE2STOP, ++baseSearchRadius);
            t3 = LookForNeighbor(map, targetSection, mapSize, TYPE3STOP, ++baseSearchRadius);
        }
        //if still no reststop found
        if (t2 <= -1 && t3 <= -1) {
            printf("No path found\n");
            free(path);
            break;
        }

        if (desiredType == 0) { //pick type closest
            if (t2 == -1 ) restStopIdx = t3;
            else if (t3 == -1 ) restStopIdx = t2;
            else {
                int distance2 = heuristicManhattan(targetSection, t2 , mapSize);
                int distance3 = heuristicManhattan(targetSection, t3 , mapSize);
                if (distance2 == distance3) {
                    int goalDistance2 = heuristicManhattan(t2, goalIdx, mapSize);
                    int goalDistance3 = heuristicManhattan(t3, goalIdx, mapSize);
                    restStopIdx = (goalDistance2 < goalDistance3) ? t2 : t3;
                }
                else {
                    restStopIdx = (distance2 < distance3 ? t2 : t3);
                }
            }
        } else if (desiredType == TYPE3STOP) {
            restStopIdx = (t3 != -1) ? t3 : t2;
        } else { // TYPE2STOP
            restStopIdx = (t2 != -1) ? t2 : t3;
        }

        if (restStopIdx == -1) {
            printf("Could not find rest stop of type 3 at target section %d", targetSection);
            free(path);
            break;
        }
        //frees path for next loop,

        //debugging print and checks
        int maxNodes = mapSize * mapSize;
        if (current < 0 || current >= maxNodes) { fprintf(stderr,"BAD current=%d\n", current); abort(); }
        if (targetSection < 0 || targetSection >= maxNodes) { fprintf(stderr,"BAD targetSection=%d\n", targetSection); abort(); }
        if (t2 < -1 || t2 >= maxNodes || t3 < -1 || t3 >= maxNodes) { fprintf(stderr,"BAD neighbor t2=%d t3=%d\n", t2, t3); abort(); }


        //Divide path into sections (this fills searchPointsType3)
        // Recalculate A* to the rest stop
        int *pathToStop = RunAstarPathFinding(map, mapSize,
            current, restStopIdx, &pathLength);

        // Append subsection to fullPath
        for (int i = 0; i < pathLength; i++) {
            // avoid duplicate node when paths connect
            if (fullPathLength == 0 || fullPath[fullPathLength - 1] != pathToStop[i]) {
                fullPath[fullPathLength++] = pathToStop[i];
            }
        }
        numberStops[numSections] = restStopIdx;
        numSections++;
        // Update current position to rest stop
        current = restStopIdx;

        // Loop continues and A* now runs from rest stop to goal
        free(pathToStop);
        free(path);
    }
    printPath(fullPath, fullPathLength);
    PrintMapWPath(map, mapSize, fullPath, fullPathLength);

    printf("\n");
    printf("number of stops : %d\n", numSections);

    for (int i = 0; i < numSections; i++) {
        printf("stop at index : %d of type %d ", numberStops[i], map[numberStops[i]]);
        int tempX, tempY;
        IdxToCoords(numberStops[i], mapSize, &tempX, &tempY);
        printf("coordinates: (%d, %d)\n", tempX, tempY);
    }

    //free memory
    free(fullPath);
    free(numberStops);
}



