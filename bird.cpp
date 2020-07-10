#include "bird.h"

Bird::Bird(QWidget *parent): QWidget(parent){
    setFixedSize(900, 600);
    setStyleSheet("background:#d7f2fa;");
    position = 0;
    posImage = 0;
    timerId = startTimer(100);
}

void Bird::timerEvent(QTimerEvent *){
    position += 1;
    posImage += 2;
    if(posImage == 10)
        posImage = 0;
    repaint();
}

void Bird::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawBird(painter);
}

void Bird::drawBird(QPainter &painter){
    QPixmap birdImg(":/images/bird.png"); // load image
    double wImage = birdImg.width()/13; // width of small images
    double hImage = birdImg.height(); // height of small images
    int r = 20;
    // create a window which has fixed coordinate and size with each small images
    QRect displayWindow(wImage*posImage, 0, wImage, hImage);
    // create a display window at position
    QRect pos(position*r, 100, wImage, hImage);
//    cout << position << endl;
    if(position == 85){
        position = 0;
    }
    painter.drawPixmap(pos, birdImg, displayWindow);
}
