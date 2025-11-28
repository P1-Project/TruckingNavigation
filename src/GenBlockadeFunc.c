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


void GenBlockadeFunc(int *map, unsigned int mapSize, int numBlockades) {
    for (int i = 0; i < numBlockades; i++) {
        int row = rand() % mapSize;
        int col = rand() % mapSize;
        int idx = XYToIdx(row, col, mapSize);
        map[idx] = BLOCKADE; // 5 = blockade
    }


}

void GenerateClusterBlockades(int *map, unsigned int mapSize, int numClusters, int clusterSize) {
    for (int c = 0; c < numClusters; c++) {
        int centerRow = rand() % mapSize;
        int centerCol = rand() % mapSize;

        for (int dr = -clusterSize; dr <= clusterSize; dr++) {
            for (int dc = -clusterSize; dc <= clusterSize; dc++) {
                int r = centerRow + dr;
                int col = centerCol + dc;
                if (r >= 0 && r < mapSize && col >= 0 && col < mapSize) {
                    int idx = r * mapSize + col;
                    map[idx] = BLOCKADE;
                }
            }
        }
    }
}