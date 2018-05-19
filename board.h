//
// Created by lukas on 17.05.18.
//

#ifndef WARCABY_BOARD_H
#define WARCABY_BOARD_H

#include <GL/glut.h>
#include "field.h"
#include "pionek.h"
#include <vector>

class board {

private:
    field fields[8][8];
    std::vector<pionek> biale;
    std::vector<pionek> czarne;
    int choosen;
    int kolor;

public:
    board() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if ((i + 1) % 2 == 0 && (j + 1) % 2 != 0) {
                    fields[i][j].setKolor(white);
                    fields[i][j].setEmpty(false);
                }
                if ((i + 1) % 2 != 0 && (j + 1) % 2 == 0) {
                    fields[i][j].setKolor(white);
                    fields[i][j].setEmpty(false);
                }

                fields[i][j].setKords(0.25 * i, (0.25 * i) + 0.25, 0.25 * j, (0.25 * j) + 0.25);

                if ((j < 3 || j > 4) && fields[i][j].getKolor() == black) {
                    auto *l = new pionek;
                    fields[i][j].setEmpty(false);
                    if (j > 3) {
                        czarne.push_back(*l);
                        czarne.back().setKordsF(0.25 * i, 0.25 * j);
                        czarne.back().setKolor(black);
                        czarne.back().setField(i, j);
                    } else {
                        biale.push_back(*l);
                        biale.back().setKordsF(0.25 * i, 0.25 * j);
                        biale.back().setKolor(white);
                        biale.back().setField(i, j);
                    }

                }

            }

        }
        choosen = -1;
        kolor = white;
    }


    field &getField(int x, int y) {
        return fields[x][y];
    }

    pionek &getCzarne(int i) {
        return czarne[i];
    }

    pionek &getBiale(int i) {
        return biale[i];
    }

    int getSize() {
        return static_cast<int>(biale.size());
    }

    void delete1() {
        biale.pop_back();
        czarne.pop_back();
    }

    void setChoosen(int x) {
        choosen = x;
    }

    int getChoosen() {
        return choosen;
    }

    void move(double ox, double oy, int x) {


        if (choosen != -1) {

            int direct;
            if (x == white) {
                direct = 1;


                int x = biale[choosen].getField(0);
                int y = biale[choosen].getField(1);

                if (fields[x + 1][y + direct].getEmpty() && fields[x + 1][y + direct].findField(ox, oy)) {
                    double X = *fields[x + 1][y + direct].getX();
                    double Y = *fields[x + 1][y + direct].getY();

                    fields[x][y].setEmpty(true);
                    biale[choosen].setKords(X, Y);
                    biale[choosen].setField(x + 1, y + direct);
                    fields[x + 1][y + direct].setEmpty(false);
                    choosen = -1;
                    kolor = black;

                }
                if ((fields[x - 1][y + direct].getEmpty() && fields[x - 1][y + direct].findField(ox, oy))) {
                    double X = *fields[x - 1][y + direct].getX();
                    double Y = *fields[x - 1][y + direct].getY();

                    fields[x][y].setEmpty(true);
                    biale[choosen].setKords(X, Y);
                    biale[choosen].setField(x - 1, y + direct);
                    fields[x - 1][y + direct].setEmpty(false);
                    choosen = -1;
                    kolor = black;
                }

            }

            if (x == black) {

                direct = -1;

                int x = czarne[choosen].getField(0);
                int y = czarne[choosen].getField(1);

                if (fields[x + 1][y + direct].getEmpty() && fields[x + 1][y + direct].findField(ox, oy)) {
                    double X = *fields[x + 1][y + direct].getX();
                    double Y = *fields[x + 1][y + direct].getY();

                    fields[x][y].setEmpty(true);
                    czarne[choosen].setKords(X, Y);
                    czarne[choosen].setField(x + 1, y + direct);
                    fields[x + 1][y + direct].setEmpty(false);
                    choosen = -1;
                    kolor = white;

                }
                if ((fields[x - 1][y + direct].getEmpty() && fields[x - 1][y + direct].findField(ox, oy))) {
                    double X = *fields[x - 1][y + direct].getX();
                    double Y = *fields[x - 1][y + direct].getY();

                    fields[x][y].setEmpty(true);
                    czarne[choosen].setKords(X, Y);
                    czarne[choosen].setField(x - 1, y + direct);
                    fields[x - 1][y + direct].setEmpty(false);
                    choosen = -1;
                    kolor = white;

                }



            }


        }


    }

    int choose(double ox, double oy, bool x) {

        for (int i = 0; i < biale.size(); ++i) {
            if (biale[i].find(ox, oy) && kolor == white) {
                if (x) choosen = i;
                else choosen = -1;
                // kolor = white;


            }
            if (czarne[i].find(ox, oy) && kolor == black) {
                if (x) choosen = i;
                else choosen = -1;
                //kolor = black;


            }

        }
    }

    int getKolor() {
        return kolor;
    }

    bool kill();


};


#endif //WARCABY_BOARD_H
