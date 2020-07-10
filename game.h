#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QBrush>
#include <QColor>
#include <QPixmap>
#include <QRect>
#include <QString>
#include <QMouseEvent>
#include <QMediaPlayer>
#include "monk.h"
#include "demon.h"
#include "riverside.h"
#include "river.h"
#include "boat.h"
#include "sun.h"
#include "cloud.h"
#include "button.h"

class Game : public QGraphicsView{
    Q_OBJECT
public:
    Game();
    QGraphicsScene *scene;
    Monk *monk[3];
    Demon *demon[3];
    Riverside *riversideA;
    Riverside *riversideB;
    Boat *boat;
    River *river;
    Sun *sun;
    Cloud *cloud1;
    Cloud *cloud2;
    Button* button;
    void displayMainMenu();
    void displayFinishedGameWindow(QString textToDisplay);
    void showRule();
    void drawGUI();
public slots:
    void buttonClicked();
    void start();
    void restart();
private:
    // width and height of the screen
    int wScreen;
    int hScreen;
    // start point
    int xStart;
    int yStart;
    // width and height of riversides
    int wRiverside;
    int hRiverside;
    // width and height of the boat
    int wBoat;
    int hBoat;
    // width and height of the monk
    int wMonk;
    int hMonk;
    // width and height of the demon
    int wDemon;
    int hDemon;
    int turn;
    QPixmap riversideImg;
    QPixmap waterImg;
    QPixmap boatImg;
    QPixmap monkImg;
    QPixmap demonImg;
};

#endif // GAME_H
