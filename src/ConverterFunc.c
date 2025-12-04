//
// Created by rasmk on 22-11-2025.
//

#include "ConverterFunc.h"

#include <stdlib.h>

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

int LookForNeighbor(const int* map, int index, int mapSize, int neighbor, int maxRadius) {
    int x, y;
    IdxToCoords(index, mapSize, &x, &y);

    // search
    for (int r = 1; r <= maxRadius; ++r) {
        for (int dx = -r; dx <= r; ++dx) {
            for (int dy = -r; dy <= r; ++dy) {
                if (dx == 0 && dy == 0) continue; // skip the starting cell itself

                // If the absolute value of x AND y are both under the current radius, we are inside of a square we have already checked.
                if (abs(dx) < r && abs(dy) < r) continue;  // skip inner squares where we've already checked.

                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && nx < mapSize && ny >= 0 && ny < mapSize) { // check if the current spot is within the map
                    int neighborIndex = XYToIdx(nx, ny, mapSize); // find its index

                    // check if current cell matches the neighbor type we’re looking for
                    if (map[neighborIndex] == neighbor) {
                        // neighbor found, returning index
                        return neighborIndex;
                    }
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