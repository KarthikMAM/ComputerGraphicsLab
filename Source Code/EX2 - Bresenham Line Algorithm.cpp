#include <GL/glut.h>
#include <iostream>

using namespace std;

//Window Parameters
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char WINDOW_TITLE[] = "Bresenham Line Algorithm";

//Canvas Parameters
const float PLANE_LEFT = 0.0;
const float PLANE_RIGHT = WINDOW_WIDTH;
const float PLANE_BOTTOM = 0.0;
const float PLANE_TOP = WINDOW_HEIGHT;
const int POINT_SIZE = 2;

/*Create the variables here*/
float x1, y1, x2, y2;
float m;

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

    if (m > -1 && m < 1) {
        //Sampling in x-direction from left to right
        //Swap if from right to left
        if(x1 > x2) {
            int temp;
            temp = x1; x1 = x2; x2 = temp;
            temp = y1; y1 = y2; y2 = temp;
        }

        //Calculation Parameters
        int yInc = (y2 - y1) >= 0 ? 1 : -1;
        int dx = x2 - x1;
        int dy = yInc * (y2 - y1);
        int pk = 2 * dy - dx;

        //Bresenham Algorithm slope between -1 to +1
        glBegin(GL_POINTS);
            for (int x = x1, y = y1; x <= x2; x++) {
                glVertex2d(x, y);
                if (pk < 0) { pk += 2 * dy; }
                else {
                    y += yInc;
                    pk += 2 * ( dy - dx );
                }
            }
        glEnd();
    } else {
        //Sampling in y-direction from left to right
        //Swap if from right to left
        if(y1 > y2) {
            int temp;
            temp = x1; x1 = x2; x2 = temp;
            temp = y1; y1 = y2; y2 = temp;
        }

        //Calculation Parameters
        int xInc = (x2 - x1) >= 0 ? 1 : -1;
        int dx = xInc * (x2 - x1);
        int dy = y2 - y1;
        int pk = 2 * dx - dy;

        //Bresenham algorithm for slope -inf to -1 and +1 to +inf
        glBegin(GL_POINTS);
            for (int x = x1, y = y1; y <= y2; y++) {
                glVertex2d(x, y);
                if (pk < 0) { pk += 2 * dx; }
                else {
                    x += xInc;
                    pk += 2 * ( dx - dy );
                }
            }
        glEnd();
    }

    glFlush();
}

int main(int argc, char** argv) {
    /* Get any input you need here */
    cout<<"\n\n\tENTER THE POINTS : ";
    cin>>x1>>y1>>x2>>y2;
    m = (y2 - y1) / (x2 - x1);

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
