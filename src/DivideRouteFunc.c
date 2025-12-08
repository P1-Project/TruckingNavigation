//
// Created by steph on 08/12/2025.
//

#include "DivideRouteFunc.h"

#include <stdlib.h>

#include "DefineConst.h"

int RunDivideRoute() {
    int mapSize = 5;
    int map[25] = {
        0, 1, 0, 0, 0,
        0, 1, 0, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0
    };
    int route[] = {1, 6, 12, 17, 22};
    int routeLength = 5;

    int *searchPoints = malloc(sizeof(int)*mapSize*mapSize);

    searchPoints = DivideRoute(map, route, routeLength, searchPoints);

    free(searchPoints);

    return 0;
}

int *DivideRoute(int *map, int *route, int routeLength, int *searchPoints) {
    int timer = 0, numberOfPoints = 0;

    for (int i = 0; i < routeLength; ++i) {
        if (((map[route[i]] == INTERSTATEROAD) || (map[route[i]] == INTERSTATESTOP)) &&
            ((map[route[i+1]] == INTERSTATEROAD) || (map[route[i+1]] == INTERSTATESTOP))) {
            timer += 24;
        } else {
            timer += 40;
        }

        if (timer >= 150) {
            searchPoints[numberOfPoints] = route[i];
            numberOfPoints++;
            timer = 0;
        }
    }

    return searchPoints;
}
