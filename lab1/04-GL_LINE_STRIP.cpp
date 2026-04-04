#include <GL/glut.h>

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(10);
    glColor3f(1, 0, 0);

    glBegin(GL_LINE_STRIP);          // Draw connected line segments (does NOT close automatically)
        glVertex2i(50, 250);         // First vertex
        glVertex2i(350, 250);        // Second vertex (line from first to second)
        glVertex2i(200, 400);        // Third vertex (line from second to third)  
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