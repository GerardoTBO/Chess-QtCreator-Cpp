#include "queen.h"

Queen::Queen()
{

}

Queen::Queen(int x, int y) {
    coor.int_x = x;
    coor.int_y = y;
}

void Queen::wherePiece() {
    fs.clear();
    qDebug() << "Los elementos disponibles de la reina en la posicion ("<< coor.int_x << ", "<< coor.int_y << ") son\n";
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if(firstStep) {
                if( (((x < coor.int_x || x > coor.int_x) && y == coor.int_y)
                     || ((y < coor.int_y || y > coor.int_y) && x == coor.int_x))
                     || (abs(x-coor.int_x) == abs(y-coor.int_y)
                     && (coor.int_x != x && coor.int_y != y)) ) {
                    Coordinate pos;
                    pos.int_x = x;
                    pos.int_y = y;
                    fs.push_back(pos);
                }
            }
        }
    }

    std::for_each(fs.begin(), fs.end(), [](Coordinate i) {
        qDebug() << "x: " << i.int_x << ", y: " << i.int_y << "\n";
    });
}