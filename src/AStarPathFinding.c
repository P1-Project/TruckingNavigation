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


int chebyshevDistance(const int a, const int b, const int mapSize) {
    int ax, ay, bx, by;
    IdxToCoords(a, mapSize, &ax, &ay);
    IdxToCoords(b, mapSize, &bx, &by);

    int deltaX = abs(ax - bx);
    int deltaY = abs(ay - by);

    // Chebyshev distance: max of deltaX and deltaY
    return (deltaX > deltaY) ? deltaX : deltaY;
}



// Heuristic (Euclidean Distance)
int HeuristicEuclidean(const int a, const int b, const int mapSize) {
    int ax, ay, bx, by;
    IdxToCoords(a, mapSize, &ax, &ay);
    IdxToCoords(b, mapSize, &bx, &by);
    const int deltaX = ax - bx;
    const int deltaY = ay - by;

    return (int)sqrt(deltaX * deltaX + deltaY * deltaY);
}

// Heuristic (Manhattan)
int HeuristicManhattan(int a, int b, int mapSize) {
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
int* RunAstarPathFindingChebyshev(const int *map, const int mapSize, const int pointA, const int pointB, int *outLength){
    const int total = mapSize * mapSize;

    int *cameFrom = malloc(sizeof(int) * total);
    int *costSoFar = malloc(sizeof(int) * total);
    int *estimatedTotalCost = malloc(sizeof(int) * total);

    for (int i = 0; i < total; i++) {
        cameFrom[i] = -1;
        costSoFar[i] = INF;
        estimatedTotalCost[i] = INF;
    }

    costSoFar[pointA] = 0; //current score
    estimatedTotalCost[pointA] = chebyshevDistance(pointA, pointB, mapSize); //Score from current to goal,

    MinHeap *openSet = heapCreate(total); //initializes the min heap tree
    heapPush(openSet, pointA, estimatedTotalCost[pointA]); //push the first node, point A with the

    while (!heapEmpty(openSet)) {

        int current = heapPop(openSet);

        //checks if current == goal of pointB if true then free memory and return the path
        if (current == pointB) {
            int *path = reconstruct(cameFrom, current, outLength);
            free(cameFrom); free(costSoFar); free(estimatedTotalCost);
            free(openSet->data); free(openSet);
            return path; //Returns path if goal is reached
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

        //loops through the neighbors
        for (int i = 0; i < ncount; i++) {
            //sets nb as the array value at that index
            int nb = neighbors[i];
            //cost is calculated
            int cost = movementCost(map[nb]); //normal road is more than interstate
            if (cost == INF) continue; // blocked road

            int costThroughCurrent = costSoFar[current] + cost; //adding cost of the path to the node plus the next cost

            if (costThroughCurrent < costSoFar[nb]) {
                cameFrom[nb] = current; //curent becoms camefrom[nb]
                costSoFar[nb] = costThroughCurrent; //Setting costSoFar as costThroughCurrent
                //Estimating cost to goal
                estimatedTotalCost[nb] = costThroughCurrent + chebyshevDistance(nb, pointB, mapSize);

                //Adding the node to the min-heap
                heapPush(openSet, nb, estimatedTotalCost[nb]);
            }
        }
    }

    // no path found
    *outLength = 0;
    free(cameFrom); free(costSoFar); free(estimatedTotalCost);
    free(openSet->data); free(openSet);
    return NULL; //returns NULL if no path found
}


// A* main algorithm
int* RunAstarPathFindingManhattan(const int *map, const int mapSize, const int pointA, const int pointB, int *outLength){
    const int total = mapSize * mapSize;

    int *cameFrom = malloc(sizeof(int) * total);
    int *costSoFar = malloc(sizeof(int) * total);
    int *estimatedTotalCost = malloc(sizeof(int) * total);

    for (int i = 0; i < total; i++) {
        cameFrom[i] = -1;
        costSoFar[i] = INF;
        estimatedTotalCost[i] = INF;
    }

    costSoFar[pointA] = 0; //current score
    estimatedTotalCost[pointA] = HeuristicManhattan(pointA, pointB, mapSize); //Score from current to goal,

    MinHeap *openSet = heapCreate(total); //initializes the min heap tree
    heapPush(openSet, pointA, estimatedTotalCost[pointA]); //push the first node, point A with the

    while (!heapEmpty(openSet)) {

        int current = heapPop(openSet);

        //checks if current == goal of pointB if true then free memory and return the path
        if (current == pointB) {
            int *path = reconstruct(cameFrom, current, outLength);
            free(cameFrom); free(costSoFar); free(estimatedTotalCost);
            free(openSet->data); free(openSet);
            return path; //Returns path if goal is reached
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

        //loops through the neighbors
        for (int i = 0; i < ncount; i++) {
            //sets nb as the array value at that index
            int nb = neighbors[i];
            //cost is calculated
            int cost = movementCost(map[nb]); //normal road is more than interstate
            if (cost == INF) continue; // blocked road

            int costThroughCurrent = costSoFar[current] + cost; //adding cost of the path to the node plus the next cost

            if (costThroughCurrent < costSoFar[nb]) {
                cameFrom[nb] = current; //curent becoms camefrom[nb]
                costSoFar[nb] = costThroughCurrent; //Setting costSoFar as costThroughCurrent
                //Estimating cost to goal
                estimatedTotalCost[nb] = costThroughCurrent + HeuristicManhattan(nb, pointB, mapSize);

                //Adding the node to the min-heap
                heapPush(openSet, nb, estimatedTotalCost[nb]);
            }
        }
    }

    // no path found
    *outLength = 0;
    free(cameFrom); free(costSoFar); free(estimatedTotalCost);
    free(openSet->data); free(openSet);
    return NULL; //returns NULL if no path found
}



// A* main algorithm
int* RunAstarPathFindingEuclidean(const int *map, const int mapSize, const int pointA, const int pointB, int *outLength){
    const int total = mapSize * mapSize;

    int *cameFrom = malloc(sizeof(int) * total);
    int *costSoFar = malloc(sizeof(int) * total);
    int *estimatedTotalCost = malloc(sizeof(int) * total);

    for (int i = 0; i < total; i++) {
        cameFrom[i] = -1;
        costSoFar[i] = INF;
        estimatedTotalCost[i] = INF;
    }

    costSoFar[pointA] = 0; //current score
    estimatedTotalCost[pointA] = HeuristicEuclidean(pointA, pointB, mapSize); //Score from current to goal,

    MinHeap *openSet = heapCreate(total); //initializes the min heap tree
    heapPush(openSet, pointA, estimatedTotalCost[pointA]); //push the first node, point A with the

    while (!heapEmpty(openSet)) {

        int current = heapPop(openSet);

        //checks if current == goal of pointB if true then free memory and return the path
        if (current == pointB) {
            int *path = reconstruct(cameFrom, current, outLength);
            free(cameFrom); free(costSoFar); free(estimatedTotalCost);
            free(openSet->data); free(openSet);
            return path; //Returns path if goal is reached
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

        //loops through the neighbors
        for (int i = 0; i < ncount; i++) {
            //sets nb as the array value at that index
            int nb = neighbors[i];
            //cost is calculated
            int cost = movementCost(map[nb]); //normal road is more than interstate
            if (cost == INF) continue; // blocked road

            int costThroughCurrent = costSoFar[current] + cost; //adding cost of the path to the node plus the next cost

            if (costThroughCurrent < costSoFar[nb]) {
                cameFrom[nb] = current; //curent becoms camefrom[nb]
                costSoFar[nb] = costThroughCurrent; //Setting costSoFar as costThroughCurrent
                //Estimating cost to goal
                estimatedTotalCost[nb] = costThroughCurrent + HeuristicEuclidean(nb, pointB, mapSize);

                //Adding the node to the min-heap
                heapPush(openSet, nb, estimatedTotalCost[nb]);
            }
        }
    }

    // no path found
    *outLength = 0;
    free(cameFrom); free(costSoFar); free(estimatedTotalCost);
    free(openSet->data); free(openSet);
    return NULL; //returns NULL if no path found
}





