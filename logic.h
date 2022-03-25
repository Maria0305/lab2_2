#ifndef LOGIC_H
#define LOGIC_H

#include "appcontext.h"
#include "memoryworking.h"
#include "fileworking.h"
#include "stringworking.h"
#include "drawing.h"
#include <stdio.h>

void sortArray(float*, int);

//---------------------------------------------
ErrorType clean(AppContext*);
ErrorType load(AppContext*);
ErrorType init(AppContext*);

#endif // LOGIC_H
