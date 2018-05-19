#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>
#include "board.h"


board Board;

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

        if (Board.getChoosen() != k) {
            glColor3f(0.9, 0.9, 0.9);
        } else  {
            glColor3f(0.8, 0.8, 0.8);
        }


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

    if (Board.getChoosen() != -1) {
        drawOption(white);
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

                    Board.move(ox, oy, white);


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



    int temp1 = Board.getBiale(Board.getChoosen()).getField(0);
    int temp2 = Board.getBiale(Board.getChoosen()).getField(1);

    if (temp1 > 0 && temp1 < 7) {

        if (Board.getField(temp1 + 1, temp2 + 1).getEmpty()) {

            glBegin(GL_POLYGON);


            for (double i = 0; i < 2 * M_PI; i += M_PI / 12) //<-- Change this Value
            {

                double x2 = *Board.getField(temp1 + 1, temp2 + 1).getX() + 0.125 + cos(i) * 0.05;
                double y2 = *Board.getField(temp1 + 1, temp2 + 1).getY() + 0.125 + sin(i) * 0.05;
                //std::cout<<Board.getBiale(Board.getChoosen()).getField(0) <<" "<<Board.getBiale(Board.getChoosen()).getField(1)<< "\n";

                glVertex2d(x2, y2);

            }
            glEnd();
        }
        if (Board.getField(temp1 - 1, temp2 + 1).getEmpty()) {
            glBegin(GL_POLYGON);
            for (double i = 0; i < 2 * M_PI; i += M_PI / 12) //<-- Change this Value
            {

                double x2 = *Board.getField(temp1 - 1, temp2 + 1).getX() + 0.125 + cos(i) * 0.05;
                double y2 = *Board.getField(temp1 - 1, temp2 + 1).getY() + 0.125 + sin(i) * 0.05;
                //std::cout<<Board.getBiale(Board.getChoosen()).getField(0) <<" "<<Board.getBiale(Board.getChoosen()).getField(1)<< "\n";

                glVertex2d(x2, y2);

            }
            glEnd();
        }
    } else if (temp1 == 7) {
        if (Board.getField(temp1 - 1, temp2 + 1).getEmpty()) {
            glBegin(GL_POLYGON);
            for (double i = 0; i < 2 * M_PI; i += M_PI / 12) //<-- Change this Value
            {

                double x2 = *Board.getField(temp1 - 1, temp2 + 1).getX() + 0.125 + cos(i) * 0.05;
                double y2 = *Board.getField(temp1 - 1, temp2 + 1).getY() + 0.125 + sin(i) * 0.05;
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

                double x2 = *Board.getField(temp1 + 1, temp2 + 1).getX() + 0.125 + cos(i) * 0.05;
                double y2 = *Board.getField(temp1 + 1, temp2 + 1).getY() + 0.125 + sin(i) * 0.05;
                //std::cout<<Board.getBiale(Board.getChoosen()).getField(0) <<" "<<Board.getBiale(Board.getChoosen()).getField(1)<< "\n";

                glVertex2d(x2, y2);

            }
            glEnd();
        }
    }


}