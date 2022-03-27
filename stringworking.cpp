#include "stringworking.h"

//Функция разбития строки на массив слов
char** strSplit(char* str, AppContext* context, const char separator) {
    char** data = 0;
    int count = 0;
    char* temp = str;
    char* lastIn = 0;
    char sepArray[2];
    sepArray[0] = separator;
    sepArray[1] = 0;
    while (*temp){
        if (separator == *temp){
            count++;
            lastIn = temp;
        }
        temp++;
    }
    if (context->xSize == 0)
        context->xSize = count + 1;
    count += lastIn < (str + strlen(str) - 1);
    count++;
    data = (char**)malloc(sizeof(char*) * count);
    if (data){
        int i  = 0;
        char* token = strtok(str, sepArray);
        int check = 0;
        while (token){
            check++;
            *(data + i++) = strdup(token);
            token = strtok(0, sepArray);
        }
        if (check < context->xSize) {
            clean2DArray(data, check);
            return NULL;
        }
        *(data + i) = 0;
    }
    return data;
}

int charNum(char* str, char c) {
    int num = 0;
    for(int i = 0; i < strlen(str); i++)
        if (str[i] == c)
            num++;
    return num;
}
