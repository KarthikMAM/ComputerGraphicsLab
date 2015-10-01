#include <GL/glut.h>

void init() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(80, 1.5, 1, 100);

    glClearColor(1, 1, 1, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0, 0, -40);
    glRotatef(-30, 0, 0.1, 0);
    glColor3ub(255, 0, 0);
    glutSolidCube(5);

    glTranslatef(0, -1, 20);
    glRotatef(-45, 0, 0.1, 0);
    glColor3ub(0, 255, 0);
    glutSolidCube(5);

    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(20, 30);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("cubes");

    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
