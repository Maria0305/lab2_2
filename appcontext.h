#ifndef APPCONTEXT_H
#define APPCONTEXT_H

typedef struct {
    float* values;
    int counter;
    int fieldNum;
} DataFromScreen;

typedef struct {
    float max;
    float min;
    float med;
    float maxMod;
} MetricsData;

struct AppContext{
    char*** data;
    char** titles;
    char* fileName;
    int rows;
    int columns;
    bool fileOk;
    MetricsData metrics;
    DataFromScreen dataForCalculating;
};

enum ErrorType{
    Nofilechoosen,
    NoRegionChoosen,
    NoColumnChoosen,
    WrongColumnInput,
    Unreadfile,
    Initial,
    MetricsInit,
    NoDataForThisRegion,
    Correct,
};

#endif // APPCONTEXT_H
