#include <GL/glut.h>

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen
    glLineWidth(5);                // Set line thickness
    glColor3f(1,0,0);              // Set drawing color to red

    glBegin(GL_LINES);              // Each pair of vertices makes one line
        // vertical lines
        glVertex2i(100, 250);       // Left bottom
        glVertex2i(100, 450);       // Left top
        glVertex2i(250, 250);       // Right bottom
        glVertex2i(250, 450);       // Right top

        // horizontal lines
        glVertex2i(100, 450);       // Top left
        glVertex2i(250, 450);       // Top right
        glVertex2i(100, 250);       // Bottom left
        glVertex2i(250, 250);       // Bottom right

        // diagonal lines
        glVertex2i(100, 450);       // Top left
        glVertex2i(250, 250);       // Bottom right
        glVertex2i(100, 250);       // Bottom left
        glVertex2i(250, 450);       // Top right
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