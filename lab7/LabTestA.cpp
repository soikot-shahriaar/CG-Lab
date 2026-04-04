#include <GL/glut.h>
#include <math.h>

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    float i, x, y, theta;

    glColor3f(0,0,0);
    glLineWidth(5);

    // head
    glBegin(GL_LINE_LOOP);
    for(i=0;i<=360;i++){
        theta=i*3.1416/180;
        x=500+60*cos(theta);
        y=870+60*sin(theta);
        glVertex2f(x,y);
    }
    glEnd();

    // shoulder
    glBegin(GL_LINE_LOOP);
    for(i=0;i<=150;i++){
        theta=i*3.1416/180;
        x=480+80*cos(theta);
        y=700+80*sin(theta);
        glVertex2f(x,y);
    }
    glEnd();

    // body
    glBegin(GL_LINE_LOOP);
    glVertex2i(415,730);
    glVertex2i(550,700);
    glVertex2i(530,500);
    glVertex2i(400,500);
    glEnd();

    // front leg upper
    glBegin(GL_LINE_LOOP);
    glVertex2i(400,500);
    glVertex2i(530,500);
    glVertex2i(600,350);
    glVertex2i(500,350);
    glEnd();

    // front leg lower
    glBegin(GL_LINE_LOOP);
    glVertex2i(500,350);
    glVertex2i(600,350);
    glVertex2i(550,150);
    glVertex2i(480,150);
    glEnd();

    // back leg upper
    glBegin(GL_LINE_LOOP);
    glVertex2i(400,500);
    glVertex2i(470,385);
    glVertex2i(420,280);
    glVertex2i(370,320);
    glEnd();

    // back leg lower
    glBegin(GL_LINE_LOOP);
    glVertex2i(370,320);
    glVertex2i(420,280);
    glVertex2i(320,150);
    glVertex2i(250,150);
    glEnd();

    // front hand
    glBegin(GL_LINE_LOOP);
    glVertex2i(550,680);
    glVertex2i(690,560);
    glVertex2i(670,530);
    glVertex2i(540,610);
    glEnd();

    // back hand upper
    glBegin(GL_LINE_LOOP);
    glVertex2i(415,715);
    glVertex2i(405,630);
    glVertex2i(340,570);
    glVertex2i(340,620);
    glEnd();

    // back hand lower
    glBegin(GL_LINE_LOOP);
    glVertex2i(340,620);
    glVertex2i(340,570);
    glVertex2i(280,470);
    glVertex2i(275,500);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Lab Test");

    glClearColor(1,1,1,1);
    gluOrtho2D(0,1000,0,1000);

    glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}