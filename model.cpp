#include "model.h"


Model::Model()
{
//    box = new Box;
    bricks = new QList<Bricks*>;
    monsters = new QList<Monster*>;
    bulletsOfPlayer = new QList<Bullet*>;
    //
    medicines = new QList<Medicine*>;
    medicinescores = new QList<MedicineScore*>;

    //
    shootmonsters = new QList<ShootMonster*>;
    bulletsOfMonster = new QList<Bullet*>;
    hearts = new QList<Blood*>;
    score = new Score;
    gameovers = new Gameover(280 + control->adjy, 50 + control->adj);
    mylevels = new Level;
    invisiblebricks = new QList<InvisibleBrick*>;
    //readNewMap();
}

void Model::readNewMap(int level){
    ligne1.clear();
    ligne2.clear();
    ligne3.clear();
    ligne4.clear();
    ligne5.clear();
    ligne6.clear();
    ligne7.clear();
    ligne8.clear();
    ligne9.clear();
    ligne10.clear();
    ligne11.clear();
    ligne12.clear();
    QString file = "../Game/ModelMap_";
    file.append(level + 48);
    file.append(".txt");
    QFile fichier(file);

    if(fichier.open(QIODevice::ReadOnly))
    {
        QTextStream in (&fichier);
        while(!in.atEnd())
        {
            stock = in.readLine();
            if (stock.left(6)=="LIGNEa")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne1.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEb")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne2.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEc")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne3.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEd")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne4.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEe")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne5.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEf")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne6.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEg")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne7.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEh")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne8.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEi")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne9.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEj")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne10.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEk")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne11.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEl")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne12.append(stock.at(i));
                    }
                }
            }
        }
        fichier.close();
    }
}

void Model::createBrick(QList<QChar> l ,int num){
    int adjy = control->adjy;
    int adj = control->adj;
    QChar myChar = l.at(mapPosition);

    if(myChar == '0')
        return;
    else if(myChar == '2'){
        box= new Box(0,(mapPosition - 7) * 50 + adjy-10, num * 50+adj -25);
        control->addItem(static_cast<QGraphicsPixmapItem*>(box));
        return;
    }
    else if(myChar == '9'){
        Bricks *k= new Bricks(0,(mapPosition - 7) * 50 + adjy, num * 50 + adj,"../Game/images/brickside.png");
        control->addItem(k);
        bricks->append(k);
        return;
    }
    else if(myChar == '3'){
        Monster *k= new Monster(0,(mapPosition - 7) * 50 + adjy, num * 50 +adj,"../Game/images/swordmonster.png");
        control->addItem(k);
        monsters ->append(k);
        return;
    }
    else if(myChar == '4'){
        ShootMonster *k= new ShootMonster(0,(mapPosition - 7) * 50 + adjy, adj + num * 50,"../Game/images/firemonster1.png");
        control->addItem(k);
        shootmonsters ->append(k);
        return;
    }
    else if(myChar == '6'){
        Medicine *k = new Medicine(0,(mapPosition - 7) * 50 + adjy, adj+num * 50,"../Game/images/medicine.png");
        control->addItem(k);
        medicines->append(k);
        return;
    }
    else if(myChar == '7'){
        MedicineScore *k = new MedicineScore(0,(mapPosition - 7) * 50 + adjy, adj+num * 50,"../Game/images/medicine1.png");
        control->addItem(k);
        medicinescores->append(k);
        return;
    }
    else if(myChar == '8'){
        InvisibleBrick *k= new InvisibleBrick(0,(mapPosition - 7) * 50 + adjy, adj+num * 50,"../Game/images/brick1.png");
        control->addItem(k);
        invisiblebricks->append(k);
        return;
    }
}

void Model::updateMap(){
    control->effectType = 1;
    mapPosition = 6;
    for(int i = 0; i<ligne1.size() -6; i ++){
        createBrick(ligne1,1);
        createBrick(ligne2,2);
        createBrick(ligne3,3);
        createBrick(ligne4,4);
        createBrick(ligne5,5);
        createBrick(ligne6,6);
        createBrick(ligne7,7);
        createBrick(ligne8,8);
        createBrick(ligne9,9);
        createBrick(ligne10,10);
        createBrick(ligne11,11);
        createBrick(ligne12,12);
        mapPosition++;
    }
    for(int i = 0; i < control->getlife(); i++){
        Blood *k = new Blood(0, i * 50, 0,"../Game/images/heart.png");
        control->addItem(k);
        hearts->append(k);
    }
    control->addItem(score);
    score->setPos(control->width() - 230, 0);
    control->addItem(mylevels);
    mylevels->setPos(control->width()/2-100,0);

}


