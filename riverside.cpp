#include "riverside.h"
#include <QDebug>
#include "game.h"

extern Game *game; // external variable

Riverside::Riverside(QGraphicsItem *parent) : QGraphicsPixmapItem(){
}

void Riverside::drawRiverside(const QPixmap &pixmap, int x, int y, int w, int h){
    setPos(x, y);
    setPixmap(pixmap.scaled(w, h));
}

int Riverside::countNbMonks(){
    int cnt = 0;
    for(int i = 0; i < 3; i++){
        if(collidesWithItem(game->monk[i]))
            cnt++;
    }
    return cnt;
}

int Riverside::countNbDemons(){
    int cnt = 0;
    for(int i = 0; i < 3; i++){
        if(collidesWithItem(game->demon[i]))
            cnt++;
    }
    return cnt;
}
