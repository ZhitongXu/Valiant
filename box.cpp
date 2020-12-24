#include "box.h"
#include <QPainter>
#include<iostream>
#include<QString>
#include<QDebug>

Box::Box(QGraphicsItem *parent, int x , int y,QString file):QGraphicsPixmapItem(parent)
{
       this->file = file;
       this->setPos(x, y);
       setMyPixmap(file,size);
       moveRPictures[0] = QString("../Game/images/soldier.png");
       for(int i = 1;i < 4; i ++){
           moveRPictures[i] = QString("../Game/images/soldier");
           moveRPictures[i].append(i+48);
           moveRPictures[i].append(QString(".png"));
       }
       hurtsoldiers[0] = QString("../Game/images/hurtsoldier.png");
       for(int i = 1;i < 4; i ++){
           hurtsoldiers[i] = QString("../Game/images/hurtsoldier");
           hurtsoldiers[i].append(i+48);
           hurtsoldiers[i].append(QString(".png"));
       }
       moveLPictures[0] = QString("../Game/images/soldierleft.png");
       for(int i = 1;i < 4; i ++){
           moveLPictures[i] = QString("../Game/images/soldierleft");
           moveLPictures[i].append(i+48);
           moveLPictures[i].append(QString(".png"));
       }
       hurtsoldiersleft[0] = QString("../Game/images/hurtsoldierleft.png");
       for(int i = 1;i < 4; i ++){
           hurtsoldiersleft[i] = QString("../Game/images/hurtsoldierleft");
           hurtsoldiersleft[i].append(i+48);
           hurtsoldiersleft[i].append(QString(".png"));
       }
       die = QString("../Game/images/diesoldier");
}

void Box::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget*){
    QPixmap pixmap = this->pixmap();
    QRect rect = pixmap.rect();
    painter->drawPixmap(rect,pixmap);
}

QRectF Box::boundingRect()const{
    QRect rect = this->pixmap().rect();
    return QRectF(rect.x(),rect.y(),rect.height(),rect.width());
}

void Box::setMyPixmap(QString file, int size)
{
    QPixmap pixmap;
    pixmap.load(file);
    pixmap= pixmap.scaled(size,size,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(pixmap);
}

void Box::moveToLeft(){
    moveBy(-3,0);
}
void Box::moveToRight(){
    moveBy(3,0);

}
void Box::jump(){//跳跃，到最高点停止
    setIsFalling(true);
    vy = 10.0;
}
void Box::freelyFall(){
    //qDebug()<<getIsFalling();
    if(getIsFalling()){
        if(vy>-10)
            vy -= 0.3;
        moveBy(0, -vy);
    }

}
void Box::drawMoveR(int num){
    setMyPixmap(moveRPictures[num], size);
}
void Box::drawMoveL(int num){
    setMyPixmap(moveLPictures[num], size);
}

void Box::drawMoveRR(int num){
    setMyPixmap(hurtsoldiers[num], size);
}
void Box::drawMoveLL(int num){
    setMyPixmap(hurtsoldiersleft[num], size);
}

void Box::drawdie(){
    setMyPixmap(die,size);
}
