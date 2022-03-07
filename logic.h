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
ErrorType clean2(AppContext*);
ErrorType load2(AppContext*);
ErrorType calculate2(AppContext*);
ErrorType init2(AppContext*);
ErrorType initMetrics2(AppContext*);





#endif // LOGIC_H
