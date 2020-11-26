#include "horse.h"

Horse::Horse()
{

}

Horse::Horse(int x, int y, QString dir_image, QString piece_color, QString class_name, bool background_color) : Piece(dir_image,piece_color,class_name,background_color){
    coor.int_x = x;
    coor.int_y = y;
}

void Horse::wherePiece(Piece* casillas[8][8]) {
    fs.clear();
    qDebug() << "Los elementos disponibles del caballo en la posicion ("<< coor.int_x << ", "<< coor.int_y << ") son\n";
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if(firstStep) {
                // (coor.int_x != x && coor.int_y != y) && (x > coor.int_x - 3 && x < coor.int_x + 3) && (y > coor.int_y - 3 && y < coor.int_y + 3) && (coor.int_x != x && coor.int_y != y) && (abs(x-y) == 1 || abs(x-y) == 3)
                if( ((x-2 == coor.int_x || x+2 == coor.int_x) && (y-1 == coor.int_y || y+1 == coor.int_y))
                        || ((y-2 == coor.int_y || y+2 == coor.int_y) && (x-1 == coor.int_x || x+1 == coor.int_x))) {
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
