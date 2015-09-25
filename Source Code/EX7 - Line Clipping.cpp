#include <GL/glut.h>
#include <iostream>

using namespace std;

//Window Parameters
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char WINDOW_TITLE[] = "OPENGL TEMPLATE";

//Canvas Parameters
const float PLANE_LEFT = 0.0;
const float PLANE_RIGHT = WINDOW_WIDTH;
const float PLANE_BOTTOM = 0.0;
const float PLANE_TOP = WINDOW_HEIGHT;
const int POINT_SIZE = 5;

/*Create the variables here*/
int winLeft, winRight, winTop, winBottom;
float px[2], py[2];
float fx[2], fy[2];
bool tbrl[4];

void canvasInit() {
    //Initialize the canvas
    glClearColor(1, 1, 1, 0);
    glColor3f(1, 0, 0);
    glPointSize(POINT_SIZE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(PLANE_LEFT, PLANE_RIGHT, PLANE_BOTTOM, PLANE_TOP);
}

bool setTBRL(int x, int y) {
    tbrl[0] = y > winTop;
    tbrl[1] = y < winBottom;
    tbrl[2] = x > winRight;
    tbrl[3] = x < winLeft;

    for(int i=0; i<4; i++) {
        if(tbrl[i]) {
            return false;
        }
    }
    return true;
}

void myDisplay() {
    //Compute the slope of the line
    float m = (py[1] - py[0]) / (px[1] - px[0]);

    //Do the calculations and display
    for(int i = 0; i<2; i++) {
        for(int j=0; j<4; j++) {
            //Clear the canvas
            glClear(GL_COLOR_BUFFER_BIT);

            //Draw the clipping window
            glBegin(GL_LINES);
                glVertex2d(0, winTop);
                glVertex2d(WINDOW_WIDTH, winTop);
                glVertex2d(0, winBottom);
                glVertex2d(WINDOW_WIDTH, winBottom);
                glVertex2d(winLeft, 0);
                glVertex2d(winLeft, WINDOW_HEIGHT);
                glVertex2d(winRight, 0);
                glVertex2d(winRight, WINDOW_HEIGHT);
            glEnd();

            //Draw the clipped line
            glBegin(GL_LINES);
                glVertex2d(fx[0], fy[0]);
                glVertex2d(fx[1], fy[1]);
            glEnd();

            //Flush the buffer to the screen
            glFlush();

            //If it is a trivial accept then break
            if(setTBRL(fx[i], fy[i])) { break; }

            //If there is an intersection possible
            //Then find the point of intersection
            if(tbrl[j] == true) {
                switch (j) {
                    case 0:{
                        fx[i] = px[i] + (winTop - py[i]) / m;
                        fy[i] = winTop;
                        break;
                    }
                    case 1: {
                        fx[i] = px[i] + (winBottom - py[i]) / m;
                        fy[i] = winBottom;
                        break;
                    }
                    case 2: {
                        fx[i] = winRight;
                        fy[i] = py[i] + m * (winRight - px[i]);
                        break;
                    }
                    case 3: {
                        fx[i] = winLeft;
                        fy[i] = py[i] + m * (winLeft - px[i]);
                        break;
                    }
                }

                //Wait for user input
                int a;
                cin>>a;
            }
        }
    }
}

int main(int argc, char** argv) {
    /* Get any input you need here */
    cout<<"\n\n\tENTER THE TBRL : ";
    cin>>winTop>>winBottom>>winRight>>winLeft;
    cout<<"\n\n\tENTER THE POINTS : ";
    cin>>px[0]>>py[0]>>px[1]>>py[1];
    fx[0] = px[0];
    fy[0] = py[0];
    fx[1] = px[1];
    fy[1] = py[1];

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
