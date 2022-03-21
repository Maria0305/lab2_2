#include "entrypoint.h"

ErrorType entryPoint(Operation operation, AppContext* context){
    switch(operation){
    case Clean:
        return (clean(context));
        break;
    case Load:
        return (load(context));
        break;
    case Calculate:
        return (calculate(context));
        break;
    case Initialization:
        return (init(context));
        break;
    case Metrics:
        return (initMetrics(context));
        break;
    }
    return Correct;
}
