#include <GL/glut.h>

float matSpecular[] = {1, 1, 1, 0};
float matShininess[] = {70};
float lightPos[] = {0, 0, 20, 1};
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

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50, 50, -50, 50, -50, 50);
}

int roX = 2;
int roY = 2;

//Points to represent numbers on the each face of the dice
int dicePoint[][3] = {
    { 0,  0,  6},

    { 5,  6,  0},
    {-5,  6,  0},

    { 6,  5,  0},
    { 6, -5,  0},
    { 6,  0,  0},

    {-6,  5,  5},
    {-6, -5, -5},
    {-6, -5,  5},
    {-6,  5, -5},

    { 5, -6, -5},
    {-5, -6,  5},
    {-5, -6, -5},
    { 5, -6,  5},
    { 0, -6,  0},

    { 5,  5, -6},
    {-5, -5, -6},
    { 5, -5, -6},
    {-5,  5, -6},
    { 5,  0, -6},
    {-5,  0, -6},
};

void display() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Rotate in the x and y directions
    glRotatef(roX, 0, 1, 0);
    glRotatef(roY, 1, 0, 0);

    //Create the cube part of the dice
    glColor3f(0, 0, 1);
    glutSolidCube(15);
    glColor3f(1, 0, 0);

    //Display the numbers as spheres on each face
    for(int i = 1, p = 0; i <= 6; i++) {
        for(int j=0; j < i; j++, p++) {
            glTranslatef( dicePoint[p][0],  dicePoint[p][1],  dicePoint[p][2]);
            glutSolidSphere(2, 100, 100);
            glTranslatef(-dicePoint[p][0], -dicePoint[p][1], -dicePoint[p][2]);
        }
    }

    glFlush();
}

void special(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_RIGHT: {
            roX++;
            break;
        }
        case GLUT_KEY_LEFT: {
            roX--;
            break;
        }
        case GLUT_KEY_UP: {
            roY--;
            break;
        }
        case GLUT_KEY_DOWN: {
            roY++;
            break;
        }
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("3D dice rotation");

    glutDisplayFunc(display);
    glutSpecialFunc(special);
    init();
    glutMainLoop();
}
