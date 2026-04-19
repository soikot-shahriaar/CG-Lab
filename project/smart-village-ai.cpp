#include <windows.h>
#include <GL\glut.h>
#include <GL/glu.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define PI 3.1416

// --- GLOBAL VARIABLES ---

GLint i;

// State Variables
GLfloat day_angle = PI / 2.0f; // Starts at PI/2 (Daytime)
bool isDay = true;             // Day/Night toggle state
bool isPlaying = false;        // Play/Pause animation state
GLfloat anim_speed = 1.0f;     // Speed multiplier for all animations

// Animation Offsets
GLfloat ax = 0, bx = 0, cx = 0, dx = 0; // Cloud X-axis positions
GLfloat spin = 0.0;                     // Windmill blade rotation angle
GLfloat position6 = 100.0f;             // Airplane X-axis position
GLfloat motorboat_x = 1000.0f;          // Motorboat X-axis position
GLfloat sailboat_x = 650.0f;            // Sailboat X-axis position
GLfloat wave_offset = 0.0f;             // River wave scrolling offset

// --- INITIALIZATION ---

void init(void)
{
    glMatrixMode(GL_PROJECTION);
    // Sets the 2D viewing area: X from 0 to 1000, Y from -280 to 500
    gluOrtho2D(0.0, 1000.0, -280.0, 500.0);
}

// --- UTILITY DRAWING FUNCTIONS ---

// Standard circle drawing using trigonometric functions
void circle(GLdouble rad) {
    GLint points = 50;
    GLdouble delTheta = (2.0 * PI) / (GLdouble)points;
    GLdouble theta = 0.0;

    glBegin(GL_POLYGON);
    for (i = 0; i <= points; i++, theta += delTheta) {
        glVertex2f(rad * cos(theta), rad * sin(theta));
    }
    glEnd();
}

// Midpoint Circle Algorithm using GL_QUADS
void midpoint_circle(int r) {
    int x = 0;
    int y = r;
    int p = 1 - r;

    glBegin(GL_QUADS);
    while (x <= y) {
        // Draw 1-unit thick rectangles connecting symmetric points
        glVertex2i(-x, y); // Top
        glVertex2i(x, y);
        glVertex2i(x, y - 1);
        glVertex2i(-x, y - 1); 
        glVertex2i(-x, -y); // Bottom
        glVertex2i(x, -y);
        glVertex2i(x, -y + 1);
        glVertex2i(-x, -y + 1); 
        glVertex2i(-y, x); // Upper Mid
        glVertex2i(y, x);
        glVertex2i(y, x - 1);
        glVertex2i(-y, x - 1); 
        glVertex2i(-y, -x); // Lower Mid
        glVertex2i(y, -x);
        glVertex2i(y, -x + 1);
        glVertex2i(-y, -x + 1); 

        x++;
        if (p < 0) {
            p = p + 2 * x + 1;
        }
        else {
            y--;
            p = p + 2 * x - 2 * y + 1;
        }
    }
    glEnd();
}

// --- BASE MODELS (SHAPES & COLORS) ---

// Environment
void draw_sky_gradient() {
    // Calculates a value 't' between 0.0 (Night) and 1.0 (Day) based on angle
    float t = (sin(day_angle) + 1.0f) / 2.0f;

    // Interpolate colors based on 't'
    float tr = 0.05f + t * (0.15f - 0.05f), tg = 0.05f + t * (0.45f - 0.05f), tb = 0.20f + t * (0.90f - 0.20f); // Top Sky
    float br = 0.05f + t * (0.55f - 0.05f), bg = 0.05f + t * (0.85f - 0.05f), bb = 0.15f + t * (1.00f - 0.15f); // Bottom Sky

    glShadeModel(GL_SMOOTH); // Enables smooth blending
    glBegin(GL_QUADS);
    glColor3f(tr, tg, tb);
    glVertex2f(0.0f, 500.0f);
    glVertex2f(1000.0f, 500.0f);
    glColor3f(br, bg, bb);
    glVertex2f(1000.0f, -280.0f);
    glVertex2f(0.0f, -280.0f);
    glEnd();
    glShadeModel(GL_FLAT);
}

void Sun_Model() {
    glPushMatrix();
    glTranslatef(850, 420, 0);
    midpoint_circle(35); // Uses Midpoint Circle Algorithm
    glPopMatrix();
}

void Sun() {
    // Calculates Sun/Moon color (Yellow/White) based on Day/Night angle
    float t = (sin(day_angle) + 1.0f) / 2.0f;
    float sr = 0.8f + t * (1.0f - 0.8f);
    float sg = 0.8f + t * (0.95f - 0.8f);
    float sb = 0.9f + t * (0.0f - 0.9f);
    
    glColor3f(sr, sg, sb);
    Sun_Model();
}

// Clouds
void cloud_model_one() {
    glColor3f(1.25f, 0.924f, 0.930f);
    glPushMatrix();
    glTranslatef(320, 210, 0);
    circle(15);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(340, 225, 0);
    circle(16);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(360, 210, 0);
    circle(16);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(355, 210, 0);
    circle(16);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(350, 210, 0);
    circle(16);
    glPopMatrix();
    // Cloud Base Filler
    for (int i = 305; i <= 345; i += 5) {
        glPushMatrix();
        glTranslatef(i, 204, 0);
        circle(10);
        glPopMatrix();
    }
}

void cloud_model_Two() {
    glColor3f(1.25f, 0.924f, 0.930f);
    glPushMatrix();
    glTranslatef(305, 205, 0);
    circle(10);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(320, 210, 0);
    circle(15);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(334, 207, 0);
    circle(10);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(320, 207, 0);
    circle(10);
    glPopMatrix();
}

void cloud_model_Three() {
    glColor3f(1.25f, 0.924f, 0.930f);
    glPushMatrix();
    glTranslatef(300, 200, 0);
    circle(15);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(320, 210, 0);
    circle(15);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(340, 220, 0);
    circle(16);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(360, 210, 0);
    circle(15);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(380, 200, 0);
    circle(15);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(360, 190, 0);
    circle(20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(320, 190, 0);
    circle(20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(340, 190, 0);
    circle(20);
    glPopMatrix();
}

// Hills/Mountains
void hill_big() {
    glBegin(GL_POLYGON);
    glColor3ub(100, 105, 95); // Rocky Base
    glVertex2i(50, 70);
    glVertex2i(200, 300);
    glVertex2i(350, 70);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(250, 250, 255); // Snow Cap
    glVertex2i(200, 300);
    glVertex2i(240, 238);
    glVertex2i(225, 225);
    glVertex2i(200, 240);
    glVertex2i(175, 225);
    glVertex2i(160, 238);
    glEnd();
}

void hill_small() {
    glBegin(GL_POLYGON);
    glColor3ub(80, 85, 90); // Rocky Base
    glVertex2i(200, 70);
    glVertex2i(310, 220);
    glVertex2i(420, 70);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(250, 250, 255); // Snow Cap
    glVertex2i(310, 220);
    glVertex2i(340, 179);
    glVertex2i(325, 165);
    glVertex2i(310, 180);
    glVertex2i(295, 165);
    glVertex2i(280, 179);
    glEnd();
}

//  Landscape
void Tilla_One_Model() {
    glBegin(GL_POLYGON);
    glColor3ub(65, 175, 35);
    glVertex2i(125, 70);
    glVertex2i(150, 80);
    glVertex2i(160, 90);
    glVertex2i(170, 90);
    glVertex2i(180, 100);
    glVertex2i(190, 105);
    glVertex2i(200, 108);
    glVertex2i(300, 110);
    glVertex2i(300, 70);
    glEnd();
}

void Tilla_Two_Model() {
    glColor3ub(65, 175, 35);
    glPushMatrix();
    glTranslatef(430, 90, 0);
    circle(30);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(420, 87, 0);
    circle(30);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(410, 80, 0);
    circle(30);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(400, 80, 0);
    circle(30);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(390, 70, 0);
    circle(30);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(445, 80, 0);
    circle(30);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(455, 75, 0);
    circle(30);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(465, 70, 0);
    circle(30);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(470, 65, 0);
    circle(30);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(480, 60, 0);
    circle(30);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(485, 55, 0);
    circle(20);
    glPopMatrix();
}

// Houses
void house() {
    // Roofs
    glBegin(GL_POLYGON);
    glColor3ub(140, 65, 45);
    glVertex2i(285, 105);
    glVertex2i(285, 130);
    glVertex2i(380, 115);
    glVertex2i(380, 105);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(110, 45, 30);
    glVertex2i(285, 105);
    glVertex2i(285, 120);
    glVertex2i(380, 105);
    glVertex2i(380, 105);
    glEnd(); 
    // Main Wall
    glBegin(GL_POLYGON);
    glColor3ub(230, 215, 185);
    glVertex2i(290, 70);
    glVertex2i(290, 104);
    glVertex2i(375, 104);
    glVertex2i(375, 70);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(200, 185, 155);
    glVertex2i(310, 70);
    glVertex2i(350, 104);
    glVertex2i(375, 104);
    glVertex2i(375, 70);
    glEnd(); 
    // Door & Windows
    glBegin(GL_POLYGON);
    glColor3ub(80, 50, 35);
    glVertex2i(330, 70);
    glVertex2i(330, 100);
    glVertex2i(350, 100);
    glVertex2i(350, 70);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(60, 40, 45);
    glVertex2i(295, 75);
    glVertex2i(295, 90);
    glVertex2i(310, 90);
    glVertex2i(310, 75);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(60, 40, 45);
    glVertex2i(312, 75);
    glVertex2i(312, 90);
    glVertex2i(327, 90);
    glVertex2i(327, 75);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(60, 40, 45);
    glVertex2i(355, 75);
    glVertex2i(355, 90);
    glVertex2i(370, 90);
    glVertex2i(370, 75);
    glEnd();
    // Attached Side Room
    glBegin(GL_POLYGON);
    glColor3ub(160, 75, 50);
    glVertex2i(250, 90);
    glVertex2i(257, 104);
    glVertex2i(290, 104);
    glVertex2i(290, 90);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(210, 195, 165);
    glVertex2i(255, 70);
    glVertex2i(255, 90);
    glVertex2i(290, 90);
    glVertex2i(290, 70);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(70, 45, 35);
    glVertex2i(260, 70);
    glVertex2i(260, 80);
    glVertex2i(285, 80);
    glVertex2i(285, 70);
    glEnd();
}

// Windmills
void Windmill_Stand_Model() {
    // Base
    glBegin(GL_POLYGON);
    glColor3ub(160, 100, 80);
    glVertex2i(350, 100);
    glVertex2i(365, 240);
    glVertex2i(395, 240);
    glVertex2i(410, 100);
    glEnd();

    // Wooden Dome
    glColor3ub(80, 50, 35);
    glPushMatrix();
    glTranslatef(380, 240, 0);
    circle(18);
    glPopMatrix();
}

// Single Blade
void draw_single_blade(float angle_offset) {
    glPushMatrix();
    // Rotate specific blade based on the animation spin + its offset
    glRotatef(spin + angle_offset, 0, 0, 1);

    // Wooden Arm Structure
    glColor3ub(90, 55, 30);
    glBegin(GL_POLYGON);
    glVertex2i(-3, 0);
    glVertex2i(3, 0);
    glVertex2i(3, 85);
    glVertex2i(-3, 85);
    glEnd();
    // Canvas Sail Attached to Arm
    glColor3ub(240, 235, 220);
    glBegin(GL_POLYGON);
    glVertex2i(3, 15);
    glVertex2i(25, 15);
    glVertex2i(25, 80);
    glVertex2i(3, 80);
    glEnd();
    // Outer Wooden Frame for Sail
    glColor3ub(100, 60, 35);
    glBegin(GL_LINE_LOOP);
    glVertex2i(3, 15);
    glVertex2i(25, 15);
    glVertex2i(25, 80);
    glVertex2i(3, 80);
    glEnd();

    glPopMatrix();
}

void Windmill_Blades() {
    // 4 Blades
    draw_single_blade(0.0f);   // Blade 1 (Top)
    draw_single_blade(90.0f);  // Blade 2 (Left)
    draw_single_blade(180.0f); // Blade 3 (Bottom)
    draw_single_blade(270.0f); // Blade 4 (Right)
}

void Windmill() {
    glPushMatrix();
    Windmill_Stand_Model();
    glPopMatrix();

    // Center Peg for Blades
    glColor3ub(50, 30, 20);
    glPushMatrix();
    glTranslatef(380, 245, 0);
    circle(8);
    glPopMatrix();

    // Blades Attach at Top
    glPushMatrix();
    glTranslatef(380, 245, 0);
    Windmill_Blades();
    glPopMatrix();
}

// Small Trees
void Tree_Model_One() { // Round dual-bush tree
    glColor3ub(30, 110, 18);
    glPushMatrix();
    glTranslatef(110, 110, 0);
    circle(15);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(110, 100, 0);
    circle(15);
    glPopMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(85, 50, 15);
    glVertex2f(109, 70);
    glVertex2f(109, 90);
    glVertex2f(111, 90);
    glVertex2f(111, 70);
    glEnd();
}

void Tree_Model_Two() { // Multi-circle fluffy tree
    glColor3ub(30, 110, 18);
    glPushMatrix();
    glTranslatef(130, 130, 0);
    circle(5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(125, 126, 0);
    circle(5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(135, 126, 0);
    circle(5);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(130, 125, 0);
    circle(5);
    glPopMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(85, 50, 15);
    glVertex2f(129, 110);
    glVertex2f(129, 124);
    glVertex2f(131, 124);
    glVertex2f(131, 110);
    glEnd();
}

void Tree_Model_Three() { // Sharp Pine tree
    glColor3ub(30, 110, 18);
    glBegin(GL_POLYGON);
    glVertex2f(125, 123);
    glVertex2f(133, 145);
    glVertex2f(141, 123);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(85, 50, 15);
    glVertex2f(132, 110);
    glVertex2f(132, 124);
    glVertex2f(134, 124);
    glVertex2f(134, 110);
    glEnd();
}

// --- SCENE INSTANCES ---

// Clouds (Using Variables ax, bx, cx, dx to Animate Horizontally)
void cloud_one() { // Lower middle cloud
    glPushMatrix();
    glTranslatef(cx, -40, 0);       
    cloud_model_one();
    glPopMatrix();
}
void cloud_two() { // High right cloud
    glPushMatrix();
    glTranslatef(bx + 100, 150, 0); 
    cloud_model_one();
    glPopMatrix();
}
void cloud_three() { // Mid-left cloud
    glPushMatrix();
    glTranslatef(ax - 80, 80, 0);   
    cloud_model_Two();
    glPopMatrix();
}
void cloud_four() { // Far right cloud
    glPushMatrix();
    glTranslatef(dx + 300, 125, 0); 
    cloud_model_Two();
    glPopMatrix();
}
void cloud_five() { // High left cloud
    glPushMatrix();
    glTranslatef(ax - 300, 170, 0); 
    cloud_model_Three();
    glPopMatrix();
}
void cloud_six() { // Far left low cloud
    glPushMatrix();
    glTranslatef(cx - 500, 20, 0);  
    cloud_model_Three();
    glPopMatrix();
}

// Houses 
void house_one() { // Ground level, center-left
    glPushMatrix();
    glTranslatef(0, 0, 0);          
    house();
    glPopMatrix();
}
void house_two() {  // Ground level, center-right
    glPushMatrix();
    glTranslatef(450, 0, 0);       
    house();
    glPopMatrix();
}
void house_three() {  // Elevated House on the Hill
    glPushMatrix();
    glTranslatef(320, 37, 0);      
    house();
    glPopMatrix();
}
void house_four() { // Far left ground house
    glPushMatrix();
    glTranslatef(-250, 0, 0);       
    house();
    glPopMatrix();
}
void house_five() { // Far right ground house
    glPushMatrix();
    glTranslatef(630, 0, 0);        
    house();
    glPopMatrix();
}

// Mountains/Hills
void Hill_Big_One() {  // Main left mountain
    glPushMatrix();
    glTranslatef(0, -10, 0);       
    hill_big();
    glPopMatrix();
}
void Hill_Big_Two() { // Main right mountain
    glPushMatrix();
    glTranslatef(550, -30, 0);      
    hill_big();
    glPopMatrix();
}
void Hill_Small_One() { // Small background mountain peek
    glPushMatrix();
    glTranslatef(-25, 0, 0);        
    hill_small();
    glPopMatrix();
}
void Tilla_One() { // Rolling green hill (Left)
    glPushMatrix();
    glTranslatef(0, 0, 0);          
    Tilla_One_Model();
    glPopMatrix();
}
void Tilla_Two() { // Bumpy midground hill (Left)
    glPushMatrix();
    glTranslatef(0, 0, 0);          
    Tilla_Two_Model();
    glPopMatrix();
}
void Tilla_Three() { // Bumpy midground hill (Right)
    glPushMatrix();
    glTranslatef(400, 0, 0);        
    Tilla_Two_Model();
    glPopMatrix();
}
void Tilla_Four() { // Rolling green hill (Right)
    glPushMatrix();
    glTranslatef(380, 0, 0);        
    Tilla_One_Model();
    glPopMatrix();
}

// Small Trees (Background/Midground)
void Tree_One() { // Round tree near house two
    glPushMatrix();
    glTranslatef(540, 0, 0);        
    Tree_Model_One();
    glPopMatrix();
}
void Tree_Two() { // Round tree on far right
    glPushMatrix();
    glTranslatef(750, 0, 0);        
    Tree_Model_One();
    glPopMatrix();
}
void Tree_Three() { // Round tree up on the hill
    glPushMatrix();
    glTranslatef(292, 40, 0);      
    Tree_Model_One();
    glPopMatrix();
}
void Tree_Four() { // Fluffy tree far left
    glPushMatrix();
    glTranslatef(30, -20, 0);       
    Tree_Model_Two();
    glPopMatrix();
}
void Tree_Five() { // Fluffy tree mid-left
    glPushMatrix();
    glTranslatef(50, -10, 0);       
    Tree_Model_Two();
    glPopMatrix();
}
void Tree_Six() {  // Fluffy tree center
    glPushMatrix();
    glTranslatef(322, 0, 0);       
    Tree_Model_Two();
    glPopMatrix();
}
void Tree_Seven() { // Fluffy tree center-right
    glPushMatrix();
    glTranslatef(350, -15, 0);      
    Tree_Model_Two();
    glPopMatrix();
}
void Tree_Eight() { // Pine tree far left
    glPushMatrix();
    glTranslatef(90, -2, 0);        
    Tree_Model_Three();
    glPopMatrix();
}
void Tree_Nine() { // Pine tree mid-left
    glPushMatrix();
    glTranslatef(125, 0, 0);        
    Tree_Model_Three();
    glPopMatrix();
}
void Tree_Ten() { // Pine tree center-right
    glPushMatrix();
    glTranslatef(408, -22, 0);      
    Tree_Model_Three();
    glPopMatrix();
}

// Windmills
void Windmill_One() { // Primary left windmill
    glPushMatrix();
    glTranslatef(0, -10, 0);        
    Windmill();
    glPopMatrix();
}
void Windmill_Two() { // Primary right windmill (placed lower)
    glPushMatrix();
    glTranslatef(508, -70, 0);      
    Windmill();
    glPopMatrix();
}
void Windmill_Three() { // Distant background windmill
    glPushMatrix();
    glTranslatef(108, -90, 0);      
    Windmill();
    glPopMatrix();
}

// --- COMPLEX SCENE ELEMENTS ---

// Village Road
void draw_village_road() {
    glColor3ub(180, 135, 85);
    // Main Horizontal Street
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 52.0f);
    glVertex2f(1000.0f, 52.0f);
    glVertex2f(1000.0f, 65.0f);
    glVertex2f(0.0f, 65.0f);
    glEnd();
    glBegin(GL_POLYGON); // Driveway for House 1 (Center Left)
    glVertex2f(330, 65);
    glVertex2f(350, 65);
    glVertex2f(350, 70);
    glVertex2f(330, 70);
    glEnd();
    glBegin(GL_POLYGON); // Driveway for House 2 (Center Right)
    glVertex2f(780, 65);
    glVertex2f(800, 65);
    glVertex2f(800, 70);
    glVertex2f(780, 70);
    glEnd();
    glBegin(GL_POLYGON); // Slanted Path for Hill House 3
    glVertex2f(555, 65);
    glVertex2f(585, 65);
    glVertex2f(605, 107);
    glVertex2f(580, 107);
    glEnd();
    glBegin(GL_POLYGON); // Driveway for House 4 (Far Left)
    glVertex2f(80, 65);
    glVertex2f(100, 65);
    glVertex2f(100, 70);
    glVertex2f(80, 70);
    glEnd();
    glBegin(GL_POLYGON); // Driveway for House 5 (Far Right)
    glVertex2f(960, 65);
    glVertex2f(980, 65);
    glVertex2f(980, 70);
    glVertex2f(960, 70);
    glEnd();
}

// River & Shorelines
// Sine functions are used to create Smooth, Natural-looking Wavy River Edges
float river_top_y(float x) {
    return -35.0f + 10.0f * sin(x * PI / 280.0f) + 6.0f * sin(x * PI / 150.0f + 0.8f);
}
float river_bottom_y(float x) {
    return -210.0f + 20.0f * sin(x * PI / 350.0f) + 12.0f * sin(x * PI / 130.0f + 1.1f);
}

// Top Green Riverbank (Separates the Road from the Water)
void field() {
    glBegin(GL_POLYGON); // Flat Top Green Section
    glColor3ub(65, 175, 35);
    glVertex2i(0, 50);
    glVertex2i(0, 70);
    glVertex2i(1000, 70);
    glVertex2i(1000, 50);
    glEnd();
    glBegin(GL_POLYGON); // Wavy Bottom Green Section
    glColor3ub(40, 130, 22);
    glVertex2f(1000.0f, 50.0f);
    glVertex2f(0.0f, 50.0f);
    for (int s = 0; s <= 150; s++) {
        float x = (float)s / 150.0f * 1000.0f;
        glVertex2f(x, river_top_y(x));
    }
    glEnd();
}

// Dynamic Blue River Body
void draw_river() {
    glBegin(GL_POLYGON);
    // Wavy Top Edge of the Water (Lighter Blue)
    for (int s = 0; s <= 150; s++) {
        float x = (float)s / 150.0f * 1000.0f;
        glColor3ub(30, 120, 240);
        glVertex2f(x, river_top_y(x));
    }
    // Wavy Bottom Edge of the Water (Darker Blue)
    for (int s = 150; s >= 0; s--) {
        float x = (float)s / 150.0f * 1000.0f;
        glColor3ub(15, 70, 175);
        glVertex2f(x, river_bottom_y(x));
    }
    glEnd();
}

// One Single Wave Ripple
void draw_single_ripple(float startX, float baseY, float amplitude) {
    glBegin(GL_LINE_STRIP);
    for (int pt = 0; pt <= 30; pt++) {
        // 't' goes from 0.0 to 1.0 to draw a full sine wave curve
        float t = (float)pt / 30.0f; 
        float x = startX + (t * 110.0f);
        float y = baseY + (amplitude * sin(t * PI * 2.0f));
        
        // Only draw it if it's actually visible on the screen (0 to 1000)
        if (x >= 0 && x <= 1000) {
            glVertex2f(x, y);
        }
    }
    glEnd();
}

// Animated Sine Wave Water Ripples
void draw_waves() { 
    float waveYLevels[] = {-55.0f, -90.0f, -130.0f, -165.0f, -200.0f}; // 5 rows of waves
    
    glColor3ub(70, 150, 240);
    // Loop through the 5 Vertical Rows
    for (int w = 0; w < 5; w++) {
        float baseY = waveYLevels[w];
        float amplitude = 5.0f + (w % 2) * 2.0f; // Alternates Height between 5.0 and 7.0
        
        // Loop Horizontally Across the River to Place Multiple Ripples in a Line
        for (float x = wave_offset - 120.0f; x < 1050.0f; x += 120.0f) {
            draw_single_ripple(x, baseY, amplitude);
        }
    }
}

// Foreground Fields & Details
void draw_large_foreground_tree(float x, float y) {
    // Brown Wooden Trunk
    glBegin(GL_POLYGON);
    glColor3ub(85, 50, 15);
    glVertex2f(x - 8, y);
    glVertex2f(x - 8, y - 50);
    glVertex2f(x + 8, y - 50);
    glVertex2f(x + 8, y);
    glEnd();
    // Green Leaf Clusters (3 Overlapping Circles)
    glColor3ub(30, 110, 18);
    glPushMatrix();
    glTranslatef(x, y + 20, 0); // Top Center Leaf Blob
    circle(38);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(x - 25, y - 5, 0); // Bottom Left Leaf Blob
    circle(32);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(x + 25, y - 5, 0); // Bottom Right Leaf Blob
    circle(32);
    glPopMatrix();
}

// Bottom Fields & Details
void draw_bottom_field() {
    // Base Green Grass (Flat Bottom Part)
    glBegin(GL_POLYGON);
    glColor3ub(40, 130, 22);
    glVertex2f(0.0f, -280.0f);
    glVertex2f(1000.0f, -280.0f);
    glVertex2f(1000.0f, -230.0f);
    glVertex2f(0.0f, -230.0f);
    glEnd();

    // Base Green Grass (Wavy Top Part Touching the River)
    glBegin(GL_POLYGON);
    glColor3ub(65, 175, 35);
    for (int s = 0; s <= 150; s++) {
        float x = (float)s / 150.0f * 1000.0f;
        glVertex2f(x, river_bottom_y(x));
    }
    glVertex2f(1000.0f, -280.0f);
    glVertex2f(0.0f, -280.0f);
    glEnd();

    // Angled Dirt Path to the Water
    glColor3ub(180, 135, 85);
    glBegin(GL_POLYGON);
    glVertex2f(250, -280); // Bottom Left
    glVertex2f(340, -280); // Bottom Right
    glVertex2f(310, -220); // Top Right
    glVertex2f(270, -220); // Top Left
    glEnd();

    // Wooden Fence
    glColor3ub(120, 70, 40);
    // Two Horizontal Rails
    glBegin(GL_QUADS); 
    glVertex2f(400, -250); // Top Rail
    glVertex2f(950, -250);
    glVertex2f(950, -246);
    glVertex2f(400, -246); 
    glVertex2f(400, -265); // Bottom Rail
    glVertex2f(950, -265);
    glVertex2f(950, -261);
    glVertex2f(400, -261); 
    glEnd();
    // Vertical Fence Posts
    glBegin(GL_QUADS); 
    for (int i = 400; i <= 950; i += 50) {
        glVertex2f(i, -275);
        glVertex2f(i + 8, -275);
        glVertex2f(i + 8, -240);
        glVertex2f(i, -240);
    }
    glEnd();

    // Left Bush (Next to the Dirt Path)
    glColor3ub(30, 110, 18);
    glPushMatrix();
    glTranslatef(75, -242, 0); // Top Bush
    circle(21);
    glPopMatrix(); 
    glPushMatrix();
    glTranslatef(95, -255, 0); // Right Bush
    circle(17);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(57, -256, 0); // Left Bush
    circle(16);
    glPopMatrix();       
    glBegin(GL_POLYGON); // Small Trunk
    glColor3ub(85, 50, 15);
    glVertex2f(71, -260);
    glVertex2f(71, -280);
    glVertex2f(77, -280);
    glVertex2f(77, -260);
    glEnd();

    // Middle Right Bush
    glColor3ub(35, 120, 20);
    glPushMatrix();
    glTranslatef(510, -241, 0); // Top Bush
    circle(20);
    glPopMatrix(); 
    glPushMatrix();
    glTranslatef(530, -253, 0); // Right Bush
    circle(16);
    glPopMatrix(); 
    glPushMatrix();
    glTranslatef(490, -253, 0); // Left Bush
    circle(16);
    glPopMatrix();       
    glBegin(GL_POLYGON); // Small Trunk
    glColor3ub(85, 50, 15);
    glVertex2f(507, -257);
    glVertex2f(507, -280);
    glVertex2f(512, -280);
    glVertex2f(512, -257);
    glEnd();

    // Large Overlapping Foreground Trees
    draw_large_foreground_tree(55, -173);  // Left Edge
    draw_large_foreground_tree(180, -215); // Mid-Left
    draw_large_foreground_tree(400, -230); // Center
    draw_large_foreground_tree(570, -190); // Mid-Right (Higher)
    draw_large_foreground_tree(685, -225); // Mid-Right (Lower)
    draw_large_foreground_tree(790, -185); // Right (Higher)
    draw_large_foreground_tree(930, -230); // Far Right Edge
}

// --- VEHICLES --- 

// Plane
void draw_plane() {
    float baseY = 365.0f;
    glPushMatrix();
    glTranslatef(position6, baseY, 0.0f); // Animates Across the Sky
    glScalef(1.2f, 1.2f, 1.0f);

    // Back Wing
    glBegin(GL_POLYGON); 
    glColor3ub(180, 30, 30);
    glVertex2f(10, 5);
    glVertex2f(30, 5);
    glVertex2f(45, 20);
    glVertex2f(25, 20);
    glEnd(); 
    // Main Fuselage (Body)
    glBegin(GL_POLYGON);
    glColor3ub(245, 245, 250);
    glVertex2f(-50, 0);
    glVertex2f(40, -10);
    glVertex2f(60, -5);
    glVertex2f(65, 5);
    glVertex2f(50, 15);
    glVertex2f(-40, 15);
    glVertex2f(-60, 10);
    glEnd(); 
    // Cockpit Window
    glBegin(GL_POLYGON); 
    glColor3ub(100, 200, 255);
    glVertex2f(20, 15);
    glVertex2f(45, 15);
    glVertex2f(55, 5);
    glVertex2f(25, 5);
    glEnd(); 
    // Red Detail Stripe
    glBegin(GL_POLYGON); 
    glColor3ub(220, 40, 40);
    glVertex2f(-55, 5);
    glVertex2f(40, -2);
    glVertex2f(40, 2);
    glVertex2f(-55, 8);
    glEnd(); 
    // Tail Fin
    glBegin(GL_POLYGON); 
    glColor3ub(220, 40, 40);
    glVertex2f(-45, 12);
    glVertex2f(-35, 35);
    glVertex2f(-55, 35);
    glVertex2f(-60, 12);
    glEnd(); 
    // Front Wing
    glBegin(GL_POLYGON); 
    glColor3ub(220, 40, 40);
    glVertex2f(-10, -5);
    glVertex2f(25, -5);
    glVertex2f(15, -25);
    glVertex2f(-20, -25);
    glEnd(); 
    // Nose Cone (Propeller Hub)
    glBegin(GL_POLYGON); 
    glColor3ub(50, 50, 50);
    glVertex2f(65, 0);
    glVertex2f(72, 2);
    glVertex2f(72, 8);
    glVertex2f(65, 10);
    glEnd(); 
    // Spinning Propeller Blur
    glBegin(GL_POLYGON); 
    glColor3ub(180, 180, 180);
    glVertex2f(70, -18);
    glVertex2f(74, -18);
    glVertex2f(74, 28);
    glVertex2f(70, 28);
    glEnd(); 

    glPopMatrix();
}

// Motor Boat
void draw_motorboat(float cx, float cy) {
    // Main Hull (Base of the Boat)
    glBegin(GL_POLYGON);
    glColor3ub(230, 230, 235);
    glVertex2f(cx - 100, cy);
    glVertex2f(cx - 110, cy - 30);
    glVertex2f(cx + 85, cy - 30);
    glVertex2f(cx + 110, cy);
    glEnd();
    // Blue Bottom Stripe (Touching the Water)
    glBegin(GL_POLYGON);
    glColor3ub(50, 100, 210);
    glVertex2f(cx - 100, cy);
    glVertex2f(cx - 100, cy - 8);
    glVertex2f(cx + 110, cy - 8);
    glVertex2f(cx + 110, cy);
    glEnd();
    // Upper Cabin (Roof Section)
    glBegin(GL_POLYGON);
    glColor3ub(235, 235, 240);
    glVertex2f(cx - 45, cy);
    glVertex2f(cx - 45, cy + 40);
    glVertex2f(cx + 45, cy + 40);
    glVertex2f(cx + 65, cy);
    glEnd();
    // Left Window
    glBegin(GL_POLYGON);
    glColor3ub(110, 185, 230);
    glVertex2f(cx - 32, cy + 10);
    glVertex2f(cx - 32, cy + 30);
    glVertex2f(cx - 8, cy + 30);
    glVertex2f(cx - 8, cy + 10);
    glEnd();
    // Right Window
    glBegin(GL_POLYGON);
    glColor3ub(110, 185, 230);
    glVertex2f(cx + 5, cy + 10);
    glVertex2f(cx + 5, cy + 30);
    glVertex2f(cx + 28, cy + 30);
    glVertex2f(cx + 28, cy + 10);
    glEnd();
}

// Sailboat
void draw_sailboat(float cx, float cy) {
    // Main Wooden Hull
    glBegin(GL_POLYGON);
    glColor3ub(120, 72, 30);
    glVertex2f(cx - 90, cy);
    glVertex2f(cx - 100, cy - 35);
    glVertex2f(cx + 75, cy - 35);
    glVertex2f(cx + 95, cy);
    glEnd();
    // Red Top Rim
    glBegin(GL_POLYGON);
    glColor3ub(200, 50, 50);
    glVertex2f(cx - 90, cy);
    glVertex2f(cx - 90, cy - 10);
    glVertex2f(cx + 95, cy - 10);
    glVertex2f(cx + 95, cy);
    glEnd();
    // Wooden Mast (Center Pole)
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3ub(90, 55, 18);
    glVertex2f(cx + 5, cy + 5);
    glVertex2f(cx + 5, cy + 145);
    glEnd();
    glLineWidth(1.0f); 
    // Large Yellow Main Sail (Back sail)
    glBegin(GL_POLYGON);
    glColor3ub(245, 210, 70);
    glVertex2f(cx + 5, cy + 8);
    glVertex2f(cx + 5, cy + 140);
    glVertex2f(cx - 75, cy + 14);
    glEnd(); 
    // Small Orange Front Sail (Jib)
    glBegin(GL_POLYGON);
    glColor3ub(230, 130, 50);
    glVertex2f(cx + 5, cy + 110);
    glVertex2f(cx + 5, cy + 8);
    glVertex2f(cx + 70, cy + 18);
    glEnd(); 
}

// --- MAIN DISPLAY FUNCTION ---

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Deep Background
    draw_sky_gradient();
    Sun();

    // Distant Background Elements
    Windmill_Three();
    Hill_Big_One();
    Tilla_Four();
    house_three();
    Hill_Big_Two();
    Hill_Small_One();
    cloud_three();
    cloud_four();
    Windmill_One();
    Windmill_Two();

    // Midground Village
    Tilla_One();
    Tilla_Two();
    Tilla_Three();
    house_one();
    house_two();
    house_four();
    house_five();
    cloud_one();
    cloud_two();
    cloud_five();
    cloud_six();
    Tree_One();
    Tree_Two();
    Tree_Three();
    Tree_Four();
    Tree_Five();
    Tree_Six();
    Tree_Seven();
    Tree_Eight();
    Tree_Nine();
    Tree_Ten();

    // Ground Layer
    field();
    draw_village_road();
    draw_river();
    draw_waves();

    // Vehicles on River
    glPushMatrix();
    glTranslatef(motorboat_x, -60.0f, 0.0f);
    glScalef(-1.0f, 1.0f, 1.0f);
    draw_motorboat(0.0f, 0.0f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(sailboat_x, -60.0f, 0.0f);
    glScalef(-1.0f, 1.0f, 1.0f);
    draw_sailboat(0.0f, 0.0f);
    glPopMatrix();

    // Foreground
    draw_bottom_field();
    draw_plane();

    glFlush();
}

// --- ANIMATION ---

void move_right() {
    // Rotate Windmills
    spin += 0.3f * anim_speed; // Rotate Windmills

    // Move Clouds
    ax += 0.05f * anim_speed;
    if (ax > 1000)
        ax = -600;
    bx += 0.08f * anim_speed;
    if (bx > 1000)
        bx = -400;
    cx += 0.10f * anim_speed;
    if (cx > 1000)
        cx = -300;
    dx += 0.15f * anim_speed;
    if (dx > 1000)
        dx = -500;

    // Move Airplane
    position6 += 0.9f * anim_speed;
    if (position6 > 1250.0f)
        position6 = -250.0f;

    // Move Boats (Right to Left)
    motorboat_x -= 0.35f * anim_speed;
    if (motorboat_x < -220.0f)
        motorboat_x = 1200.0f;
    sailboat_x -= 0.2f * anim_speed;
    if (sailboat_x < -250.0f)
        sailboat_x = 1200.0f;

    // Scroll River Waves
    wave_offset += 0.6f * anim_speed;
    if (wave_offset > 120.0f)
        wave_offset -= 120.0f;

    glutPostRedisplay(); // Refresh Screen
}

// --- INPUT / CONTROLS ---

void keyboard(unsigned char key, int x, int y) {
    if (key == ' ') {
        // Spacebar = Toggle Play/Pause
        isPlaying = !isPlaying;
        if (isPlaying)
            glutIdleFunc(move_right);
        else
            glutIdleFunc(NULL);
    }
    else if (key == '+' || key == '=') {
        // '+' = Increase Speed
        anim_speed += 0.3f;
    }
    else if (key == '-' || key == '_') {
        // '-' = Decrease Speed
        anim_speed -= 0.3f;
        if (anim_speed < 0.0f)
            anim_speed = 0.0f;
    }
    else if (key == 't' || key == 'T' || key == 'd' || key == 'D') {
        // 'T'/'D' = Toggle Day to Night immediately
        isDay = !isDay;
        if (isDay)
            day_angle = PI / 2.0f; // Snap to Day
        else
            day_angle = 3.0f * PI / 2.0f; // Snap to Night
        glutPostRedisplay();
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