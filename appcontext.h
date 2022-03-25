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
    char* fileName;
    int ySize;
    int xSize;
    bool fileOk;
};

enum ErrorType{
    Nofilechoosen,
    Unreadfile,
    Initial,
    Correct,
};

#endif // APPCONTEXT_H
