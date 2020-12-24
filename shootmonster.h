#ifndef SHOOTMONSTER_H
#define SHOOTMONSTER_H

#include "monster.h"
#include <QPixmap>
#include <QObject>
#include "gameboard.h"
#include "model.h"

class ShootMonster:public QObject, public Monster {
    Q_OBJECT
public:
    ShootMonster(QGraphicsItem *parent = 0, int x = 0, int y = 0, QString file = "../Game/images/firemonster1.png");
    void autoMove(bool b,double &p, double &q);
    void setFireMonster(bool s)  {isFireMonster = s;}
    bool getFireMonster() {return isFireMonster;}
private:
    bool isFireMonster;

};

#endif // SHOOTMONSTER_H
