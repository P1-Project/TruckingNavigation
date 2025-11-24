//
// Created by rasmk on 20-11-2025.
//

#include "CheckCoordinateSetFunc.h"

#include <stdio.h>

void TestConCheckCoordinateSetFunc() {
    printf("Hello, World from CheckCoordinateSetFunc!\n");
}

int XYToIndex(int x, int y, int mapSize) {
    return x * mapSize + y;
}

int IndexToX(int index, int mapSize) {
    return index % mapSize;                      //eller hvad??
}

int IndexToY(int index, int mapSize) {
    return index / mapSize;
}

int CheckCoordinateSet(int *map, int x, int y, int mapSize){
    int index_i = XYToIndex(x, y, mapSize);
    if (map[index_i] != 5)
        return index_i;

    for (int r = 1; r < mapSize; r++) {          // r tæller op hver gang og udvider søgningen med et felt

        int j = index_i + 1 * r;                 // Tjekker højre
            if (j <= mapSize * mapSize)      // ved ikke lige, skal tjekke den ikke springer på næste linje
            if (map[j] != 5) return j;

        j = index_i - 1 * r;                     // Tjekker venstre, og skal tjekke den bliver på linjen
            if (map[j] != 5) return j;

        j = index_i + mapSize * r;               // Tjekker "nede" samt index er indenfor array
            if (j < mapSize * mapSize && map[j] != 5) return j;

        j = index_i + (mapSize + 1) * r;         // Tjekker skråt ned højre
            if (j > 0 && map[j] != 5) return j;

        j = index_i + (mapSize - 1) * r;         // Tjekker skråt ned venstre
            if (j > 0 && map[j] != 5) return j;

        j = index_i - mapSize * r;               // Tjekker "oppe" samt index er indenfor array
            if (j > 0 && map[j] != 5) return j;

        j = index_i - (mapSize + 1) * r;         // Tjekker skråt op højre
            if (j > 0 && map[j] != 5) return j;

        j = index_i - (mapSize - 1) * r;         // Tjekker skråt op venstre
            if (j > 0 && map[j] != 5) return j;
    }                                            // Returnerer index. Skal den konverteres tilbage til x,y?

return -1;                                       // Ingen "ledig plads"
}

/*int main(void) {

    int x, y, mapSize, i;
    int map[] = {0, 0, 0, 0, 0, 5,
                 5, 5, 5, 0, 0, 0,
                 0, 5, 5, 5, 0, 0,};
    int index = CheckCoordinateSet(map, 3, 1, 6);
    printf("%d", index);
} */