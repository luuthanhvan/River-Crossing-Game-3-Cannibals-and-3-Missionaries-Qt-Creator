#include "cloud.h"
#include <QLinearGradient>

Cloud::Cloud(QGraphicsItem *parent): QGraphicsEllipseItem(parent){
}

void Cloud::drawCloud(int x, int y, int r, int offset, int n){
    QPen pen;
    pen.setBrush(QBrush(QColor("#ffffff")));
    QGraphicsEllipseItem *circle[n];
    int i;
    for(i = 0; i < n; i++){
        // create a QGraphicsEllipseItem array with n elements
        circle[i] = new QGraphicsEllipseItem(this);
        circle[i]->setPen(pen);
        // fill color
        circle[i]->setBrush(QBrush(QColor("#ffffff")));
    }
    // draw the first circle
    circle[0]->setRect(x, y, r, r);
    // draw the circle[1] -> circle[n-1]
    for(i = 1; i < n-1; i++){
        // this circle will overlap on the other circle and separate by 10px
        // so that increasing x to offset (translate x-coordinate by 10px)
        x += offset;
        // the radius of from circle 1 -> n-1 greater than circle[0] and circle[n-1] 10px
        circle[i]->setRect(x, y, r+10, r+10);
    }
    // draw the last circle
    circle[n-1]->setRect(x+offset+10, y, r, r);
}
