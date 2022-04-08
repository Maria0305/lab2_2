#include "logic.h"

ErrorType clean(AppContext* context){
    if (context->data)
        clean3DArray(context->data, context->xSize, context->ySize);
    if  (context->fileName)
        free(context->fileName);
    if (context->coordinates)
        cleanCoordinates(context->coordinates, context->ySize);
    if (context->grafCoordinates)
        cleanGrafCoordinates(context->grafCoordinates, context->ySize);
    return Initial;
}

ErrorType load(AppContext* context){
    if (!context->fileName)
        return Nofilechoosen;
    FILE* f = fopen(context->fileName, "r");
    if (f != NULL){
        char** tempData = readFile(f, context);
        if (!checkFile(tempData, context))
            return Unreadfile;
        else {
            char ***data = (char***)malloc((context->ySize) * sizeof(char**));
            int l = 0; //для пропуска "пустых" строк
            for (int i = 0; i < context->ySize; i++){
                data[i - l] = strSplit(tempData[i], context, ',');
                if (data[i - l] == NULL)
                    l++;
            }
            context->ySize -= l; //минус "пустные" строки
            clean2DArray(tempData, context->ySize);
            context->data = data;
            if (context->data == NULL)
                return NoDataInFile;
            return Correct;
        }
    }
    else
        return Unreadfile;
}

ErrorType init(AppContext* context) {
    context->data = NULL;
    context->xSize = 0;
    context->offsets.x = 0;
    context->offsets.y = 0;
    context->offsets.z = 0;
    context->scales.x = 1;
    context->scales.y = 1;
    context->scales.z = 1;
    context->radians.x = 0;
    context->radians.y = 0;
    context->radians.z = 0;
    context->range.to = 0;
    context->range.from = 100;
    return Correct;
}

void moveOx(Coordinate coordinates, GrafCoordinate* grafCoordinates){
    int curX;
    curX = - coordinates.x * cos(30*PI/180) + coordinates.y * cos(30*PI/180);
    grafCoordinates->x = curX;
}

void moveOy(Coordinate coordinates, GrafCoordinate* grafCoordinates){
    int curY;
    curY = coordinates.x * sin(30*PI/180) + coordinates.y * sin(30*PI/180) - coordinates.z;
    grafCoordinates->y = curY;
}

void converCharArrayToIntArray(AppContext* context){
    context->coordinates = allocateCordinates(context->xSize, context->ySize);
    context->grafCoordinates = allocateGrafCoordinates(context->xSize, context->ySize);
    for (int i = 0; i < context->ySize; i++) {
        for (int j = 0; j < context->xSize; j++) {
            context->coordinates[i][j].x = j;
            context->coordinates[i][j].y = i;
            context->coordinates[i][j].z = atoi(*(*(context->data + i) + j));
        }
    }

}

int findMax(AppContext* context) {
   int max = context->coordinates[0][0].z;
   for(int i = 0; i < context->ySize; i++)
       for(int j = i+1; j < context->xSize; j++){
           if((*(*(context->coordinates + i)+j)).z > max){
               max = (*(*(context->coordinates + i)+j)).z;
           }
       }
   return max;
}

int findMin(AppContext* context) {
    int min = context->coordinates[0][0].z;
    for(int i = 0; i < context->ySize; i++)
        for(int j = i+1; j < context->xSize; j++){
            if((*(*(context->coordinates + i)+j)).z < min){
                min = (*(*(context->coordinates + i)+j)).z;
            }
        }
    return min;
}

void scaleData(AppContext* context) { //нормировка значений
    int max = findMax(context);
    int min = findMin(context);
    for (int i = 0; i < context->xSize; i++)
        for (int j = 0; j < context->ySize; j++)
            (*(*(context->coordinates + j) + i)).z = scaleValue(context, (*(*(context->coordinates + j) + i)).z, max, min);
}

int scaleValue(AppContext* context, int x, int max, int min) { //масштабирование одного значения
    if (max != min)
        x =context->range.to + (x - min)*(context->range.from - context->range.to)/(max - min);
    return x;
}

void rolateOx(AppContext* context, Coordinate* coordinates){
    int y = coordinates->y * BASE_SCALE * context->scales.y;
    int z = coordinates->z;
    coordinates->y =y*cos(context->radians.x)-z*sin(context->radians.x) ;
    coordinates->z =y*sin(context->radians.x)+z*cos(context->radians.x) ;
}

void rolateOy(AppContext* context, Coordinate* coordinates){
    int x = coordinates->x * BASE_SCALE * context->scales.x;
    int z = coordinates->z;
    coordinates->x = x*cos(context->radians.y)+z*sin(context->radians.y);
    coordinates->z = -x*sin(context->radians.y)+z*cos(context->radians.y);
}

void rolateOz(AppContext* context, Coordinate* coordinates){
    int x = coordinates->x;
    int y = coordinates->y;
    coordinates->x = x*cos(context->radians.z)-y*sin(context->radians.z);
    coordinates->y = x*sin(context->radians.z)+y*cos(context->radians.z);
    coordinates->z *= context->scales.z;
}

ErrorType convertCoordinates(AppContext* context){
    context->grafCoordinates = allocateGrafCoordinates(context->xSize, context->ySize);
    for (int i = 0; i < context->xSize; i++)
        for (int j = 0; j < context->ySize; j++) {
            rolateOx(context, &(context->coordinates[i][j]));
            rolateOy(context, &(context->coordinates[i][j]));
            rolateOz(context, &(context->coordinates[i][j]));
            addOffsets(context, &(context->coordinates[i][j]));
            moveOx(context->coordinates[i][j], &(context->grafCoordinates[i][j]));
            moveOy(context->coordinates[i][j], &(context->grafCoordinates[i][j]));
        }
    return Correct;
}

ErrorType prepareData(AppContext* context){
    converCharArrayToIntArray(context);
    scaleData(context);
    convertDegreesToRadians(context);    
    return Correct;
}

void addOffsets(AppContext* context, Coordinate* coordinates){
    coordinates->x += context->offsets.x * context->scales.x;
    coordinates->y += context->offsets.y * context->scales.y;
    coordinates->z += context->offsets.z * context->scales.z;
}

void convertDegreesToRadians(AppContext* context) {
    context->radians.x = context->radians.x * PI / 180;
    context->radians.y = context->radians.y * PI / 180;
    context->radians.z = context->radians.z * PI / 180;
}
