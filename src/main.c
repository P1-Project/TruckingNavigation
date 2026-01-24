#include <ctype.h>
#include <stdio.h>
#include "MapGenFunc.h"
#include "GetDestinationFunc.h"
#include "DefineConst.h"
#include "DefineStruct.h"
#include "Navigation.h"

int main(void) {
    printf("Hello, World!\n");
    char input = 'a';
    while (input != 'q') {
        do {
            printf("Do you want a random map (r) or map (a), (b) or (c) - (q) for exit\n");
            scanf(" %c", &input);
            input = (char)tolower(input);
            if (input == 'q') {exit(0);}
        } while (!(input == 'r' || input == 'a' || input == 'b' || input == 'c'));
        switch (input) {
            case 'r':
                printf("Generating random map\n");
                srand(time(NULL)); //used to gen a random seed
                break;
            case 'a': srand(100); printf("Printing map 'a'\n"); break; //seed 67 does nt work dont know, but change it and it works
            case 'b': srand(21); printf("Printing map 'b'\n"); break;
            case 'c': srand(42); printf("Printing map 'c'\n"); break;
            default: printf ("Map choice error"); exit(EXIT_FAILURE);
        }
        for (int i = 0; i < 10; i++) {
            printf("%d) %d \n", i, rand());
        }
        printf("\n");


        int map[MAPSIZE*MAPSIZE];
        //Stops *restStops = malloc(sizeof(Stops)*NUMBEROFSTOPS23);
        Stops restStops[NUMBEROFSTOPS];
        //runMapGen()
        RunMapGen(map, MAPSIZE, restStops);
        // Find optimal route between start and end points
        Destination destination;
        RunDestination(&destination,MAPSIZE);
        int pathLength = 0, numSections = 0;
        int *stops = malloc(sizeof(int) * MAPSIZE * MAPSIZE);
        int *path = Navigate(map, MAPSIZE, destination, &pathLength, &numSections, stops);
        //call NavigateWrapper for printing of map with stops
        NavigateWrapper(map , MAPSIZE, path, pathLength, stops, numSections);
        free(stops); free(path);
    }

}