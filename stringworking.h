#ifndef STRINGWORKING_H
#define STRINGWORKING_H

#include <string.h>
#include <stdlib.h>
#include "appcontext.h"
#include "memoryworking.h"

char** strSplit(char* a_str, AppContext* context, const char a_delim);
int charNum(char*, char);

#endif // STRINGWORKING_H
