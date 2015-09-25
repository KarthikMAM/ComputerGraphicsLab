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
const int POINT_SIZE = 5;

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

    if(m <= 1) {
        //Swap the points to start from left to right
        int fx = x1, fy = y1;
        if(x1 > x2) {
            fx = x1; fy = y1;
            x1 = x2; y1 = y2;
            x2 = fx; y2 = fy;
        }

        //Calculate values for computation
        int dx = x2 - x1;
        int dy = y2 - y1;
        int pk = 2 * dy - dx;

        //Draw the actual line
        glBegin(GL_POINTS);
            while (fx < x2) {
                if(pk < 0) {
                    fx++;
                    pk += 2 * dy;
                } else {
                    fx++; fy++;
                    pk += 2 * (dy - dx);
                }

                glVertex2d(fx, fy);
            }
        glEnd();
    } else {
        //Swap the points to start from left to right
        int fx = x1, fy = y1;
        if(y1 > y2) {
            fx = x1; fy = y1;
            x1 = x2; y1 = y2;
            x2 = fx; y2 = fy;
        }

        //Calculate values for computation
        int dx = x2 - x1;
        int dy = y2 - y1;
        int pk = 2 * dx - dy;

        //Draw the actual line
        glBegin(GL_POINTS);
            while (fy < y2) {
                if(pk < 0) {
                    fy++;
                    pk += 2 * dx;
                } else {
                    fx++; fy++;
                    pk += 2 * (dx - dy);
                }

                glVertex2d(fx, fy);
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
