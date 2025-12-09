//
// Created by rasmk on 20-11-2025.
//

#include "CheckCoordinateSetFunc.h"
#include "DefineConst.h"
#include "ConverterFunc.h"

#include <stdio.h>
#include <stdlib.h>

#define OUTOFBOUNDS (-1)
#define NOSPACEAVAILABLE (-2)


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

/*

int runTestIdx63() {
    int Map[] = {5,0,5,5,5,0,0,5,
                 0,0,5,5,5,0,0,0,
                 0,0,0,0,0,0,0,0,
                 5,0,0,5,5,0,0,0,
                 5,0,0,5,5,5,0,0,
                 0,0,0,5,5,5,0,0,
                 0,0,0,0,0,0,0,5,
                 5,0,0,0,0,0,5,5};

    int mapSize = 8;
    return CheckCoordinateSet(Map, 7, 7, mapSize);
}

int runTestIdx0() {
    int Map[] = {5,0,5,5,5,0,0,5,
                 0,0,5,5,5,0,0,0,
                 0,0,0,0,0,0,0,0,
                 5,0,0,5,5,0,0,0,
                 5,0,0,5,5,5,0,0,
                 0,0,0,5,5,5,0,0,
                 0,0,0,0,0,0,0,5,
                 5,0,0,0,0,0,5,5};

    int mapSize = 8;
    return CheckCoordinateSet(Map, 0, 0, mapSize);
}

int runTestIdx3() {
    int Map[] = {5,0,5,5,5,0,0,5,
                 0,0,5,5,5,0,0,0,
                 0,0,0,0,0,0,0,0,
                 5,0,0,5,5,0,0,0,
                 5,0,0,5,5,5,0,0,
                 0,0,0,5,5,5,0,0,
                 0,0,0,0,0,0,0,5,
                 5,0,0,0,0,0,5,5};

    int mapSize = 8;
    return CheckCoordinateSet(Map, 3, 0, mapSize);
}

int runTestIdx7() {
    int Map[] = {5,0,5,5,5,0,0,5,
                 0,0,5,5,5,0,0,0,
                 0,0,0,0,0,0,0,0,
                 5,0,0,5,5,0,0,0,
                 5,0,0,5,5,5,0,0,
                 0,0,0,5,5,5,0,0,
                 0,0,0,0,0,0,0,5,
                 5,0,0,0,0,0,5,5};

    int mapSize = 8;
    int res = 6;
    return CheckCoordinateSet(Map, 7, 0, mapSize);
}

int runTestIdx56() {
    int Map[] = {5,0,5,5,5,0,0,5,
                 0,0,5,5,5,0,0,0,
                 0,0,0,0,0,0,0,0,
                 5,0,0,5,5,0,0,0,
                 5,0,0,5,5,5,0,0,
                 0,0,0,5,5,5,0,0,
                 0,0,0,0,0,0,0,5,
                 5,0,0,0,0,0,5,5};

    int mapSize = 8;
    return CheckCoordinateSet(Map, 0, 7, mapSize);
}

int runTestIdx24() {
    int Map[] = {5,0,5,5,5,0,0,5,
                 0,0,5,5,5,0,0,0,
                 0,0,0,0,0,0,0,0,
                 5,0,0,5,5,0,0,0,
                 5,0,0,5,5,5,0,0,
                 0,0,0,5,5,5,0,0,
                 0,0,0,0,0,0,0,5,
                 5,0,0,0,0,0,5,5};

    int mapSize = 8;
    return CheckCoordinateSet(Map, 0, 3, mapSize);
}

int runTestIdx36() {
    int Map[] = {5,0,5,5,5,0,0,5,
                 0,0,5,5,5,0,0,0,
                 0,0,0,0,0,0,0,0,
                 5,0,0,5,5,0,0,0,
                 5,0,0,5,5,5,0,0,
                 0,0,0,5,5,5,0,0,
                 0,0,0,0,0,0,0,5,
                 5,0,0,0,0,0,5,5};

    int mapSize = 8;
    return CheckCoordinateSet(Map, 4, 4, mapSize);
}

int runTestIdx70() {
    int Map[] = {5,0,5,5,5,0,0,5,
                 0,0,5,5,5,0,0,0,
                 0,0,0,0,0,0,0,0,
                 5,0,0,5,5,0,0,0,
                 5,0,0,5,5,5,0,0,
                 0,0,0,5,5,5,0,0,
                 0,0,0,0,0,0,0,5,
                 5,0,0,0,0,0,5,5};

    int mapSize = 8;
    return CheckCoordinateSet(Map, 6, 8, mapSize);
}

int runTestIdxNULL() {
    int Map[] = {5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,5,5,
                 5,5,5,5,5,5,5,5};

    int mapSize = 8;
    return CheckCoordinateSet(Map, 5, 5, mapSize);
}


void runAllTests() {
    printf("Index63: %d\n", runTestIdx63());
    printf("Index0: %d\n", runTestIdx0());
    printf("Index3: %d\n", runTestIdx3());
    printf("Index7: %d\n", runTestIdx7());
    printf("Index56: %d\n", runTestIdx56());
    printf("Index24: %d\n", runTestIdx24());
    printf("Index36: %d\n", runTestIdx36());
    printf("Index70: %d\n", runTestIdx70());
    printf("IndexNULL: %d\n", runTestIdxNULL());
    }
*/