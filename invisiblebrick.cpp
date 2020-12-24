#include <QGraphicsEffect>
#include "invisiblebrick.h"

InvisibleBrick::InvisibleBrick(QGraphicsItem *parent, int x , int y,QString file)
{
       brushColor = Qt::red;
       this->file = file;
       this->setPos(x, y);
       setMyPixmap(file);
       Nosee();

}


/*
void InvisibleBrick::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget*){
    painter->setBrush(brushColor);
    QPixmap pixmap = this->pixmap();
    QRect rect = pixmap.rect();
    painter->drawPixmap(rect,pixmap);
}

QRectF InvisibleBrick::boundingRect()const{
    QRect rect = this->pixmap().rect();
    //return QRectF(rect);
    return QRectF(0,0,rect.height(),rect.width());
}

void InvisibleBrick::setMyPixmap(QString file, int width, int height)
{
    //myImage = file;
    QPixmap pixmap;
    pixmap.load(file);
    pixmap= pixmap.scaled(width, height,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(pixmap);
}
*/
void InvisibleBrick::Nosee(){
    QGraphicsOpacityEffect *nosee = new QGraphicsOpacityEffect;
    nosee->setOpacity(0);
    setGraphicsEffect(nosee);
}
