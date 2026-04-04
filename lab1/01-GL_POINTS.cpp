#include <GL/glut.h>   // Include the GLUT library for OpenGL windowing and input

// Function that draws on the screen
void draw() {
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the window using the current background color
    glPointSize(10);                // Set the size of the point (in pixels)
    glColor3f(1, 0, 0);             // Set drawing color to red (R=1, G=0, B=0)
    
    glBegin(GL_POINTS);             // Start drawing points
        glVertex2i(250, 250);       // Specify the position of the point (x=250, y=250)
    glEnd();                        // End drawing
    
    glFlush();                      // Force OpenGL to execute all drawing commands
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);          // Initialize GLUT library
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Use single buffer and RGB color mode
    glutInitWindowSize(500, 500);   // Set window size to 500x500 pixels
    glutCreateWindow("First Lab");  // Create a window with title "First Lab"
    glClearColor(1, 1, 1, 1);       // Set background color to white (RGBA)
    gluOrtho2D(0, 500, 0, 500);     // Define a 2D coordinate system from (0,0) to (500,500)
    glutDisplayFunc(draw);          // Register the draw function to display callback
    glutMainLoop();                 // Enter the GLUT event-processing loop
    return 0;                       // End program (never reached due to main loop)
}