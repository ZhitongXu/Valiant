#include "monster.h"
#include<QDebug>
Monster::Monster(QGraphicsItem *parent, int x, int y, QString file):Bricks(parent, x, y,file){
    swordmonsters[0] = QString("../Game/images/swordmonster.png");
    fireMonsters[0] = QString("../Game/images/firemonster.png");
    for(int i = 1;i < 3; i ++){
        swordmonsters[i] = QString("../Game/images/swordmonster");
        swordmonsters[i].append(i+48);
        swordmonsters[i].append(QString(".png"));
    }
    swordmonsterlefts[0] = QString("../Game/images/swordmonsterleft.png");
    for(int i = 1;i < 3; i ++){
        swordmonsterlefts[i] = QString("../Game/images/swordmonsterleft");
        swordmonsterlefts[i].append(i+48);
        swordmonsterlefts[i].append(QString(".png"));
    }
    for(int i = 1;i < 3; i ++){
        fireMonsters[i] = QString("../Game/images/firemonster");
        fireMonsters[i].append(i+48);
        fireMonsters[i].append(QString(".png"));
    }
    fireMonsterlefts[0] = QString("../Game/images/firemonsterleft.png");
    for(int i = 1;i < 3; i ++){
        fireMonsterlefts[i] = QString("../Game/images/firemonsterleft");
        fireMonsterlefts[i].append(i+48);
        fireMonsterlefts[i].append(QString(".png"));
    }
}
void Monster::autoMove(bool b,double &p, double &q){
    //static int p = 0;
    //static int q = 0;
    if(b) direction *= -1;
    moveBy(direction *speed , 0);
    if(direction > 0 ){
        setMyPixmap(swordmonsters[int(p)], 50);
        p = double((int(10 * p + 2))%30)/10;
    }
    else if(direction < 0 ){
        setMyPixmap(swordmonsterlefts[int(q)], 50);
        q = double((int(10 * q + 2))%30)/10;
    }
}

void Monster::setDirection(int i)
{
    direction = i;
}
