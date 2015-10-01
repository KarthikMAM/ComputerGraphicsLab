#include <GL/glut.h>
#include <iostream>

using namespace std;

double rotate_x = 0;
double rotate_y = 0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);

    double mat[][3] = {
        { 0.5, -0.5, -0.5},
        { 0.5,  0.5, -0.5},
        {-0.5,  0.5, -0.5},
        {-0.5, -0.5, -0.5},

        { 0.5, -0.5, -0.5},
        { 0.5,  0.5, -0.5},
        { 0.5,  0.5,  0.5},
        { 0.5, -0.5,  0.5},
    };

    int j=0;

    for(int i=0; i<=8; ) {
        glBegin(GL_POLYGON);
            for(int j=0; j<4; j++) {
                cout<<i<<endl;
                glVertex3f( mat[i][0], mat[i][1], mat[i++][2]);
            }
        glEnd();
    }

    glutSolidCube(5);

    glFlush();
    glutSwapBuffers();
}

void specialKeys(int key, int x, int y) {
    rotate_y += 5;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Cube");
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutMainLoop();

    return 0;
}
