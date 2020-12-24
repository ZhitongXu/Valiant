#include <QDesktopWidget>
#include <QApplication>
#include <QGraphicsView>
#include <QPixmap>
#include <QDebug>
#include "model.h"
#include "view.h"
#include "gameboard.h"
void center(View &view)
{
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //int x, y;
    int screenWidth;
    int screenHeight;

    QDesktopWidget *desktop = QApplication::desktop();
    screenWidth = desktop->availableGeometry().width();
    screenHeight = desktop->availableGeometry().height();
   // view.resize(Model::Longueur, Model::Hauteur);
    //view.control->setSceneRect(0, 0, Model::Longueur - x, Model::Hauteur - y);
    //view.resize(screenWidth, screenHeight);
    view.showMaximized();
    //view.control->setSceneRect(desktop->availableGeometry());
    view.control->setSceneRect(0, 0, screenWidth-4, screenHeight-31);
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Model m;
    View v;
    GameBoard window(&m, &v);
    v.setScene(&window);
    v.setControl(&window);
    m.setControl(&window);
    QPixmap background("../Game/images/newbackground.png");
   // window.setBackgroundBrush(background);
    center(v);
    v.show();
    return app.exec();
}
