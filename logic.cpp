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

float findMaxMod(float* values, int counter){
    float maxMod = values[0];
    for (int i = 0; i < counter; i++)
        if (abs(values[i]) > maxMod)
            maxMod = abs(values[i]);
    return maxMod;
}

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
        clean3DArray(context->data, context->columns, context->rows);
    if (context->titles)
        clean2DArray(context->titles, context->columns);
    if  (context->fileName)
        free(context->fileName);
    if (context->dataForCalculating.values)
        free(context->dataForCalculating.values);
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
            char ***data = (char***)malloc((context->rows - 1) * sizeof(char**));
            int l = 0; //для пропуска "пустых" строк
            for (int i = 0; i < context->rows - 1; i++){
                data[i - l] = strSplit(tempData[i+1], context, ',');
                if (data[i - l] == NULL)
                    l++;
            }
            (context->rows)--; //минус названия колонок
            context->rows -= l; //минус "пустные" строки
            char **titles = strSplit(tempData[0], context, ',');
            clean2DArray(tempData, context->rows);
            context->data = data;
            context->titles = titles;
            if (context->titles == NULL)
                return Unreadfile;
            return Correct;
        }
    }
    else
        return Unreadfile;
}

ErrorType calculate(AppContext* context){
    if (context->dataForCalculating.counter == 0)
        return NoDataForThisRegion;
    context->metrics.max = findMax(context->dataForCalculating.values, context->dataForCalculating.counter);
    context->metrics.min = findMin(context->dataForCalculating.values, context->dataForCalculating.counter);
    context->metrics.med = findMed(context->dataForCalculating.values, context->dataForCalculating.counter);
    context->metrics.maxMod = findMaxMod(context->dataForCalculating.values, context->dataForCalculating.counter);
    return Correct;
}

ErrorType init(AppContext* context) {
    context->fileName = NULL;
    context->data = NULL;
    context->titles = NULL;
    context->dataForCalculating.values = NULL;
    context->columns = 0;
    return Initial;
}

ErrorType initMetrics(AppContext* context) {
    context->metrics.max = 0;
    context->metrics.med = 0;
    context->metrics.min = 0;
    return MetricsInit;
}

int scaleMetrics(AppContext* context, int size) {
    int scale = (size / 2 - 20) / context->metrics.maxMod;
    for(int i = 0; i < context->dataForCalculating.counter; i++)
        context->dataForCalculating.values[i] *= scale;
    return scale;
}

