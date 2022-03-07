#include "logic.h"

float findMax(float* values, int counter) {
    float max = values[0];
    for (int i = 0; i < counter; i++)
        if (values[i] > max)
            max = values[i];
    return max;
}

float findMin(float* values, int counter) {
    float min = values[0];
    for (int i = 0; i < counter; i++)
        if (values[i] < min)
            min = values[i];
    return min;
}

float findMed(float* values, int counter) {
    float sum = 0;
    for(int i = 0; i < counter; i++)
        sum += values[i];
    return (sum / counter);
}

//--------------------------------------------------------

ErrorType clean2(AppContext* context){
    if (context->data)
        clean3DArray(context->data, context->columns, context->rows);
    if (context->titles)
        clean2DArray(context->titles, context->columns);
    if  (context->fileName)
        free(context->fileName);
    if (context->values)
        free(context->values);
    return Correct;
}

ErrorType load2(AppContext* context){
    if (!context->fileName)
        return Nofilechoosen;
    FILE* f = fopen(context->fileName, "r");
    if (f != NULL){
        char** tempData = readFile(f, context);
        if (!checkFile(tempData, context))
            return Unreadfile;
        else {
            char ***data = (char***)malloc((context->rows - 1) * sizeof(char**));
            int l = 0; //для пропуска пустых строк
            for (int i = 0; i < context->rows - 1; i++){
                data[i - l] = strSplit(tempData[i+1], context, ',');
                if (data[i - l] == NULL)
                    l++;
            }
            (context->rows)--; //минус названия колонок
            context->rows -= l; //минус пустные строки
            char **titles = strSplit(tempData[0], context, ',');
            clean2DArray(tempData, context->rows);
            context->data = data;
            context->titles = titles;
            return Correct;
        }
    }
    else
        return Unreadfile;
}

ErrorType calculate2(AppContext* context){
    if (context->counter == 0)
        return NoDataForThisRegion;
    context->max = findMax(context->values, context->counter);
    context->min = findMin(context->values, context->counter);
    context->med = findMed(context->values, context->counter);
    return Correct;
}

ErrorType init2(AppContext* context) {
    context->fileName = NULL;
    context->data = NULL;
    context->titles = NULL;
    context->values = NULL;
    context->columns = 0;
    return Initial;
}

ErrorType initMetrics2(AppContext* context) {
    context->max = 0;
    context->med = 0;
    context->min = 0;
    return MetricsInit;
}

