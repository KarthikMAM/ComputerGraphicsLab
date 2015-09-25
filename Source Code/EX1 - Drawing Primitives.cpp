#include <GL/glut.h>
#include <iostream>

using namespace std;

//Window Parameters
const int WINDOW_WIDTH = 480;
const int WINDOW_HEIGHT = 640;
const char WINDOW_TITLE[] = "Primitives in OPENGL";

//Canvas Parameters
const float PLANE_LEFT = 0.0;
const float PLANE_RIGHT = 640.0;
const float PLANE_BOTTOM = 0.0;
const float PLANE_TOP = 480.0;
const int POINT_SIZE = 10;

//Conditions
int primitiveSelected = 1;

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
    while (primitiveSelected != 10) {
        //Get the selected primitive
        cout<<"\n\n\tENTER THE SELECTED PRIMITIVE : ";
        cin>>primitiveSelected;

        //Display the selected primitive
        //Primitives are enum so they indices can be used instead of enum-id
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(primitiveSelected);
            glVertex2d(100, 200);
            glVertex2d(200, 300);
            glVertex2d(400, 400);
            glVertex2d(400, 200);
            glVertex2d(100, 150);
            glVertex2d(200, 200);
        glEnd();
        glFlush();
    }
}

int main(int argc, char** argv) {
    /*Get any input you need here*/
    cout<<"\n\n\tOPTIONS"
        <<"\n\t\t"<<"0. GL_POINTS"
        <<"\n\t\t"<<"1. GL_LINES"
        <<"\n\t\t"<<"2. GL_LINE_STRIP"
        <<"\n\t\t"<<"3. GL_LINE_LOOP"
        <<"\n\t\t"<<"4. GL_TRIANGLES"
        <<"\n\t\t"<<"5. GL_TRIANGLE_STRIP"
        <<"\n\t\t"<<"6. GL_TRIANGLE_FAN"
        <<"\n\t\t"<<"7. GL_QUADS"
        <<"\n\t\t"<<"8. GL_QUAD_STRIP"
        <<"\n\t\t"<<"9. GL_POLYGON"
        <<"\n\t\t"<<"10. EXIT";

    //Initialize the window attributes
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(WINDOW_TITLE);
    glutDisplayFunc(myDisplay);

    //Initialize the canvas ans start the main loop
    canvasInit();
    glutMainLoop();
    return 0;
}
