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