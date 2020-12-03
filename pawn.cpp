#include "pawn.h"

Pawn::Pawn()
{

}

Pawn::Pawn(int x, int y, QString dir_image, QString piece_color, QString class_name, bool background_color) : Piece(dir_image,piece_color,class_name,background_color){
    coor.int_x = x;
    coor.int_y = y;
}

void Pawn::wherePiece(Piece* casillas[8][8]) {
    fs.clear();
    qDebug() << "Los elementos disponibles del peon en la posicion ("<< coor.int_x << ", "<< coor.int_y << ") son\n";

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if(casillas[x][y]->piece_color.compare("")==0 && piece_color.compare("white")==0 && (coor.int_x + (1+firstStep) >= x && x > coor.int_x) && y == coor.int_y) {
                addMovement(x,y);
            }
            else if(casillas[x][y]->piece_color.compare("black")==0 && piece_color.compare("white")==0 && ((coor.int_x+1==x && coor.int_y-1==y) || (coor.int_x+1==x && coor.int_y+1==y))){
                addMovement(x,y);
            }
            else if(casillas[x][y]->piece_color.compare("")==0 && piece_color.compare("black")==0 && (coor.int_x - (1+firstStep) <= x && x < coor.int_x) && y == coor.int_y) {
                addMovement(x,y);
            }
            else if(casillas[x][y]->piece_color.compare("white")==0 && piece_color.compare("black")==0 && ((coor.int_x-1==x && coor.int_y-1==y) || (coor.int_x-1==x && coor.int_y+1==y))){
                addMovement(x,y);
            }
        }
    }
    std::for_each(fs.begin(), fs.end(), [](Coordinate i) {
        qDebug() << "x: " << i.int_x << ", y: " << i.int_y << "\n";
    });

}

void Pawn::addMovement(int x,int y){
    pos.int_x = x;
    pos.int_y = y;
    fs.push_back(pos);
}
