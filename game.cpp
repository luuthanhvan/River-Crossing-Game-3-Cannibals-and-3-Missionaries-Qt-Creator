#include "game.h"
#include "bird.h"
#include "button.h"
#include <QDebug>
#include <QTimer>
#include <QFont>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#define TURN_RIGHT 1
#define TURN_LEFT 0

Game::Game() : QGraphicsView(){
    wScreen = 900;
    hScreen  = 600;
    xStart = 0;
    yStart = 350;
    wRiverside = 220;
    hRiverside = 350;
    wBoat = 200;
    hBoat = 200;
    wMonk = 100;
    hMonk = 100;
    wDemon = 90;
    hDemon = 100;
    turn = TURN_RIGHT;

    //  load images
    riversideImg.load(":/images/land.png");
    waterImg.load(":/images/water.png");
    boatImg.load(":/images/boat.png");
    monkImg.load(":/images/monk.png");
    demonImg.load(":/images/demon.png");

    // set fixed size for the view
    setFixedSize(wScreen, hScreen);

    // set background for the view
    setBackgroundBrush(QBrush(QColor("#d7f2fa")));

    // hide scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // create a scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, wScreen, hScreen);
    setScene(scene);
}

void Game::start(){
    // clear the screen
    scene->clear();
    showRule();
}

void Game::restart(){
    scene->clear();
    drawGUI();
}

void Game::showRule(){
    int y = 10;

    QFile file("E:\\Qt\\Qt5.1.1\\Tools\\QtCreator\\bin\\Project\\rules.txt");
    // open file
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Something wrong! Cannot open file!";
    }
    else{
        QTextStream in(&file);
        while(!in.atEnd()){
            // read data from file
            QString data = in.readLine();
            // create a text
            QGraphicsTextItem * text = new QGraphicsTextItem();
            // display the text to screen
            text->setPlainText(data);
            text->setPos(10, 150+y);
            text->setFont(QFont("comic sans", 13));
            text->setDefaultTextColor(QColor("#000000"));
            y += 25; // translate y-coordinate of the text by 25px
            scene->addItem(text);
        }
    }
    file.close();

    // create close button
    Button *closeBtn = new Button(QString("OK"));
    closeBtn->setPos(410,500);
    scene->addItem(closeBtn);
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(restart()));
}

void Game::drawGUI(){
    // create a bird
    Bird *bird = new Bird();
    scene->addWidget(bird);
    // create riverside A (left side)
    riversideA = new Riverside();
    riversideA->drawRiverside(riversideImg, xStart, yStart, wRiverside, hRiverside);
    // create riverside B (right side)
    riversideB = new Riverside();
    riversideB->drawRiverside(riversideImg, ((wScreen-(2*wRiverside))+wRiverside), yStart, wRiverside, hRiverside);
    // create a river
    river = new River();
    river->drawRiver(waterImg, (xStart+wRiverside), yStart-100, (wScreen-(2*wRiverside)), hRiverside);
    // create a boat
    boat = new Boat();
    boat->drawBoat(boatImg, (((wScreen-(2*wRiverside))+wRiverside)-wBoat), yStart+50, wBoat, hBoat);
    // create 3 monks and 3 demons
    for(int i = 0; i < 3; i++){
        monk[i] = new Monk();
        demon[i] = new Demon();
    }
    int xMonk = riversideB->pos().x()+20;
    int yMonk = riversideB->pos().y()-50;
    int xDemon = riversideB->pos().x();
    int yDemon = yMonk+30;
    // draw 3 monks and 3 demons
    for(int i = 0; i < 3; i++){
        monk[i]->drawMonk(monkImg, xMonk, yMonk, wMonk, hMonk, i+1);
        demon[i]->drawDemon(demonImg, xDemon, yDemon, wDemon, hDemon, i+1);
        xMonk += 40;
        xDemon += 60;
    }

    // create the sun
    sun = new Sun();
    sun->drawTheSun(800, 20, 80);
    // create the first cloud
    cloud1 = new Cloud();
    cloud1->drawCloud(50, 30, 50, 40, 3);
    // create the second cloud
    cloud2 = new Cloud();
    cloud2->drawCloud(400, 10, 70, 50, 3);
    int xLeft = 400;
    int yLeft = 100;
    // create the button
    button = new Button(QString("Go"));
    button->setPos(xLeft, yLeft);
    connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));

    // add items to the scene
    scene->addItem(riversideA);
    scene->addItem(riversideB);
    scene->addItem(river);
    scene->addItem(boat);
    for(int i = 0; i < 3; i++){
        scene->addItem(monk[i]);
        scene->addItem(demon[i]);
    }
    scene->addItem(sun);
    scene->addItem(cloud1);
    scene->addItem(cloud2);
    scene->addItem(button);
}

void Game::buttonClicked(){
    turn = !turn;
    boat->buttonClicked(turn);
}

void Game::displayMainMenu(){
    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("3 Monks and 3 Demons Game"));
    QFont titleFont("comic sans", 30);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos, tyPos);
    scene->addItem(titleText);

    // create the play button
    Button* playButton = new Button(QString("Play"));
    int pxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int pyPos = 275;
    playButton->setPos(pxPos, pyPos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(playButton);

    // create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos, qyPos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

void Game::displayFinishedGameWindow(QString textToDisplay){
    // disable all scene items
    for (size_t i = 0, n = scene->items().size(); i < n; i++){
        scene->items()[i]->setEnabled(false);
    }

    // create playAgain button
    Button* playAgain = new Button(QString("Play Again"));
    int pxPos = this->width()/2 - playAgain->boundingRect().width()/2;
    int pyPos = 300;
    playAgain->setPos(pxPos, pyPos);
    connect(playAgain, SIGNAL(clicked()), this, SLOT(restart()));
    scene->addItem(playAgain);

    // create quit button
    Button* quit = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quit->boundingRect().width()/2;
    int qyPos = 450;
    quit->setPos(qxPos, qyPos);
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quit);

    // create text annoucning wining/losing
    QGraphicsTextItem* overText = new QGraphicsTextItem(textToDisplay);
    QFont overTextFont("comic sans", 30);
    overText->setFont(overTextFont);
    int txPos = this->width()/2 - overText->boundingRect().width()/2;
    int tyPos = 225;
    overText->setPos(txPos, tyPos);
    scene->addItem(overText);
}
