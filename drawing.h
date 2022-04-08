#ifndef DRAWING_H
#define DRAWING_H

#include <QPainter>
#include "appcontext.h"
#include "entrypoint.h"
#include "logic.h"

//размеры графика

#define X 780
#define Y 880

//толщина пера для элементов графика

#define LINE_WIDTH 1

void drawGrafic(AppContext*, QPixmap*);
void drawSegment(AppContext*, QPixmap*);


#endif // DRAWING_H
