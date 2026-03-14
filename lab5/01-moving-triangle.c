#include <GL/glut.h>

float x = 40, i = 0.3; // x = horizontal position of the triangle
                       // i = speed and direction of movement
void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw Triangle
    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2i(x, 250);
    glVertex2i(100 + x, 250);
    glVertex2i(50 + x, 400);
    glEnd();

    // Movement Logic
    if (x <= 50)
        i = 0.3; // If triangle reaches the left boundary, change direction to move right
    if (x >= 350)
        i = -0.3; // If triangle reaches the right boundary, change direction to move left
    x = x + i;    // Update the triangle position each frame

    // Draw Rectangle
    glColor3f(0, 0, 1);
    glBegin(GL_QUADS);
    glVertex2i(150, 20);
    glVertex2i(400, 20);
    glVertex2i(400, 200);
    glVertex2i(150, 200);
    glEnd();

    glFlush(); // Forces OpenGL to execute drawing commands immediately

    glutSwapBuffers(); // Swap back buffer with front buffer (for smooth animation)

    glutPostRedisplay(); // Requests the window to redraw again to create continuous animation
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Moving Triangle Animation");
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}