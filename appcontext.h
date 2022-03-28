#ifndef APPCONTEXT_H
#define APPCONTEXT_H

typedef struct {
   int x;
   int y;
   int z;
} Coordinates;

typedef struct {
    int x;
    int y;
} GrafCoordinates;

typedef struct {
   int offsetX;
   int offsetY;
   int offsetZ;
} Offsets;

typedef struct {
    float radiansX;
    float radiansY;
    float radiansZ;
} Radians;

typedef struct {
    int upLimit;
    int downLimit;
} Range;

typedef struct {
    int scaleX;
    int scaleY;
    int scaleZ;
} Scales;

struct AppContext{
    char*** data;
    int** intData;
    char* fileName;
    char* fileNamePrevious;
    Coordinates coordinates;
    Coordinates nextPointCoordinates;
    GrafCoordinates grafCoordinates;
    GrafCoordinates nextPointGrafCoordinates;
    Offsets offsets;
    Scales scales;
    Radians radians;
    Range range;
    int ySize;
    int xSize;
    bool fileOk;
};

enum ErrorType{
    Nofilechoosen,
    Unreadfile,
    NoDataInFile,
    Initial,
    Correct,
};

#endif // APPCONTEXT_H
