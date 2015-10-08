#include <GL/glut.h>

float matSpecular[] = {1, 1, 1, 1};
float matShininess[] = {70};
float lightPos[] = {30, 30, 30, 1};
float lightAmb[] = {1, 1, 1, 0};

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
}

int rotateAngle = 2;

void display() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100, 100, -100, 100, -100, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glRotatef(40, 1, 1, 0);
    glColor3f(1, 1, 0);
    glutSolidSphere(8, 100, 100);
    glColor3f(1, 1, 1);

    for(int i=1; i<5; i++) {
        glutSolidTorus(0.5, i * 20, 100, 100);

        glRotatef(rotateAngle, 0, 0, 1);
        glTranslatef(0, i * 20, 0);
        glColor3f(0.2 * i, 0.1 * i, 0.05 * i);
        glutSolidSphere(4, 100, 100);
        glColor3f(1, 1, 1);
        glTranslatef(0, -i * 20, 0);
    }

    glFlush();
}

void special(int key, int x, int y) {
    rotateAngle++;
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
