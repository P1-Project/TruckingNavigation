//
// Created by rasmk on 22-11-2025.
//

#ifndef TRUCKINGNAVIGATION_CONVERTERFUNC_H
#define TRUCKINGNAVIGATION_CONVERTERFUNC_H
int XYToIdx(int x, int y, int mapSize);
void IdxToCoords(int index, int mapSize, int *x, int *y);
int randomBetween(int a, int b);
#endif //TRUCKINGNAVIGATION_CONVERTERFUNC_H