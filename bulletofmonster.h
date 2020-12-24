#ifndef BULLETOFMONSTER_H
#define BULLETOFMONSTER_H
#include"bullet.h"

class BulletOfMonster:public Bullet
{
public:
    BulletOfMonster(int, QGraphicsItem *parent = 0, int x = 0, int y = 0, QString file = "../Game/images/fire.png");
};

#endif // BULLETOFMONSTER_H
