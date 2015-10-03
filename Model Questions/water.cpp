/*##############################################################################

AUTHOR  : KARTHIK M A M
MAIL    : karthik_m_a_M@outlook.com
GITHUB  : github.com/KarthikMAM

##############################################################################*/

#include <GL/glut.h>
#include <iostream>

using namespace std;

//Window Parameters
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int WINDOW_LEFT = 30;
const int WINDOW_TOP = 30;
const char WINDOW_TITLE[] = "OPENGL TEMPLATE";

//Canvas Parameters
const int PLANE_LEFT = 0.0;
const int PLANE_RIGHT = WINDOW_WIDTH;
const int PLANE_BOTTOM = 0.0;
const int PLANE_TOP = WINDOW_HEIGHT;
const int POINT_SIZE = 5;

/*Create the variables here*/
int inc = 5;

void canvasInit() {
    //Initialize the canvas
    glClearColor(1, 1, 1, 0);
    glColor3f(1, 0, 0);
    glPointSize(POINT_SIZE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(PLANE_LEFT, PLANE_RIGHT, PLANE_BOTTOM, PLANE_TOP);
}

void translatePoint(int *ptX, int *ptY, int transX, int transY) {
    float matTrans[3][3] = {
        {1, 0, transX},
        {0, 1, transY},
        {0, 0,      1}
    };

    float matPt[3][1] = {
        {*ptX},
        {*ptY},
        {   1}
    };

    float matRes[3][1] = {};

    for(int i=0; i<3; i++) {
        for(int j=0; j<1; j++) {
            for(int k=0; k<3; k++) {
                matRes[i][j] += matTrans[i][k] * matPt[k][j];
            }
        }
    }

    *ptX = matRes[0][0];
    *ptY = matRes[0][1];

}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    /* Implement your drawing logic here */
    glBegin(GL_LINE_STRIP);
        glVertex2d(100, 300);
        glVertex2d(100, 100);
        glVertex2d(300, 100);
        glVertex2d(300, 300);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2d(300, 100);
        glVertex2d(300, 130);
        glVertex2d(350, 130);
        glVertex2d(350, 100);

        glVertex2d(350, 130);
        glVertex2d(350, 050);
        glVertex2d(370, 050);
        glVertex2d(370, 130);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glVertex2d(320, 90);
        glVertex2d(320, 10);
        glVertex2d(390, 10);
        glVertex2d(390, 90);
    glEnd();


    glColor3f(0,0,1);
    glBegin(GL_QUADS);
        static int x1 = 100;
        static int y1 = 300;
        static int x2 = 300;
        static int y2 = 300;

        translatePoint(&x1, &y1, 0, -inc);
        translatePoint(&x2, &y2, 0, -inc);

        glVertex2d(x1, y1);
        glVertex2d(100, 100);
        glVertex2d(300, 100);
        glVertex2d(x2, y2);

        static int x3 = 320;
        static int y3 = 10;
        static int x4 = 390;
        static int y4 = 10;

        translatePoint(&x3, &y3, 0, inc);
        translatePoint(&x4, &y4, 0, inc);

        glVertex2d(x3, y3);
        glVertex2d(320, 10);
        glVertex2d(390, 10);
        glVertex2d(x4, y4);
    glEnd();
    glColor3f(1,0,0);

    glFlush();
}

void specFunc(int key, int x, int y) {
    /* Implement the logic to manipulate control variables */
    switch (key) {
        case GLUT_KEY_UP: {
            inc = -5;
            glutPostRedisplay();
            break;
        }
        case GLUT_KEY_DOWN: {
            inc = +5;
            glutPostRedisplay();
            break;
        }
    }
}

int main(int argc, char** argv) {
    /* Get any input you need here */

    //Initialize the main window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(WINDOW_LEFT, WINDOW_TOP);
    glutCreateWindow(WINDOW_TITLE);

    //Callback functions
    glutDisplayFunc(myDisplay);
    glutSpecialFunc(specFunc);

    //Initialize the canvas and start the main loop
    canvasInit();
    glutMainLoop();
    return 0;
}
