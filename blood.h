#ifndef BLOOD_H
#define BLOOD_H
#include "bricks.h"

class Blood:public Bricks{
public:
    Blood(QGraphicsItem *parent = 0, int x = 0, int y = 0, QString file = "../Game/images/heart.png");
private:
    //QString file;
};

#endif // BLOOD_H
