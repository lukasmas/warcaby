//
// Created by lukas on 17.05.18.
//

#ifndef WARCABY_PIONEK_H
#define WARCABY_PIONEK_H

#include "needed.h"
#include <cmath>

/*enum{
    black, white
};*/

class pionek {
private:
    double radius;
    double x,y;
    int kolor;
    bool live;
    int field[2];

public:
    pionek(){
        radius = 0.1;
        x = 0.125;
        y = 0.125;
        kolor = black;
        live = true;
        field[0] = 0;
        field[1] = 0;
    }

    void setKordsF(double x1, double y1 ){
        x= (x + x1)-1;
        y= (y + y1)-1;
    }
    void setKords(double x1, double y1 ){
        x= (0.125 + x1);
        y= (0.125 + y1);
    }



    void setKolor(int k){
        kolor = k;
    }

    double getX()
    {

        return x;

    }

    double getY()
    {

        return y;

    }

    int getKolor()
    {
        return kolor;
    }

    double getRadius()
    {
        return radius;
    }

    bool find(double X, double Y){
        return sqrt(pow(X - x, 2) + pow(Y - y, 2)) <= radius;
    }


    void setField(int a, int b){
        field[0] = a;
        field[1] = b;
    }

    int &getField(int x){
        return field[x];
    }

    void option(){

    }



};


#endif //WARCABY_PIONEK_H
