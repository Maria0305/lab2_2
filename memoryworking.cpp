#include "memoryworking.h"


void clean2DArray(char** arr, int x){
    for (int i = 0; i < x; i++)
        free(arr[i]);
    free(arr);
}

void clean3DArray(char*** arr, int x, int y){
    for(int i = 0; i < y; i++)
        clean2DArray(arr[i], x);
    free(arr);
}

void clean2DArrayInt(int** arr, int y){
    for (int i = 0; i < y; i++)
        free(arr[i]);
    free(arr);
}

Coordinate** allocateCordinates(int x, int y){
    Coordinate** coordinates = (Coordinate**) malloc (y*sizeof(Coordinate*));
    for (int i = 0; i < y; i++) {
        coordinates[i] = (Coordinate*) malloc(x * sizeof(Coordinate));
    }
    return coordinates;
}

GrafCoordinate** allocateGrafCoordinates(int x, int y){
    GrafCoordinate** grafCoordinates = (GrafCoordinate**) malloc (y*sizeof(GrafCoordinate*));
    for (int i = 0; i < y; i++) {
        grafCoordinates[i] = (GrafCoordinate*) malloc(x * sizeof(GrafCoordinate));
    }
    return grafCoordinates;
}

void cleanCoordinates(Coordinate** coordinates, int y){
    for(int i = 0; i < y; i++)
        free(coordinates[i]);
    free(coordinates);
}
void cleanGrafCoordinates(GrafCoordinate** grafCoordinates, int y){
    for(int i = 0; i < y; i++)
        free(grafCoordinates[i]);
    free(grafCoordinates);
}
