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

void canvasInit() {
    //Initialize the canvas
    glClearColor(1, 1, 1, 0);
    glColor3f(1, 0, 0);
    glPointSize(POINT_SIZE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(PLANE_LEFT, PLANE_RIGHT, PLANE_BOTTOM, PLANE_TOP);
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    /* Implement your drawing logic here */
    glBegin(GL_LINE_STRIP);
        glVertex2d(170, 350);
        glVertex2d(100, 400);
        glVertex2d(150, 350);
        glVertex2d(100, 300);
        glVertex2d(170, 350);

        glVertex2d(180, 340);
        glVertex2d(200, 330);
        glVertex2d(230, 320);
        glVertex2d(270, 310);

        glVertex2d(310, 320);
        glVertex2d(340, 330);
        glVertex2d(360, 340);
        glVertex2d(370, 350);

        glVertex2d(360, 360);
        glVertex2d(340, 370);
        glVertex2d(310, 380);

        glVertex2d(270, 390);
        glVertex2d(230, 380);
        glVertex2d(200, 370);
        glVertex2d(180, 360);
        glVertex2d(170, 350);
    glEnd();

    glPointSize(20);
    glBegin(GL_POINTS);
        glVertex2d(340, 350);
    glEnd();
    glPointSize(POINT_SIZE);

    glFlush();
}

void specFunc(int key, int x, int y) {
    /* Implement the logic to manipulate control variables */

    glutPostRedisplay();
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
