#include "score.h"
#include <QFont>

Score::Score(QGraphicsTextItem *parent): QGraphicsTextItem(parent) {
    score = 0;
    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::gray);
    setFont(QFont("Segoe Print",20,600));//Papyrus
}

void Score::increase()
{
    score += 30;
    setPlainText(QString("Score: ") + QString::number(score));
}

void Score::increase1()
{
    score += 50;
    setPlainText(QString("Score: ") + QString::number(score));
}

void Score::increase2()
{
    score += 25;
    setPlainText(QString("Score: ") + QString::number(score));
}
int Score::getScore()
{
    return score;
}
void Score::update(){
    setPlainText(QString("Score: ") + QString::number(score));
}
