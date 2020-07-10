#ifndef CLOUD_H
#define CLOUD_H

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QColor>
#include <QPen>

class Cloud : public QGraphicsEllipseItem{
public:
    Cloud(QGraphicsItem *parent=0);
    void drawCloud(int x, int y, int r, int offset, int n);
};

#endif // CLOUD_H
