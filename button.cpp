#include "button.h"
#include <QBrush>
#include <QColor>
#include <QUrl>

Button::Button(QString name, QGraphicsItem *parent): QGraphicsRectItem(parent){
    // draw the rect
    setRect(0, 0, 80, 30);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor("#0d7519"));
    setBrush(brush);

    // draw the text
    text = new QGraphicsTextItem(name, this);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos, yPos);
    text->setDefaultTextColor(Qt::white);

    // allow responding to hover events
    setAcceptHoverEvents(true);

    clickSound = new QMediaPlayer();
    clickSound->setMedia(QUrl("qrc:/sounds/mouse_click.mp3"));
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    // play clickSound
    clickSound->play();
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    // change color
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor("#88ff00"));
    setBrush(brush);
    text->setDefaultTextColor(Qt::black);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    // change color
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor("#0d7519"));
    setBrush(brush);
    text->setDefaultTextColor(Qt::white);
}

