// Bresenham's Implementation

#include <GL/glut.h>
#include <math.h>

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    int x1, x2, y1, y2, dx, dy, p;

    x1 = 10;
    y1 = 10;
    x2 = 80;
    y2 = 90;
    dx = x2 - x1;
    dy = y2 - y1;

    if (dx > dy) {
        p = 2 * dy - dx;
        while (x1 <= x2) {
            glColor3f(1, 0, 0);
            glPointSize(5);
            glBegin(GL_POINTS);
            glVertex2i(x1, y1);
            glEnd();

            if (p < 0) {
                x1 = x1 + 1;
                y1 = y1;
                p = p + 2 * dy;
            }
            else {
                x1 = x1 + 1;
                y1 = y1 + 1;
                p = p + 2 * dy - 2 * dx;
            }
        }
    }
    else {
        p = 2 * dx - dy;
        while (y1 <= y2) {
            glColor3f(1, 0, 0);
            glPointSize(5);
            glBegin(GL_POINTS);
            glVertex2i(x1, y1);
            glEnd();

            if (p < 0) {
                y1 = y1 + 1;
                p = p + 2 * dx;
            }
            else {
                x1 = x1 + 1;
                y1 = y1 + 1;
                p = p + 2 * dx - 2 * dy;
            }
        }
    }
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Point");
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}
