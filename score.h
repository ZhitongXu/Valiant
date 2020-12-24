#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score: public QGraphicsTextItem {
public:
    Score(QGraphicsTextItem * parent=0);
    void increase();
    void increase1();
    void increase2();
    void update();
    int getScore();
    void setScore(int s ){score = s;}
private:
    int score;
};
#endif // SCORE_H
