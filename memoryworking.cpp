#include "memoryworking.h"


void clean2DArray(char** arr, int x){
    for (int i = 0; i < x; i++)
        free(arr[i]);
}

void clean3DArray(char*** arr, int x, int y){
    for(int i = 0; i < y; i++)
        clean2DArray(arr[i], x);
}
