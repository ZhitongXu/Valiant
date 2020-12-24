#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QMutableMapIterator>
#include <QFile>
#include <QString>
#include <QList>
#include <QTextStream>
#include <QChar>

#include "box.h"
#include "bricks.h"
#include "monster.h"
#include "gameboard.h"
#include "bullet.h"
#include "medicines.h"
#include "medicinescore.h"
#include "blood.h"
#include "shootmonster.h"
#include "invisiblebrick.h"
#include "score.h"
#include "gameover.h"
#include "levels.h"

class Box;
class GameBoard;
class ShootMonster;
class Monster;
class Model
{
public:
    Model();
    Box* getBox(){return box;}
    QList<Monster*> *getMonsters(){ return monsters; }
    QList<ShootMonster*> *getShootMonsters() {return shootmonsters; }
//private:
    Box *box;
    Blood *blood;
    Score *score;
    Level *mylevels;
    Gameover *gameovers;
    void updateMap();
    void createBrick(QList<QChar> l ,int num);
    void readNewMap(int level = 1 );
    GameBoard *control;
    void setControl(GameBoard *control){this -> control = control;}
    static int const brickSize = 50;
    static int const Hauteur = 950;
    static int const Longueur = 1600;
    static int const NbrBrickVisible = 20;
    int mapPosition = 6;
    QString stock;
    QList<QChar> ligne1;
    QList<QChar> ligne2;
    QList<QChar> ligne3;
    QList<QChar> ligne4;
    QList<QChar> ligne5;
    QList<QChar> ligne6;
    QList<QChar> ligne7;
    QList<QChar> ligne8;
    QList<QChar> ligne9;
    QList<QChar> ligne10;
    QList<QChar> ligne11;
    QList<QChar> ligne12;
    QList<Bricks*> *bricks;
    QList<Monster*> *monsters;
    QList<Bullet*> *bulletsOfPlayer;
    QList<Medicine*>  *medicines;
    QList<MedicineScore*> *medicinescores;
    QList<Bullet*> *bulletsOfMonster;
    QList<ShootMonster*> *shootmonsters;
    QList<Blood*>  *hearts;
    QList<InvisibleBrick*> *invisiblebricks;

};

#endif // MODEL_H
