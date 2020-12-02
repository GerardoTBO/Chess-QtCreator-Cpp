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
//                qDebug() << "Los elementos disponibles del peon en la posicion ("<< coor.int_x << ", "<< coor.int_y << ") son\n";
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(casillas[i][j]->class_name.compare("piece")!=0){
                qDebug() << "x: " << i << " y: " << j << " tipo: " << casillas[i][j]->class_name << "\n";
            }
        }
    }

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if(firstStep) {
                if(piece_color.compare("white")==0 && (coor.int_x + 2 >= x && x > coor.int_x) && y == coor.int_y) {
                    pos.int_x = x;
                    pos.int_y = y;
                    fs.push_back(pos);
                }
                else if(piece_color.compare("black")==0 && (coor.int_x - 2 <= x && x < coor.int_x) && y == coor.int_y) {
                    pos.int_x = x;
                    pos.int_y = y;
                    fs.push_back(pos);
                }
            }
            else{
                if(piece_color.compare("white")==0 && (coor.int_x + 1 >= x && x > coor.int_x) && y == coor.int_y) {
                    pos.int_x = x;
                    pos.int_y = y;
                    fs.push_back(pos);
                }
                else if(piece_color.compare("black")==0 && (coor.int_x - 1 <= x && x < coor.int_x) && y == coor.int_y) {
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

