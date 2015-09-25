#include <GL/glut.h>
#include <iostream>

using namespace std;

//Window Parameters
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char WINDOW_TITLE[] = "Target Board Concentric Circles";

//Canvas Parameters
const float PLANE_LEFT = 0.0;
const float PLANE_RIGHT = WINDOW_WIDTH;
const float PLANE_BOTTOM = 0.0;
const float PLANE_TOP = WINDOW_HEIGHT;
const int POINT_SIZE = 5;

/*Conditional Parameters*/
int radius;
int centerX, centerY;

void canvasInit() {
    //Initialize the canvas
    glClearColor(1, 1, 1, 0);
    glColor3f(1, 0, 0);
    glPointSize(POINT_SIZE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(PLANE_LEFT, PLANE_RIGHT, PLANE_BOTTOM, PLANE_TOP);
}

void circle(int centerX, int centerY, int radius) {
    //Initialize the required variables
    int x = radius;
    int y = 0;
    int pk = 1 - x;

    while (y <= x) {
        //Since the circle is symmetric about both x-axis, y-axis and origin
        //The circle can be considered as 8 equal parts
        //So Calculate for one part and extends it to the other parts
        glVertex2d( x + centerX,  y + centerY);
        glVertex2d( y + centerX,  x + centerY);
        glVertex2d(-x + centerX,  y + centerY);
        glVertex2d(-y + centerX,  x + centerY);
        glVertex2d(-x + centerX, -y + centerY);
        glVertex2d(-y + centerX, -x + centerY);
        glVertex2d( x + centerX, -y + centerY);
        glVertex2d( y + centerX, -x + centerY);


        //Increment x (if required), y, pk(based on the condition)
        y++;
        if (pk <= 0) { pk += 2 * y + 1; }
        else {
            x--;
            pk += 2 * (y - x) + 1;
        }
    }
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    /* Implement your drawing logic here */
    glBegin(GL_POINTS);
    for(int r = radius; r >= 0; r-=20) {
        circle(centerX, centerY, r);
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    /* Get any input you need here */
    cout<<"\n\n\tENTER THE RADIUS : ";
    cin>>radius;
    cout<<"\n\tENTER THE CENTER : ";
    cin>>centerX>>centerY;
    
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
