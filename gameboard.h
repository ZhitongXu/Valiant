#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include<QWidget>
//#include <QKeyEvent>
//#include <QMutableMapIterator>
#include <QDesktopWidget>
#include <QObject>
#include<QGraphicsScene>

#include "model.h"
#include "view.h"
#include "model.h"
#include "medicines.h"
#include "blood.h"
#include "shootmonster.h"
#include "bulletofmonster.h"
#include "play.h"
class View;
class Model;
class Play;
class GameBoard:public QGraphicsScene
{
    Q_OBJECT
public:
    GameBoard( Model * model,View * view);
    ~GameBoard();
    View * view;
    Model * model;
    View* getView(){return view; }
    Model* getModel(){return model;}
    bool gameStart = true;
    void timerEvent(QTimerEvent *);
    //改变玩家行为状态
    void setIsMovingR(bool b){isMovingR = b;}
    void setIsMovingL(bool b){isMovingL = b;}
    void setIsJumping(bool b){isJumping = b;}
    void setFire(bool b){isFire = b;}
    void playerChangeDirection(int d){directionOfPlayer = d;}//改变玩家方向

    //改变玩家的子弹的速度
    void bulletChangeSpeed(int s){speedOfBulletsShootByPlayer = s;}
    //void
    void colorEffect(int b);
    void eatmedicine();
    void eatmedicinescore();
    //改变怪兽的方向以及怪兽发射子弹
    void setDirToPlayer();
    void shootAtPlayer();
    int  effectType = 0;
    int getSizeOfBrick(){return sizeOfBrick;}
    //大小
    int sizeOfSoldier = 75;
    int sizeOfBrick = 50;
    int getlife(){return life;}
    void setlife(int l){life = l;}
    void setStart(bool s){isStart = s;}
    void setOver(bool o){isOver = o;}
    Play *p = 0;
    Play *over = 0;
    Play *replay = 0;
    void setLevel(int l){level = l;}
    void removeAllItems();
    int adjy;
    int adj;
    int screenWidth;
    int screenHeight;


private:
    bool stopDrawing = false;
    bool isStart = false;
    bool isOver = false;
    bool isComPlete = false;
    int life = 5;
    int level = 0;
    int speedOfBulletsShootByPlayer = 10;//玩家子弹的速度
    int directionOfPlayer = 1;//玩家（子弹）的方向
    bool isMovingR = false;//是否朝某方向运动
    bool isMovingL = false;
    bool isJumping = false;
    bool isFire = false;//玩家是否发射子弹
    bool isCollideWithBrickR = false;
    bool isCollideWithBrickL = false;
    bool isCollideWithBrickT = false;
    bool isCollideWithBrickB = false;
    int timerId=0;

    void clearMenu();
    //检测玩家的碰撞
    void ifCollidesWithBrick(bool &r, bool &l, bool&t, bool&b);
    void judgehurted();
    void hurted();
    void heartreduce();

    //玩家的运动行为
    void movement(bool&r, bool&l, bool&t, bool&b);
    void fire();

    //检测怪物的碰撞
    void attackMonster();

    //怪物的运动行为
    void movemenOfMonsters();
    void movementOfShootMonsters();
    bool ifChangeDiretion(int);
    bool ifChangeDirectionSpecial(int);
    //检测子弹碰撞墙面
    void bulletsCollideWithBricks();
    void paint();
    void paintover();

};

#endif // GAMEBOARD_H
