#include "shootmonster.h"
#include "gameboard.h"
#include "view.h"
#include "bullet.h"

ShootMonster::ShootMonster(QGraphicsItem *parent, int x, int y, QString file):Monster(parent, x, y,file){
}
void ShootMonster::autoMove(bool b,double &p, double &q){
    if(b) direction *= -1;
    moveBy(direction *speed, 0);
    if(direction > 0 ){
        setMyPixmap(fireMonsters[int(p)], 50);
        p = double((int(10 * p + 2))%30)/10;
    }
    else if(direction < 0 ){
        setMyPixmap(fireMonsterlefts[int(q)], 50);
        q = double((int(10 * q + 2))%30)/10;
    }
}
