// Smiley Emoji Animation

#include <GL/glut.h>
#include <math.h>

float t = 0;

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    float i, x, y, theta;
    float r = 20;

    // Face (Yellow Circle)
    glColor3f(1,1,0);
    glBegin(GL_POLYGON);
    for(i=0;i<=360;i++){
        theta=i*3.1416/180;
        x=250+150*cos(theta);
        y=250+150*sin(theta);
        glVertex2f(x,y);
    }
    glEnd();

    // Face Border
    glColor3f(0,0,0);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    for(i=0;i<=360;i++){
        theta=i*3.1416/180;
        x=250+150*cos(theta);
        y=250+150*sin(theta);
        glVertex2f(x,y);
    }
    glEnd();

    // Mouth
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    for(i=180;i<=360;i+=3){
        theta=i*3.1416/180;
        x=250+70*cos(theta);
        y=200+60*sin(theta);
        glVertex2f(x,y);
    }
    glEnd();

    // Eye White Left
    glColor3f(1,0,1);
    glBegin(GL_POLYGON);
    for(i=0;i<=360;i++){
        theta=i*3.1416/180;
        x=200+30*cos(theta);
        y=290+50*sin(theta);
        glVertex2f(x,y);
    }
    glEnd();

    // Eye White Right
    glBegin(GL_POLYGON);
    for(i=0;i<=360;i++){
        theta=i*3.1416/180;
        x=300+30*cos(theta);
        y=290+50*sin(theta);
        glVertex2f(x,y);
    }
    glEnd();

    // Pupil Left (LEFT-RIGHT motion)
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    for(i=0;i<=360;i++){
        theta=i*3.1416/180;

        x=(200 + r*cos(t)) + 10*cos(theta);   // horizontal movement
        y=290 + 20*sin(theta);                // fixed vertical

        glVertex2f(x,y);
    }
    glEnd();

    // Pupil Right (LEFT-RIGHT motion)
    glBegin(GL_POLYGON);
    for(i=0;i<=360;i++){
        theta=i*3.1416/180;

        x=(300 + r*cos(t)) + 10*cos(theta);   // horizontal movement
        y=290 + 20*sin(theta);

        glVertex2f(x,y);
    }
    glEnd();

    // Animation
    t = t+0.004;

    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Smiley Face Animation");

    glClearColor(1,1,1,1);
    gluOrtho2D(0,500,0,500);

    glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}