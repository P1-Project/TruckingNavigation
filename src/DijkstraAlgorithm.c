//
// Created by rasmk on 22-11-2025.
//

#include "DijkstraAlgorithm.h"

#include <stdbool.h>
#include <stdio.h>
#include "ConverterFunc.h"

void TestDijkstraAlgorithmCon() {
    printf("Testing DijkstraAlgorithmCon\n");
}


#include <stdlib.h>

#define INF 999999999


//
// PRIORITY QUEUE (MIN-HEAP)
//


/**
 * initiates the MinHeap tree for storage of nodes
 * @param heap Struct of the type MinHeap
 * @param cap capacity of the heap
 */
void heap_init(MinHeap *heap, int cap) {
    heap->data = malloc(sizeof(Node) * cap);
    heap->size = 0;
    heap->capacity = cap;
}

void heap_push(MinHeap *h, int index, int cost) {
    int i = h->size++;
    h->data[i].index = index;
    h->data[i].cost = cost;

    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->data[p].cost <= h->data[i].cost) break;
        Node tmp = h->data[p];
        h->data[p] = h->data[i];
        h->data[i] = tmp;
        i = p;
    }
}

Node heap_pop(MinHeap *h) {
    Node res = h->data[0];
    h->data[0] = h->data[--h->size];

    int i = 0;
    while (1) {
        int l = i * 2 + 1;
        int r = i * 2 + 2;
        int smallest = i;

        if (l < h->size && h->data[l].cost < h->data[smallest].cost) smallest = l;
        if (r < h->size && h->data[r].cost < h->data[smallest].cost) smallest = r;

        if (smallest == i) break;

        Node tmp = h->data[smallest];
        h->data[smallest] = h->data[i];
        h->data[i] = tmp;

        i = smallest;
    }

    return res;
}

int heap_empty(MinHeap *h) {
    return h->size == 0;
}

//Change here for tilecost
int cost_of_tile(int t) {
    switch(t) {
        case 0: return 2;   // road
        case 1: return 1;   // highway
        case 2: return 5;   // slow terrain
        default: return 999999; // fallback
    }
}

//
// DIJKSTRA ON 1D ARRAY (representing 2D grid)
//
int *dijkstra(const int *map, int mapSize, int start, int goal, int *outPathLength){
    int total = mapSize * mapSize;

    int *dist = malloc(sizeof(int) * total);
    int *prev = malloc(sizeof(int) * total);
    bool *visited = calloc(total, sizeof(bool));

    for (int i = 0; i < total; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }

    dist[start] = 0;

    MinHeap pq;
    heap_init(&pq, total);
    heap_push(&pq, start, 0);

    while (!heap_empty(&pq)) {
        Node node = heap_pop(&pq);
        int u = node.index;

        if (visited[u]) continue;
        visited[u] = true;

        if (u == goal) break;

        int ux, uy;
        IdxToCoords(u, mapSize, &ux, &uy);

        const int dx[4] = {1, -1, 0, 0};
        const int dy[4] = {0, 0, 1, -1};


        for (int i = 0; i < 4; i++) {
            int nx = ux + dx[i];
            int ny = uy + dy[i];
            if (nx < 0 || ny < 0 || nx >= mapSize || ny >= mapSize) continue;

            int v = XYToIdx(nx, ny, mapSize);
            if (visited[v]) continue;

            int tile = map[v];
            if (tile == TERRAIN) continue;

            int weight = cost_of_tile(tile);
            int newDist = dist[u] + weight;

            if (newDist < dist[v]) {
                dist[v] = newDist;
                prev[v] = u;
                heap_push(&pq, v, newDist);
            }
        }
    }

    //Reconstruct path
    int current = goal;
    int count = 0;

    while (current != -1) {
        count++;
        current = prev[current];
    }

    int *path = malloc(sizeof(int) * count);
    *outPathLength = count;

    current = goal;
    for (int i = count - 1; i >= 0; i--) {
        path[i] = current;
        current = prev[current];
    }
    //frees the memory to avoid it being leaked
    free(dist);
    free(prev);
    free(visited);
    free(pq.data);

    return path;
}



void runDijstraks(int *map, signed int mapSize, int startIndex, int goalIndex) {
    int pathLen;
    int *path = dijkstra(map, mapSize, startIndex, goalIndex, &pathLen);

    printf("Path:\n");
    printf("Path:\n");
    for (int i = 0; i < pathLen; i++) {
        printf("%d ", path[i]);
    }
    printf("\nPath Length: %d\n", pathLen);

    for (int i = 0; i <pathLen; i++) {
        map[path[i]] = 'H'; //sets highway to H
    }
    free(path);
}