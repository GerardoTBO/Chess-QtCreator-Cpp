#include "rook.h"

Rook::Rook()
{

}

Rook::Rook(int x, int y, QString dir_image, QString piece_color, QString class_name, bool background_color) : Piece(dir_image,piece_color,class_name,background_color){
    coor.int_x = x;
    coor.int_y = y;
}

void Rook::wherePiece(Piece* casillas[8][8]) {
    fs.clear();
    qDebug() << "Los elementos disponibles de la torre en la posicion ("<< coor.int_x << ", "<< coor.int_y << ") son\n";
//    for (int x = 0; x < 8; x++) {
//        for (int y = 0; y < 8; y++) {
//            if( (x != coor.int_x && y == coor.int_y) || (y != coor.int_y && x == coor.int_x) ) {
//                pos.int_x = x;
//                pos.int_y = y;
//                fs.push_back(pos);
//            }
//        }
//    }

    //Sentido del reloj
    //direcciones permitidas norte, este, sur, oeste
    bool direcciones[4] = {true, true, true, true};

    //Movimiemtos hacia el norte
    for(int x=coor.int_x+1; x<8 && direcciones[0]; x++){
        addMovement(direcciones[0],casillas[x][coor.int_y],x,coor.int_y);
    }

    //Movimiemtos hacia la este
    for(int y=coor.int_y+1; y<8 && direcciones[1]; y++){
        addMovement(direcciones[1],casillas[coor.int_x][y],coor.int_x,y);
    }

    //Movimiemtos hacia sur
    for(int x=coor.int_x-1; x>=0 && direcciones[2]; x--){
        addMovement(direcciones[2],casillas[x][coor.int_y],x,coor.int_y);
    }

    //Movimiemtos hacia el oeste
    for(int y=coor.int_y-1; y>=0 && direcciones[3]; y--){
        addMovement(direcciones[3],casillas[coor.int_x][y],coor.int_x,y);
    }

    std::for_each(fs.begin(), fs.end(), [](Coordinate i) {
        qDebug() << "x: " << i.int_x << ", y: " << i.int_y << "\n";
    });
}

void Rook::addMovement(bool& d,Piece* p,int x,int y){
    //Si es una pieza jugable del mismo color
    if(p->piece_color.compare(piece_color)==0){
        d=false;
    }
    //Si es una pieza jugable de diferente color
    else if(p->piece_color.compare("")!=0){
        pos.int_x = x;
        pos.int_y = y;
        fs.push_back(pos);
        d=false;
    }
    else{
        pos.int_x = x;
        pos.int_y = y;
        fs.push_back(pos);
    }
}
