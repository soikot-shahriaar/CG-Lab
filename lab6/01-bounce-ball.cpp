#include <GL/glut.h>
#include <math.h>

float cy = 100;
float speed = 0.4;
int direction = 1;

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    float x, y, theta;

    // red ball
    glColor3f(1, 0, 0);

    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.1416 / 180;
        x = 500 + 20 * cos(theta);
        y = cy + 20 * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();

    cy = cy + speed * direction;

    if (cy >= 580) direction = -1;
    if (cy <= 20) direction = 1;

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutCreateWindow("Bouncing Ball");

    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 1000, 0, 600);

    glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}
