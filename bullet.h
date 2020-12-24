#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsObject>
#include <QGraphicsItem>

#include "bricks.h"

class Bullet : public Bricks
{
public:
     Bullet(int, QGraphicsItem *parent = 0, int x = 0, int y = 0, QString file = "../Game/images/bullet1.png");
     void shoot(int);
     int getOx() {return ox;}
private:
     int direction;
     int ox;
};

#endif // BULLET_H

