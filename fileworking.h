#ifndef FILEWORKING_H
#define FILEWORKING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "appcontext.h"
#include "stringworking.h"

#define MAX_LEN 200

char** readFile(FILE*, AppContext*);
bool checkFile(char**, AppContext*);

#endif // FILEWORKING_H
