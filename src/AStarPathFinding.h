
#ifndef TRUCKINGNAVIGATION_ASTARPATHFINDING_H
#define TRUCKINGNAVIGATION_ASTARPATHFINDING_H
#include <stdbool.h>

// Priority Queue (min-heap)
typedef struct {
    int node;
    int fScore;
} HeapNode;

typedef struct {
    HeapNode *data;
    int size;
    int capacity;
} MinHeap;
void heapSwap(HeapNode *a, HeapNode *b);
void heapPush(MinHeap *h, int node, int fScore);
int heapPop(MinHeap *h);
bool heapEmpty(MinHeap *h);
int* reconstruct(const int *cameFrom, int current, int *outLength);

int* runAstarPathFinding(const int *map, int mapSize,
    int pointA, int pointB, int *outLength);
void TestAstarPathFindingConnection(void);
#endif //TRUCKINGNAVIGATION_ASTARPATHFINDING_H