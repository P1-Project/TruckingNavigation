#include "AStarPathFinding.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "ConverterFunc.h"
#include "DefineConst.h"
#include "DefineStruct.h"

void TestAstarPathFindingConnection(void) {
    printf("TestAstarPathFindingConnection\n");
}

#define INF 999999999
// Heuristic (Euclidean Distance)
int heuristic(int a, int b, int mapSize) {
    int ax, ay, bx, by;
    IdxToCoords(a, mapSize, &ax, &ay);
    IdxToCoords(b, mapSize, &bx, &by);
    int deltaX = ax - bx;
    int deltaY = ay - by;

    return (int)sqrt(deltaX * deltaX + deltaY * deltaY);
}
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
    if (cellType == INTERSTATEROAD || cellType == INTERSTATESTOP) return 1;

    return 2;        // simple version: all roads cost 1
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
        int l = 2*i + 1;
        int r = 2*i + 2;
        int smallest = i;

        if (l < h->size && h->data[l].fScore < h->data[smallest].fScore)
            smallest = l;
        if (r < h->size && h->data[r].fScore < h->data[smallest].fScore)
            smallest = r;

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
int* runAstarPathFinding(const int *map, const int mapSize, const int pointA, const int pointB, int *outLength){
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

        if (cx > 0) neighbors[ncount++] = XYToIdx(cx-1, cy, mapSize);
        if (cx < mapSize-1) neighbors[ncount++] = XYToIdx(cx+1, cy, mapSize);
        if (cy > 0) neighbors[ncount++] = XYToIdx(cx, cy-1, mapSize);
        if (cy < mapSize-1) neighbors[ncount++] = XYToIdx(cx, cy+1, mapSize);

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
