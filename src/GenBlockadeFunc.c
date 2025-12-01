//
// Created by rasmk on 20-11-2025.
//

#include "GenBlockadeFunc.h"
#include "MapGenFunc.h"
#include "ConverterFunc.h"
#include "DefineStruct.h"
#include "DefineConst.h"


#include <stdio.h>
#include <stdlib.h>

void TestConGenBlockadeFunc() {
    printf("Hello World from TestConGenBlockadeFunc\n");
}


void GenBlockadeFunc(int *map, int mapSize, int numBlockades) {
    for (int i = 0; i < numBlockades; i++) {
        int row = rand() % mapSize;
        int col = rand() % mapSize;
        int idx = XYToIdx(row, col, mapSize);
        map[idx] = BLOCKADE; // 5 = blockade
    }


}

void GenClusterBlockadeFunc(int *map, int mapSize, int numClusters, int clusterSize) {
    for (int c = 0; c < numClusters; c++) {
        int centerRow = rand() % mapSize;
        int centerCol = rand() % mapSize;

        for (int dr = -clusterSize; dr <= clusterSize; dr++) {
            for (int dc = -clusterSize; dc <= clusterSize; dc++) {
                int row = centerRow + dr;
                int col = centerCol + dc;
                if (row >= 0 && row < mapSize && col >= 0 && col < mapSize) {
                    int idx = row * mapSize + col;
                    map[idx] = BLOCKADE;
                }
            }
        }
    }
}