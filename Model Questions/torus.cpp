#include <GL/glut.h>

float matSpecular[] = { 1, 1, 1, 1 };
float matShininess[] = { 70 };
float lightPos[] = { 0, 20, 10, 1 };
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

    glTranslatef(0, 0, -20);
    glRotatef(20, 1, 0, 0);
    glColor3f(0, 120, 0);
    glutSolidTorus(1, 5, 100, 100);
    //glutWireTeapot(4);

    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(20, 30);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("Torus");

    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
