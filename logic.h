#ifndef LOGIC_H
#define LOGIC_H

#include "appcontext.h"
#include "memoryworking.h"
#include "fileworking.h"
#include "stringworking.h"
#include "drawing.h"
#include <stdio.h>
#include <math.h>

#define PI 3.14159265
#define BASE_SCALE 5

ErrorType clean(AppContext*);
ErrorType load(AppContext*);
ErrorType init(AppContext*);
//---------------------------------------------
void moveOx(AppContext*);
void moveOy(AppContext*);
//---------------------------------------------
void rolateOx(AppContext*);
void rolateOy(AppContext*);
void rolateOz(AppContext*);
//---------------------------------------------
void convertCoordinates(AppContext*);
void addOffsets(AppContext*);
void getOxCoordinates(AppContext*, int, int);
void getOyCoordinates(AppContext*, int, int);
//---------------------------------------------
void converCharArrayToIntArray(AppContext*);
void convertDegreesToRadians(AppContext*);
int findMax(AppContext*);
int findMin(AppContext*);
void scaleData(AppContext*);
int scaleValue(AppContext*, int, int, int);

#endif // LOGIC_H
