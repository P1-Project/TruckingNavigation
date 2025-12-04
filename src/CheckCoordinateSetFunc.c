//
// Created by rasmk on 20-11-2025.
//

#include "CheckCoordinateSetFunc.h"
#include  "DefineConst.h"
#include  "ConverterFunc.h"

#include <stdio.h>

void TestConCheckCoordinateSetFunc() {
    printf("Hello, World from CheckCoordinateSetFunc!\n");
}

/**
 * Description: Validating a given destination (x,y) - changing to nearest index if index is a blockade
 * @param map
 * @param x
 * @param y
 * @param mapSize
 * @return Updated index
 */
int CheckCoordinateSet(int *map, int x, int y, int mapSize){
    int index_i = XYToIdx(x, y, mapSize);
    if (map[index_i] != BLOCKADE)
        return index_i;

    for (int r = 1; r < mapSize; r++) {                // Expands with one round for each loop

        int j = index_i + 1 * r;                       // Right
            if (j <= mapSize * mapSize && j%mapSize > index_i %mapSize)
            if (map[j] != BLOCKADE) return j;

        j = index_i - 1 * r;                           // Left
        if (j% mapSize < index_i%mapSize) {
            if (map[j] != BLOCKADE) return j;
        }

        j = index_i - mapSize * r;                     // Up
        if (j > 0 && map[j] != BLOCKADE) return j;

        j = index_i + mapSize * r;                    // Down
            if (j < mapSize * mapSize && map[j] != BLOCKADE) return j;


        j = index_i + (mapSize + 1 * r);              // Diagonal down right
        if (j < mapSize * mapSize && j%mapSize <= index_i%mapSize) {
            if (j > 0 && map[j] != BLOCKADE) return j;
        }

        j = index_i + (mapSize - 1 * r);             // Diagonal down left
        if (j >= 0 && j%mapSize < index_i%mapSize) {
            if (j > 0 && map[j] != BLOCKADE) return j;
        }

        j = index_i - mapSize + (1*r);              // Diagonal up right
        if (j >= 0 && j%mapSize > index_i%mapSize) {
            if (j > 0 && map[j] != BLOCKADE) return j;
        }

        j = index_i - mapSize - (1 * r);            // Diagonal up left
        if (j >= 0 && j%mapSize < index_i%mapSize) {
            if (map[j] != BLOCKADE) return j;
        }
    }                                              // Maybe convert back to x,y?

return -1;                                         // No space available
}