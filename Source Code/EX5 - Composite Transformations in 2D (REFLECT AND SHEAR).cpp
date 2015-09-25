#include <GL/glut.h>
#include <iostream>
#include <math.h>

using namespace std;

//Window Parameters
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char WINDOW_TITLE[] = "Composite Transformations (Reflect and Shear)";

//Canvas Parameters
const float PLANE_LEFT = 0.0;
const float PLANE_RIGHT = WINDOW_WIDTH;
const float PLANE_BOTTOM = 0.0;
const float PLANE_TOP = WINDOW_HEIGHT;
const int POINT_SIZE = 5;

/*Create the variables here*/
int quadLeft, quadRight, quadTop, quadBottom;
enum TRANSFORMATIONS { NORMAL, TRANSLATE, ROTATE, SCALE,  SHEAR, REFLECT};
int reflectAxis;
float shearX, shearY;

struct Matrix {
    float a[3][3];
    int m, n;
};


Matrix pointMatrix(int a, int b) {
    Matrix x = {{{a}, {b}, {1}}, 3, 1};
    return x;
}

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

Matrix transformPoint(Matrix point, int op, float p1, float p2) {
    Matrix trans = {
        {   /*The transformation Matrix*/
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}
        }, 3, 3
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
            trans.a[1][2] = p2;
            break;
        }
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

Matrix compositeTransform(int pointX, int pointY) {
    Matrix point = {{{pointX}, {pointY}, {1}}, 3, 1};

    //1. Reflected about the given axis
    //2. Sheared by the given factors
    Matrix result = transformPoint(
        transformPoint(point, REFLECT, reflectAxis, 0),
        SHEAR, shearX, shearY
    );

    return result;
}

void myDisplay() {
    //Clear the canvas
    glClear(GL_COLOR_BUFFER_BIT);

    //Find the mid-point offset
    int xOffset = WINDOW_WIDTH / 2;
    int yOffset = WINDOW_HEIGHT / 2;

    //Draw the Cartesian coordinates
    glBegin(GL_LINES);
        glVertex2d(0, yOffset);
        glVertex2d(WINDOW_WIDTH, yOffset);
        glVertex2d(xOffset, 0);
        glVertex2d(xOffset, WINDOW_HEIGHT);
    glEnd();

    //Transform the points and display them as a quad
    glBegin(GL_QUADS);
        //Transformed points
        Matrix point1 = compositeTransform(quadLeft, quadBottom);
        Matrix point2 = compositeTransform(quadLeft, quadTop);
        Matrix point3 = compositeTransform(quadRight, quadTop);
        Matrix point4 = compositeTransform(quadRight, quadBottom);

        //Original untouched quad
        glColor3f(0, 1, 0);
        glVertex2d(xOffset + quadLeft, yOffset + quadBottom);
        glVertex2d(xOffset + quadLeft, yOffset + quadTop);
        glVertex2d(xOffset + quadRight, yOffset + quadTop);
        glVertex2d(xOffset + quadRight, yOffset + quadBottom);

        //Transformed quad
        glColor3f(1, 0, 0);
        glVertex2d(xOffset + point1.a[0][0], yOffset + point1.a[1][0]);
        glVertex2d(xOffset + point2.a[0][0], yOffset + point2.a[1][0]);
        glVertex2d(xOffset + point3.a[0][0], yOffset + point3.a[1][0]);
        glVertex2d(xOffset + point4.a[0][0], yOffset + point4.a[1][0]);
    glEnd();

    //Flush the buffer to the screen
    glFlush();
}

int main(int argc, char** argv) {
    /* Get any input you need here */
    cout<<"\n\n\tENTER THE BOUNDARIES L R T B : ";
    cin>>quadLeft>>quadRight>>quadTop>>quadBottom;
    cout<<"\n\n\tENTER THE AXIS TO REFLECT : ";
    cin>>reflectAxis;
    cout<<"\n\n\tENTER THE SHEAR FACTORS : ";
    cin>>shearX>>shearY;

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
