#ifndef APPCONTEXT_H
#define APPCONTEXT_H

struct AppContext{
    char*** data;
    char** titles;
    float max;
    float min;
    float med;
    char* fileName;
    float* values;
    int counter;
    int fieldNum;
    int rows;
    int columns;
    bool fileOk;
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
