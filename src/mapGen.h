//
// Created by rasmk on 19-11-2025.
//

#ifndef TRUCKINGNAVIGATION_MAPGEN_H
#define TRUCKINGNAVIGATION_MAPGEN_H
void TestMapGenConcetion(void);
int XYToIndex(int x, int y, int mapSize);
void PrintMap(int *map, int mapSize);
void GenRandomMap(int *map, const unsigned int mapSize);
#endif //TRUCKINGNAVIGATION_MAPGEN_H