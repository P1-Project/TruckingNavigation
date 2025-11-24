//
// Created by rasmk on 22-11-2025.
//

#ifndef TRUCKINGNAVIGATION_DIJKSTRAALGORIGTHM_H
#define TRUCKINGNAVIGATION_DIJKSTRAALGORIGTHM_H
#define TERRAIN 1

void TestDijkstraAlgorithmCon();
int *dijkstra(const int *map, int mapSize, int start, int goal, int *outPathLength);
void runDijstraks(int *map, signed int mapSize, int startIndex, int goalIndex);

typedef struct {
    int index;
    int cost;
} Node;

typedef struct {
    Node *data;
    int size;
    int capacity;
} MinHeap;


#endif //TRUCKINGNAVIGATION_DIJKSTRAALGORIGTHM_H