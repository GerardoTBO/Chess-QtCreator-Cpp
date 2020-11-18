#include "bishop.h"

Bishop::Bishop()
{

}

Bishop::Bishop(int x, int y) {
    coor.int_x = x;
    coor.int_y = y;
}

void Bishop::wherePiece() {
    qDebug() << "Los elementos disponibles del alfil en la posicion ("<< coor.int_x << ", "<< coor.int_y << ") son\n";
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if(firstStep) {
                if( abs(x-coor.int_x) == abs(y-coor.int_y) && (coor.int_x != x && coor.int_y != y) ) {
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
