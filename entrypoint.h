#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"
#include "logic.h"

enum Operation{
    Clean,
    Load,
    Calculate,
    Initialization,
    Metrics,
};

ErrorType entryPoint(Operation, AppContext*);

#endif // ENTRYPOINT_H
