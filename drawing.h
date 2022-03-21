#ifndef DRAWING_H
#define DRAWING_H

#include <QPainter>
#include "appcontext.h"
#include "logic.h"

//размеры графика

#define X 780
#define Y 880

//толщина пера для элементов графика

#define ORIGIN_WIDTH 1
#define POINT_WIDTH 7
#define LINE_WIDTH 3
#define METRICS_POINT_WIDTH 9

void drawOrigins(AppContext*, QPixmap*);
void drawGrafic(AppContext*, QPixmap*);


#endif // DRAWING_H
