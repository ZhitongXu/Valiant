#include "gameboard.h"
#include "view.h"
#include "model.h"
#include <QApplication>
#include<QGraphicsScene>
#include <QDesktopWidget>
#include <QTimer>
#include<QObject>
#include<QGraphicsScene>
#include <QDebug>
#include <iostream>
#include <windows.h>
#include <QDesktopWidget>
#include "bullet.h"

class View;
class Model;
class Bullet;
GameBoard::GameBoard(Model *model,View *view):QGraphicsScene()
{
    QDesktopWidget *desktop = QApplication::desktop();
    screenWidth = desktop->availableGeometry().width();
    screenHeight = desktop->availableGeometry().height();
    adjy = int(screenWidth/2)-11 * 50;
    adj = int(screenHeight/2)-6 * 50;
    this -> model = model;
    this -> view = view;
    timerId = startTimer(10);
    gameStart = false;
    this->level = 0;
    this->p = new Play(this,"play");

}
GameBoard::~GameBoard(){
    delete model;
    delete view;
}
void GameBoard::timerEvent(QTimerEvent *event)
{
    colorEffect(effectType);
    if(isStart && !isOver){
        if(effectType ==0 ){
            clearMenu();
        }
        if(!gameStart ){
            if(level == 0 && effectType == 0){
                model->readNewMap();qDebug() << QString("readNewMap1");
                model->updateMap();qDebug() << QString("updateMap");
                gameStart = true;qDebug() << QString("gameStart");
                level ++;qDebug() << QString("level");
                model->score->update();
            }
            if(effectType == 0){
                if(level <5){
                    removeItem(model->box);
                    delete model->box;
                    removeAllItems();
                    model->bricks->clear();
                    model->invisiblebricks->clear();
                    model->bulletsOfMonster->clear();
                    model->hearts->clear();
                    model->medicines->clear();
                    model->medicinescores->clear();
                    level ++;

                    model->readNewMap(level);
                    model->updateMap();
                    directionOfPlayer = 1;
                    gameStart = true;
                }
                else if(level == 5){
                    paintover();
                }
            }
        }
        model->mylevels->setlevel(level);
        if(level > 0){
            movement(isCollideWithBrickR,isCollideWithBrickL,isCollideWithBrickT,isCollideWithBrickB);
            paint();
            movemenOfMonsters();
            movementOfShootMonsters();
            fire();
            setDirToPlayer();
            bulletsCollideWithBricks();
            judgehurted();
            hurted();
            heartreduce();
            attackMonster();
            eatmedicine();
            eatmedicinescore();
            paintover();
        }
    }
    else if(!isStart && !isOver && !stopDrawing){
        p->setPos(60+adjy, 60+adj);
        addItem(p);
        this->over = new Play(this,"over");
        over->setPos(60+adjy, 250+adj);
        addItem(over);
        stopDrawing = true;
    }
    else if(isOver && !stopDrawing && effectType == 0){
        effectType = 1;
        this->over = new Play(this,"over");
        this->replay = new Play(this,"replay");
        //qDebug()<< QString("Over!");
        replay->replay();
        addItem(over);
        addItem(replay);
        model->control->addItem(model->gameovers);
        over->setPos(screenWidth/2-400, 400+adj);
        replay->setPos(screenWidth/2+100, 400+adj);
        stopDrawing = true;
    }
}
void GameBoard::colorEffect( int b){
    static double n = 255;

    if(n > 255)n = 255;
    if(n < 0) n = 0;
    //qDebug() << QString("n") << n;
    switch (b){
    case 0:
        break;
    case 1:
        if(n >= 255){
            effectType = 0;
        }
        setForegroundBrush(QColor(255, 255, 255, 255-n));
        n += 2;
        break;
    case 2:
        if(n <= 0){
            effectType = 0;
        }
        setForegroundBrush(QColor(255, 255, 255, 255-n));
        n -= 2;
        break;

    }
}
void GameBoard::movement(bool &r, bool &l, bool&t, bool&b){
    ifCollidesWithBrick(r, l, t, b);
    if(isJumping&&t){model->box->jump();}
    if(!t){
        model->box->freelyFall();
    }
    if(isMovingL && !r){
        model->box->moveToLeft();
        playerChangeDirection(-1);
    }
    if(isMovingR && !l){
        model->box->moveToRight();
        playerChangeDirection(1);
    }
    r = l = b = t = false;
}

void GameBoard::movemenOfMonsters(){
    for(int i = 0; i < model->getMonsters()->size(); i ++){
        model->getMonsters()->at(i)->autoMove(ifChangeDiretion(i),model->getMonsters()->at(i)->p, model->getMonsters()->at(i)->q);
    }
}
void GameBoard::movementOfShootMonsters() {
    for(int i = 0; i < model->getShootMonsters()->size(); i++) {
        model->getShootMonsters()->at(i)->autoMove(ifChangeDirectionSpecial(i), model->getShootMonsters()->at(i)->p, model->getShootMonsters()->at(i)->q);
    }
}
bool GameBoard::ifChangeDiretion(int i){
    for(int j = 0; j < model->bricks->size(); j ++){
        if(model->getMonsters()->at(i)->collidesWithItem(model->bricks->at(j))){
            QPointF monsterPos = model->getMonsters()->at(i)->scenePos();
            QPointF brickPos = model->bricks->at(j)->scenePos();
            int dx = monsterPos.x() - brickPos.x();
            //int dy = monsterPos.y() - brickPos.y();
            if(dx <= 50 && dx >= -50){
                return true;
            }
        }
    }
    for(int j = 0; j < model->invisiblebricks->size(); j ++){
        if(model->getMonsters()->at(i)->collidesWithItem(model->invisiblebricks->at(j))){
            QPointF monsterPos = model->getMonsters()->at(i)->scenePos();
            QPointF brickPos = model->invisiblebricks->at(j)->scenePos();
            int dx = monsterPos.x() - brickPos.x();
            //int dy = monsterPos.y() - brickPos.y();
            if(dx <= 50 && dx >= -50){return true;}
        }
    }
    return false;
}
bool GameBoard::ifChangeDirectionSpecial(int i){
    for(int j = 0; j < model->bricks->size(); j ++){
        if(model->getShootMonsters()->at(i)->collidesWithItem(model->bricks->at(j))){
            QPointF monsterPos = model->getShootMonsters()->at(i)->scenePos();
            QPointF brickPos = model->bricks->at(j)->scenePos();
            int dx = monsterPos.x() - brickPos.x();
            //int dy = monsterPos.y() - brickPos.y();
            if(dx <= 50 && dx >= -50){
                return true;
            }
        }
    }
    for(int j = 0; j < model->invisiblebricks->size(); j ++){
        if(model->getShootMonsters()->at(i)->collidesWithItem(model->invisiblebricks->at(j))){
            QPointF monsterPos = model->getShootMonsters()->at(i)->scenePos();
            QPointF brickPos = model->invisiblebricks->at(j)->scenePos();
            int dx = monsterPos.x() - brickPos.x();
            //int dy = monsterPos.y() - brickPos.y();
            if(dx <= 50 && dx >= -50){return true;}
        }
    }
    return false;
}

void GameBoard::ifCollidesWithBrick(bool &r, bool &l, bool&t, bool&b){
    double dx;
    double dy;
    QPointF boxPos;
    QPointF brickPos;
    for(int i = 0; i < model->bricks->size(); i ++){
        if(model->box->collidesWithItem(model->bricks->at(i))){
            //qDebug()<<model->box->collidesWithItem(model->bricks->at(i));
            boxPos = model->box->scenePos();
            brickPos = model->bricks->at(i)->scenePos();
            dx = boxPos.x() - brickPos.x();
            dy = boxPos.y() - brickPos.y();
            //qDebug()<< QString("dx=") << dx<< QString("dy= ") << dy;
            if(dy <= 50 && dy >30 ){

                model->getBox()->vy *= -1;
                model->getBox()->setY(brickPos.y() + sizeOfBrick);
                b = true;
            }
            else if(dy <-60  && dy >= -75 ){
                model->getBox()->setIsFalling(false);
                model->getBox()->vy =0.0;
                model->getBox()->setY(brickPos.y() - 75);
                t = true;
            }
            else if(dx < 73 && dx > 23 && (dy<49 && dy > -70)){

                model->getBox()->setX(boxPos.x() + 5);
                r = true;
            }
            else if(dx > -73 && dx < -23 && dy<49 && dy > -70 ){
                model->getBox()->setX(boxPos.x() - 5);
                l = true;
            }
        }
    }
    if(!b){
        model->getBox()->setIsFalling(true);
    }
    return ;
}



void GameBoard::fire(){
    QPointF pos = model->getBox()->scenePos();
    if(model->bulletsOfPlayer->size() > 0){
        for(int i = 0; i < model->bulletsOfPlayer->size(); i ++){
            model->bulletsOfPlayer->at(i)->shoot(speedOfBulletsShootByPlayer);
            int dx = model->bulletsOfPlayer->at(i)->scenePos().x()-model->bulletsOfPlayer->at(i)->getOx();
            if(dx >= 330 || dx <= -330){
                removeItem(model->bulletsOfPlayer->at(i));
                model->bulletsOfPlayer->removeAt(i);
            }
        }
    }
    if(isFire){
        Bullet* b = new Bullet(directionOfPlayer,0, (pos.x()+37+model->box->boxDirection*37), pos.y()+20);
        this->addItem(b);
        model->bulletsOfPlayer->append(b);
        setFire(false);
    }
}

void GameBoard::judgehurted(){
    //遍历怪物组，是否与玩家有碰撞
    if(!model->box->getuntouchable()){
        for(int i = 0; i<model->monsters->size();i++){
            if(model->box->collidesWithItem(model->monsters->at(i))){
                model->box->sethurted(true);
                break;
            }
        }
        for(int i = 0; i < model->shootmonsters->size(); i ++){
            if(model->box->collidesWithItem(model->shootmonsters->at(i))){
                model->box->sethurted(true);
                break;
            }
        }
        for(int i = 0; i < model->bulletsOfMonster->size(); i ++){
            if(model->box->collidesWithItem(model->bulletsOfMonster->at(i))){
                model->box->sethurted(true);
                break;
            }
        }
    }
}

void GameBoard::hurted(){
    if(model->box->gethurted()){
        model->box->setuntouchable(true);
        if(model->box->getInvisible() == 0)
            setlife(getlife() - 1);
        if(model->box->getInvisible()>100){
            model->box->sethurted(false);
            model->box->setuntouchable(false);
            model->box->setInvisible(0);
        }
        else model->box->setInvisible(model->box->getInvisible()+1);
    }
}
void GameBoard::attackMonster(){
    //遍历子弹和怪兽组，是否相互有碰撞
    for(int i = 0;i<model->monsters->size();i++){
        for(int j = 0; j<model->bulletsOfPlayer->size();j++){
            if(model->monsters->at(i)->collidesWithItem(model->bulletsOfPlayer->at(j))){
                removeItem(model->monsters->at(i));
                removeItem(model->bulletsOfPlayer->at(j));
                model->monsters->removeAt(i);
                model->bulletsOfPlayer ->removeAt(j);
                model->score->increase();
                goto checkShootMonster;
            }
        }
    }
checkShootMonster:
    for(int i = 0;i<model->shootmonsters->size();i++){
        for(int j = 0; j<model->bulletsOfPlayer->size();j++){
            if(model->shootmonsters->at(i)->collidesWithItem(model->bulletsOfPlayer->at(j))){
                removeItem(model->shootmonsters->at(i));
                removeItem(model->bulletsOfPlayer->at(j));
                model->shootmonsters->removeAt(i);
                model->bulletsOfPlayer ->removeAt(j);
                model->score->increase1();
                goto checkEnd;
            }
        }
    }
checkEnd:
    if(model->shootmonsters->size() == 0 && model->monsters->size() == 0){
        effectType = 2;
        gameStart = false;

    }
}

void GameBoard::eatmedicine(){
    for(int i = 0; i<model->medicines->size();i++){
        if(model->box->collidesWithItem(model->medicines->at(i))){
            removeItem(model->medicines->at(i));
            // delete model->medicines->at(i);
            model->medicines->removeAt(i);
            if(getlife()<5&&getlife()>0){
                Blood *k = new Blood(0, getlife() * 50, 0,"../Game/images/heart.png");
                model->control->addItem(k);
                model->hearts->append(k);
                setlife(getlife()+1);
            }
        }
    }
}

void GameBoard::eatmedicinescore(){
    for(int i = 0; i<model->medicinescores->size();i++){
        if(model->box->collidesWithItem(model->medicinescores->at(i))){
            removeItem(model->medicinescores->at(i));
            // delete model->medicines->at(i);
            model->medicinescores->removeAt(i);
            model->score->increase2();
        }
    }
}

void GameBoard::setDirToPlayer() {
    for(int i = 0; i < model->shootmonsters->size(); i++) {
        int dy = model->box->scenePos().y() - model->shootmonsters->at(i)->scenePos().y();
        int dx = model->box->scenePos().x() - model->shootmonsters->at(i)->scenePos().x();
        if((dy<=10 && dy >-30)&& (dx<0 && dx > -300)) {
            model->shootmonsters->at(i)->setDirection(-1);
            if(model->bulletsOfMonster->size()==0)
                model->shootmonsters->at(i)->setFireMonster(true);
        }
        else if((dy<=10 && dy >-30)&& (dx>0 && dx < 300)) {
            model->shootmonsters->at(i)->setDirection(1);
            if(model->bulletsOfMonster->size()==0)
                model->shootmonsters->at(i)->setFireMonster(true);
        }
        if(model->shootmonsters->at(i)->getFireMonster())shootAtPlayer();
    }
    if(model->bulletsOfMonster->size() > 0){
        for(int j = 0; j < model->bulletsOfMonster->size(); j++) {
            model->bulletsOfMonster->at(j)->shoot(speedOfBulletsShootByPlayer);
            int dx = model->bulletsOfMonster->at(j)->scenePos().x()-model->bulletsOfMonster->at(j)->getOx();
            if(dx >= speedOfBulletsShootByPlayer * 50 || dx <= -speedOfBulletsShootByPlayer * 50){
                removeItem(model->bulletsOfMonster->at(j));
                model->bulletsOfMonster->removeAt(j);
            }
        }
    }

    return;
}

void GameBoard::shootAtPlayer() {
    if(model->bulletsOfMonster->size() <= 1){
        for(int i = 0; i < model->getShootMonsters()->size(); i++) {
            if(model->shootmonsters->at(i)->getFireMonster()) {
                Bullet* b = new Bullet(model->getShootMonsters()->at(i)->getDirection(),0, model->shootmonsters->at(i)->scenePos().x()+30, model->shootmonsters->at(i)->scenePos().y(),"../Game/images/fire.png");
                if(model->getShootMonsters()->at(i)->getDirection()>0){
                    b->setMyPixmap("../Game/images/fire.png", 40, 40);
                    //model->getShootMonsters()->at(i)->setMyPixmap("../Game/images/firemonsterOpenMouth.png");
                }
                else if(model->getShootMonsters()->at(i)->getDirection()<0){
                    b->setMyPixmap("../Game/images/fireLeft.png", 40, 40);
                    //model->getShootMonsters()->at(i)->setMyPixmap("../Game/images/firemonsterOpenMouthLeft.png");
                }
                this->addItem(b);
                model->bulletsOfMonster->append(b);
                model->shootmonsters->at(i)->setFireMonster(false);
            }
        }
    }
}

void GameBoard::paint(){
    static int n = 0;
    //int num = n%4;
    if(model->box->getInvisible() == 0){
        if(isMovingR){
            model->box->drawMoveR(n);
        }
        else if(isMovingL){
            model->box->drawMoveL(n);
        }
        else{
            switch(model->box->boxDirection){
            case 1:
                model->box->drawMoveR(0);
                break;
            case -1:
                model->box->drawMoveL(0);
            }
        }
        n = (n+1)%4;
    }
    else if(model->box->getInvisible() > 0){
        if(isMovingR){
            model->box->drawMoveRR(n);
        }
        else if(isMovingL){
            model->box->drawMoveLL(n);
        }
        else{
            switch(model->box->boxDirection){
            case 1:
                model->box->drawMoveRR(0);
                break;
            case -1:
                model->box->drawMoveLL(0);
            }
        }
        n = (n+1)%4;
    }
}

void GameBoard::heartreduce(){
    if(getlife()<5&&getlife()>=0){
        for(int i = model->hearts->size() - 1; i >= getlife(); i--){
            if(model->hearts->contains(model->hearts->at(i))){
                removeItem(model->hearts->at(i));
                model->hearts->removeAt(i);
            }
        }
    }
}

void GameBoard::bulletsCollideWithBricks(){
    for(int i = 0; i < model->bulletsOfPlayer->size(); i ++){
        for(int j = 0; j < model->bricks->size(); j ++){
            if(model->bulletsOfPlayer->at(i)->collidesWithItem(model->bricks->at(j))){
                removeItem(model->bulletsOfPlayer->at(i));
                model->bulletsOfPlayer->removeAt(i);
                goto checkBulletsOfMonster;
            }
        }
    }

checkBulletsOfMonster:
    for(int i = 0; i < model->bulletsOfMonster->size(); i ++){
        for(int j = 0; j < model->bricks->size(); j ++){
            if(model->bulletsOfMonster->at(i)->collidesWithItem(model->bricks->at(j))){
                removeItem(model->bulletsOfMonster->at(i));
                model->bulletsOfMonster->removeAt(i);
                goto checkBetweenBullets;
            }
        }
    }

checkBetweenBullets:
    for(int i = 0; i < model->bulletsOfMonster->size(); i ++){
        for(int j = 0; j < model->bulletsOfPlayer->size(); j ++){
            if(model->bulletsOfMonster->at(i)->collidesWithItem(model->bulletsOfPlayer->at(j))){
                removeItem(model->bulletsOfMonster->at(i));
                model->bulletsOfMonster->removeAt(i);
                removeItem(model->bulletsOfPlayer->at(j));
                model->bulletsOfPlayer->removeAt(j);
                return;
            }
        }
    }
}

void GameBoard::paintover(){
    if(getlife() <= 0){
        if(!model->gameovers)model->gameovers = new Gameover(screenWidth/2-325, 50 + adj);
        model->box->drawdie();
        effectType = 2;
        setOver(true);
    }
    else if(level == 5 && !gameStart){
       if(!model->gameovers)model->gameovers = new Gameover(screenWidth/2-325, 50 + adj);
        model->gameovers->setMyPixmap("../Game/images/win.png", 650, 250);
        effectType = 2;
        setOver(true);
    }
}



void GameBoard::removeAllItems(){
    for(int i = 0; i < model->bulletsOfPlayer->size(); i ++){
        removeItem(model->bulletsOfPlayer->at(i));
    }
    for(int i = 0; i < model->shootmonsters->size(); i ++){
        removeItem(model->shootmonsters->at(i));
    }
    for(int i = 0; i < model->monsters->size(); i ++){
        removeItem(model->monsters->at(i));
    }
    for(int i= 0; i < model->bulletsOfMonster->size(); i ++){
        removeItem(model->bulletsOfMonster->at(i));
    }
    for(int i = 0; i < model->bricks->size(); i ++){
        removeItem(model->bricks->at(i));
    }
    for(int i= 0; i < model->invisiblebricks->size(); i ++){
        removeItem(model->invisiblebricks->at(i));
    }
    for(int i = 0; i < model->medicines->size(); i ++){
        removeItem(model->medicines->at(i));
    }
    for(int i = 0; i < model->medicinescores->size(); i ++){
        removeItem(model->medicinescores->at(i));
    }
    for(int i = 0; i < model->hearts->size(); i ++){
        removeItem(model->hearts->at(i));
    }
}
void GameBoard::clearMenu(){
    stopDrawing = false;
    if(p){
        removeItem(p);
        p = 0;
    }
    if(over){
        removeItem(over);
        over = 0;
    }
    if(replay){
        removeItem(replay);
        replay = 0;
    }
    if(model->gameovers){
        removeItem(model->gameovers);
        model->gameovers = 0;

    }
}

