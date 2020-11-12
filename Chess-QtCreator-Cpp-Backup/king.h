#ifndef KING_H
#define KING_H

#include "piece.h"
#include <cmath>

class King : public Piece {

    private:
        bool firstStep{true};

    public:
        King();

        King(int x, int y) {
            coor.int_x = x;
            coor.int_y = y;
        }

        void wherePiece() {
            fs.clear();
            qDebug() << "Los elementos disponibles del rey en la posicion ("<< coor.int_x << ", "<< coor.int_y << ") son\n";
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    if(firstStep) {
                        if( (abs(x-coor.int_x) == 1 && abs(y-coor.int_y) == 1)
                                || (abs(x-coor.int_x) == 1 && y-coor.int_y == 0 )
                                || (abs(y-coor.int_y) == 1 && x-coor.int_x == 0 )) {
                            Coordinate pos{0,0};
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

};

#endif // KING_H
