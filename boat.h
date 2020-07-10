#ifndef BOAT_H
#define BOAT_H
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <QTransform>
#include <QMediaPlayer>
#include <QTimer>
#include <vector>
using namespace std;

class Boat : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Boat(QGraphicsItem *parent=0);
    void drawBoat(const QPixmap &pixmap, int x, int y, int w, int h);
    void buttonClicked(int act);
    void moveDemon(int id);
    void moveMonk(int id);
    bool isSlotEmpty(QPointF slot);
    bool isOnBoat(QGraphicsItem *item);
    bool isAtRiverside(QGraphicsItem *item);
    bool isValidMove();
    void gotoBoat(QGraphicsItem *item);
    void gotoRiverside(QGraphicsItem *item, vector<QPointF> position);
    int countNbMonks();
    int countNbDemons();
    bool checkGoal();
public slots:
    void moveLeft();
    void moveRight();
private:
    int action;
    QTimer *timer;
    char posBoat;
    vector<QPointF> positionDemons;
    vector<QPointF> positionMonks;
    QMediaPlayer *rowingSound;
    QMediaPlayer *winSound;
    QMediaPlayer *failSound;
    QMediaPlayer *tadaSound;
    QMediaPlayer *forbiddenSound;
    QMediaPlayer *jumpSound;
};

#endif // BOAT_H
