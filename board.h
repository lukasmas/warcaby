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
    std::vector <pionek> biale;
    std::vector <pionek> czarne;
    int choosen;

public:
    board() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if((i+1)%2== 0 && (j+1)%2!=0) fields[i][j].setKolor(white);
                if((i+1)%2!= 0 && (j+1)%2==0) fields[i][j].setKolor(white);

                fields[i][j].setKords(0.25 * i, (0.25 * i) + 0.25, 0.25 * j, (0.25 * j) +0.25);

                if((j<3 || j> 4) && fields[i][j].getKolor()==black){
                    auto *l = new pionek;
                    fields[i][j].setEmpty(false);
                    if(j>3) {
                        czarne.push_back(*l);
                        czarne.back().setKordsF(0.25 * i, 0.25 * j);
                        czarne.back().setKolor(black);
                    }
                    else {
                        biale.push_back(*l);
                        biale.back().setKordsF(0.25 * i, 0.25 * j);
                        biale.back().setKolor(white);
                    }

                }

            }

        }
        choosen = -1;
    }

    int getFieldKolor(int x, int y) {
        return fields[x][y].getKolor();
    }

    field getField(int x, int y) {
        return fields[x][y];
    }

    pionek &getCzarne(int i){
        return czarne[i];
    }

    pionek &getBiale(int i){
        return biale[i];
    }

    int getSize(){
        return static_cast<int>(biale.size());
    }

    void delete1(){
        biale.pop_back();
        czarne.pop_back();
    }

    void setChoosen(int x){
        choosen = x;
    }

    int getChoosen(){
        return choosen;
    }


};


#endif //WARCABY_BOARD_H
