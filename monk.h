#ifndef MONK_H
#define MONK_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <QPointF>

class Monk : public QGraphicsPixmapItem{
public:
    Monk(QGraphicsItem *parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void drawMonk(const QPixmap &pixmap, int x, int y, int w, int h, int id);
    QPointF getDefaultPos();
    int getMonkId();
private:
    int monkId;
    QPointF defaultPos;
};

#endif // MONK_H
