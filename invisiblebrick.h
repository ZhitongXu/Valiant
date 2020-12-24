#ifndef INVISIBLEBRIKE_H
#define INVISIBLEBRIKE_H

#include <QGraphicsObject>
#include <QGraphicsItem>
#include "bricks.h"

class InvisibleBrick:public Bricks
{
public:
    InvisibleBrick(QGraphicsItem *parent = 0, int x = 0, int y = 0, QString file = "../Game/images/brick.png");
    //父对象、x,y坐标，图像文件
    /*
    QRectF boundingRect()const;
    void paint(QPainter*painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setColor(const QColor &color){brushColor = color;}
    void setMyPixmap(QString file,int width = 50, int height = 50);
    */
    void Nosee();

private:
    QColor brushColor;
    QString file;

};

#endif // INVISIBLEBRIKE_H
