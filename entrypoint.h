#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"
#include "logic.h"
#include "drawing.h"

enum Operation{
    Clean,
    Load,
    Initialization,
};

ErrorType entryPoint(Operation, AppContext*);

#endif // ENTRYPOINT_H
