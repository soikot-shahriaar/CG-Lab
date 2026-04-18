#include <windows.h>
#include <GL\glut.h>
#include <GL/glu.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// --- GLOBAL VARIABLES ---

GLint i;

// State Variables
bool isPlaying = false;

// Animation Offsets
GLfloat ax = 0, bx = 0;      // Clouds X-axis Movement
GLfloat spin = 0.0;          // Windmill Blades Rotation Angle
GLfloat plane_x = 850.0f;    // Airplane X-axis position
GLfloat sailboat_x = 250.0f; // Sailboat X-axis position

// --- INITIALIZATION ---

void init(void) {
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 1000.0, -280.0, 500.0); // X from 0 to 1000, Y from -280 to 500
}

// --- UTILITY DRAWING FUNCTIONS ---

// Midpoint Circle Algorithm (Filled using GL_QUADS)
void circle(GLdouble rad) {
    int r = (int)rad;
    int x = 0;
    int y = r;
    int p = 1 - r;

    glBegin(GL_QUADS);
    while (x <= y) { // Loops until X and Y cross (calculates 1/8th of the circle)
        // Draws a horizontal strip across the TOP of the circle
        glVertex2i(-x, y);      // Top strip - Left outer point
        glVertex2i(x, y);       // Top strip - Right outer point
        glVertex2i(x, y - 1);   // Top strip - Right inner point (1 pixel thick)
        glVertex2i(-x, y - 1);  // Top strip - Left inner point (1 pixel thick)
        // Draws a horizontal strip across the BOTTOM of the circle
        glVertex2i(-x, -y);     // Bottom strip - Left outer point
        glVertex2i(x, -y);      // Bottom strip - Right outer point
        glVertex2i(x, -y + 1);  // Bottom strip - Right inner point
        glVertex2i(-x, -y + 1); // Bottom strip - Left inner point
        // Draws a vertical strip across the UPPER SIDES of the circle
        glVertex2i(-y, x);      // Upper sides - Left outer point
        glVertex2i(y, x);       // Upper sides - Right outer point
        glVertex2i(y, x - 1);   // Upper sides - Right inner point
        glVertex2i(-y, x - 1);  // Upper sides - Left inner point
        // Draws a vertical strip across the LOWER SIDES of the circle
        glVertex2i(-y, -x);     // Lower sides - Left outer point
        glVertex2i(y, -x);      // Lower sides - Right outer point
        glVertex2i(y, -x + 1);  // Lower sides - Right inner point
        glVertex2i(-y, -x + 1); // Lower sides - Left inner point

        x++;                   // Always steps right in the X axis
        if (p < 0) {           // If the midpoint is INSIDE the circle border
            p = p + 2 * x + 1; // Update parameter (Y stays the same, move purely right)
        }
        else {                         // If the midpoint is OUTSIDE the circle border
            y--;                       // Step down in the Y axis (curve downwards)
            p = p + 2 * x - 2 * y + 1; // Update parameter for diagonal move
        }
    }
    glEnd();
}

// --- ENVIRONMENT MODELS ---

void draw_sky() {
    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.85f, 1.00f); // light-blue
    glVertex2i(0, 500);             // Top-left
    glVertex2i(1000, 500);          // Top-right
    glVertex2i(1000, -280);         // Bottom-right
    glVertex2i(0, -280);            // Bottom-left
    glEnd();
}

void Sun() {
    glColor3f(1.0f, 0.95f, 0.0f); // bright-yellow
    glPushMatrix();               // Saves the current coordinate system
    glTranslatef(500, 425, 0);    // Moves origin to X=500, Y=420 (Center top)
    circle(37);                   // Draws a circle with radius 37
    glPopMatrix();                // Restores the original coordinate system
}

void cloud_model() {
    glColor3f(1.25f, 0.924f, 0.930f); // off-white
    glPushMatrix();
    glTranslatef(300, 200, 0); // Bottom-left
    circle(15);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(320, 210, 0); // Mid-left
    circle(15);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(340, 220, 0); // Top-center
    circle(16);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(360, 210, 0); // Mid-right
    circle(15);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(380, 200, 0); // Bottom-right
    circle(15);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(360, 190, 0); // Lower-right
    circle(20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(320, 190, 0); // Lower-left
    circle(20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(340, 190, 0); // Lower-center
    circle(20);
    glPopMatrix();
}

void hill_big_model() {
    // Rocky Base
    glBegin(GL_POLYGON);
    glColor3ub(100, 105, 95);  // dark-gray
    glVertex2i(50, 70);        // Bottom-left
    glVertex2i(200, 300);      // Top peak
    glVertex2i(350, 70);       // Bottom-right
    glEnd();
    // Snow Cap
    glBegin(GL_POLYGON);
    glColor3ub(250, 250, 255); // snow-white
    glVertex2i(200, 300);      // Top-peak
    glVertex2i(240, 238);      // Right-edge
    glVertex2i(225, 225);      // Right-inner-curve
    glVertex2i(200, 240);      // Center-inner-curve
    glVertex2i(175, 225);      // Left-inner-curve
    glVertex2i(160, 238);      // Left-edge
    glEnd();
}

void hill_small_model() {
    // Rocky Base
    glBegin(GL_POLYGON);
    glColor3ub(80, 85, 90);    // medium-gray
    glVertex2i(200, 70);       // Bottom-left
    glVertex2i(310, 220);      // Top-peak
    glVertex2i(420, 70);       // Bottom-right
    glEnd();
    // Snow Cap
    glBegin(GL_POLYGON);
    glColor3ub(250, 250, 255); // snow-white
    glVertex2i(310, 220);      // Top-peak
    glVertex2i(340, 179);      // Right-edge
    glVertex2i(325, 165);      // Right-inner-curve
    glVertex2i(310, 180);      // Center-inner-curve
    glVertex2i(295, 165);      // Left-inner-curve
    glVertex2i(280, 179);      // Left-snow-edge
    glEnd();
}

void Tilla_One_Model() {
    glBegin(GL_POLYGON);
    glColor3ub(65, 175, 35); // green
    glVertex2i(125, 70);     // Bottom-left Start
    glVertex2i(150, 80);
    glVertex2i(160, 90);
    glVertex2i(170, 90);
    glVertex2i(180, 100);
    glVertex2i(190, 105);
    glVertex2i(200, 108);
    glVertex2i(300, 110);
    glVertex2i(300, 70);     // Down to Base
    glEnd();
}

void Tilla_Two_Model() {
    glBegin(GL_POLYGON);
    glColor3ub(65, 175, 35); // green
    glVertex2i(360, 70);     // Bottom-left Start
    glVertex2i(380, 85);
    glVertex2i(400, 105);
    glVertex2i(430, 120);    // Top-peak
    glVertex2i(455, 105);
    glVertex2i(475, 85);
    glVertex2i(505, 70);     // Bottom-right End
    glEnd();
}

void field() {
    // Top Flat Rectangle
    glBegin(GL_POLYGON);
    glColor3ub(65, 175, 35);   // green
    glVertex2i(0, 50);         // Bottom-left
    glVertex2i(0, 70);         // Top-left
    glVertex2i(1000, 70);      // Top-right
    glVertex2i(1000, 50);
    glEnd();

    // Wavy Riverbank
    glBegin(GL_QUAD_STRIP);
    glColor3ub(40, 130, 22);   // dark-Green
    glVertex2i(0, 50);         // Far Left edge
    glVertex2i(0, -10);
    glVertex2i(150, 50);       // First curve up
    glVertex2i(150, 10);
    glVertex2i(300, 50);       // Deep curve down
    glVertex2i(300, -15);
    glVertex2i(500, 50);       // Middle curve up
    glVertex2i(500, 5);
    glVertex2i(700, 50);       // Right curve down
    glVertex2i(700, -15);
    glVertex2i(850, 50);       // Far right curve up
    glVertex2i(850, 10);
    glVertex2i(1000, 50);      // Far Right edge
    glVertex2i(1000, -10);
    glEnd();
}

void draw_river() {
    glBegin(GL_QUAD_STRIP);
    glColor3ub(15, 70, 175);    // deep-blue
    glVertex2i(0, -10);         // Far Left edge
    glVertex2i(0, -210);
    glVertex2i(150, 10);        // First curve up
    glVertex2i(150, -190);
    glVertex2i(300, -15);       // Deep curve down
    glVertex2i(300, -215);
    glVertex2i(500, 5);         // Middle curve up
    glVertex2i(500, -195);
    glVertex2i(700, -15);       // Right curve down
    glVertex2i(700, -215);
    glVertex2i(850, 10);        // Far right curve up
    glVertex2i(850, -190);
    glVertex2i(1000, -10);      // Far Right edge
    glVertex2i(1000, -210);
    glEnd();
}

// --- ARCHITECTURE MODELS ---

void house() {
    // Roof
    glBegin(GL_POLYGON);
    glColor3ub(140, 65, 45);        // dark-brown
    glVertex2i(285, 105);           // Bottom-left
    glVertex2i(285, 130);           // Top-left
    glVertex2i(380, 115);           // Top-right
    glVertex2i(380, 105);           // Bottom-right
    glEnd();
    // Main Wall
    glBegin(GL_POLYGON);
    glColor3ub(230, 215, 185);      // beige
    glVertex2i(290, 70);            // Bottom-left
    glVertex2i(290, 104);           // Top-left
    glVertex2i(375, 104);           // Top-right
    glVertex2i(375, 70);            // Bottom-right
    glEnd();
    // Door
    glBegin(GL_POLYGON);
    glColor3ub(80, 50, 35);         // wooden
    glVertex2i(330, 70);            // Bottom-left
    glVertex2i(330, 100);           // Top-left
    glVertex2i(350, 100);           // Top-right
    glVertex2i(350, 70);            // Bottom-right
    glEnd();
    // Left Window
    glBegin(GL_POLYGON);
    glColor3ub(60, 40, 45);         // glass-color
    glVertex2i(295, 75);            // Bottom-left
    glVertex2i(295, 90);            // Top-left
    glVertex2i(310, 90);            // Top-right
    glVertex2i(310, 75);            // Bottom-right
    glEnd();
    // Middle Window
    glBegin(GL_POLYGON);
    glColor3ub(60, 40, 45);         // glass-color
    glVertex2i(312, 75);            // Bottom-left
    glVertex2i(312, 90);            // Top-left
    glVertex2i(327, 90);            // Top-right
    glVertex2i(327, 75);            // Bottom-right
    glEnd();
    // Right Window
    glBegin(GL_POLYGON);
    glColor3ub(60, 40, 45);         // glass-color
    glVertex2i(355, 75);            // Bottom-left
    glVertex2i(355, 90);            // Top-left
    glVertex2i(370, 90);            // Top-right
    glVertex2i(370, 75);            // Bottom-right
    glEnd();
    // Side Room Roof
    glBegin(GL_POLYGON);
    glColor3ub(160, 75, 50);        // brown
    glVertex2i(250, 90);            // Bottom-left
    glVertex2i(257, 104);           // Top-left
    glVertex2i(290, 104);           // Top-right
    glVertex2i(290, 90);            // Bottom-right
    glEnd();
    // Side Room Wall
    glBegin(GL_POLYGON);
    glColor3ub(210, 195, 165);      // beige
    glVertex2i(255, 70);            // Bottom-left
    glVertex2i(255, 90);            // Top-left
    glVertex2i(290, 90);            // Top-right
    glVertex2i(290, 70);            // Bottom-right
    glEnd();
    // Garage Door
    glBegin(GL_POLYGON);
    glColor3ub(70, 45, 35);         // dark-brown
    glVertex2i(260, 70);            // Bottom-left
    glVertex2i(260, 80);            // Top-left
    glVertex2i(285, 80);            // Top-right
    glVertex2i(285, 70);            // Bottom-right
    glEnd();
}

void Windmill_Blade() {
    glPushMatrix();
    // glRotatef(angle, x, y, z) --> Spins Object around Z-axis
    glRotatef(spin, 0, 0, 90);  // Blade 1
    glBegin(GL_POLYGON);
    glVertex2i(-5, 0);          // Center pivot point
    glVertex2i(-85, -36);       // Outer tip bottom
    glVertex2i(-83, -37);       // Outer tip edge
    glVertex2i(-3, -8);         // Inner edge
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glRotatef(spin, 0, 0, 90);  // Blade 2
    glBegin(GL_POLYGON);
    glVertex2i(0, 5);           // Center pivot point
    glVertex2i(45, 70);         // Outer tip right
    glVertex2i(50, 73);         // Outer tip edge
    glVertex2i(5, 0);           // Inner edge
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glRotatef(spin, 0, 0, 90);  // Blade 3
    glBegin(GL_POLYGON);
    glVertex2i(68, -78);        // Outer tip right
    glVertex2i(0, 0);           // Center pivot point
    glVertex2i(5, 5);           // Inner edge
    glVertex2i(70, -77);        // Outer tip edge
    glEnd();
    glPopMatrix();
}

void Windmill() {
    // Windmill Stand
    glColor3f(0.38, 0.41, 0.36); // grayish-green
    glBegin(GL_POLYGON);
    glVertex2i(375, 100);        // Bottom-left
    glVertex2i(380, 240);        // Top-left
    glVertex2i(384, 240);        // Top-right
    glVertex2i(390, 100);        // Bottom-right
    glEnd();
    glColor3f(0.11, 0.23, 0.36); // dark-blue
    // Center Circle
    glPushMatrix();
    glTranslatef(380, 250, 0);
    circle(10);
    glPopMatrix();
    // Rotating Blades
    glPushMatrix();
    glTranslatef(380, 251, 0);
    Windmill_Blade();
    glPopMatrix();
}

// --- TREE MODELS ---

// Small Round Tree
void Tree_Model_One() {
    // Rectangle Trunk
    glColor3ub(85, 50, 15);  // brown
    glBegin(GL_POLYGON);
    glVertex2i(-2, 0);
    glVertex2i(2, 0);
    glVertex2i(2, 20);
    glVertex2i(-2, 20);
    glEnd();
    // 2 Circles Leaf
    glColor3ub(30, 110, 18); // green-leaf
    glPushMatrix();
    glTranslatef(0, 20, 0);  // Bottom leaf circle
    circle(15);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 30, 0);  // Top leaf circle
    circle(15);
    glPopMatrix();
}

// Small Fluffy Tree
void Tree_Model_Two() {
    // Rectangle Trunk
    glColor3ub(85, 50, 15);  // brown
    glBegin(GL_POLYGON);
    glVertex2i(-2, 0);
    glVertex2i(2, 0);
    glVertex2i(2, 14);
    glVertex2i(-2, 14);
    glEnd();
    // 4 Circles Leaf
    glColor3ub(30, 110, 18); // green-leaf
    glPushMatrix();
    glTranslatef(0, 15, 0);  // Center leaf circle
    circle(8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-6, 16, 0); // Left leaf circle
    circle(8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(6, 16, 0);  // Right leaf circle
    circle(8);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 23, 0);  // Top leaf circle
    circle(8);
    glPopMatrix();
}

// Small Pine Tree
void Tree_Model_Three() {
    // Rectangle Trunk
    glColor3ub(85, 50, 15);  // brown
    glBegin(GL_POLYGON);
    glVertex2i(-2, 0);
    glVertex2i(2, 0);
    glVertex2i(2, 14);
    glVertex2i(-2, 14);
    glEnd();
    // Triangle pine leaf
    glColor3ub(30, 110, 18); // green-leaf
    glBegin(GL_POLYGON);
    glVertex2i(-9, 13);
    glVertex2i(9, 13);
    glVertex2i(0, 35);
    glEnd();
}

// Large Broad-leaf Tree
void Tree_Model_Four() {
    // Shaded Rectangular Trunk
    glColor3ub(85, 50, 15);     // brown
    glBegin(GL_POLYGON);        // Left half
    glVertex2i(-8, 0);
    glVertex2i(0, 0);
    glVertex2i(0, 50);
    glVertex2i(-8, 50);
    glEnd();
    glColor3ub(60, 32, 10);     // brown-shade
    glBegin(GL_POLYGON);        // Right half
    glVertex2i(0, 0);
    glVertex2i(8, 0);
    glVertex2i(8, 50);
    glVertex2i(0, 50);
    glEnd();
    // 3 Circles large Leaf
    glColor3ub(30, 110, 18);    // green-leaf
    glPushMatrix();
    glTranslatef(0, 70, 0);     // Top leaf circle
    circle(38);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-25, 45, 0);   // Left leaf circle
    circle(32);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(25, 45, 0);    // Right leaf circle
    circle(32);
    glPopMatrix();
}

// Medium Broad-leaf Tree
void Tree_Model_Five() {
    // Shaded Rectangular Trunk
    glColor3ub(85, 50, 15);     // brown
    glBegin(GL_POLYGON);        // Left half
    glVertex2i(-5, 0);
    glVertex2i(0, 0);
    glVertex2i(0, 30);
    glVertex2i(-5, 30);
    glEnd();
    glColor3ub(60, 32, 10);     // brown-shade
    glBegin(GL_POLYGON);        // Right half
    glVertex2i(0, 0);
    glVertex2i(5, 0);
    glVertex2i(5, 30);
    glVertex2i(0, 30);
    glEnd();
    // 3 Circles medium-large Leaf
    glColor3ub(30, 110, 18);    // green-leaf
    glPushMatrix();
    glTranslatef(0, 42, 0);     // Top leaf circle
    circle(23);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-15, 27, 0);   // Left leaf circle
    circle(19);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(15, 27, 0);    // Right leaf circle
    circle(19);
    glPopMatrix();
}

// --- VEHICLES ---

void draw_sailboat() {
    float baseY = -95.0f;    // Boat's Vertical Position
    glPushMatrix();
    glTranslatef(sailboat_x, baseY, 0.0f);
    glScalef(1.0f, 1.0f, 1.0f);

    // Boat Hull
    glBegin(GL_POLYGON);
    glColor3ub(120, 72, 30); // brown
    glVertex2i(-95, 0);      // Top-left
    glVertex2i(-75, -35);    // Bottom-left
    glVertex2i(75, -35);     // Bottom-right
    glVertex2i(95, 0);       // Top-right
    glEnd();
    // Top Rim
    glBegin(GL_POLYGON);
    glColor3ub(200, 50, 50); // red
    glVertex2i(-95, 0);      // Bottom-left
    glVertex2i(-95, -10);    // Top-left
    glVertex2i(95, -10);     // Top-right
    glVertex2i(95, 0);       // Bottom-right
    glEnd();
    // Center Pole
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(90, 55, 18);  // dark-brown
    glVertex2i(5, 5);        // Bottom
    glVertex2i(5, 145);      // Top
    glEnd();
    glLineWidth(1.0f);
    // Yellow Sail
    glBegin(GL_TRIANGLES);
    glColor3ub(245, 210, 70);// yellow
    glVertex2i(5, 8);        // Bottom-right
    glVertex2i(5, 140);      // Top
    glVertex2i(-75, 14);     // Far-left
    glEnd();
    // Orange Sail
    glBegin(GL_TRIANGLES);
    glColor3ub(230, 130, 50);// orange
    glVertex2i(5, 110);      // Top point
    glVertex2i(5, 8);        // Bottom-left
    glVertex2i(70, 18);      // Far-right
    glEnd();

    glPopMatrix();
}

void draw_plane() {
    float baseY = 365.0f;        // Plane's Vertical Position
    glPushMatrix();
    glTranslatef(plane_x, baseY, 0.0f);
    glScalef(-1.0f, 1.0f, 1.0f); // Flips the Plane Horizontally

    // Main Body
    glBegin(GL_POLYGON);
    glColor3ub(245, 245, 250); // white
    glVertex2i(-55, -3);       // Bottom-left
    glVertex2i(35, -3);        // Bottom-right
    glVertex2i(55, 5);         // Aerodynamic Nose Tip
    glVertex2i(40, 15);        // Top-right
    glVertex2i(-50, 15);       // Top-left
    glEnd();
    // Cockpit Window
    glBegin(GL_POLYGON);
    glColor3ub(100, 200, 255); // light-blue
    glVertex2i(25, 15);        // Bottom-left
    glVertex2i(40, 15);        // Bottom-right
    glVertex2i(50, 8);         // Top-right
    glVertex2i(25, 8);         // Top-left
    glEnd();
    // Main Wing
    glBegin(GL_POLYGON);
    glColor3ub(220, 40, 40); // red
    glVertex2i(-10, 3);      // Top-left
    glVertex2i(25, 3);       // Top-right
    glVertex2i(5, -25);      // Bottom-right
    glVertex2i(-20, -25);    // Bottom-left
    glEnd();
    // Tail Fin
    glBegin(GL_POLYGON);
    glColor3ub(220, 40, 40); // red
    glVertex2i(-45, 15);     // Bottom-right
    glVertex2i(-35, 35);     // Top-right
    glVertex2i(-50, 35);     // Top-left
    glVertex2i(-55, 15);     // Bottom-left
    glEnd();

    glPopMatrix();
}

// --- TERRAIN ---

void village_road() {
    glColor3ub(180, 135, 85); // Dirt Brown color
    // Main Rectangle Road
    glBegin(GL_POLYGON);
    glVertex2i(0, 52);        // Bottom-left
    glVertex2i(1000, 52);     // Bottom-right
    glVertex2i(1000, 65);     // Top-right
    glVertex2i(0, 65);        // Top-left
    glEnd();
    // Road to House 1
    glBegin(GL_POLYGON);
    glVertex2i(330, 65);
    glVertex2i(350, 65);
    glVertex2i(350, 70);
    glVertex2i(330, 70);
    glEnd();
    // Road to House 2
    glBegin(GL_POLYGON);
    glVertex2i(780, 65);
    glVertex2i(800, 65);
    glVertex2i(800, 70);
    glVertex2i(780, 70);
    glEnd();
    // Road up to Hill House
    glBegin(GL_POLYGON);
    glVertex2i(555, 65);
    glVertex2i(585, 65);
    glVertex2i(605, 107);
    glVertex2i(580, 107);
    glEnd();
    // Road to House 4
    glBegin(GL_POLYGON);
    glVertex2i(80, 65);
    glVertex2i(100, 65);
    glVertex2i(100, 70);
    glVertex2i(80, 70);
    glEnd();
    // Road to Right House
    glBegin(GL_POLYGON);
    glVertex2i(960, 65);
    glVertex2i(980, 65);
    glVertex2i(980, 70);
    glVertex2i(960, 70);
    glEnd();
}

void draw_bottom_field() {
    // Top Wavy Part
    glBegin(GL_POLYGON);
    glColor3ub(65, 175, 35);    // Bright-green Color
    glVertex2i(0, -280);        // Bottom-left
    glVertex2i(0, -210);
    glVertex2i(150, -190);
    glVertex2i(300, -215);
    glVertex2i(500, -195);
    glVertex2i(700, -215);
    glVertex2i(850, -190);
    glVertex2i(1000, -210);
    glVertex2i(1000, -280);     // Bottom-right
    glEnd();

    // Dirt Path
    glBegin(GL_POLYGON);
    glColor3ub(180, 135, 85);   // Dirt-brown Color
    glVertex2i(250, -280);      // Bottom-left
    glVertex2i(340, -280);      // Bottom-right
    glVertex2i(310, -215);      // Top-right
    glVertex2i(270, -210);      // Top-left
    glEnd();

    // Wooden Fence Posts(12)
    glColor3ub(120, 70, 40);
    glBegin(GL_QUADS);
    for (int i = 400; i <= 950; i += 50) {
        glVertex2i(i, -275);
        glVertex2i(i + 8, -275);
        glVertex2i(i + 8, -240);
        glVertex2i(i, -240);
    }
    glEnd();
    // Wooden Fence Rails(2)
    glBegin(GL_QUADS);
    glVertex2i(400, -250);      // Upper Rail
    glVertex2i(950, -250);
    glVertex2i(950, -246);
    glVertex2i(400, -246);
    glVertex2i(400, -265);      // Lower Rail
    glVertex2i(950, -265);
    glVertex2i(950, -261);
    glVertex2i(400, -261);
    glEnd();
}

// --- SCENE INSTANCES (POSITIONING MODELS) ---

// Clouds
void cloud_one() {   // Upper Cloud
    glPushMatrix();
    glTranslatef(ax + 150, 150, 0);
    cloud_model();
    glPopMatrix();
}

void cloud_two() {   // Lower Cloud
    glPushMatrix();
    glTranslatef(bx + 350, 180, 0);
    cloud_model();
    glPopMatrix();
}

// Hills
void Hill_Big_One() {  // Left Large Hill
    glPushMatrix();
    glTranslatef(0, -10, 0);
    hill_big_model();
    glPopMatrix();
}

void Hill_Big_Two() {  // Right Large Hill
    glPushMatrix();
    glTranslatef(550, -30, 0);
    hill_big_model();
    glPopMatrix();
}

void Hill_Small_One() { // Left Small Hill
    glPushMatrix();
    glTranslatef(-25, 0, 0);
    hill_small_model();
    glPopMatrix();
}

// Tillas
void Tilla_One() {      // Far Left Tilla
    glPushMatrix();
    glTranslatef(0, 0, 0);
    Tilla_One_Model();
    glPopMatrix();
}

void Tilla_Two() {      // Center-left Bumpy Tilla
    glPushMatrix();
    glTranslatef(0, 0, 0);
    Tilla_Two_Model();
    glPopMatrix();
}

void Tilla_Three() {     // Center-right Tilla
    glPushMatrix();
    glTranslatef(380, 0, 0);
    Tilla_One_Model();
    glPopMatrix();
}

// Houses
void house_one() {   // Middle-left House
    glPushMatrix();
    glTranslatef(0, 0, 0);
    house();
    glPopMatrix();
}

void house_two() {   // Center House
    glPushMatrix();
    glTranslatef(450, 0, 0);
    house();
    glPopMatrix();
}

void house_three() {  // Tilla House
    glPushMatrix();
    glTranslatef(320, 37, 0);
    house();
    glPopMatrix();
}

void house_four() {   // Far Left House
    glPushMatrix();
    glTranslatef(-250, 0, 0);
    house();
    glPopMatrix();
}

void house_five() {   // Far Right House
    glPushMatrix();
    glTranslatef(630, 0, 0);
    house();
    glPopMatrix();
}

// Windmills
void Windmill_One() {   // Left Windmill
    glPushMatrix();
    glTranslatef(0, -10, 0);
    Windmill();
    glPopMatrix();
}

void Windmill_Two() {   // Right Windmill
    glPushMatrix();
    glTranslatef(508, -70, 0);
    Windmill();
    glPopMatrix();
}

void Windmill_Three() { // Center Windmill
    glPushMatrix();
    glTranslatef(108, -90, 0);
    Windmill();
    glPopMatrix();
}

// Small Trees (Upper-side)
void Tree_One() {       // Round Tree
    glPushMatrix();
    glTranslatef(135, 75, 0);
    Tree_Model_One();
    glPopMatrix();
}

void Tree_Two() {       // Pine Tree
    glPushMatrix();
    glTranslatef(165, 92, 0);
    Tree_Model_Three();
    glPopMatrix();
}

void Tree_Three() {     // Pine Tree
    glPushMatrix();
    glTranslatef(190, 105, 0);
    Tree_Model_Three();
    glPopMatrix();
}

void Tree_Four() {      // Round Tree
    glPushMatrix();
    glTranslatef(395, 67, 0);
    Tree_Model_One();
    glPopMatrix();
}

void Tree_Five() {      // Fluffy Tree
    glPushMatrix();
    glTranslatef(440, 108, 0);
    Tree_Model_Two();
    glPopMatrix();
}

void Tree_Six() {       // Fluffy Tree
    glPushMatrix();
    glTranslatef(470, 82, 0);
    Tree_Model_Two();
    glPopMatrix();
}

void Tree_Seven() {     // Round Tree
    glPushMatrix();
    glTranslatef(610, 70, 0);
    Tree_Model_One();
    glPopMatrix();
}

void Tree_Eight() {     // Fluffy Tree
    glPushMatrix();
    glTranslatef(690, 70, 0);
    Tree_Model_Two();
    glPopMatrix();
}

void Tree_Nine() {      // Round Tree
    glPushMatrix();
    glTranslatef(880, 70, 0);
    Tree_Model_One();
    glPopMatrix();
}

// Large Trees (Lower-side)
void Fore_Tree_One() {  // Far Left
    glPushMatrix();
    glTranslatef(55, -230, 0);
    Tree_Model_Four();
    glPopMatrix();
}

void Fore_Tree_Two() {  // Mid Left
    glPushMatrix();
    glTranslatef(208, -260, 0);
    Tree_Model_Four();
    glPopMatrix();
}

void Fore_Tree_Three() { // Center
    glPushMatrix();
    glTranslatef(380, -270, 0);
    Tree_Model_Four();
    glPopMatrix();
}

void Fore_Tree_Four() { // Mid Right
    glPushMatrix();
    glTranslatef(570, -240, 0);
    Tree_Model_Four();
    glPopMatrix();
}

void Fore_Tree_Five() { // Right
    glPushMatrix();
    glTranslatef(685, -270, 0);
    Tree_Model_Four();
    glPopMatrix();
}

void Fore_Tree_Six() {  // Far Right
    glPushMatrix();
    glTranslatef(820, -237, 0);
    Tree_Model_Four();
    glPopMatrix();
}

void Fore_Tree_Seven() { // Edge Right
    glPushMatrix();
    glTranslatef(930, -270, 0);
    Tree_Model_Four();
    glPopMatrix();
}

void Bush_One() {        // Left
    glPushMatrix();
    glTranslatef(120, -275, 0);
    Tree_Model_Five();
    glPopMatrix();
}

void Bush_Two() {        // Lower-middle
    glPushMatrix();
    glTranslatef(490, -285, 0);
    Tree_Model_Five();
    glPopMatrix();
}

void Bush_Three() {      // Upper-middle
    glPushMatrix();
    glTranslatef(470, -220, 0);
    Tree_Model_Five();
    glPopMatrix();
}

void Bush_Four() {       // Right
    glPushMatrix();
    glTranslatef(777, -287, 0);
    Tree_Model_Five();
    glPopMatrix();
}

// --- MAIN DISPLAY FUNCTION ---

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    draw_sky();
    Sun();
    Windmill_Three();
    Hill_Big_One();
    Tilla_Two();
    Tilla_Three();
    house_three();
    Hill_Big_Two();
    Hill_Small_One();
    cloud_one();
    cloud_two();
    Windmill_One();
    Windmill_Two();
    field();
    village_road();
    Tilla_One();
    house_one();
    house_two();
    house_four();
    house_five();
    draw_plane();

    Tree_One();
    Tree_Two();
    Tree_Three();
    Tree_Four();
    Tree_Five();
    Tree_Six();
    Tree_Seven();
    Tree_Eight();
    Tree_Nine();

    draw_river();
    draw_sailboat();

    draw_bottom_field();
    Fore_Tree_One();
    Fore_Tree_Two();
    Fore_Tree_Three();
    Fore_Tree_Four();
    Fore_Tree_Five();
    Fore_Tree_Six();
    Fore_Tree_Seven();
    Bush_One();
    Bush_Two();
    Bush_Three();
    Bush_Four();

    glFlush();
}

// --- ANIMATION ---

void move_func() {
    // Windmills Rotation
    spin -= 0.15f;

    // Clouds Animation (Left-Right)
    ax += 0.10f;        // Lower Cloud
    if (ax > 1000)
        ax = -600;
    bx += 0.12f;        // Upper Cloud
    if (bx > 1000)
        bx = -800;

    // Plane Animation (Right-Left)
    plane_x -= 0.25f;
    if (plane_x < -250.0f) {
        plane_x = 1250.0f;
    }

    // Boat Animation (Left-Right)
    sailboat_x += 0.20f;
    if (sailboat_x > 1250.0f) {
        sailboat_x = -250.0f;
    }

    glutPostRedisplay();  // Calls display() again
}

// --- INPUT / CONTROLS ---

void keyboard(unsigned char key, int x, int y) {
    if (key == ' ') {           // Spacebar
        isPlaying = !isPlaying; // Switch the State

        if (isPlaying)
            glutIdleFunc(move_func);
        else
            glutIdleFunc(NULL);
    }
}

// --- MAIN FUNCTION ---

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(1200, 750);
    glutCreateWindow("Smart Village Project");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
