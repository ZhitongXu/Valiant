#ifndef VIEW_H
#define VIEW_H

#include"gameboard.h"
#include <QWidget>
#include<QGraphicsView>

class GameBoard;
class View :public QGraphicsView
{
    Q_OBJECT
public:
    View(QWidget *parent = 0);
    ~View();
    GameBoard *control;
    void setControl(GameBoard *control){this -> control = control;}
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);

};

#endif // VIEW_H
