#include "CheckCoordinateSetFunc.h"
#include "DefineConst.h"
#include "HelperFunc.h"
#include <stdio.h>
#include <stdlib.h>

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

    if (x < 0 || x >= mapSize || y < 0 || y >= mapSize) {
        return OUTOFBOUNDS;         // Return error if destination is out of bounds
    };

    // Return index if available
    int destination = XYToIdx(x, y, mapSize);
    if (map[destination] != BLOCKADE) return destination;

    for (int r = 1; r <= mapSize; ++r) {
        for (int dx = -r; dx <= r; ++dx) {
            for (int dy = -r; dy <= r; ++dy) {
                // Skip the cells which are within the search radius 'ring'
                if (abs(dx) != r && abs(dy) != r) continue;

                int nx = x + dx;
                int ny = y + dy;

                if (nx < 0 || nx >= mapSize || ny < 0 || ny >= mapSize) continue; // Skip ahead if the current cell is out of bounds

                int idxDestination = XYToIdx(nx, ny, mapSize); // Find corresponding index

                if (map[idxDestination] != BLOCKADE) {          // Return if current cell is not blockade
                    return idxDestination;
                }
            }
        }
    }

    /*int index_i = XYToIdx(x, y, mapSize);
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
        if (j >= 0 && j < mapSize*mapSize && j%mapSize < index_i%mapSize) {
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
    }                                              // Maybe convert back to x,y? */


    return NOSPACEAVAILABLE;                       // Return error if no space available
}