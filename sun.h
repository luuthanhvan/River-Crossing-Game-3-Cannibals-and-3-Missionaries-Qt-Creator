#ifndef SUN_H
#define SUN_H

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QBrush>
#include <QColor>
#include <QPen>
#include <QPoint>
#include <math.h>

class Sun: public QGraphicsEllipseItem{
public:
    Sun(QGraphicsItem *parent=0);
    void drawTheSun(int x, int y, int r);
};

#endif // SUN_H
