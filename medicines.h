#ifndef MEDICINES_H
#define MEDICINES_H
#include "bricks.h"

class Medicine:public Bricks
{
public:
    Medicine(QGraphicsItem *parent = 0, int x = 0, int y = 0, QString file = "../Game/images/medicine.png");
private:
    QString file;

};

#endif // MEDICINES_H
