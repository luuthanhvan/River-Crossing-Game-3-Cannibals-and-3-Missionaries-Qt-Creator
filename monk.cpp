#include "monk.h"
#include "game.h"

extern Game *game; // external variable

Monk::Monk(QGraphicsItem *parent) : QGraphicsPixmapItem(parent){
}

void Monk::mousePressEvent(QGraphicsSceneMouseEvent *event){
    game->boat->moveMonk(monkId);
}

void Monk::drawMonk(const QPixmap &pixmap, int x, int y, int w, int h, int id){
    setPos(x, y);
    setPixmap(pixmap.scaled(w, h));
    monkId = id; // save id
    // save position
    defaultPos.setX(x);
    defaultPos.setY(y);
}

QPointF Monk::getDefaultPos(){
    return defaultPos;
}

int Monk::getMonkId(){
    return monkId;
}
