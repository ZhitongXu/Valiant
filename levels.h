#ifndef LEVELS_H
#define LEVELS_H

#include <QGraphicsTextItem>

class Level: public QGraphicsTextItem {
public:
    Level(QGraphicsTextItem * parent=0);
    void setlevel(int LEVEL);
private:
    int mylevel;
};

#endif // LEVELS_H
