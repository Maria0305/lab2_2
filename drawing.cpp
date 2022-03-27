#include "drawing.h"

void drawSegment(AppContext* context, QPixmap* pix) {
    QPainter painter(pix);
    painter.translate(X / 2, Y / 2);
    QPen penLine(Qt::green, LINE_WIDTH);
    painter.setPen(penLine);
    painter.drawPoint(context->grafCoordinates.x, context->grafCoordinates.y);
    painter.drawPoint(context->nextPointGrafCoordinates.x, context->nextPointGrafCoordinates.y);
    painter.drawLine(context->grafCoordinates.x, context->grafCoordinates.y, context->nextPointGrafCoordinates.x, context->nextPointGrafCoordinates.y);
}

void drawGrafic(AppContext* context, QPixmap* pix){
    converCharArrayToIntArray(context);
    scaleData(context);
    convertDegreesToRadians(context);
    for (int i = 0; i < context->xSize; i++)
        for (int j = 0; j < context->ySize - 1; j++) {
            getOxCoordinates(context, i, j);
            convertCoordinates(context);
            drawSegment(context, pix);
        }
    for (int i = 0; i < context->xSize - 1; i++)
        for (int j = 0; j < context->ySize; j++) {
            getOyCoordinates(context, i, j);
            convertCoordinates(context);
            drawSegment(context, pix);
        }
}


