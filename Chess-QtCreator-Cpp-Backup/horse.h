#ifndef HORSE_H
#define HORSE_H

#include "piece.h"
#include <vector>
#include <string>
#include <cmath>

class Horse : public Piece{

    private:
        bool firstStep{true};

    public:
        Horse();

        Horse(int x, int y) {
            coor.int_x = x;
            coor.int_y = y;
        }

        void wherePiece() {
            fs.clear();
            qDebug() << "Los elementos disponibles del caballo en la posicion ("<< coor.int_x << ", "<< coor.int_y << ") son\n";
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    if(firstStep) {
                        // (coor.int_x != x && coor.int_y != y) && (x > coor.int_x - 3 && x < coor.int_x + 3) && (y > coor.int_y - 3 && y < coor.int_y + 3) && (coor.int_x != x && coor.int_y != y) && (abs(x-y) == 1 || abs(x-y) == 3)
                        if( ((x-2 == coor.int_x || x+2 == coor.int_x) && (y-1 == coor.int_y || y+1 == coor.int_y))
                                || ((y-2 == coor.int_y || y+2 == coor.int_y) && (x-1 == coor.int_x || x+1 == coor.int_x))) {
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

#endif // HORSE_H
