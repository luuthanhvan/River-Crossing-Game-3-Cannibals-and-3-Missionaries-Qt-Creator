#include "demon.h"
#include "game.h"
#include <QDebug>
#include <QVariant>

extern Game *game; // external variable

Demon::Demon(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent){
}

void Demon::mousePressEvent(QGraphicsSceneMouseEvent *event){
    game->boat->moveDemon(demonId);
}

void Demon::drawDemon(const QPixmap &pixmap, int x, int y, int w, int h, int id){
    setPos(x, y);
    setPixmap(pixmap.scaled(w, h));
    demonId = id; // save id
    // save position
    defaultPos.setX(x);
    defaultPos.setY(y);
}

QPointF Demon::getDefaultPos(){
    return defaultPos;
}

int Demon::getDemonId(){
    return demonId;
}
