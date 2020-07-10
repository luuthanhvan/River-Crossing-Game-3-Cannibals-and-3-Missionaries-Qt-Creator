#include "boat.h"
#include "game.h"
#include <QDebug>
#include <QMessageBox>
#include <QUrl>
#define LEFT_SIDE 'A'
#define RIGHT_SIDE 'B'
#define TURN_LEFT 0
#define TURN_RIGHT 1
#define MAX_MONK 3
#define MAX_DEMON 3

extern Game *game; // external variable

Boat::Boat(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent){
    posBoat = RIGHT_SIDE; // default side

    int xMonk = game->riversideA->pos().x()+200;
    int yMonk = game->riversideB->pos().y()-60;

    int xDemon = game->riversideA->pos().x()+195;
    int yDemon = yMonk+40;

    QPointF posMonk(xMonk, yMonk);
    QPointF posDemon(xDemon, yDemon);

    // init list of positions in the riverside A (left side) for 3 monks and 3 demons
    for(int i = 0; i < 3; i++){
        positionMonks.push_back(posMonk);
        positionDemons.push_back(posDemon);
        posMonk.setX(posMonk.x()-50);
        posDemon.setX(posDemon.x()-55);
    }

    rowingSound = new QMediaPlayer();
    rowingSound->setMedia(QUrl("qrc:/sounds/rowing_boat.mp3"));

    winSound = new QMediaPlayer();
    winSound->setMedia(QUrl("qrc:/sounds/you_win.mp3"));

    failSound = new QMediaPlayer();
    failSound->setMedia(QUrl("qrc:/sounds/fail.mp3"));

    tadaSound = new QMediaPlayer();
    tadaSound->setMedia(QUrl("qrc:/sounds/tada.mp3"));

    forbiddenSound = new QMediaPlayer();
    forbiddenSound->setMedia(QUrl("qrc:/sounds/forbidden.mp3"));

    jumpSound = new QMediaPlayer();
    jumpSound->setMedia(QUrl("qrc:/sounds/jump.mp3"));
}

void Boat::drawBoat(const QPixmap &pixmap, int x, int y, int w, int h){
    setPos(x, y);
    setPixmap(pixmap.scaled(w, h));
}

void Boat::buttonClicked(int act){
    // act = 0 => the boat turn left
    // act = 1 => the boat turn right
    action = act;
    if(action == TURN_LEFT){
        timer = new QTimer();
        connect(timer, SIGNAL(timeout()), this, SLOT(moveLeft()));
    }
    if(action == TURN_RIGHT){
        timer = new QTimer();
        connect(timer, SIGNAL(timeout()), this, SLOT(moveRight()));
    }
    timer->start(100);
}

bool Boat::isSlotEmpty(QPointF slot){
    for(int i = 0; i < 3; i++){
        if((game->demon[i]->pos().x() == slot.x()) || (game->monk[i]->pos().x() == slot.x()))
            return false;
    }
    return true;
}

bool Boat::isOnBoat(QGraphicsItem *item){
    if(collidesWithItem(item))
        return true;
    return false;
}

bool Boat::isAtRiverside(QGraphicsItem *item){
    if(posBoat == RIGHT_SIDE){
        if(game->riversideB->collidesWithItem(item))
            return true;
        return false;
    }
    else
        if(posBoat == LEFT_SIDE){
            if(game->riversideA->collidesWithItem(item))
                return true;
            return false;
        }
}

int Boat::countNbMonks(){
    int cnt = 0;
    for(int i = 0; i < 3; i++){
        if(collidesWithItem(game->monk[i]))
            cnt++;
    }
    return cnt;
}

int Boat::countNbDemons(){
    int cnt = 0;
    for(int i = 0; i < 3; i++){
        if(collidesWithItem(game->demon[i]))
            cnt++;
    }
    return cnt;
}

bool Boat::isValidMove(){
    int totalMonk, totalDemon;
    if(posBoat == RIGHT_SIDE){
        totalMonk = this->countNbMonks() + game->riversideB->countNbMonks();
        totalDemon = this->countNbDemons() + game->riversideB->countNbDemons();
        if((totalDemon < totalMonk && totalMonk == MAX_MONK) ||
                (totalDemon == totalMonk) || (totalDemon > totalMonk && totalMonk == 0))
            return true;
        return false;
    }
    if(posBoat == LEFT_SIDE){
        totalMonk = this->countNbMonks() + game->riversideA->countNbMonks();
        totalDemon = this->countNbDemons() + game->riversideA->countNbDemons();
        if((totalDemon < totalMonk && totalMonk == MAX_MONK) ||
                (totalDemon == totalMonk) || (totalDemon > totalMonk && totalMonk == 0))
            return true;
        return false;
    }
}

void Boat::gotoBoat(QGraphicsItem *item){
    // the boat will have two available position
    // one is its position (x,y) and the other is (x+70, y)
    QPointF newPos(this->pos().x()+70, this->pos().y());
    if(isSlotEmpty(this->pos())){
        item->setPos(this->pos());
    }
    else{
        if(isSlotEmpty(newPos)){
            item->setPos(newPos);
        }
        else{ // if no empty slot left -> show notification
            forbiddenSound->stop();
            forbiddenSound->play();
            QMessageBox::information(game, "Message", "The boat has no empty slot left!");
        }
    }
}

void Boat::gotoRiverside(QGraphicsItem *item, vector<QPointF> position){
    for(int i = 0; i < position.size(); i++){
        if(isSlotEmpty(position[i])){
            item->setPos(position[i]);
            return;
        }
    }
}

bool Boat::checkGoal(){
    return ((game->riversideA->countNbDemons() == 3) && (game->riversideA->countNbMonks() == 3) && (posBoat == LEFT_SIDE));
}

void Boat::moveDemon(int id){
    // boat is at right side position
    if(posBoat == RIGHT_SIDE){
        // if the demon is on the boat then move it ashore
        if(isOnBoat(game->demon[id-1])){
            // move it back to the original position in the riverside B
            game->demon[id-1]->setTransform(QTransform().rotate(360, Qt::YAxis));
            game->demon[id-1]->setPos(game->demon[id-1]->getDefaultPos());
        }
        else{ // else move it to the boat
            gotoBoat(game->demon[id-1]);
        }
        jumpSound->stop();
        jumpSound->play();
    }
    // boat is at left side position
    if(posBoat == LEFT_SIDE){
        // if the demon is on the boat then move it ashore
        // in the riverside A, there three available position for 3 demons
        // it is stored in list positionDemons (for more details, let review the constructor)
        if(isOnBoat(game->demon[id-1])){
            game->demon[id-1]->setTransform(QTransform().rotate(180, Qt::YAxis));
            gotoRiverside(game->demon[id-1], positionDemons);
            if(checkGoal()){
                game->displayFinishedGameWindow("Done!");
                winSound->stop();
                tadaSound->stop();
                winSound->play();
                tadaSound->play();
            }
        }
        else{ // else move it to the boat
            game->demon[id-1]->setTransform(QTransform().rotate(360, Qt::YAxis));
            gotoBoat(game->demon[id-1]);
        }
        jumpSound->stop();
        jumpSound->play();
    }
}

void Boat::moveMonk(int id){
    // boat is at right side position
    if(posBoat == RIGHT_SIDE){
        // if the monk is on the boat then move it ashore
        if(isOnBoat(game->monk[id-1])){
            // move it back to the original position in the riverside B
            game->monk[id-1]->setTransform(QTransform().rotate(360, Qt::YAxis));
            game->monk[id-1]->setPos(game->monk[id-1]->getDefaultPos());
        }
        else{ // else move it to the boat
            gotoBoat(game->monk[id-1]);
        }
        jumpSound->stop();
        jumpSound->play();
    }
    if(posBoat == LEFT_SIDE){
        // if the monk is on the boat then move it ashore
        // in the riverside A, there three available position for 3 monks
        // it is stored in list positionMonks (for more details, let review the constructor)
        if(isOnBoat(game->monk[id-1])){
            game->monk[id-1]->setTransform(QTransform().rotate(180, Qt::YAxis));
            gotoRiverside(game->monk[id-1], positionMonks);
            if(checkGoal()){
                game->displayFinishedGameWindow("Done!");
                winSound->stop();
                tadaSound->stop();
                winSound->play();
                tadaSound->play();
            }
        }
        else{ // else move it to the boat
            game->monk[id-1]->setTransform(QTransform().rotate(360, Qt::YAxis));
            gotoBoat(game->monk[id-1]);
        }
        jumpSound->stop();
        jumpSound->play();
    }
}

void Boat::moveLeft(){
    if(action == TURN_LEFT){
        rowingSound->play();
        // when move the monk or demon ashore, if no one in the boat -> show notification
        if(this->countNbDemons() == 0 && this->countNbMonks() == 0){
            rowingSound->stop();
            forbiddenSound->stop();
            forbiddenSound->play();
            QMessageBox::information(game, "Message", "The boat must have at least 1 Demon or 1 Monk!");
            delete timer;
            return; // stop
        }
        setPos(this->pos().x()-5, this->pos().y());
        for(int i = 0; i < 3; i++){
            if(collidesWithItem(game->monk[i])){
                game->monk[i]->setPos(game->monk[i]->pos().x()-5, game->monk[i]->pos().y());
            }
            if(collidesWithItem(game->demon[i])){
                game->demon[i]->setPos(game->demon[i]->pos().x()-5, game->demon[i]->pos().y());
            }
        }
        if(this->pos().x() < 220){
            this->setPos(this->pos());
            rowingSound->stop();
            delete timer;
            if(!isValidMove()){
                QMessageBox::information(game, "Message", "Invalid action! The number of Demons is greater than the number of Monks.");
                game->displayFinishedGameWindow("Game over!");
                failSound->stop();
                failSound->play();
            }
        }
        posBoat = LEFT_SIDE;
    }
}

void Boat::moveRight(){
    if(action == TURN_RIGHT){
        rowingSound->play();
        // when move the monk ashore, if no one in the boat -> show notification
        if(this->countNbDemons() == 0 && this->countNbMonks() == 0){
            rowingSound->stop();
            forbiddenSound->stop();
            forbiddenSound->play();
            QMessageBox::information(game, "Message", "The boat must have at least 1 Demon or 1 Monk!");
            delete timer;
            return; // stop
        }
        this->setPos(pos().x()+5, pos().y());
        for(int i = 0; i < 3; i++){
            if(collidesWithItem(game->monk[i])){
                game->monk[i]->setPos(game->monk[i]->pos().x()+5, game->monk[i]->pos().y());
            }
            if(collidesWithItem(game->demon[i])){
                game->demon[i]->setPos(game->demon[i]->pos().x()+5, game->demon[i]->pos().y());
            }
        }
        if(this->pos().x() > 485){
            this->setPos(this->pos());
            rowingSound->stop();
            delete timer;
            if(!isValidMove()){
                forbiddenSound->stop();
                forbiddenSound->play();
                QMessageBox::information(game, "Message", "Invalid action! The number of Demons is greater than the number of Monks.");
                game->displayFinishedGameWindow("Game over!");
                failSound->stop();
                failSound->play();
            }
        }
        posBoat = RIGHT_SIDE;
    }
}
