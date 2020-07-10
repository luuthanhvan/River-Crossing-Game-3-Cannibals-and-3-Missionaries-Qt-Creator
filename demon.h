#ifndef DEMON_H
#define DEMON_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <QPointF>
#include <QVariant>

class Demon : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Demon(QGraphicsItem *parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void drawDemon(const QPixmap &pixmap, int x, int y, int w, int h, int id);
    QPointF getDefaultPos();
    int getDemonId();
private:
    int demonId;
    QPointF defaultPos;
};

#endif // DEMON_H
