//
// Created by rasmk on 20-11-2025.
//

#include "GetDestinationFunc.h"
#include "HelperFunc.h"
#include "DefineConst.h"
#include "DefineStruct.h"

#include <time.h>
#include <stdio.h>

void GetDestinationManual(Destination *destination, int mapSize) {
    printf("Enter start X coordinate (0-%d): ", mapSize - 1);
    scanf("%d", &destination->startX);
    printf("Enter start Y coordinate (0-%d): ", mapSize - 1);
    scanf("%d", &destination->startY);
    printf("Enter end X coordinate (0-%d): ", mapSize - 1);
    scanf("%d", &destination->endX);
    printf("Enter end Y coordinate (0-%d): ", mapSize - 1);
    scanf("%d", &destination->endY);
}

void GetDestinationRandom(Destination *destination, int mapSize) {
    // Random starting point
    destination->startX = rand() % mapSize;
    destination->startY = rand() % mapSize;

    // Generate end point on the opposite side
    // If start is in left half, put end in right half
    if (destination->startX < mapSize / 2) {
        destination->endX = mapSize / 2 + rand() % (mapSize / 2);
    } else {
        destination->endX = rand() % (mapSize / 2);
    }

    // If start is in top half, put end in the bottom half
    if (destination->startY < mapSize / 2) {
        destination->endY = mapSize / 2 + rand() % (mapSize / 2);
    } else {
        destination->endY = rand() % (mapSize / 2);
    }
}

// What has to go in the main file

void runDestination(Destination *destination) {
    int choice;

    // Initialize random
    srand(time(NULL));

    printf("Choose mode:\n");
    printf("Choose 1 if you want to enter coordinates manually\n");
    printf("Choose 0 if you want the coordinates to be generated randomly\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        GetDestinationManual(destination, MAPSIZE);
    } else {
        GetDestinationRandom(destination, MAPSIZE);
    }

    printf("\n---Route Information---\n");
    printf("Start Point: (%d, %d)\n", destination->startX, destination->startY);
    printf("End Point: (%d, %d)\n", destination->endX, destination->endY);



}


