//
// Created by rasmk on 22-11-2025.
//

#include "ConverterFunc.h"

#include <stdlib.h>
#include <stdio.h>

/**
 *
 * @param x x coordinate
 * @param y y coordinate
 * @param mapSize Size of the map
 * @return Returns the index in the map for that coordinate set
 */
int XYToIdx(int x, int y, int mapSize) {
    return y * mapSize + x;
}


/**
 *
 * @param index The specific index in the map array
 * @param mapSize The width of the map
 * @param x pointer for x coordinate to be returned
 * @param y pointer for y coordinate to be returned
 */
void IdxToCoords(int index, int mapSize, int *x, int *y) {
    *x = index % mapSize;
    *y = index / mapSize;
}

int randomBetween(int a, int b) {
    return a + rand() % (b - a + 1);
}

/**
 * This function searches for a specific neighbor, in a square one column at a time, around a chosen point.
 * It starts at the top left of the square.
 * @param map Pointer to the map you want to search in
 * @param index Index of the point you want to search from
 * @param mapSize Size of the map you're searching in
 * @param neighbor The integer value of the neighbor. E.g. 5 for BLOCKADE
 * @param maxRadius The max radius you want to search in. Choose mapsize here, if you want to search the entire map
 * @return If no neighbor is found -1 is returned. Else, the index of the first found neighbor is returned.
 */
int LookForNeighbor(const int* map, int index, int mapSize, int neighbor, int maxRadius) {
    int x, y;
    IdxToCoords(index, mapSize, &x, &y);

    // search
    for (int r = 1; r <= maxRadius; ++r) {
        for (int dx = -r; dx <= r; ++dx) {
            for (int dy = -r; dy <= r; ++dy) {
                // Skip the cells which are within the search radius 'ring'
                if (abs(dx) != r && abs(dy) != r) continue;

                int nx = x + dx;
                int ny = y + dy;

                //printf("Checking (%d, %d)\n", nx, ny);

                if (nx < 0 || nx >= mapSize || ny < 0 || ny >= mapSize) continue; // Skip ahead if the current cell is out of bounds
                //printf("(%d, %d) is within bounds. Continuing\n", nx, ny);

                int neighborIndex = XYToIdx(nx, ny, mapSize); // find its index

                // check if current cell matches the neighbor type we’re looking for
                if (map[neighborIndex] == neighbor) {
                    //printf("Neighbor found at (%d, %d). Returning\n", nx, ny);
                    // neighbor found, returning index
                    return neighborIndex;
                }
            }
        }
    }

    // No neighbor found
    return -1;

    /*
    Search pattern visualized
    00: point not checked
    Number (1, 2, 3...): order which points get checked
    -S: points that get skipped

    00 00 00 00 00      09 14 16 18 20
    00 01 04 06 00      10 -S -S -S 21
    00 02 -S 07 00  ->  11 -S -S -S 22
    00 03 05 08 00      12 -S -S -S 23
    00 00 00 00 00      13 15 17 19 24
    */
}