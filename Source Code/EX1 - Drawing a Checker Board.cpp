#include <GL/glut.h>
#include <iostream>

using namespace std;

//Window Parameters
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char WINDOW_TITLE[] = "Checker Board";

//Canvas Parameters
const float PLANE_LEFT = 0.0;
const float PLANE_RIGHT = WINDOW_WIDTH;
const float PLANE_BOTTOM = 0.0;
const float PLANE_TOP = WINDOW_HEIGHT;
const int POINT_SIZE = 50;

//Conditions
int boxCount;
const int BOX_SIZE = POINT_SIZE;

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
    //Clear the canvas
    glClear(GL_COLOR_BUFFER_BIT);

    //Draw the checker board
    glBegin(GL_POINTS);
        for(int i=1; i<=boxCount; i++) {
            for(int j=1; j<=boxCount; j++) {
                //Creates the alternate black and white color
                if(i % 2 != 0) {
                    if(j % 2 == 0) { glColor3f(1, 1, 1); }
                    else { glColor3f(0, 0, 0); }
                } else {
                    if(j % 2 != 0) { glColor3f(1, 1, 1); }
                    else { glColor3f(0, 0, 0); }
                }

                //A point which is the size of a box
                glVertex2d(i * BOX_SIZE, j * BOX_SIZE);
            }
            cout<<"\n";
        }
    glEnd();

    //Flush the data to the screen
    glFlush();
}

int main(int argc, char** argv) {
    /*Get any input you need here*/
    cout<<"\n\n\tENTER THE NUMBER OF BOXES : ";
    cin>>boxCount;

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
