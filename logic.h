#ifndef LOGIC_H
#define LOGIC_H

#include "appcontext.h"
#include "memoryworking.h"
#include "fileworking.h"
#include "stringworking.h"
#include <stdio.h>

float findMax(float*, int);
float findMin(float*, int);
float findMed(float*, int);

//---------------------------------------------
ErrorType clean(AppContext*);
ErrorType load(AppContext*);
ErrorType calculate(AppContext*);
ErrorType init(AppContext*);
ErrorType initMetrics(AppContext*);





#endif // LOGIC_H
