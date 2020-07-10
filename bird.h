#ifndef BIRD_H
#define BIRD_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QRect>

class Bird: public QWidget{
    Q_OBJECT
public:
    Bird(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void drawBird(QPainter &painter);
private:
    double timerId;
    double position;
    double posImage;
};

#endif // BIRD_H
