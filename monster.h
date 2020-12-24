#ifndef MONSTER_H
#define MONSTER_H
#include "bricks.h"

class Monster:public Bricks
{
public:
    Monster(QGraphicsItem *parent = 0, int x = 0, int y = 0, QString file = "../Game/images/swordmonster.png");
    void autoMove(bool b,double &p, double &q);
    void setDirection(int i);
    int getDirection(){return direction;}
    int direction = 1;
    double p =0.0;
    double q = 0.0;
protected:
    QString file;
    QString swordmonsters[3];
    QString swordmonsterlefts[3];
    QString fireMonsters[3];
    QString fireMonsterlefts[3];

    double speed = 1;

};

#endif // MONSTER_H
