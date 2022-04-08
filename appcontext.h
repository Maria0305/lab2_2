#ifndef APPCONTEXT_H
#define APPCONTEXT_H

typedef struct {
   int x;
   int y;
   int z;
} Coordinate;

typedef struct {
    int x;
    int y;
} GrafCoordinate;

typedef struct {
   int x;
   int y;
   int z;
} Offsets;

typedef struct {
    float x;
    float y;
    float z;
} Radians;

typedef struct {
    int from;
    int to;
} Range;

typedef struct {
    int x;
    int y;
    int z;
} Scales;

struct AppContext{
    char*** data;
    char* fileName;
    Coordinate** coordinates;
    GrafCoordinate** grafCoordinates;
    Offsets offsets;
    Scales scales;
    Radians radians;
    Range range;
    int ySize;
    int xSize;
};

enum ErrorType{
    Nofilechoosen,
    Unreadfile,
    NoDataInFile,
    Initial,
    Correct,
};

#endif // APPCONTEXT_H
