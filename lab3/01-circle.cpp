#include <GL/glut.h>
#include <math.h>

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    float i, x, y, theta;
    for (i = 0; i <= 360; i++) {  // Loop through angles from 0 to 360 degrees
        theta = i * 3.1416 / 180; // Convert angle from degrees to radians

        // Calculate X and Y coordinates of the circle using parametric equations
        x = 250 + 100 * cos(theta); // Center X = 250, radius = 100
        y = 250 + 100 * sin(theta);

        glPointSize(5);
        glColor3f(1, 0, 0);
        glBegin(GL_POINTS);
            glVertex2i(x, y);
        glEnd();
    }
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Circle");
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}

/* The program uses the parametric equations of a circle:
x = h + r cos(θ)
y = k + r sin(θ)
where (h,k) is the center and r is the radius.

In this code:
Center = (250,250)
Radius = 100
θ varies from 0° to 360°
*/