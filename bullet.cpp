#include "bullet.h"

Bullet::Bullet(int derection, QGraphicsItem *parent, int x, int y, QString file)
    :Bricks(parent, x, y,file)
{
    ox = x;
    this->direction = derection;
    setMyPixmap(file, 20, 20);
}
void Bullet::shoot(int speed){
    moveBy(speed * direction , 0);
}
