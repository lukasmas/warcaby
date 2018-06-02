#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>
#include "board.h"


board Board;


void opponent() {
}

double minmax(board temp, int k, int g) {
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

void drawOption(int opt);


void Display() {

    // kolor tła - zawartość bufora koloru
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // czyszczenie bufora koloru
    glClear(GL_COLOR_BUFFER_BIT);



// RYSOWANIE PLANSZY
    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
            if (Board.getField(j, i).getKolor() == white) glColor3f(1.0, 0.9, 1.0);
            else if (Board.getField(j, i).getKolor() == black) glColor3f(1.0, 0.5, 0.5);

            // kolejne wierzchołki wielokąta
            glRectd(Board.getField(j, i).getX()[0], Board.getField(j, i).getY()[0], Board.getField(j, i).getX()[1],
                    Board.getField(j, i).getY()[1]);

            // koniec definicji prymitywu
            glEnd();

        }
    }

    for (int k = 0; k < Board.getSize(); ++k) {

        if (Board.getCzarne(k).getLive()) {
            if (Board.getChoosen() == k && Board.getKolor() == black) {
                glColor3f(0.3, 0.3, 0.3);
            } else {
                glColor3f(0.2, 0.2, 0.2);
            }


            // RYSOWANIE PIONKA CZARNEGO
            glBegin(GL_POLYGON);

            for (double i = 0; i < 2 * M_PI; i += M_PI / 12) {
                double x2 = Board.getCzarne(k).getX() + cos(i) * Board.getCzarne(k).getRadius();
                double y2 = Board.getCzarne(k).getY() + sin(i) * Board.getCzarne(k).getRadius();

                glVertex2d(x2, y2);

            }
            glEnd();

        }
    }

    for (int k = 0; k < Board.getSize(); ++k) {

        if (Board.getBiale(k).getLive()) {


            if (Board.getChoosen() == k && Board.getKolor() == white) {
                glColor3f(0.8, 0.8, 0.8);
            } else {
                glColor3f(0.9, 0.9, 0.9);
            }


            // RYSOWANIE PIONKA BIAŁEGO
            glBegin(GL_POLYGON);

            for (double i = 0; i < 2 * M_PI; i += M_PI / 12) {
                double x2 = Board.getBiale(k).getX() + cos(i) * Board.getBiale(k).getRadius();
                double y2 = Board.getBiale(k).getY() + sin(i) * Board.getBiale(k).getRadius();

                glVertex2d(x2, y2);

            }
            glEnd();


        }
    }

    if (Board.getChoosen() != -1) {

        drawOption(Board.getKolor());
    }


    // skierowanie poleceń do wykonania
    glFlush();

    // zamiana buforów koloru
    glutSwapBuffers();
}

// zmiana wielkości okna

/*void Reshape(int width, int height) {
    // generowanie sceny 3D
    Display();
}*/

// stałe do obsługi menu podręcznego

enum {
    EXIT // wyjście
};

// obsługa menu podręcznego

void Menu(int value) {
    switch (value) {
        // wyjście
        case EXIT:
            exit(0);
        default:
            break;
    }

}


void mouse(int btn, int state, int x, int y) {
    float mx = x;
    float my = y;
    double ox = (mx / (double) glutGet(GLUT_WINDOW_WIDTH) - 0.5) * 2;
    double oy = -(my / (double) glutGet(GLUT_WINDOW_HEIGHT) - 0.5) * 2;
    switch (btn) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {


                if (Board.getChoosen() == -1) {
                    Board.choose(ox, oy, true);


                } else {



                    Board.choose(ox, oy, false);
                    //std::cout<<Board.getKolor()<<std::endl;



                    Board.move(ox, oy, Board.getKolor());

                    Board.kill(ox, oy, Board.getKolor());


                }


                Display();
            }

            break;
        default:
            break;
    }

}


int main(int argc, char *argv[]) {
    // inicjalizacja biblioteki GLUT
    glutInit(&argc, argv);

    // inicjalizacja bufora ramki
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);


    // rozmiary głównego okna programu
    glutInitWindowSize(800, 600);

    // utworzenie głównego okna programu
    glutCreateWindow("Warcaby");

    // dołączenie funkcji generującej scenę 3D
    glutDisplayFunc(Display);

    // dołączenie funkcji wywoływanej przy zmianie rozmiaru okna
    //glutReshapeFunc( Reshape );

    // utworzenie menu podręcznego
    glutCreateMenu(Menu);

    // dodatnie pozycji do menu podręcznego
#ifdef WIN32

    glutAddMenuEntry( "Wyjście", EXIT );
#else

    glutAddMenuEntry("Wyjscie", EXIT);
#endif

    // określenie przycisku myszki obsługującej menu podręczne
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMouseFunc(mouse);

    // wprowadzenie programu do obsługi pętli komunikatów
    glutMainLoop();

    Board.delete1();

    return 0;
}


void drawOption(int opt) {
    glColor3f(0.5, 0.5, 0.5);


    int direct = 1;
    pionek temp = Board.getBiale(Board.getChoosen());
    if (opt == black) {
        temp = Board.getCzarne(Board.getChoosen());
        direct = -1;
    }


    int temp1 = temp.getField(0);
    int temp2 = temp.getField(1);

    if (temp1 > 0 && temp1 < 7) {

        if (Board.getField(temp1 + 1, temp2 + direct).getEmpty()) {

            glBegin(GL_POLYGON);


            for (double i = 0; i < 2 * M_PI; i += M_PI / 12) //<-- Change this Value
            {

                double x2 = *Board.getField(temp1 + 1, temp2 + direct).getX() + 0.125 + cos(i) * 0.05;
                double y2 = *Board.getField(temp1 + 1, temp2 + direct).getY() + 0.125 + sin(i) * 0.05;
                //std::cout<<Board.getBiale(Board.getChoosen()).getField(0) <<" "<<Board.getBiale(Board.getChoosen()).getField(1)<< "\n";

                glVertex2d(x2, y2);

            }
            glEnd();
        }
        if (Board.getField(temp1 - 1, temp2 + direct).getEmpty()) {
            glBegin(GL_POLYGON);
            for (double i = 0; i < 2 * M_PI; i += M_PI / 12) //<-- Change this Value
            {

                double x2 = *Board.getField(temp1 - 1, temp2 + direct).getX() + 0.125 + cos(i) * 0.05;
                double y2 = *Board.getField(temp1 - 1, temp2 + direct).getY() + 0.125 + sin(i) * 0.05;
                //std::cout<<Board.getBiale(Board.getChoosen()).getField(0) <<" "<<Board.getBiale(Board.getChoosen()).getField(1)<< "\n";

                glVertex2d(x2, y2);

            }
            glEnd();
        }
    } else if (temp1 == 7) {
        if (Board.getField(temp1 - 1, temp2 + direct).getEmpty()) {
            glBegin(GL_POLYGON);
            for (double i = 0; i < 2 * M_PI; i += M_PI / 12) //<-- Change this Value
            {

                double x2 = *Board.getField(temp1 - 1, temp2 + direct).getX() + 0.125 + cos(i) * 0.05;
                double y2 = *Board.getField(temp1 - 1, temp2 + direct).getY() + 0.125 + sin(i) * 0.05;
                //std::cout<<Board.getBiale(Board.getChoosen()).getField(0) <<" "<<Board.getBiale(Board.getChoosen()).getField(1)<< "\n";

                glVertex2d(x2, y2);

            }
            glEnd();
        }
    } else if (temp1 == 0) {
        if (Board.getField(temp1 + 1, temp2 + 1).getEmpty()) {
            glBegin(GL_POLYGON);
            for (double i = 0; i < 2 * M_PI; i += M_PI / 12) //<-- Change this Value
            {

                double x2 = *Board.getField(temp1 + 1, temp2 + direct).getX() + 0.125 + cos(i) * 0.05;
                double y2 = *Board.getField(temp1 + 1, temp2 + direct).getY() + 0.125 + sin(i) * 0.05;
                //std::cout<<Board.getBiale(Board.getChoosen()).getField(0) <<" "<<Board.getBiale(Board.getChoosen()).getField(1)<< "\n";

                glVertex2d(x2, y2);

            }
            glEnd();
        }
    }


}