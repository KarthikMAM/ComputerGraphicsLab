#include <GL/glut.h>
#include <iostream>

using namespace std;

//Window Parameters
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char WINDOW_TITLE[] = "DDA Line Algorithm";

//Canvas Parameters
const float PLANE_LEFT = 0.0;
const float PLANE_RIGHT = WINDOW_WIDTH;
const float PLANE_BOTTOM = 0.0;
const float PLANE_TOP = WINDOW_HEIGHT;
const int POINT_SIZE = 5;

//Condtions
float x1, y1, x2, y2;
float m, inc;
float x, y;

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
    glBegin(GL_POINTS);
        //Calculate slope
        m = (y2 - y1) / (x2 - x1);
        if(m <= 1 && m >= -1) {
            //Set increment variable
            inc = m;

            //Swap the points if we have to traverse from right to left
            if(x1 > x2) {
                int temp = x1; x1 = x2; x2 = temp;
                temp = y1; y1 = y2; y2 = temp;
            }

            //Digital Differential Algorithm for x+=1
            y = y1;
            for(int x=x1; x<=x2; x++) {
                glVertex2d(x, y);
                y += inc;
            }
        } else {
            //Set increment variable
            inc = 1/m;

            //Swap the point if we have to traverse from right to left
            if (y1 > y2) {
                int temp = x1; x1 = x2; x2 = temp;
                temp = y1; y1 = y2; y2 = temp;
            }

            //Digital Differential Algorithm for y+=1
            x = x1;
            for(int y=y1; y<=y2; y++) {
                glVertex2d(x, y);
                x += inc;
            }
        }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    /* Get any input you need here */
    cout<<"\n\n\tENTER THE COORDIANTES OF POINT 1 : ";
    cin>>x1>>y1;
    cout<<"\n\n\tENTER THE COORDIANTES OF POINT 2 : ";
    cin>>x2>>y2;

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
