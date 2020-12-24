#include "bulletofmonster.h"

BulletOfMonster::BulletOfMonster(int d, QGraphicsItem *parent, int x, int y, QString file ):Bullet(d, 0, x,y, file )
{
    if(d >0){
        setMyPixmap(file,30, 30);
    }
    else if(d<0){
        setMyPixmap(file, 30, 30);
    }
}
