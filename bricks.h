#ifndef BRICKS_H
#define BRICKS_H

#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include<QString>

class Bricks:public QGraphicsPixmapItem
{
public:
    Bricks(QGraphicsItem *parent = 0, int x = 0, int y = 0, QString file = "../Game/images/brick.png", int w = 50, int h = 50);
    //父对象、x,y坐标，图像文件
    QRectF boundingRect()const;
    void paint(QPainter*painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setColor(const QColor &color){brushColor = color;}
    void setMyPixmap(QString file,int width = 50, int height = 50);


private:
    QColor brushColor;
    QString file;
};

#endif // BRICKS_H
