//
// Created by lukas on 17.05.18.
//

#ifndef WARCABY_FIELD_H
#define WARCABY_FIELD_H

#include "needed.h"
#include <GL/glut.h>


class field {
private:

    int kolor;
    double x[2];
    double y[2];

    bool empty;

public:

    field(int k, bool e) {
        kolor = k;
        empty = e;
    }

    field() {
        kolor = black;
        empty = true;

    }

    void setKolor(int k) {
        kolor = k;
    }

    void setEmpty(bool e) {
        empty = e;
    }

    int getKolor() {
        return kolor;
    }

    bool getEmpty() {
        return empty;
    }

    void setKords(double x1, double x2, double y1, double y2) {
        x[0] = x1 - 1;
        x[1] = x2 - 1;
        y[0] = y1 - 1;
        y[1] = y2 - 1;
    }

    double *getY() {
        return y;
    }

    double *getX() {
        return x;
    }

    bool findField(double X, double Y) {
        X = X + 1;
        Y = Y + 1;
        double tempX1 = x[0] + 1, tempX2 = x[1] + 1, tempY1 = y[0] + 1, tempY2 = y[1] + 1;
        return tempX1 <= X && tempX2 >= X && tempY1 <= Y && tempY2 >= Y;
    }


};


#endif //WARCABY_FIELD_H
