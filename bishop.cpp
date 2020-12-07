#include "bishop.h"

Bishop::Bishop()
{

}

Bishop::Bishop(int x, int y, QString dir_image, QString piece_color, QString class_name, bool background_color) : Piece(dir_image,piece_color,class_name,background_color){
    coor.int_x = x;
    coor.int_y = y;
}

void Bishop::wherePiece(Piece* casillas[8][8],bool firstIteracion,bool quede) {
    fs.clear();
    qDebug() << "Los elementos disponibles del alfil en la posicion ("<< coor.int_x << ", "<< coor.int_y << ") son\n";
//    for (int x = 0; x < 8; x++) {
//        for (int y = 0; y < 8; y++) {
//            if( abs(x-coor.int_x) == abs(y-coor.int_y) && (coor.int_x != x && coor.int_y != y) ) {
//                pos.int_x = x;
//                pos.int_y = y;
//                fs.push_back(pos);
//            }
//        }
//    }

    //Sentido del reloj
    //direcciones permitidas  noreste, sureste, suroeste, noroeste
    bool direcciones[4] = {true, true, true, true};

    //Movimiemtos hacia noreste
    for(int x=coor.int_x+1, y=coor.int_y+1; x<8 && y<8 && direcciones[0]; x++, y++){
        addMovement(direcciones[0],casillas[x][y],x,y,quede);
    }

    //Movimiemtos hacia sureste
    for(int x=coor.int_x-1, y=coor.int_y+1; x>=0 && y<8 && direcciones[1]; x--, y++){
        addMovement(direcciones[1],casillas[x][y],x,y,quede);
    }

    //Movimiemtos hacia suroeste
    for(int x=coor.int_x-1, y=coor.int_y-1; x>=0 && y>=0 && direcciones[2]; x--, y--){
        addMovement(direcciones[2],casillas[x][y],x,y,quede);
    }

    //Movimiemtos hacia noroeste
    for(int x=coor.int_x+1, y=coor.int_y-1; x<8 && y>=0 && direcciones[3]; x++, y--){
        addMovement(direcciones[3],casillas[x][y],x,y,quede);
    }

    std::for_each(fs.begin(), fs.end(), [](Coordinate i) {
        qDebug() << "x: " << i.int_x << ", y: " << i.int_y << "\n";
    });
}

void Bishop::addMovement(bool& d,Piece* p,int x,int y,bool quede){
    //Si es una pieza jugable del mismo color
    if(p->piece_color.compare(piece_color)==0){
        d=false;
    }
    //Si es una pieza jugable de diferente color
    else if(p->piece_color.compare("")!=0){
        if(quede && p->class_name.compare("king")==0){
            qDebug() << "El rey esta en jake\n";
        }
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
