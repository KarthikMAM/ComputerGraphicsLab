#include <GL/glut.h>
#include <iostream>
#include <math.h>

using namespace std;

//Window Parameters
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char WINDOW_TITLE[] = "Window to Viewport animation";

//Canvas Parameters
const float PLANE_LEFT = 0.0;
const float PLANE_RIGHT = WINDOW_WIDTH;
const float PLANE_BOTTOM = 0.0;
const float PLANE_TOP = WINDOW_HEIGHT;
const int POINT_SIZE = 5;

/*Create the variables here*/
float viewLeft, viewRight, viewTop, viewBottom;
float winLeft, winRight, winTop, winBottom;
enum TRANSFORMATIONS { NORMAL, TRANSLATE, ROTATE, SCALE,  SHEAR, REFLECT};

struct Matrix {
    float a[3][3];
    int m, n;
};

Matrix multMatrix(Matrix mat1, Matrix mat2) {
    Matrix res = {{0}, mat1.m, mat2.n};

    //Multiplication of the matrices
    if (mat1.n == mat2.m) {
        for(int i=0; i<mat1.m; i++) {
            for(int j=0; j<mat2.n; j++) {
                for(int k=0; k<3; k++) {
                    res.a[i][j] += mat1.a[i][k] * mat2.a[k][j];
                }
            }
        }
    }

    return res;
}

void canvasInit() {
    //Initialize the canvas
    glClearColor(1, 1, 1, 0);
    glColor3f(1, 0, 0);
    glPointSize(POINT_SIZE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(PLANE_LEFT, PLANE_RIGHT, PLANE_BOTTOM, PLANE_TOP);
}

Matrix transformPoint(int x, int y, int op, float p1, float p2) {
    Matrix trans = {
        {   /*The transformation Matrix*/
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}
        }, 3, 3
    };
    Matrix point = {
        {
            /*The point in homogeneous coordinates*/
            {x},
            {y},
            {1}
        }, 3, 1
    };

    switch (op) {
        case 0: {
            //Display as it is without any transformation
            break;
        }
        case 1: {
            //Translation of the given point
            //p1 is the x-translation factor
            //p2 is the y-translation factor
            trans.a[0][2] = p1;
            break;
        }
            trans.a[1][2] = p2;
        case 2: {
            //Rotation of the given point
            //p1 is the rotation angle
            //p2 is a place holder
            float angle = p1 * M_PI / 180;
            trans.a[0][0] = cos(angle);
            trans.a[0][1] = -sin(angle);
            trans.a[1][0] = -trans.a[0][1];
            trans.a[1][1] = trans.a[0][0];
            break;
        }
        case 3: {
            //Scaling of the given point
            //p1 is the scaleX factor
            //p2 is the scaleY factor
            trans.a[0][0] = p1;
            trans.a[1][1] = p2;
            break;
        }
        case 4: {
            //Shearing of the given point
            //p1 is the shearX factor
            //p2 is the shearY factor
            trans.a[0][1] = p1;
            trans.a[1][0] = p2;
            break;
        }
        case 5: {
            //Reflection of the given point
            //p1 is the Reflection about point
            //0 is no Reflection
            //1 is Reflection about y-axis
            //3 is Reflection about x-axis
            float angle = (90 * M_PI / 180) * p1;
            trans.a[0][0] = cos(angle);
            trans.a[0][1] = -sin(angle);
            trans.a[1][0] = -trans.a[0][1];
            trans.a[1][1] = trans.a[0][0];
            break;
        }
    }

    return multMatrix(trans, point);
}

void myDisplay() {
    while(true) {
        //Clear the canvas
        glClear(GL_COLOR_BUFFER_BIT);

        //Transform Parameters
        int op;
        float p1 = (viewRight - viewLeft) / (winRight - winLeft);
        float p2 = (viewTop - viewBottom) / (winTop - winBottom);
        int xOffset = 10;
        int yOffset = 10;

        //Get user data
        cout<<"\n\n\tDISPLAY VIEW PORT : ";
        cin>>op;
        if (op == -1) { break; }
        op = op == 0 ? NORMAL : SCALE;

        //Draw the viewport or the window based on the user selection
        glBegin(GL_QUADS);
            glColor3f(0,0,0);
            if(op) {
                glVertex2d(xOffset + viewLeft, yOffset + viewBottom);
                glVertex2d(xOffset + viewLeft, yOffset + viewTop);
                glVertex2d(xOffset + viewRight, yOffset + viewTop);
                glVertex2d(xOffset + viewRight, yOffset + viewBottom);
            } else {
                glVertex2d(xOffset + winLeft, yOffset + winBottom);
                glVertex2d(xOffset + winLeft, yOffset + winTop);
                glVertex2d(xOffset + winRight, yOffset + winTop);
                glVertex2d(xOffset + winRight, yOffset + winBottom);
            }
        glEnd();

        //Transformed points to viewport or window based on user selection
        Matrix point1 = transformPoint(30, 50, op, p1 , p2);
        Matrix point2 = transformPoint(60, 80, op, p1, p2);
        Matrix point3 = transformPoint(60, 20, op, p1, p2);
        Matrix point4 = transformPoint(220, 50, op, p1 , p2);
        Matrix point5 = transformPoint(190, 80, op, p1, p2);
        Matrix point6 = transformPoint(190, 20, op, p1, p2);
        Matrix point7 = transformPoint(60, 40, op, p1, p2);
        Matrix point8 = transformPoint(60, 60, op, p1 , p2);
        Matrix point9 = transformPoint(190, 40, op, p1, p2);
        Matrix point10 = transformPoint(190, 60, op, p1, p2);

        //Transform the points and display them as a figure
        glBegin(GL_TRIANGLES);
            glColor3f(1,0,0);
            glVertex2d(xOffset + point1.a[0][0], yOffset + point1.a[1][0]);
            glVertex2d(xOffset + point2.a[0][0], yOffset + point2.a[1][0]);
            glVertex2d(xOffset + point3.a[0][0], yOffset + point3.a[1][0]);
            glVertex2d(xOffset + point4.a[0][0], yOffset + point4.a[1][0]);
            glVertex2d(xOffset + point5.a[0][0], yOffset + point5.a[1][0]);
            glVertex2d(xOffset + point6.a[0][0], yOffset + point6.a[1][0]);
        glEnd();
        glBegin(GL_QUADS);
            glVertex2d(xOffset + point7.a[0][0], yOffset + point7.a[1][0]);
            glVertex2d(xOffset + point8.a[0][0], yOffset + point8.a[1][0]);
            glVertex2d(xOffset + point9.a[0][0], yOffset + point9.a[1][0]);
            glVertex2d(xOffset + point10.a[0][0], yOffset + point10.a[1][0]);
        glEnd();

        //Flush the buffer to the screen
        glFlush();
    }
}

int main(int argc, char** argv) {
    /* Get any input you need here */
    cout<<"\n\n\tENTER THE VIEW BOUNDARIES L R T B : ";
    cin>>viewLeft>>viewRight>>viewTop>>viewBottom;
    winLeft = 0;
    winRight = 250;
    winTop = 100;
    winBottom = 0;

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
