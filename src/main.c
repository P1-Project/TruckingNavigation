#include <stdio.h>
#include "MapGenFunc.h"
#include "GetDestinationFunc.h"
#include "DefineConst.h"
#include "DefineStruct.h"
#include "Navigation.h"

int main(void) {
    printf("Hello, World!\n");
    char input;

    do {
        printf("Do you want a random map (r) or map (a), (b) or (c)?\n");
        scanf(" %c", &input);
    } while (!(input == 'r' || input == 'a' || input == 'b' || input == 'c'));

    switch (input) {
        case 'r':
            printf("Printing random map");
            srand(time(NULL)); //used to gen a random seed
            break;
        case 'a': srand(67); printf("Printing map 'a'\n"); break;
        case 'b': srand(21); printf("Printing map 'b'\n"); break;
        case 'c': srand(42); printf("Printing map 'c'\n"); break;
        default: printf ("Map choice error"); exit(EXIT_FAILURE);
    }

    int map[MAPSIZE*MAPSIZE];
    Stops restStops[NUMBEROFSTOPS];
    srand(time(NULL));
    // Find optimal route between start and end points
    Destination destination;
    runDestination(&destination,0,MAPSIZE);
    //runMapGen()
    RunMapGen(map, MAPSIZE, restStops);
    int pathLength = 0, numSections = 0;
    int *stops = malloc(sizeof(int) * MAPSIZE * MAPSIZE);
    int *path = Navigate(map, MAPSIZE, destination, &pathLength, &numSections, stops);
    //call NavigateWrapper for printing of map with stops
    NavigateWrapper(map , MAPSIZE, path, pathLength, stops, numSections);
    free(stops); free(path);
}