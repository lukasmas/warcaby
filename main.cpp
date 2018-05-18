#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>
#include "board.h"


board Board;


void Display() {

    // kolor tła - zawartość bufora koloru
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // czyszczenie bufora koloru
    glClear(GL_COLOR_BUFFER_BIT);

// kolor lini
/*    glColor3f(0.0, 0.0, 0.0);

    for (int i = 1; i <= 8; i++) {


        // początek definicji wielokąta
        glBegin(GL_LINES);
        glLineWidth(0.5f);
        // kolejne wierzchołki wielokąta
        glVertex2d(0.250 * i - 1, 1);
        glVertex2d(0.250 * i - 1, -1);
        //glVertex3f(1.0, 1.0, 0.0);
        //glVertex3f(1.0, 0.0, 0.0);

        // koniec definicji prymitywu
        glEnd();
    }*/

// RYSOWANIE PLANSZY
    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
            if (Board.getFieldKolor(j, i) == white) glColor3f(1.0, 0.9, 1.0);
            else if (Board.getFieldKolor(j, i) == black) glColor3f(1.0, 0.5, 0.5);

            // kolejne wierzchołki wielokąta
            glRectd(Board.getField(j, i).getX()[0], Board.getField(j, i).getY()[0], Board.getField(j, i).getX()[1],
                    Board.getField(j, i).getY()[1]);

            // koniec definicji prymitywu
            glEnd();
            /*           printf("[%f][%f] | [%f][%f] -> [%d] \n ", Board.getField(j, i).getX()[0], Board.getField(j, i).getY()[0],
                              Board.getField(j, i).getX()[1], Board.getField(j, i).getY()[1], Board.getFieldKolor(j, i));
           */

        }
    }

    for (int k = 0; k < Board.getSize(); ++k) {

        glColor3f(0.2, 0.2, 0.2);

        // RYSOWANIE PIONKA CZARNEGO
        glBegin(GL_POLYGON);
        //Change the 6 to 12 to increase the steps (number of drawn points) for a smoother circle
        //Note that anything above 24 will have little affect on the circles appearance
        //Play with the numbers till you find the result you are looking for
        //Value 1.5 - Draws Triangle
        //Value 2 - Draws Square
        //Value 3 - Draws Hexagon
        //Value 4 - Draws Octagon
        //Value 5 - Draws Decagon
        //Notice the correlation between the value and the number of sides
        //The number of sides is always twice the value given this range
        for (double i = 0; i < 2 * M_PI; i += M_PI / 12) //<-- Change this Value
        {
            double x2 = Board.getCzarne(k).getX() + cos(i) * Board.getCzarne(k).getRadius();
            double y2 = Board.getCzarne(k).getY() + sin(i) * Board.getCzarne(k).getRadius();

            glVertex2d(x2, y2);

        }
        glEnd();
        //printf("[%f][%f] -> [%d] \n ", Board.getPionek(k).getX(), Board.getPionek(k).getY(), Board.getPionek(k).getKolor());

    }

    for (int k = 0; k < Board.getSize(); ++k) {

        glColor3f(0.9, 0.9, 0.9);

        // RYSOWANIE PIONKA BIAŁEGO
        glBegin(GL_POLYGON);
        //Change the 6 to 12 to increase the steps (number of drawn points) for a smoother circle
        //Note that anything above 24 will have little affect on the circles appearance
        //Play with the numbers till you find the result you are looking for
        //Value 1.5 - Draws Triangle
        //Value 2 - Draws Square
        //Value 3 - Draws Hexagon
        //Value 4 - Draws Octagon
        //Value 5 - Draws Decagon
        //Notice the correlation between the value and the number of sides
        //The number of sides is always twice the value given this range
        for (double i = 0; i < 2 * M_PI; i += M_PI / 12) //<-- Change this Value
        {
            double x2 = Board.getBiale(k).getX() + cos(i) * Board.getBiale(k).getRadius();
            double y2 = Board.getBiale(k).getY() + sin(i) * Board.getBiale(k).getRadius();

            glVertex2d(x2, y2);

        }
        glEnd();
        //printf("[%f][%f] -> [%d] \n ", Board.getPionek(k).getX(), Board.getPionek(k).getY(), Board.getPionek(k).getKolor());

    }


    // skierowanie poleceń do wykonania
    glFlush();

    // zamiana buforów koloru
    glutSwapBuffers();
}

// zmiana wielkości okna

void Reshape(int width, int height) {
    // generowanie sceny 3D
    Display();
}

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

/*                //Board.getBiale(2).setKords(0.1, -0.1);
                printf("%f\n", ox );
                printf("%f\n",oy );
                //Board.pionki[2].y=2;*/

                if (Board.getChoosen() == -1) {
                    for (int i = 0; i < Board.getSize(); ++i) {
                        if (Board.getBiale(i).find(ox, oy)) {
                            std::cout << "Kolor : " << Board.getBiale(i).getKolor() << ", X = "
                                      << Board.getBiale(i).getX() << ", Y = " << Board.getBiale(i).getY() << std::endl;
                            Board.setChoosen(i);


                        }
                        if (Board.getCzarne(i).find(ox, oy)) {
                            //std::cout<<"Kolor : "<<Board.getCzarne(i).getKolor()<<", X = "<< Board.getCzarne(i).getX() <<", Y = "<<Board.getCzarne(i).getY()<<std::endl;

                        }

                    }


                } else {

                    for (int j = 0; j < 8; j++) {
                        for (int i = 0; i < 8; i++) {
                            if(Board.getField(i,j).findField(ox, oy) && Board.getField(i,j).getEmpty()){
                                double X = Board.getField(i,j).getX()[0];
                                double Y = Board.getField(i,j).getY()[0];
                                Board.getBiale(Board.getChoosen()).setKords(X, Y);
                                Board.getField(i,j).setEmpty(false);
                                Board.setChoosen(-1);
                                std::cout<<"dziala albo i nie \n";
                            }

                        }
                    }



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
        return 0;
    }