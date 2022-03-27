#include "logic.h"

ErrorType clean(AppContext* context){
    if (context->data)
        clean3DArray(context->data, context->xSize, context->ySize);
    if  (context->fileName)
        free(context->fileName);
    if (context->intData)
        clean2DArrayInt(context->intData, context->ySize);
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
    context->fileName = NULL;
    context->data = NULL;
    context->xSize = 0;
    context->offsets.offsetX = 0;
    context->offsets.offsetY = 0;
    context->offsets.offsetZ = 0;
    context->scales.scaleX = 1;
    context->scales.scaleY = 1;
    context->scales.scaleZ = 1;
    context->radians.radiansX = 0;
    context->radians.radiansY = 0;
    context->radians.radiansZ = 0;
    context->range.downLimit = 0;
    context->range.upLimit = 100;
    return Correct;
}

void moveOx(AppContext* context){    
    int curX;
    curX = - context->coordinates.x * cos(30*PI/180) + context->coordinates.y * cos(30*PI/180);
    context->grafCoordinates.x = curX;
    curX = - context->nextPointCoordinates.x * cos(30*PI/180) + context->nextPointCoordinates.y * cos(30*PI/180);
    context->nextPointGrafCoordinates.x = curX;
}

void moveOy(AppContext* context){
    int curY;
    curY = context->coordinates.x * sin(30*PI/180) + context->coordinates.y * sin(30*PI/180) - context->coordinates.z;
    context->grafCoordinates.y = curY;
    curY = context->nextPointCoordinates.x * sin(30*PI/180) + context->nextPointCoordinates.y * sin(30*PI/180) - context->nextPointCoordinates.z;
    context->nextPointGrafCoordinates.y = curY;
}

void converCharArrayToIntArray(AppContext* context){
    context->intData = (int**) malloc (context->ySize * sizeof(int*));
    for (int i = 0; i < context->ySize; i++) {
        *(context->intData + i) = (int*) malloc (context->xSize * sizeof(int));
        for (int j = 0; j < context->xSize; j++) {
            *(*(context->intData + i) + j) = atoi(*(*(context->data + i) + j));
        }
    }
}

int findMax(AppContext* context) {
   int max = context->intData[0][0];
   for(int i = 0; i < context->ySize; i++)
       for(int j = i+1; j < context->xSize; j++){
           if(*(*(context->intData + i)+j) > max){
               max = *(*(context->intData + i)+j);
           }
       }
   return max;
}

int findMin(AppContext* context) {
    int min = context->intData[0][0];
    for(int i = 0; i < context->ySize; i++)
        for(int j = i+1; j < context->xSize; j++){
            if(*(*(context->intData + i)+j) < min){
                min = *(*(context->intData + i)+j);
            }
        }
    return min;
}

void scaleData(AppContext* context) { //нормировка значений
    int max = findMax(context);
    int min = findMin(context);
    for (int i = 0; i < context->xSize; i++)
        for (int j = 0; j < context->ySize; j++)
            (*(*(context->intData + j) + i)) = scaleValue(context, (*(*(context->intData + j) + i)), max, min);
}

int scaleValue(AppContext* context, int x, int max, int min) { //масштабирование одного значения
    if (max != min)
        x =context->range.downLimit + (x - min)*(context->range.upLimit - context->range.downLimit)/(max - min);
    return x;
}

void rolateOx(AppContext* context){
    int y = context->coordinates.y * BASE_SCALE * context->scales.scaleY;
    int z = context->coordinates.z;
    context->coordinates.y =y*cos(context->radians.radiansX)-z*sin(context->radians.radiansX) ;
    context->coordinates.z =y*sin(context->radians.radiansX)+z*cos(context->radians.radiansX) ;
    y = context->nextPointCoordinates.y * BASE_SCALE * context->scales.scaleY;
    z = context->nextPointCoordinates.z;
    context->nextPointCoordinates.y =y*cos(context->radians.radiansX)-z*sin(context->radians.radiansX) ;
    context->nextPointCoordinates.z =y*sin(context->radians.radiansX)+z*cos(context->radians.radiansX) ;
}

void rolateOy(AppContext* context){
    int x = context->coordinates.x * BASE_SCALE * context->scales.scaleX;
    int z = context->coordinates.z;
    context->coordinates.x = x*cos(context->radians.radiansY)+z*sin(context->radians.radiansY);
    context->coordinates.z = -x*sin(context->radians.radiansY)+z*cos(context->radians.radiansY);
    x = context->nextPointCoordinates.x * BASE_SCALE * context->scales.scaleX;
    z = context->nextPointCoordinates.z;
    context->nextPointCoordinates.x = x*cos(context->radians.radiansY)+z*sin(context->radians.radiansY);
    context->nextPointCoordinates.z = -x*sin(context->radians.radiansY)+z*cos(context->radians.radiansY);
}

void rolateOz(AppContext* context){
    int x = context->coordinates.x;
    int y = context->coordinates.y;
    context->coordinates.x = x*cos(context->radians.radiansZ)-y*sin(context->radians.radiansZ);
    context->coordinates.y = x*sin(context->radians.radiansZ)+y*cos(context->radians.radiansZ);
    x = context->nextPointCoordinates.x;
    y = context->nextPointCoordinates.y;
    context->nextPointCoordinates.x = x*cos(context->radians.radiansZ)-y*sin(context->radians.radiansZ);
    context->nextPointCoordinates.y = x*sin(context->radians.radiansZ)+y*cos(context->radians.radiansZ);
    context->coordinates.z *= context->scales.scaleZ;
    context->nextPointCoordinates.z *= context->scales.scaleZ;
}

void convertCoordinates(AppContext* context){
    rolateOx(context);
    rolateOy(context);
    rolateOz(context);
    addOffsets(context);
    moveOx(context);
    moveOy(context);
}

void getOxCoordinates(AppContext* context, int i, int j){
    context->coordinates.x = i;
    context->coordinates.y = j;
    context->coordinates.z = (*(*(context->intData + j) + i));
    context->nextPointCoordinates.x = i;
    context->nextPointCoordinates.y = j + 1;
    context->nextPointCoordinates.z = (*(*(context->intData + j + 1) + i));
}

void getOyCoordinates(AppContext* context, int i, int j){
    context->coordinates.x = i;
    context->coordinates.y = j;
    context->coordinates.z = (*(*(context->intData + j) + i));
    context->nextPointCoordinates.x = i + 1;
    context->nextPointCoordinates.y = j;
    context->nextPointCoordinates.z = (*(*(context->intData + j) + i + 1));

}

void addOffsets(AppContext* context){
    context->coordinates.x += context->offsets.offsetX * context->scales.scaleX;
    context->coordinates.y += context->offsets.offsetY * context->scales.scaleY;
    context->coordinates.z += context->offsets.offsetZ * context->scales.scaleZ;
    context->nextPointCoordinates.x += context->offsets.offsetX * context->scales.scaleX;
    context->nextPointCoordinates.y += context->offsets.offsetY * context->scales.scaleY;
    context->nextPointCoordinates.z += context->offsets.offsetZ * context->scales.scaleZ;
}

void convertDegreesToRadians(AppContext* context) {
    context->radians.radiansX = context->radians.radiansX * PI / 180;
    context->radians.radiansY = context->radians.radiansY * PI / 180;
    context->radians.radiansZ = context->radians.radiansZ * PI / 180;
}
