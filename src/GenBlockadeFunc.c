//
// Created by rasmk on 20-11-2025.
//

#include "GenBlockadeFunc.h"
#include "HelperFunc.h"
#include "DefineConst.h"


#include <stdio.h>
#include <stdlib.h>

void TestConGenBlockadeFunc() {
    printf("Hello World from TestConGenBlockadeFunc\n");
}


void GenBlockadeFunc(int *map, const int mapSize, const int numBlockades) {
    for (int i = 0; i < numBlockades; i++) {
        const int row = rand() % mapSize - 1;
        const int col = rand() % mapSize - 1;
        const int idx = XYToIdx(row, col, mapSize);
        if (map[idx] == BLOCKADE) {
            i--;
            continue;
        }
        map[idx] = BLOCKADE; // 5 = blockade
    }
}

void GenClusterBlockadeFunc(int *map, const int mapSize, const int numClusters, const int clusterSize) {
    for (int c = 0; c < numClusters; c++) {
        const int centerRow = rand() % mapSize - 1;
        const int centerCol = rand() % mapSize - 1;

        for (int dr = -clusterSize; dr <= clusterSize; dr++) {
            for (int dc = -clusterSize; dc <= clusterSize; dc++) {
                const int row = centerRow + dr;
                const int col = centerCol + dc;
                if (row >= 0 && row < mapSize && col >= 0 && col < mapSize) {
                    const int idx = XYToIdx(row, col, mapSize);
                    map[idx] = BLOCKADE;
                }
            }
        }
    }
}