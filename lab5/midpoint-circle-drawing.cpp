#include <GL/glut.h>

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    int xc = 250, yc = 250;
    int R = 100;

    int x = 0;
    int y = R;
    int p = 1 - R;

    glColor3f(1, 0, 0);
    glPointSize(3);

    glBegin(GL_POINTS);

    while (x <= y) {
        // 8-way symmetry
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);

        x++;

        if (p < 0) {
            p = p + 2 * x + 1;
        } else {
            y--;
            p = p + 2 * x - 2 * y + 1;
        }
    }
    glEnd();  

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Midpoint Circle");

    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 500, 0, 500);

    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}