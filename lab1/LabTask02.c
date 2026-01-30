// lab task 2
// Tree Shape: Three Triangles and One Quadrilateral

#include <GL/glut.h>

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0,1,0);
    glBegin(GL_TRIANGLES);
        glVertex2i(150, 350);
        glVertex2i(300, 350);
        glVertex2i(225, 500);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_TRIANGLES);
        glVertex2i(170, 450);
        glVertex2i(280, 450);
        glVertex2i(225, 600);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_TRIANGLES);
        glVertex2i(190, 550);
        glVertex2i(260, 550);
        glVertex2i(225, 650);
    glEnd();

    glColor3f(1,0,0);
    glBegin(GL_QUADS);
        glVertex2i(200, 200);
        glVertex2i(250, 200);
        glVertex2i(250, 350);
        glVertex2i(200, 350);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Point");
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 1000, 0, 1000);
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}