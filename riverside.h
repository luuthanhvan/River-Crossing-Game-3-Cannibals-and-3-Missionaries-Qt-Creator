#ifndef RIVERSIDE_H
#define RIVERSIDE_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QColor>
#include <QBrush>
#include <QPen>

class Riverside : public QGraphicsPixmapItem{
public:
    Riverside(QGraphicsItem *parent=0);
    void drawRiverside(const QPixmap &pixmap, int x, int y, int w, int h);
    int countNbMonks();
    int countNbDemons();
};

#endif // RIVERSIDE_H
