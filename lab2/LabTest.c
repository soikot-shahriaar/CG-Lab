#include <GL/glut.h>

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(10);

    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
        glVertex2i(500, 650);
        glVertex2i(450, 600);
        glVertex2i(500, 300);
    glEnd();
    glColor3f(0, 0, 1);
    glBegin(GL_TRIANGLES);
        glVertex2i(500, 650);
        glVertex2i(550, 600);
        glVertex2i(500, 300);
    glEnd();

    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
        glVertex2i(450, 600);
        glVertex2i(250, 700);
        glVertex2i(300, 500);
    glEnd();
    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
        glVertex2i(550, 600);
        glVertex2i(750, 700);
        glVertex2i(700, 500);
    glEnd();

    glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
        glVertex2i(450, 600);
        glVertex2i(483, 400);
        glVertex2i(425, 350);
        glVertex2i(300, 500);
    glEnd();
    glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
        glVertex2i(550, 600);
        glVertex2i(517, 400);
        glVertex2i(575, 350);
        glVertex2i(700, 500);
    glEnd();

    glColor3f(1, 0, 1);
    glBegin(GL_QUADS);
        glVertex2i(300, 500);
        glVertex2i(275, 375);
        glVertex2i(400, 150);
        glVertex2i(425, 350);
    glEnd();
    glColor3f(1, 0, 1);
    glBegin(GL_QUADS);
        glVertex2i(575, 350);
        glVertex2i(700, 500);
        glVertex2i(725, 375);
        glVertex2i(600, 150);
    glEnd();

    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
        glVertex2i(425, 350);
        glVertex2i(400, 150);
        glVertex2i(450, 225);
    glEnd();
    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
        glVertex2i(575, 350);
        glVertex2i(600, 150);
        glVertex2i(550, 225);
    glEnd();

    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
        glVertex2i(370, 212);
        glVertex2i(400, 150);
        glVertex2i(375, 50);
    glEnd();
        glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
        glVertex2i(630, 212);
        glVertex2i(600, 150);
        glVertex2i(625, 50);
    glEnd();

    glColor3f(1, 1, 0);
    glBegin(GL_QUADS);
        glVertex2i(300, 500);
        glVertex2i(250, 700);
        glVertex2i(125, 525);
        glVertex2i(250, 475);
    glEnd();
    glColor3f(1, 1, 0);
    glBegin(GL_QUADS);
        glVertex2i(700, 500);
        glVertex2i(750, 700);
        glVertex2i(875, 525);
        glVertex2i(750, 475);
    glEnd();

    glColor3f(0, 1, 1);
    glBegin(GL_QUADS);
        glVertex2i(250, 700);
        glVertex2i(125, 525);
        glVertex2i(35, 595);
        glVertex2i(50, 675);
    glEnd();
    glColor3f(0, 1, 1);
    glBegin(GL_QUADS);
        glVertex2i(750, 700);
        glVertex2i(875, 525);
        glVertex2i(965, 595);
        glVertex2i(950, 675);
    glEnd();

    glColor3f(0, 0, 1);
    glBegin(GL_TRIANGLES);
        glVertex2i(495, 675);
        glVertex2i(455, 785);
        glVertex2i(480, 760);
    glEnd();
    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
        glVertex2i(505, 675);
        glVertex2i(545, 785);
        glVertex2i(520, 760);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Lab Test");
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 1000, 0, 1000);
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}