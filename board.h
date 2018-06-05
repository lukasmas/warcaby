//
// Created by lukas on 17.05.18.
//

#ifndef WARCABY_BOARD_H
#define WARCABY_BOARD_H


#include <GL/glut.h>
#include "field.h"
#include "pionek.h"
#include <vector>
#include <iostream>

class board {

private:
    field fields[8][8];
    std::vector<pionek> biale;
    std::vector<pionek> czarne;
    int choosen; // wybrany pionek
    int kolor; // Kto ma ruch
//    int streak;

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
        delete &biale.back();
        delete &czarne.back();
        biale.pop_back();
        czarne.pop_back();
    }

    void setChoosen(int x) {
        choosen = x;
    }

    int getChoosen() {
        return choosen;
    }

    void setKolor(int k) {
        kolor = k;
    }

    bool isMoveL(int x, int y) {
        int dir;
        //std::cout << x << y << " \n";
        if (kolor == white) {
            dir = 1;
            if (x >= 1 && x <= 7 && y >= 0 && y <= 6) {
                return (fields[x - 1][y + dir].getEmpty());
            }
        } else if (kolor == black) {
            dir = -1;
            if (x >= 1 && x <= 7 && y >= 1 && y <= 7) {
                return (fields[x - 1][y + dir].getEmpty());
            }
        }
        return false;


    }


    bool isMoveL(int x, int y, int k) {
        int dir;
        //std::cout << x << y << " \n";
        if (k == white) {
            dir = 1;
            if (x >= 1 && x <= 7 && y >= 0 && y <= 6) {
                //std::cout<< "W LEWY RUCH \n";
                return (fields[x - 1][y + dir].getEmpty());
            }
        } else if (k == black) {
            dir = -1;
            if (x >= 1 && x <= 7 && y >= 1 && y <= 7) {
                return (fields[x - 1][y + dir].getEmpty());
            }
        }
        return false;


    }

    bool isMoveR(int x, int y) {
        int dir;
        //std::cout << x << y << " \n";
        if (kolor == white) {
            dir = 1;
            if (x >= 0 && x <= 6 && y >= 0 && y <= 6) {
                return (fields[x + 1][y + dir].getEmpty());
            }
        } else if (kolor == black) {
            dir = -1;
            if (x >= 0 && x <= 6 && y >= 1 && y <= 7) {
                //std::cout << x << y << " \n";
                return (fields[x + 1][y + dir].getEmpty());
            }
        }
        return false;

    }

    bool isMoveR(int x, int y, int k) {
        int dir;
        //std::cout << x << y << " \n";
        if (k == white) {
            dir = 1;
            if (x >= 0 && x <= 6 && y >= 0 && y <= 6) {

                return (fields[x + 1][y + dir].getEmpty());
            }
        } else if (k == black) {
            dir = -1;
            if (x >= 0 && x <= 6 && y >= 1 && y <= 7) {
                return (fields[x + 1][y + dir].getEmpty());
            }
        }
        return false;

    }

    bool isKillL(int x, int y) {
        int dir;
        if (kolor == white) {
            dir = 1;
            if (x >= 2 && x <= 7 && y >= 0 && y <= 5) {
                bool j, d = false, t;
                j = !(fields[x - 1][y + dir].getEmpty());
                for (auto &i : czarne) {
                    if (i.getField(0) == x - 1 && i.getField(1) == y + dir && i.getKolor() == black) d = true;
                }
                t = fields[x - 2][y + 2 * dir].getEmpty();
                return (j && d && t);
            }

        } else if (kolor == black) {
            dir = -1;
            if (x >= 2 && x <= 7 && y >= 2 && y <= 7) {
                bool j, d = false, t;
                j = !(fields[x - 1][y + dir].getEmpty());
                for (auto &i : biale) {
                    if (i.getField(0) == x - 1 && i.getField(1) == y + dir && i.getKolor() == white) d = true;
                }
                t = fields[x - 2][y + 2 * dir].getEmpty();
                return (j && d && t);
            }


        }
        return false;
    }


    bool isKillL(int x, int y, int k) {
        int dir;
        if (k == white) {
            dir = 1;
            if (x >= 2 && x <= 7 && y >= 0 && y <= 5) {
                bool j, d = false, t;
                j = !(fields[x - 1][y + dir].getEmpty());
                for (auto &i : czarne) {
                    if (i.getField(0) == x - 1 && i.getField(1) == y + dir && i.getKolor() == black) d = true;
                }
                t = fields[x - 2][y + 2 * dir].getEmpty();
                return (j && d && t);
            }

        } else if (k == black) {
            dir = -1;
            if (x >= 2 && x <= 7 && y >= 2 && y <= 7) {
                bool j, d = false, t;
                j = !(fields[x - 1][y + dir].getEmpty());
                for (auto &i : biale) {
                    if (i.getField(0) == x - 1 && i.getField(1) == y + dir && i.getKolor() == white) d = true;
                }
                t = fields[x - 2][y + 2 * dir].getEmpty();
                return (j && d && t);
            }


        }
        return false;
    }

    bool isKillR(int x, int y) {
        int dir;
        if (kolor == white) {
            dir = 1;
            if (x >= 0 && x <= 5 && y >= 0 && y <= 5) {
                bool j, d = false, t;
                j = !(fields[x + 1][y + dir].getEmpty());
                for (auto &i : czarne) {
                    if (i.getField(0) == x + 1 && i.getField(1) == y + dir && i.getKolor() == black) d = true;
                }
                t = fields[x + 2][y + 2 * dir].getEmpty();
                return (j && d && t);
            }

        } else if (kolor == black) {
            dir = -1;
            if (x >= 0 && x <= 5 && y >= 2 && y <= 7) {
                bool j, d = false, t;
                j = !(fields[x - 1][y + dir].getEmpty());
                for (auto &i : biale) {
                    if (i.getField(0) == x + 1 && i.getField(1) == y + dir && i.getKolor() == white) d = true;
                }
                t = fields[x + 2][y + 2 * dir].getEmpty();
                return (j && d && t);
            }


        }
        return false;
    }

    bool isKillR(int x, int y, int k) {
        int dir;
        if (k == white) {
            dir = 1;
            if (x >= 0 && x <= 5 && y >= 0 && y <= 5) {
                bool j, d = false, t;
                j = !(fields[x + 1][y + dir].getEmpty());
                for (auto &i : czarne) {
                    if (i.getField(0) == x + 1 && i.getField(1) == y + dir && i.getKolor() == black) d = true;
                }
                t = fields[x + 2][y + 2 * dir].getEmpty();
                return (j && d && t);
            }

        } else if (k == black) {
            dir = -1;
            if (x >= 0 && x <= 5 && y >= 2 && y <= 7) {
                bool j, d = false, t;
                j = !(fields[x - 1][y + dir].getEmpty());
                for (auto &i : biale) {
                    if (i.getField(0) == x + 1 && i.getField(1) == y + dir && i.getKolor() == white) d = true;
                }
                t = fields[x + 2][y + 2 * dir].getEmpty();
                return (j && d && t);
            }


        }
        return false;
    }

    void move(double ox, double oy, int k) {


        if (choosen != -1) {

            int direct;
            if (k == white) {
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

            if (k == black) {

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
        //opponent(black);


    }

    int choose(double ox, double oy, bool x) {


        for (int i = 0; i < biale.size(); ++i) {
            if (biale[i].find(ox, oy) && kolor == white && biale[i].getLive()) {
                if (x && (isMoveL(biale[i].getField(0), biale[i].getField(1)) ||
                          isMoveR(biale[i].getField(0), biale[i].getField(1)) ||
                          isKillL(biale[i].getField(0), biale[i].getField(1)) ||
                          isKillR(biale[i].getField(0), biale[i].getField(1)))) {
                    choosen = i;
/*                    std::cout << isMoveL(biale[i].getField(0), biale[i].getField(1))
                              << isMoveR(biale[i].getField(0), biale[i].getField(1))
                              << isKillL(biale[i].getField(0), biale[i].getField(1))
                              << isKillR(biale[i].getField(0), biale[i].getField(1)) << " \n";*/
                } else choosen = -1;
                // kolor = white;


            }
            if (czarne[i].find(ox, oy) && kolor == black && czarne[i].getLive()) {
                if (x && (isMoveL(czarne[i].getField(0), czarne[i].getField(1)) ||
                          isMoveR(czarne[i].getField(0), czarne[i].getField(1)) ||
                          isKillL(czarne[i].getField(0), czarne[i].getField(1)) ||
                          isKillR(czarne[i].getField(0), czarne[i].getField(1)))) {

/*                    std::cout << isMoveL(czarne[i].getField(0), czarne[i].getField(1))
                              << isMoveR(czarne[i].getField(0), czarne[i].getField(1))
                              << isKillL(czarne[i].getField(0), czarne[i].getField(1))
                              << isKillR(czarne[i].getField(0), czarne[i].getField(1)) << " \n";*/
                    choosen = i;
                } else choosen = -1;
                //kolor = black;


            }

        }

    }

    int getKolor() {
        return kolor;
    }

    void killL(int indeks, int k) {
        int direct;
        if (k == black) {
            direct = -1;

            int x = czarne[indeks].getField(0);
            int y = czarne[indeks].getField(1);

            double X = *fields[x - 2][y + (2 * direct)].getX();
            double Y = *fields[x - 2][y + (2 * direct)].getY();

            fields[x][y].setEmpty(true);
            czarne[indeks].setKords(X, Y);
            czarne[indeks].setField(x - 2, y + (2 * direct));
            fields[x - 2][y + (2 * direct)].setEmpty(false);

            for (auto &i : biale) {
                if (i.getField(0) == x - 1 && i.getField(1) == y + direct && i.getLive()) {
                    i.dead();
                    fields[x - 1][y + direct].setEmpty(true);

                }

            }


        } else if (k == white) {

            direct = 1;

            int x = biale[indeks].getField(0);
            int y = biale[indeks].getField(1);

            double X = *fields[x - 2][y + (2 * direct)].getX();
            double Y = *fields[x - 2][y + (2 * direct)].getY();

            fields[x][y].setEmpty(true);
            biale[indeks].setKords(X, Y);
            biale[indeks].setField(x - 2, y + (2 * direct));
            fields[x - 2][y + (2 * direct)].setEmpty(false);

            for (auto &i : czarne) {
                if (i.getField(0) == x - 1 && i.getField(1) == y + direct && i.getLive()) {
                    i.dead();
                    fields[x - 1][y + direct].setEmpty(true);

                }

            }

        }

    }

    void killR(int indeks, int k) {
        int direct;
        if (k == black) {
            direct = -1;

            int x = czarne[indeks].getField(0);
            int y = czarne[indeks].getField(1);

            double X = *fields[x + 2][y + (2 * direct)].getX();
            double Y = *fields[x + 2][y + (2 * direct)].getY();

            fields[x][y].setEmpty(true);
            czarne[indeks].setKords(X, Y);
            czarne[indeks].setField(x + 2, y + (2 * direct));
            fields[x + 2][y + (2 * direct)].setEmpty(false);

            for (auto &i : biale) {
                if (i.getField(0) == x + 1 && i.getField(1) == y + direct && i.getLive()) {
                    i.dead();
                    fields[x + 1][y + direct].setEmpty(true);

                }

            }


        } else if (k == white) {

            direct = 1;

            int x = biale[indeks].getField(0);
            int y = biale[indeks].getField(1);

            double X = *fields[x + 2][y + (2 * direct)].getX();
            double Y = *fields[x + 2][y + (2 * direct)].getY();

            fields[x][y].setEmpty(true);
            biale[indeks].setKords(X, Y);
            biale[indeks].setField(x + 2, y + (2 * direct));
            fields[x + 2][y + (2 * direct)].setEmpty(false);

            for (auto &i : czarne) {
                if (i.getField(0) == x + 1 && i.getField(1) == y + direct && i.getLive()) {
                    i.dead();
                    fields[x + 1][y + direct].setEmpty(true);

                }

            }

        }
    }

    void moveL(int indeks, int k) {
        int direct;
        if (k == black) {
            direct = -1;

            int x = czarne[indeks].getField(0);
            int y = czarne[indeks].getField(1);


            double X = *fields[x - 1][y + direct].getX();
            double Y = *fields[x - 1][y + direct].getY();

            fields[x][y].setEmpty(true);
            czarne[indeks].setKords(X, Y);
            czarne[indeks].setField(x - 1, y + direct);
            fields[x - 1][y + direct].setEmpty(false);

        } else if (k == white) {
            direct = 1;
            int x = biale[indeks].getField(0);
            int y = biale[indeks].getField(1);


            double X = *fields[x - 1][y + direct].getX();
            double Y = *fields[x - 1][y + direct].getY();
            fields[x][y].setEmpty(true);
            biale[indeks].setKords(X, Y);
            biale[indeks].setField(x - 1, y + direct);
            fields[x - 1][y + direct].setEmpty(false);

        }
    }

    /*void moveR(pionek &T, int k) {
         int direct;
         if (k == black) {
             direct = -1;

             int x = T.getField(0);
             int y = T.getField(1);


             double X = *fields[x + 1][y + direct].getX();
             double Y = *fields[x + 1][y + direct].getY();

             fields[x][y].setEmpty(true);
             T.setKords(X, Y);
             T.setField(x + 1, y + direct);
             fields[x + 1][y + direct].setEmpty(false);

         } else if (k == white) {
             direct = 1;
             int x = T.getField(0);
             int y = T.getField(1);


             double X = *fields[x + 1][y + direct].getX();
             double Y = *fields[x + 1][y + direct].getY();

             fields[x][y].setEmpty(true);
             T.setKords(X, Y);
             T.setField(x + 1, y + direct);
             fields[x + 1][y + direct].setEmpty(false);

         }
     }*/

    void moveR(int indeks, int k) {
        int direct;
        if (k == black) {
            direct = -1;
            int x = czarne[indeks].getField(0);
            int y = czarne[indeks].getField(1);

            double X = *fields[x + 1][y + direct].getX();
            double Y = *fields[x + 1][y + direct].getY();

            fields[x][y].setEmpty(true);
            czarne[indeks].setKords(X, Y);
            czarne[indeks].setField(x + 1, y + direct);
            fields[x + 1][y + direct].setEmpty(false);


        } else if (k == white) {
            direct = 1;
            int x = biale[indeks].getField(0);
            int y = biale[indeks].getField(1);


            double X = *fields[x + 1][y + direct].getX();
            double Y = *fields[x + 1][y + direct].getY();

            fields[x][y].setEmpty(true);
            biale[indeks].setKords(X, Y);
            biale[indeks].setField(x + 1, y + direct);
            fields[x + 1][y + direct].setEmpty(false);

        }
    }

    void kill(double ox, double oy, int k) {
        if (choosen != -1) {

            int direct;
            if (k == white) {
                direct = 1;


                int x = biale[choosen].getField(0);
                int y = biale[choosen].getField(1);

                if (!(fields[x + 1][y + direct].getEmpty()) && fields[x + 1][y + direct].findField(ox, oy)) {
                    bool d = false;
                    for (auto &i : czarne) {
                        if (i.getField(0) == x + 1 && i.getField(1) == y + direct && i.getKolor() == black) d = true;
                    }

                    if (fields[x + 2][y + (2 * direct)].getEmpty() && d) {

                        double X = *fields[x + 2][y + (2 * direct)].getX();
                        double Y = *fields[x + 2][y + (2 * direct)].getY();

                        fields[x][y].setEmpty(true);
                        biale[choosen].setKords(X, Y);
                        biale[choosen].setField(x + 2, y + (2 * direct));
                        fields[x + 2][y + (2 * direct)].setEmpty(false);

                        for (auto &i : czarne) {
                            if (i.getField(0) == x + 1 && i.getField(1) == y + direct && i.getLive()) {
                                i.dead();
                                fields[x + 1][y + direct].setEmpty(true);

                            }

                        }

                        choosen = -1;
                        kolor = black;


                    }


                }
                if (!(fields[x - 1][y + direct].getEmpty()) && fields[x - 1][y + direct].findField(ox, oy)) {

                    bool d = false;
                    for (auto &i : czarne) {
                        if (i.getField(0) == x - 1 && i.getField(1) == y + direct && i.getKolor() == black) d = true;
                    }

                    if (fields[x - 2][y + 2 * direct].getEmpty() && d) {

                        double X = *fields[x - 2][y + 2 * direct].getX();
                        double Y = *fields[x - 2][y + 2 * direct].getY();

                        fields[x][y].setEmpty(true);
                        biale[choosen].setKords(X, Y);
                        biale[choosen].setField(x - 2, y + 2 * direct);
                        fields[x - 2][y + 2 * direct].setEmpty(false);

                        for (auto &i : czarne) {
                            if (i.getField(0) == x - 1 && i.getField(1) == y + direct && i.getLive()) {
                                i.dead();
                                fields[x - 1][y + direct].setEmpty(true);

                            }

                        }


                        choosen = -1;
                        kolor = black;


                    }
                }

            }

            if (k == black) {

                direct = -1;


                int x = czarne[choosen].getField(0);
                int y = czarne[choosen].getField(1);

                if (!(fields[x + 1][y + direct].getEmpty()) && fields[x + 1][y + direct].findField(ox, oy)) {

                    bool d = false;
                    for (auto &i : biale) {
                        if (i.getField(0) == x + 1 && i.getField(1) == y + direct && i.getKolor() == white) d = true;
                    }

                    if (fields[x + 2][y + (2 * direct)].getEmpty() && d) {

                        double X = *fields[x + 2][y + (2 * direct)].getX();
                        double Y = *fields[x + 2][y + (2 * direct)].getY();

                        fields[x][y].setEmpty(true);
                        czarne[choosen].setKords(X, Y);
                        czarne[choosen].setField(x + 2, y + (2 * direct));
                        fields[x + 2][y + (2 * direct)].setEmpty(false);

                        for (auto &i : biale) {
                            if (i.getField(0) == x + 1 && i.getField(1) == y + direct && i.getLive()) {
                                i.dead();
                                fields[x + 1][y + direct].setEmpty(true);

                            }

                        }


                        choosen = -1;
                        kolor = white;


                    }


                }
                if (!(fields[x - 1][y + direct].getEmpty()) && fields[x - 1][y + direct].findField(ox, oy)) {
                    bool d = false;
                    for (auto &i : biale) {
                        if (i.getField(0) == x - 1 && i.getField(1) == y + direct && i.getKolor() == white) d = true;
                    }

                    if (fields[x - 2][y + (2 * direct)].getEmpty() && d) {

                        double X = *fields[x - 2][y + (2 * direct)].getX();
                        double Y = *fields[x - 2][y + (2 * direct)].getY();

                        fields[x][y].setEmpty(true);
                        czarne[choosen].setKords(X, Y);
                        czarne[choosen].setField(x - 2, y + (2 * direct));
                        fields[x - 2][y + (2 * direct)].setEmpty(false);

                        for (auto &i : biale) {
                            if (i.getField(0) == x - 1 && i.getField(1) == y + direct && i.getLive()) {
                                i.dead();
                                fields[x - 1][y + direct].setEmpty(true);

                            }

                        }


                        choosen = -1;
                        kolor = white;


                    }
                }


            }


        }

    }

    int win() {
        int W = 0;
        int Wl = 0;
        int Wb = 0;
        int B = 0;
        for (auto &i : biale) {
            if (i.getLive()) {
                Wl++;
                if (isMoveL(i.getField(0), i.getField(1), white) ||
                    isMoveR(i.getField(0), i.getField(1), white) ||
                    isKillL(i.getField(0), i.getField(1), white) ||
                    isKillR(i.getField(0), i.getField(1), white)) {
                    W++;

                }
            }
        }

        for (auto &i : czarne) {
            if (i.getLive()) {
                Wb++;
                if (isMoveL(i.getField(0), i.getField(1), black) ||
                    isMoveR(i.getField(0), i.getField(1), black) ||
                    isKillL(i.getField(0), i.getField(1), black) ||
                    isKillR(i.getField(0), i.getField(1), black)) {
                    B++;

                }
            }
        }



        if(B == 0 && W == 0) {
            if(Wl > Wb) return 1;
            else return  2;
        }

        if(B == 0) return 2;
        if(W == 0) return 1;

        return 0;


    }


    /*void opponent(int k) {
        std::vector<pionek> AI;
        std::vector<pionek> symW;
        std::vector<double> M;
        field temp[8][8];

        for (int j = 0; j < 8; ++j) {
            for (int i = 0; i < 8; ++i) {
                temp[j][i] = fields[j][i];
            }

        }

        for (auto &i : czarne) {

            AI.push_back(i);

        }
        for (auto &i : biale) {

            symW.push_back(i);


        }
        //std::cout<<AI.size()<< " \n";
        for (int i = 0; i < AI.size(); i++) {
            *//*std::cout << isMoveL(AI[i].getField(0), AI[i].getField(1), black)
                      << isMoveR(AI[i].getField(0), AI[i].getField(1), black)
                      << isKillL(AI[i].getField(0), AI[i].getField(1), black, AI, symW)
                      << isKillR(AI[i].getField(0), AI[i].getField(1), black, AI, symW) << " \n";*//*

            //std::cout << AI[i].getLive()<<" \n";
            if (AI[i].getLive()) {
                if (isMoveL(AI[i].getField(0), AI[i].getField(1), black) ||
                    isMoveR(AI[i].getField(0), AI[i].getField(1), black) ||
                    isKillL(AI[i].getField(0), AI[i].getField(1), black, AI, symW) ||
                    isKillR(AI[i].getField(0), AI[i].getField(1), black, AI, symW)) {
                    M.push_back(minmax(AI[i], AI, symW, black, 0));

                }

            }

        }
        for (int j = 0; j < 8; ++j) {
            for (int i = 0; i < 8; ++i) {
                fields[j][i] = temp[j][i];
            }

        }

*//*        for (int l = 0; l <M.size(); ++l) {
            std::cout<<M[l]<< " \n";

        }*//*
        std::cout << " \n";


    }

    double minmax(pionek S, std::vector<pionek> &B, std::vector<pionek> &W, int k, int g) {
        double M = 0;
        if (k == black) {
            if (isKillL(S.getField(0), S.getField(1), black, B, W)) {
                killL(S, black, B, W);
                M++;
                M = minmax(B, W, white, g) + M + 0.1;
                return M;
            }
            if (isKillR(S.getField(0), S.getField(1), black, B, W)) {
                killR(S, black, B, W);
                M++;
                M = minmax(B, W, white, g) + M + 0.2;
                return M;
            }
            if (isMoveL(S.getField(0), S.getField(1), black)) {
                moveL(S, black, B, W);
                M = minmax(B, W, white, g) + M + 0.3;
            }
            if (isMoveR(S.getField(0), S.getField(1), black)) {
                moveR(S, black, B, W);
                M = minmax(B, W, white, g) + M + 0.4;
            }

        }
        return M;


    }


    int minmax(std::vector<pionek> &B, std::vector<pionek> &W, int k, int g) {
        int M = 0;
        if (g < 3) {
            if (k == black) {
                for (int i = 0; i < B.size(); ++i) {
                    if (isKillL(B[i].getField(0), B[i].getField(1))) {
                        killL(B[i], black, B, W);
                        M++;
                        M = minmax(B, W, white, g) + M;
                        return M;
                    }
                    if (isKillR(B[i].getField(0), B[i].getField(1))) {
                        killR(B[i], black, B, W);
                        M++;
                        M = minmax(B, W, white, g) + M;
                        return M;
                    }
                    if (isMoveL(B[i].getField(0), B[i].getField(1))) {
                        moveL(B[i], black, B, W);
                        M = minmax(B, W, white, g) + M;
                    }
                    if (isMoveR(B[i].getField(0), B[i].getField(1))) {
                        moveR(B[i], black, B, W);
                        M = minmax(B, W, white, g) + M;
                    }
                }
                return M;

            }


            if (k == white) {

                for (int i = 0; i < W.size(); ++i) {
                    if (isKillL(W[i].getField(0), W[i].getField(1))) {
                        killL(W[i], white, B, W);
                        M++;
                        M = minmax(B, W, black, ++g) + M;
                        return M;
                    }
                    if (isKillR(W[i].getField(0), W[i].getField(1))) {
                        killR(W[i], white, B, W);
                        M++;
                        M = minmax(B, W, black, ++g) + M;
                        return M;
                    }
                    if (isMoveL(W[i].getField(0), W[i].getField(1))) {
                        moveL(W[i], white, B, W);
                        M = minmax(B, W, black, ++g) + M;
                    }
                    if (isMoveR(W[i].getField(0), W[i].getField(1))) {
                        moveR(W[i], white, B, W);
                        M = minmax(B, W, black, ++g) + M;
                    }
                }
                return M;

            }

        }
        return 0;


    }*/


};


#endif //WARCABY_BOARD_H
