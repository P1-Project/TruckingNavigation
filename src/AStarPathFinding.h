
#ifndef TRUCKINGNAVIGATION_ASTARPATHFINDING_H
#define TRUCKINGNAVIGATION_ASTARPATHFINDING_H
#include <stdbool.h>

#include "DefineStruct.h"

// Priority Queue (min-heap)
typedef struct {
    int nIndex;
    int fScore;
} HeapNode;

typedef struct {
    HeapNode *data;
    int size;
    int capacity;
} MinHeap;
void HeapSwap(HeapNode *a, HeapNode *b);
void HeapPush(MinHeap *h, int node, int fScore);
int HeapPop(MinHeap *h);
bool HeapEmpty(MinHeap *h);
int* Reconstruct(const int *cameFrom, int current, int *outLength);


int HeuristicManhattan(int a, int b, int mapSize);
int HeuristicEuclidean(int a, int b, int mapSize);
int HeuristicChebyshev(int a, int b, int mapSize);

void TestAstarPathFindingConnection(void);

int* RunAstarPathFindingChebyshev(const int *map, int mapSize, int pointA, int pointB, int *outLength);
int* RunAstarPathFindingEuclidean(const int *map, int mapSize, int pointA, int pointB, int *outLength);
int* RunAstarPathFindingManhattan(const int *map, int mapSize, int pointA, int pointB, int *outLength);



#endif //TRUCKINGNAVIGATION_ASTARPATHFINDING_H