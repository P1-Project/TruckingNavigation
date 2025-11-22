//
// Created by rasmk on 22-11-2025.
//

#include "ConverterFunc.h"

int XYToIdx(int x, int y, int width) {
    return y * width + x;
}

void IdxToCoords(int index, int width, int *x, int *y) {
    *x = index % width;
    *y = index / width;
}
