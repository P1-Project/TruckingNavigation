//
// Created by steph on 08/12/2025.
//

#include <stdio.h>
#include <stdlib.h>

#include "DivideRouteFunc.h"
#include "DefineConst.h"

/**
 * This function divides a route into break points by simulating travel time between consecutive points on the route.
 * If adding the next move would exceed maxTime, it records the current point as a break and resets the timer.
 * @param map Pointer to the map array
 * @param route Pointer to the route array
 * @param routeLength Number of points on route
 * @param searchPoints Pointer to output array for break points
 * @param numberOfPoints Pointer to count of break points
 * @param maxTime Maximum time allowed before a break
 * @return Pointer to searchPoints
 */
int *DivideRoute(int *map, int *route, int routeLength, int *searchPoints, int *numberOfPoints, int maxTime) {
    int timer = 0;

    // Iterates through move 'pairs'
    for (int i = 0; i < routeLength - 1; ++i) {
        int current = route[i];
        int next = route[i+1];
        int moveCost;

        int currentIsInterstate = (map[current] == INTERSTATEROAD) || (map[current] == INTERSTATESTOP);
        int nextIsInterstate = (map[next] == INTERSTATEROAD) || (map[next] == INTERSTATESTOP);

        // Decide move cost
        if (currentIsInterstate && nextIsInterstate) {
            moveCost = 24;
        } else {
            moveCost = 40;
        }

        // Check if next move pushes us over the max time
        if (timer + moveCost > maxTime) {
            searchPoints[*numberOfPoints] = current;
            (*numberOfPoints)++;
            timer = 0;
        }

        timer += moveCost;
    }

    return searchPoints;
}
