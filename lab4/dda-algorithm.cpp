// DDA Implementation

#include <GL/glut.h>
#include <math.h>

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    float x1, x2, y1, y2, dx, dy, dx1, dy1, step, i, x_inc, y_inc;

    x1 = 10;
    y1 = 0;
    x2 = 60;
    y2 = 90;

    dx = x2 - x1;
    dy = y2 - y1;

    dx1 = fabs(dx);
    dy1 = fabs(dy);

    if (dx1 > dy1)
        step = dx1;
    else
        step = dy1;

    x_inc = dx / step;
    y_inc = dy / step;

    glPointSize(3);

    for (i = 0; i <= step; i++) {
        glColor3f(1, 0, 0);
        glBegin(GL_POINTS);
        glVertex2f(x1, y1);
        glEnd();

        x1 += x_inc;
        y1 += y_inc;
    }

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA");
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}