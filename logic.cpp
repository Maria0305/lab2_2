#include "logic.h"

void sortArray(float* arr, int counter){
    for (int i = 0; i < counter - 1; i++)
        for (int j = i + 1; j < counter; j++)
            if (arr[i] > arr[j]) {
                float temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
}
//--------------------------------------------------------

ErrorType clean(AppContext* context){
    if (context->data)
        clean3DArray(context->data, context->xSize, context->ySize);
    if  (context->fileName)
        free(context->fileName);
    return Initial;
}

ErrorType load(AppContext* context){
    if (!context->fileName)
        return Nofilechoosen;
    FILE* f = fopen(context->fileName, "r");
    if (f != NULL){
        char** tempData = readFile(f, context);
        if (!checkFile(tempData, context))
            return Unreadfile;
        else {
            char ***data = (char***)malloc((context->ySize) * sizeof(char**));
            int l = 0; //для пропуска "пустых" строк
            for (int i = 0; i < context->ySize; i++){
                data[i - l] = strSplit(tempData[i], context, ',');
                if (data[i - l] == NULL)
                    l++;
            }
            context->ySize -= l; //минус "пустные" строки
            clean2DArray(tempData, context->ySize);
            context->data = data;
            if (context->data == NULL)
                return Unreadfile;
            return Correct;
        }
    }
    else
        return Unreadfile;
}

ErrorType init(AppContext* context) {
    context->fileName = NULL;
    context->data = NULL;
    context->xSize = 0;
    return Initial;
}


