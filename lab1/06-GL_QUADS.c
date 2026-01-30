#include <GL/glut.h>

void draw() {
    glClear(GL_COLOR_BUFFER_BIT); 
    glLineWidth(10);                  // Line width (not effective for filled shapes)
    glColor3f(0, 0, 1);

    // filled quadrilateral
    glBegin(GL_QUADS);                // Begin drawing a quadrilateral
        glVertex2i(50, 250);          // First vertex
        glVertex2i(350, 250);         // Second vertex
        glVertex2i(450, 400);         // Third vertex
        glVertex2i(200, 400);         // Fourth vertex
    glEnd();

    // filled triangle
    glBegin(GL_TRIANGLES);            // Begin drawing a filled triangle
        glVertex2i(50, 50);           // First vertex of triangle
        glVertex2i(350, 50);          // Second vertex of triangle
        glVertex2i(200, 200);         // Third vertex of triangle
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