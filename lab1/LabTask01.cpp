// lab task 1
// Three Colored Triangles

#include <GL/glut.h>

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,0,1);
    glBegin(GL_TRIANGLES);
        glVertex2i(50, 250);
        glVertex2i(350, 250);
        glVertex2i(200, 400);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_TRIANGLES);
        glVertex2i(50, 250);
        glVertex2i(50, 50);
        glVertex2i(200, 50);
    glEnd();

    glColor3f(1,0,0);
    glBegin(GL_TRIANGLES);
        glVertex2i(200, 50);
        glVertex2i(350, 50);
        glVertex2i(350, 250);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
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