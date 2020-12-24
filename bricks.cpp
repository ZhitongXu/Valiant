#include "bricks.h"
#include <QPainter>
#include<iostream>
#include<QString>
#include <QDebug>
Bricks::Bricks(QGraphicsItem *parent, int x , int y,QString file, int w, int h):QGraphicsPixmapItem(parent)
{
       brushColor = Qt::red;
       this->file = file;
       this->setPos(x, y);
       setMyPixmap(file, w, h);

}



void Bricks::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget*){
    painter->setBrush(brushColor);
    QPixmap pixmap = this->pixmap();
    QRect rect = pixmap.rect();
    painter->drawPixmap(rect,pixmap);
}

QRectF Bricks::boundingRect()const{
    QRect rect = this->pixmap().rect();
    //return QRectF(rect);
    return QRectF(0,0,rect.height(),rect.width());
}

void Bricks::setMyPixmap(QString file, int width, int height)
{
    //myImage = file;
    QPixmap pixmap;
    pixmap.load(file);
    pixmap= pixmap.scaled(width, height,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(pixmap);
}
