#ifndef MEDICINESCORE_H
#define MEDICINESCORE_H

#include "bricks.h"
#include "medicines.h"

class MedicineScore: public Medicine {
public:
    MedicineScore(QGraphicsItem *parent = 0, int x = 0, int y = 0, QString file = "../Game/images/medicine1.png");
};

#endif // MEDICINESCORE_H
