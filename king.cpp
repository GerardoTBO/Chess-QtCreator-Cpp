#include "king.h"

King::King()
{

}

King::King(int x, int y, QString dir_image, QString piece_color, QString class_name, bool background_color) : Piece(dir_image,piece_color,class_name,background_color){
    coor.int_x = x;
    coor.int_y = y;
}

void King::wherePiece(Piece* casillas[8][8],bool firstIteracion,bool quede) {
    fs.clear();
    qDebug() << "Los elementos disponibles del rey en la posicion ("<< coor.int_x << ", "<< coor.int_y << ") son\n";
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if(casillas[x][y]->piece_color.compare(piece_color)!=0 && ((abs(x-coor.int_x) == 1 && abs(y-coor.int_y) == 1)
                                                                       || (abs(x-coor.int_x) == 1 && y-coor.int_y == 0 )
                                                                       || (abs(y-coor.int_y) == 1 && x-coor.int_x == 0 ))) {
                pos.int_x = x;
                pos.int_y = y;
                fs.push_back(pos);
            }
        }
    }

    //Calculando jake
    for(int x=0; x<8 && firstIteracion; x++){
        for(int y=0;y<8;y++){
            if(casillas[x][y]->class_name.compare("piece")!=0 && casillas[x][y]->piece_color.compare(piece_color)!=0){
                casillas[x][y]->wherePiece(casillas,false,false);
                //recorre fs de casillas[x][y] y borra las coincidencias con fs de king
                for(std::size_t i=0;i<casillas[x][y]->fs.size();i++){
                    deleteElementFs(fs[i]);
                }
            }
        }
    }

    std::for_each(fs.begin(), fs.end(), [](Coordinate i) {
        qDebug() << "x: " << i.int_x << ", y: " << i.int_y << "\n";
    });
}
