/*##############################################################################

AUTHOR  : KARTHIK M A M
MAIL    : karthik_m_a_M@outlook.com
GITHUB  : github.com/KarthikMAM

##############################################################################*/

#include <GL/glut.h>
#include <iostream>
#include <math.h>

using namespace std;

//Window Parameters
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const char WINDOW_TITLE[] = "OPENGL TEMPLATE";

//Canvas Parameters
const float PLANE_LEFT = 0.0;
const float PLANE_RIGHT = WINDOW_WIDTH;
const float PLANE_BOTTOM = 0.0;
const float PLANE_TOP = WINDOW_HEIGHT;
const int POINT_SIZE = 5;

/*Create the variables here*/
float ag = 1;

void canvasInit() {
    //Initialize the canvas
    glClearColor(1, 1, 1, 0);
    glColor3f(1, 0, 0);
    glPointSize(POINT_SIZE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(PLANE_LEFT, PLANE_RIGHT, PLANE_BOTTOM, PLANE_TOP);
}

void glCircle2d(int cx, int cy, int r) {
    int x = r;
    int y = 0;
    int pk = 1 - x;

    while (y <= x) {
        glVertex2d( x + cx,  y + cy);
        glVertex2d( y + cx,  x + cy);
        glVertex2d(-x + cx,  y + cy);
        glVertex2d(-y + cx,  x + cy);
        glVertex2d(-x + cx, -y + cy);
        glVertex2d(-y + cx, -x + cy);
        glVertex2d( x + cx, -y + cy);
        glVertex2d( y + cx, -x + cy);

        y++;
        if(pk < 0) { pk += 2 * y + 1; }
        else {
            x--;
            pk += 2 * (y - x) + 1;
        }
    }
}

void rotate(float* x, float* y) {
    float trans[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    float hPoint[3][1] = {
        {*x},
        {*y},
        {1}
    };

    float agl = ag * M_PI / 180.0;

    //Set rotation Parameters
    trans[0][0] = cos(agl);
    trans[0][1] = -sin(agl);
    trans[1][0] = sin(agl);
    trans[1][1] = cos(agl);
    trans[0][2] = 400 * ( 1 - cos(agl) ) + 400 * sin(agl);
    trans[1][2] = 400 * ( 1 - cos(agl) ) - 400 * sin(agl);

    float res[3][1] = {{0}, {0}, {0}};

    for(int i=0; i<3; i++) {
        for(int j=0; j<1; j++) {
            for(int k=0; k<3; k++) {
                res[i][j] += trans[i][k] * hPoint[k][j];
            }
        }
    }

    *x = res[0][0];
    *y = res[1][0];
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    /* Implement your drawing logic here */
    glBegin(GL_POINTS);
        for (int i=0; i<9; i++) {
            glCircle2d(400, 400, i * 40);
        }
    glEnd();

    glColor3f(0, 1, 0);
    glBegin(GL_POINTS);
        for (int i=0; i<9; i++) {
            float x = 400+i * 40;
            float y = 400;
            rotate(&x, &y);
            glCircle2d(x, y, 3);
        }
    glEnd();
    glColor3f(1, 0, 0);

    glFlush();
}

void sp(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_RIGHT:
            ag += 1;
            break;
        case GLUT_KEY_LEFT:
            ag -= 1;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    /* Get any input you need here */

    //Initialize the main window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(WINDOW_TITLE);
    glutDisplayFunc(myDisplay);
    glutSpecialFunc(sp);

    //Initialize the canvas and start the main loop
    canvasInit();
    glutMainLoop();
    return 0;
}
