#include "river.h"

River::River(QGraphicsItem *parent) : QGraphicsPixmapItem(){
}

void River::drawRiver(const QPixmap &pixmap, int x, int y, int w, int h){
    setPos(x,y);
    setPixmap(pixmap.scaled(w, h));
}
