#ifndef MEMORYWORKING_H
#define MEMORYWORKING_H
#include <stdlib.h>
#include "appcontext.h"

void clean2DArray(char**, int);
void clean3DArray(char***, int, int);
void clean2DArrayInt(int** arr, int x);
Coordinate** allocateCordinates(int x, int y);
GrafCoordinate** allocateGrafCoordinates(int x, int y);
void cleanCoordinates(Coordinate**,int y);
void cleanGrafCoordinates(GrafCoordinate**,int y);

#endif // MEMORYWORKING_H
