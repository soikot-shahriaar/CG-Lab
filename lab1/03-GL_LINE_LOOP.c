#include <GL/glut.h>

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(15);
    glColor3f(1, 0, 0);

    glBegin(GL_LINE_LOOP);           // Start drawing connected lines and close the shape
        glVertex2i(50, 250);         // First vertex of the triangle
        glVertex2i(350, 250);        // Second vertex of the triangle
        glVertex2i(200, 400);        // Third vertex of the triangle
    glEnd();
    
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("First Lab");
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}