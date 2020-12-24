#include "view.h"
#include <QPainter>
#include <iostream>
#include <QApplication>
#include <QDebug>
#include <QRect>
#include<QKeyEvent>
#include "model.h"
#include <QGraphicsScene>
#include<QGraphicsView>


View::View(QWidget *parent): QGraphicsView(parent)
{}

View::~View()
{
    std::cout << ("View deleted\n");
}

void View::drawBackground(QPainter *painter, const QRectF &rect){
    QPixmap background("../Game/images/newbackground.png");
    //painter->drawPixmap(sceneRect, background);
    painter->drawPixmap(QRect(0, 0, width(), height()), background);

}
void View::keyPressEvent(QKeyEvent *event){
    switch (event -> key()) {
    case Qt::Key_Down:
        //control->setIsMovingD(true);
        break;
    case Qt::Key_Up:
        control->setIsJumping(true);
        break;
    case Qt::Key_Right:
        control->setIsMovingR(true);
        control->model->box->boxDirection = 1;
        break;
    case Qt::Key_Left:
        control->setIsMovingL(true);
        control->model->box->boxDirection = -1;
        //control->model->getBox()->moveBy(10,0);
        break;
    case Qt::Key_Space:
        if(control->model->bulletsOfPlayer->size()<=5 && control->model->box->getInvisible() == 0)
            control->setFire(true);
        break;
    }
    QGraphicsView::keyPressEvent(event);
}
void View::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right )
        control->setIsMovingR(false);
    else if(event->key() == Qt::Key_Left )
    {
        if(event->isAutoRepeat())return;
        control->setIsMovingL(false);
    }
    else if(event->key() == Qt::Key_Up )
        control->setIsJumping(false);
    else if(event->key() == Qt::Key_Space )
        control->setFire(false);
        //control->setIsMovingD(false);
    QGraphicsView::keyReleaseEvent(event);
}
