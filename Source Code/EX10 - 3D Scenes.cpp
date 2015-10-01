#include <GL/glut.h>

float matSpecular[] = { 1, 1, 1, 1 };
float matShininess[] = { 70 };
float lightPos[] = { 0, 0, 1000, 100 };
float lightAmb[] = { .9, .8, .7, 1 };

void init() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_COLOR_MATERIAL);

    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0, 0, -10);
    glRotatef(-45, 0.1, 0.1, 0.1);
    glColor3f(255, 0, 0);
    glutSolidSphere(1, 40, 16);

    glTranslatef(0, 0, -10);
    glRotatef(-45, 0.1, 0.1, 0.1);
    glColor3f(0, 120, 0);
    glutSolidCube(4);

    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(20, 30);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("cubes");

    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
