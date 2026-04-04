#include <GL/glut.h>
#include <math.h>

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    float i, x, y, theta;
    glPointSize(5);

    // Face
    glColor3f(1, 0, 0);
    for(i=0; i<=360; i++) {
        theta = i*3.1416/180;
        x = 250 + 150*cos(theta);
        y = 250 + 150*sin(theta);
        glBegin(GL_POINTS);
        glVertex2f(x,y);
        glEnd();
    }

    // Eyes
    for(i=0; i<=360; i++) {
        theta = i*3.1416/180;

        // Left eye
        x = 200+25*cos(theta);
        y = 300+15*sin(theta);
        glBegin(GL_POINTS);
        glVertex2f(x,y);
        glEnd();

        // Right eye
        x = 300+25*cos(theta);
        y = 300+15*sin(theta);
        glBegin(GL_POINTS);
        glVertex2f(x,y);
        glEnd();
    }

    glColor3f(0,0,0);

    // Left pupil
    glBegin(GL_POLYGON);
    for(i=0; i<=360; i++) {
        theta = i*3.1416/180;
        x = 200 + 7*cos(theta);
        y = 300 + 7*sin(theta);
        glVertex2f(x,y);
    }
    glEnd();

    // Right pupil
    glBegin(GL_POLYGON);
    for(i=0; i<=360; i++) {
        theta = i*3.1416/180;
        x = 300 + 7*cos(theta);
        y = 300 + 7*sin(theta);
        glVertex2f(x,y);
    }
    glEnd();

    // Smile
    glColor3f(1, 0, 0);
    for(i=200; i<=340; i++) {
        theta = i*3.1416/180;
        x=250+90*cos(theta);
        y=230+60*sin(theta);
        glBegin(GL_POINTS);
        glVertex2f(x,y);
        glEnd();
    }

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Smiley Emoji");

    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 500, 0, 500);

    glutDisplayFunc(draw);

    glutMainLoop();
    return 0;
}
