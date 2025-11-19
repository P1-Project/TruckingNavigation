//
// Created by rasmk on 19-11-2025.
//

#include "mapGen.h"

#include <stdio.h>
#include <stdlib.h>

void TestMapGenConcetion(void) {
    printf("Testing con from mapGen\n");
}

void PrintMap(int *map, int mapSize) {
    for (int i = 0; i <mapSize; i++) {
        if (i % 10 == 0) printf("\n");
        printf("%d ", map[i]);
    }
}

void GenRandomMap(int *map) {
    for (int i = 0; i < 100; i++) {
        map[i] = 0;
    }
}


int main() {
    int mapSize;
    int map[100];
    GenRandomMap(map);
    PrintMap(map, 100);
    return 0;
}
