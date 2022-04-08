#include "drawing.h"

void drawSegment(GrafCoordinate point1, GrafCoordinate point2, QPixmap* pix) {
    QPainter painter(pix);
    painter.translate(X / 2, Y / 2);
    QPen penLine(Qt::green, LINE_WIDTH);
    painter.setPen(penLine);
    //painter.drawPoint(context->grafCoordinates.x, context->grafCoordinates.y);
    //painter.drawPoint(context->nextPointGrafCoordinates.x, context->nextPointGrafCoordinates.y);
    painter.drawLine(point1.x, point1.y, point2.x, point2.y);
}

void drawGrafic(AppContext* context, QPixmap* pix){
    entryPoint(PrepareData, context);
    entryPoint(Convert, context);
    for (int i = 0; i < context->xSize; i++)
        for (int j = 0; j < context->ySize - 1; j++) {
            //getOxCoordinates(context, i, j);
            //entryPoint(Convert, context);
            drawSegment(context->grafCoordinates[i][j], context->grafCoordinates[i][j + 1], pix);
        }
    for (int i = 0; i < context->xSize - 1; i++)
        for (int j = 0; j < context->ySize; j++) {
            //getOyCoordinates(context, i, j);
            //entryPoint(Convert, context);
            drawSegment(context->grafCoordinates[i][j], context->grafCoordinates[i + 1][j], pix);
        }
}


