#include "drawing.h"

void drawOrigins(AppContext* context, QPixmap* pix){
    QPainter painter(pix);
    painter.fillRect(0, 0, X, Y, QBrush(QColor(Qt::GlobalColor::white)));
    QPen origin(Qt::lightGray, ORIGIN_WIDTH);
    painter.setPen(origin);
    painter.drawLine(0, Y / 2, X, Y / 2); // горизонтальная ось
    painter.drawLine(X - 20, Y / 2 - 10, X, Y / 2);
    painter.drawLine(X - 20, Y / 2 + 10, X, Y / 2);
    painter.drawText(720, 460, "year");
    painter.drawLine(20,0,20, Y); //вертикальная ось
    painter.drawLine(10,20,20,0);
    painter.drawLine(30,20,20,0);
    painter.drawText(35, 20, context->titles[context->dataForCalculating.fieldNum]);
}

void drawGrafic(AppContext* context, QPixmap* pix){
    int scale = scaleMetrics(context, Y);
    QPainter painter(pix);
    QPen penLine(Qt::gray, LINE_WIDTH);
    painter.setPen(penLine);
    int step = X / (context->dataForCalculating.counter + 1);
    for (int i = 0; i < context->dataForCalculating.counter - 1; i++)
        painter.drawLine(i*step + 20, Y / 2 - context->dataForCalculating.values[i], (i+1)*step + 20, Y / 2 - context->dataForCalculating.values[i + 1]);
    QPen pen(Qt::gray, POINT_WIDTH);
    QPen maxPen(Qt::red, METRICS_POINT_WIDTH);
    QPen minPen(Qt::blue, METRICS_POINT_WIDTH);
    QPen medPen(Qt::green, ORIGIN_WIDTH);
    painter.setPen(medPen);
    painter.drawLine(0, Y / 2 - context->metrics.med * scale, X, Y / 2 - context->metrics.med * scale);
    for (int i = 0; i < context->dataForCalculating.counter; i++) {
        float current = context->dataForCalculating.values[i];
        if (current == context->metrics.min * scale)
            painter.setPen(minPen);
        else if (current == context->metrics.max * scale)
            painter.setPen(maxPen);
        else
            painter.setPen(pen);
        painter.drawPoint(i*step + 20, Y / 2 - context->dataForCalculating.values[i]);
    }
}
