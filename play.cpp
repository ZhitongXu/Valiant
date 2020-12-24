#include "play.h"
#include <stdlib.h>
#include <QDebug>
class GameBoard;
Play::Play(GameBoard * control, QString t):Bricks(0, 0, 0, "../Game/images/button.jpg", 100, 50)
{
    this->control = control;
    this->type = t;
    if(type == "play"){
        setMyPixmap("../Game/images/play.png", 300, 150);
    }
    else if(type == "over"){
        setMyPixmap("../Game/images/over.png", 300, 150);
    }
    else if(type == "replay"){
        setMyPixmap("../Game/images/replay.png", 300, 150);
    }
    qDebug() << type << QString("create");
}
void Play::mousePressEvent(QGraphicsSceneMouseEvent* event){
    if(type == "play"){
        control->setStart(true);
        control->effectType = 2;
    }
   else if(type == "replay"){
        control->effectType = 2;
        control->gameStart = false;
        control->setOver(false);
        control->setStart(true);

    }
    else if(type == "over"){
        exit(1);
    }
    //this->setVisible(false);
    //control->removeItem(this);
}
void Play::replay(){
    control->setLevel(0);qDebug("setLevel");
    control->setlife(5);
    control->model->score->setScore(0);

    control->removeItem(control->model->mylevels);
    control->removeItem(control->model->box);qDebug("removeItem");
    control->removeAllItems();qDebug("removeAllItems");
    control->model->box= 0;qDebug("box= 0");
    control->model->hearts->clear();
    control->model->bricks->clear();qDebug() << QString("brick");
    control->model->bulletsOfMonster->clear();qDebug() << QString("bullmon");
    control->model->monsters->clear();qDebug() << QString("monsters");
    control->model->shootmonsters->clear();qDebug() << QString("shootmonsters");
    control->model->medicines->clear();qDebug() << QString("medicines");
    control->model->medicinescores->clear();qDebug() << QString("medicinescores");

}
