#ifndef PLAY_H
#define PLAY_H
#include "bricks.h"
#include "gameboard.h"
class GameBoard;
class Play:public Bricks
{
public:
    Play(GameBoard * control, QString t);
    void replay();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    GameBoard *control;

private:
    QString type;

};

#endif // PLAY_H
