#include "fileworking.h"
#include <iostream>

char** readFile(FILE* f, AppContext* context){
    char temp[MAX_LEN];
    int len;
    int count = 0;
    int maxCount = 1;
    char** data = (char**)malloc(maxCount * sizeof(char*));
    while(fgets(temp, MAX_LEN, f)) {
        if (count >= maxCount - 1) {
            maxCount *= 2;
            data = (char**)realloc(data, maxCount * sizeof(char*));
        }
        len = strlen(temp);
        data[count] = (char*) malloc ((len + 1) * sizeof(char));
        strcpy(data[count], temp);
        count++;
    }
    context->rows = count;
    fclose(f);
    return data;
}

bool checkFile(char** tempData, AppContext* context){
    int number = charNum(tempData[0], ',');
    for(int i = 1; i < context->rows; i++)
        if (charNum(tempData[i], ',') != number)
            return false;
    return true;

}
