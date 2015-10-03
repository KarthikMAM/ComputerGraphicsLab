/*##############################################################################

AUTHOR  : KARTHIK M A M
MAIL    : karthik_m_a_M@outlook.com
GITHUB  : github.com/KarthikMAM

##############################################################################*/

#include <GL/glut.h>
#include <iostream>

using namespace std;

//Window Parameters
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 480;
const char WINDOW_TITLE[] = "OPENGL TEMPLATE";

//Canvas Parameters
const float PLANE_LEFT = 0.0;
const float PLANE_RIGHT = WINDOW_WIDTH;
const float PLANE_BOTTOM = 0.0;
const float PLANE_TOP = WINDOW_HEIGHT;
const int POINT_SIZE = 10;

/*Create the variables here*/
char num[10];

void canvasInit() {
    //Initialize the canvas
    glClearColor(1, 1, 1, 0);
    glColor3f(1, 0, 0);
    glPointSize(POINT_SIZE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(PLANE_LEFT, PLANE_RIGHT, PLANE_BOTTOM, PLANE_TOP);
}

void glLine2d(float x1, float y1, float x2, float y2) {
    float m = (y2 - y1) / (x2 - x1);

    if(m >= -1 && m <= 1) {
        float fx = x1, fy = y1;
        if (x1 > x2) {
            fx = x2; fy = y2;
            x2 = x1; y2 = y1;
            x1 = fx; y1 = fy;
        }

        float inc = m;
        while (fx <= x2) {
            fx += 1;
            fy += inc;
            glVertex2d(fx, fy);
        }
    } else {
        float fx = x1, fy = y1;
        if (y1 > y2) {
            fx = x2; fy = y2;
            x2 = x1; y2 = y1;
            x1 = fx; y1 = fy;
        }

        float inc = 1 / m;
        while (fy <= y2) {
            fx += inc;
            fy += 1;
            glVertex2d(fx, fy);
        }
    }
}

void glCircle2d(int cx, int cy, int r, bool complete) {
    int x = r;
    int y = 0;
    int pk = 1 - x;

    while (y <= x) {
        glVertex2d( x + cx,  y + cy);
        glVertex2d( y + cx,  x + cy);
        if (complete) glVertex2d(-x + cx,  y + cy);
        glVertex2d(-y + cx,  x + cy);
        if (complete) glVertex2d(-x + cx, -y + cy);
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

void drawNum(char num, int offset) {
    switch (num) {
        case '1': {
            glLine2d(30 + offset, 100, 30 + offset, 40);
            break;
        }
        case '2': {
            glCircle2d(0 + offset + 15, 80, 20, false);
            glLine2d(0 + offset, 65, 0 + offset, 40);
            glLine2d(0 + offset, 40, 30 + offset, 40);
            break;
        }
        case '3': {
            glCircle2d(0 + offset + 15, 85, 15, false);
            glCircle2d(0 + offset + 15, 55, 15, false);
            break;
        }
        case '4': {
            glLine2d(0 + offset, 60, 30 + offset, 100);
            glLine2d(30 + offset, 100, 30 + offset, 40);
            glLine2d(0 + offset, 60, 40 + offset, 60);
            break;
        }
        case '5': {
            glLine2d(0 + offset, 100, 30 + offset, 100);
            glLine2d(0 + offset, 65, 0 + offset, 100);
            glCircle2d(0 + offset + 15, 60, 20, false);
            break;
        }
        case '6': {
            glLine2d(1 + offset, 65, 30 + offset, 100);
            glCircle2d(0 + offset + 20, 60, 20, true);
            break;
        }
        case '7': {
            glLine2d(0 + offset, 100, 30 + offset, 100);
            glLine2d(10 + offset, 70, 30 + offset, 70);
            glLine2d(30 + offset, 100, 30 + offset, 40);
            break;
        }
        case '8': {
            glCircle2d(0 + offset + 15, 85, 15, true);
            glCircle2d(0 + offset + 15, 55, 15, true);
            break;
        }
        case '9': {
            glCircle2d(0 + offset + 15, 85, 20, true);
            glLine2d(35 + offset, 80, 00 + offset, 40);
            break;
        }
        case '0': {
            glCircle2d(0 + offset + 20, 70, 25, true);
            break;
        }
    }
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    /* Implement your drawing logic here */
    glBegin(GL_POINTS);
        for(int i = 0; num[i] != '\0'; i++) {
            drawNum(num[i], (i + 1) * 70);
        }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    /* Get any input you need here */
    cout<<"\n\n\tENTER THE NUMBER : ";
    cin>>num;

    //Initialize the main window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(WINDOW_TITLE);
    glutDisplayFunc(myDisplay);

    //Initialize the canvas and start the main loop
    canvasInit();
    glutMainLoop();
    return 0;
}
