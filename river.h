#ifndef RIVER_H
#define RIVER_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class River : public QGraphicsPixmapItem{
public:
    River(QGraphicsItem *parent=0);
    void drawRiver(const QPixmap &pixmap, int x, int y, int w, int h);
};

#endif // RIVER_H
