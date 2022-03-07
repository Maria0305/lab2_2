#include "entrypoint.h"
#include <iostream>

ErrorType entryPoint2(Operation operation, AppContext* context){
    switch(operation){
    case Clean:
        return (clean2(context));
        break;
    case Load:
        return (load2(context));
        break;
    case Calculate:
        return (calculate2(context));
        break;
    case Initialization:
        return (init2(context));
        break;
    case Metrics:
        return (initMetrics2(context));
        break;
    }
    return Correct;
}
