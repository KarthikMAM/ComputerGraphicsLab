#include <GL/glut.h>

float matSpecular[] = {1, 1, 1, 1};
float matShininess[] = {70};
float lightPos[] = {0, 0, 0, 1};
float lightAmb[] = {1, 1, 1, 0};

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
}

int ro = 2;

void display() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50, 50, -50, 50, -50, 50);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutSolidSphere(4, 100, 100);
    glRotatef(ro, 0, 0, 1);

    for(int i=0; i<2; i++) {
        glTranslatef(0, 20, 0);
        glRotatef(ro, 1, 1, 0);
        glutSolidSphere(4, 100, 100);
    }

    glFlush();
}

void special(int key, int x, int y) {
    ro++;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("hello");

    glutDisplayFunc(display);
    glutSpecialFunc(special);
    init();
    glutMainLoop();
}
