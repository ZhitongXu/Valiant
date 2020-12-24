#include "gameover.h"
#include <QFont>

Gameover::Gameover(int x, int y): Bricks(0, x, y, "../Game/images/win.png") {
    setMyPixmap("../Game/images/gameover.png", 650, 250);
}
