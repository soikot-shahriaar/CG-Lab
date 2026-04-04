#include <GL/glut.h>
#include <math.h>

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    float i, x, y, theta;
    glColor3f(1, 0, 0);

    glBegin(GL_TRIANGLE_FAN);       // Draw filled shape using triangle fan
        glVertex2f(250, 250);       // Center of the circle

        for (i = 0; i <= 360; i++) {
            theta = i * 3.1416 / 180;

            // Calculate circle boundary points
            x = 250 + 100 * cos(theta); // Center X = 250, radius = 100
            y = 250 + 100 * sin(theta);

            glVertex2f(x, y);        // Add boundary vertex
        }
    glEnd();

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Filled Circle");
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}