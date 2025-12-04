//
// Created by rasmk on 22-11-2025.
//

#ifndef TRUCKINGNAVIGATION_CONVERTERFUNC_H
#define TRUCKINGNAVIGATION_CONVERTERFUNC_H
int XYToIdx(int x, int y, int mapSize);
void IdxToCoords(int index, int mapSize, int *x, int *y);
int randomBetween(int a, int b);
int LookForNeighbor(const int* map, int index, int mapSize, int neighbor, int maxRadius);

#endif //TRUCKINGNAVIGATION_CONVERTERFUNC_H