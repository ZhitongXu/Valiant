#include "levels.h"
#include <QFont>

Level::Level(QGraphicsTextItem *parent): QGraphicsTextItem(parent) {
    mylevel = 1;
    setPlainText(QString("Level: ") + QString::number(mylevel));
    setDefaultTextColor(Qt::gray);
    setFont(QFont("Papyrus",30,700));//Papyrus
}

void Level::setlevel(int LEVEL){
    mylevel = LEVEL;
    setPlainText(QString("Level: ") + QString::number(mylevel));
}
