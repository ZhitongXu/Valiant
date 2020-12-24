#ifndef BOX_H
#define BOX_H

#include <QGraphicsItem>
#include <QGraphicsPathItem>
#include <QPropertyAnimation>
#include<QString>

class Box :public QGraphicsPixmapItem
{
public:
    Box(QGraphicsItem *parent = 0, int x = 0, int y = 0, QString file = "../Game/images/soldier.png");
    QRectF boundingRect()const;
    void paint(QPainter*painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setMyPixmap(QString file,int size);
    void moveToLeft();
    void moveToRight();
    void jump();
    void freelyFall();
    double vy = 0.0;
    void setIsFalling(bool b){isFalling = b;}
    bool getIsFalling(){return isFalling;}
    void setuntouchable(bool Untouchable){untouchable = Untouchable;}
    bool getuntouchable(){return untouchable;}
    void sethurted(bool HURT){ifhurted = HURT;}
    bool gethurted(){return ifhurted;}
    int getInvisible(){return Invisible;}
    void setInvisible(int i){Invisible = i;}
    void drawdie();
    void drawMoveR(int);
    void drawMoveL(int);
    void drawMoveRR(int);
    void drawMoveLL(int);
    int boxDirection = 1;
private:
    QString file;
    int size = 75;
    bool isFalling = false;
    bool untouchable = false;
    bool ifhurted = false;
    bool invisible = false;
    int Invisible = 0;
    QString die;
    QString moveRPictures[4];
    QString hurtsoldiers[4];
    QString moveLPictures[4];
    QString hurtsoldiersleft[4];
};

#endif // BOX_H
