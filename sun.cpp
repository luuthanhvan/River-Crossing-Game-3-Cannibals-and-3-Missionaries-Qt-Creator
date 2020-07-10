#include "sun.h"
#include <QLinearGradient>

Sun::Sun(QGraphicsItem *parent): QGraphicsEllipseItem(parent){
}

void Sun::drawTheSun(int x, int y, int r){
    QPen pen;
    QLinearGradient gradientColor;
    gradientColor.setStart(x, y);
    gradientColor.setColorAt(0, QColor("#ffffff"));
    gradientColor.setStart(x+r, y);
    gradientColor.setColorAt(0.1, QColor("#ff8c00"));
    pen.setBrush(QBrush(gradientColor));
    pen.setWidth(4);
    setRect(x, y, r, r);
    setPen(pen);
    setBrush(QBrush(gradientColor));
}
