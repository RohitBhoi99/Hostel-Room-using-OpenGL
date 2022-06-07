#include <cstdlib>
#include <vector>
#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h> 
#include <cmath>

// Initialization routine

//Light Switch
int light = 1;

//Cloth 
float wavelength = 43;
float amplitude = 0.85;
//Colors
float almirahColor[] = { 0.81, 0.81, 0.76 };
float roomWallColor[] = { 0.56, 0.86, 0.06, 1 };


//Fan 
float t = 0;
int fanSwitch = 1;
float fanSpeed = 0;
//Movements 
double theta = 0;
double neckSpeed = 0.05;
int speed = 3;
int rotate = 0;
//Room dimensions
int ROOM_LENGTH = 100;
int ROTATE_ANGLE = 0;
int ROTATE_ANGLE_ALMIRAH = 0;

// Camera angle
double centerX = 0.0;
double centerY = 0.0;
double centerZ = -10000.0;

double eye_x_init = 0;
double eye_y_init = 0;
double eye_z_init = 50;
double eye_x = eye_x_init, eye_y = eye_y_init, eye_z = eye_z_init;
int WINDOW_SHIFT = 0;

void setup(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST); // Enable depth testing.
	// Turn on OpenGL lighting.
	//glEnable(GL_LIGHTING);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-4.0, 4.0, -4.0, 4.0, 5.0, 1000.0);

	glMatrixMode(GL_MODELVIEW);
}

void keyInput(unsigned char key, int x, int y) {
	int radius = 30;
	int divs = 30;
	// Movement
	if (key == 'd') {
		rotate = 1;

		eye_x += speed * cos(theta);
		eye_z += speed * sin(theta);

		glutPostRedisplay();
		printf("d");
	}
	if (key == 'a') {
		rotate = 1;
		eye_x -= speed * cos(theta);
		eye_z -= speed * sin(theta);


		glutPostRedisplay();
		printf("a");
	}
	if (key == 'w') {
		rotate = 1;
		//eye_x = eye_x + 1;
		eye_z -= speed * cos(theta);
		eye_x += speed * sin(theta);


		glutPostRedisplay();
		printf("w");
	}
	if (key == 's') {
		rotate = 1;
		eye_z += speed * cos(theta);
		eye_x -= speed * sin(theta);

		glutPostRedisplay();
		printf("s");
	}

	// Eye Rotation
	if (key == 'r')
	{

		rotate = 1;
		theta += neckSpeed;
		centerX = 10000 * sin(theta);
		centerZ = -10000 * cos(theta);

		glutPostRedisplay();
	}
	if (key == 'f')
	{

		rotate = 1;
		theta -= neckSpeed;
		centerX = 10000 * sin(theta);
		centerZ = -10000 * cos(theta);


		glutPostRedisplay();
	}

	// Fan Speed
	if (key == 'z')				// Fan Speed Increase
	{
		if (fanSpeed > 0.1){
			fanSpeed -= 0.1;
		}
		
		

		glutPostRedisplay();
	}
	if (key == 'x')				// Fan Speed Decrease
	{
		fanSpeed+=0.1;

		glutPostRedisplay();
	}
	
	// Main Door Open and Close
	if (key == 't')				// Open Room Doors
	{
		if (ROTATE_ANGLE < 100) {
			ROTATE_ANGLE += 3;
		}

		glutPostRedisplay();
	}
	if (key == 'g')				// Close Room Doors
	{
		if (ROTATE_ANGLE > 0) {
			ROTATE_ANGLE -= 3;
		}

		glutPostRedisplay();
	}

	// Almirah Doors Open and Close
	if (key == 'y')				// Open Almirah Doors
	{
		if (ROTATE_ANGLE_ALMIRAH < 90) {
			ROTATE_ANGLE_ALMIRAH += 2;
		}

		glutPostRedisplay();
	}
	if (key == 'h')				// Close Almirah Doors
	{
		if (ROTATE_ANGLE_ALMIRAH > 0) {
			ROTATE_ANGLE_ALMIRAH -= 2;
		}

		glutPostRedisplay();
	}

	// Lights on and off
	if (key == 'l')				
	{
		if (light)
		{
			light = 0;
			glDisable(GL_LIGHT1);
			glDisable(GL_LIGHT2);

		}
		else
		{
			light = 1;
			glEnable(GL_LIGHT1);
			glEnable(GL_LIGHT2);
		}

		glutPostRedisplay();
	}

	// Window opening/closing
	if (key == 'o') {									// opens window

		if (WINDOW_SHIFT < ROOM_LENGTH * 2 / 10) {
			WINDOW_SHIFT += ROOM_LENGTH / 40;
		}

		glutPostRedisplay();
	}
	if (key == 'p') {									// closes window

		if (WINDOW_SHIFT > 0) {
			WINDOW_SHIFT -= ROOM_LENGTH / 40;
		}

		glutPostRedisplay();
	}
	
	// Crouch
	if (key == 'c') {
		if (eye_y <= eye_y_init + 20 && eye_y > -30) {
			eye_y -= 5;
		}
	}
	if (key == 'v') {
		if (eye_y < eye_y_init+20) {
			eye_y += 5;
		}
	}
}

void cuboid(int x, int y, int z) {
	glScalef(x, y, z);
	glutSolidCube(1);
}

void corridor() {


	float corridorColor[4] = { 1, 1, 1, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, corridorColor);
	// Floor
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH, -ROOM_LENGTH / 2, -ROOM_LENGTH);
	cuboid(ROOM_LENGTH * 6, 3, ROOM_LENGTH / 2);
	glPopMatrix();

	// Roof
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH, ROOM_LENGTH / 2, -ROOM_LENGTH);
	cuboid(ROOM_LENGTH * 6, 3, ROOM_LENGTH / 2);
	glPopMatrix();

}
// Room Contains All the walls
void room()
{
	// Rod
	float rodcolor[4] = { 0.6, 0.6, 0.6, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, rodcolor);
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH/2, 23, ROOM_LENGTH*3/4 - 5);
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(1, ROOM_LENGTH, 5, 5);
	glPopMatrix();

	float dcolor[4] = { 1, 1, 1, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, dcolor);

	// Roof
	glPushMatrix();
	glTranslatef(0, ROOM_LENGTH / 2, 0);
	cuboid(ROOM_LENGTH, 1, ROOM_LENGTH * 3 / 2);
	glPopMatrix();

	// Floor
	glPushMatrix();
	glTranslatef(0, -ROOM_LENGTH / 2, 0);
	cuboid(ROOM_LENGTH, 1, ROOM_LENGTH * 3 / 2);
	glPopMatrix();

	float roomColor[4] = { 1, 0.87, 0.16, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, roomColor);

	// Right Wall
	glColor3f(1, 0.9, 0);
	glPushMatrix();
	glTranslatef(ROOM_LENGTH / 2, 0, 0);
	cuboid(1, ROOM_LENGTH, ROOM_LENGTH * 3 / 2);
	glPopMatrix();

	// Left Wall
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH / 2, 0, 0);
	cuboid(1, ROOM_LENGTH, ROOM_LENGTH * 3 / 2);
	glPopMatrix();

	// Window Wall (Above part)
	glPushMatrix();
	glTranslatef(0, 0.34 * ROOM_LENGTH, ROOM_LENGTH * 3 / 4);
	cuboid(ROOM_LENGTH, ROOM_LENGTH * 32 / 100, 1);
	glPopMatrix();

	// Window Wall (Below part)
	glPushMatrix();
	glTranslatef(0, -0.34 * ROOM_LENGTH, ROOM_LENGTH * 3 / 4);
	cuboid(ROOM_LENGTH, ROOM_LENGTH * 32 / 100, 1);
	glPopMatrix();

	// Window Wall (Centre part)
	glPushMatrix();
	glTranslatef(0, 0, ROOM_LENGTH * 3 / 4);
	cuboid(ROOM_LENGTH * 0.2, ROOM_LENGTH * 36 / 100, 1);
	glPopMatrix();

	// Door Wall (Left Part)
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH * 35 / 100, 0, -ROOM_LENGTH * 3 / 4);
	cuboid(ROOM_LENGTH * 3 / 10, ROOM_LENGTH, 1);
	glPopMatrix();

	// Door Wall (Right Part)
	glPushMatrix();
	glTranslatef(ROOM_LENGTH * 35 / 100, 0, -ROOM_LENGTH * 3 / 4);
	cuboid(ROOM_LENGTH * 3 / 10, ROOM_LENGTH, 1);
	glPopMatrix();

	// Door Wall (Centre Part)
	glPushMatrix();
	glTranslatef(0, ROOM_LENGTH * 35 / 100, -ROOM_LENGTH * 3 / 4);
	cuboid(ROOM_LENGTH * 2 / 5, ROOM_LENGTH * 3 / 10, 1);
	glPopMatrix();
}
void drawRoom() {

	glColor3f(1.0, 0, 0);
	room();
}

void windows() {
	
	float gold_color[4] = { 1, 0.0, 0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, gold_color);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);
	
	// Left window static (POV from inside the room)
	glPushMatrix();
	glTranslatef(ROOM_LENGTH * 4 / 10, 0, ROOM_LENGTH * 3 / 4 + 0.25);
	cuboid(ROOM_LENGTH * 0.2, ROOM_LENGTH * 36 / 100, 0.5);
	glPopMatrix();

	// Right window static (POV from inside the room)
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH * 4 / 10, 0, ROOM_LENGTH * 3 / 4 + 0.25);
	cuboid(ROOM_LENGTH * 0.2, ROOM_LENGTH * 36 / 100, 0.5);
	glPopMatrix();

	glColor3f(0.0, 1.0, 1.0);
	// Left window moving (POV from inside the room)
	glPushMatrix();
	glTranslatef(ROOM_LENGTH * 4 / 10 - WINDOW_SHIFT, 0, ROOM_LENGTH * 3 / 4 - 0.25);
	cuboid(ROOM_LENGTH * 0.2, ROOM_LENGTH * 36 / 100, 0.5);
	glPopMatrix();

	// Right window moving (POV from inside the room)
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH * 4 / 10 + WINDOW_SHIFT, 0, ROOM_LENGTH * 3 / 4 - 0.25);
	cuboid(ROOM_LENGTH * 0.2, ROOM_LENGTH * 36 / 100, 0.5);
	glPopMatrix();
}
void main_door()
{
	float doorColor[4] = { 0.45, 0.14, 0.02, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, doorColor);

	glPushMatrix();
	glTranslatef(-ROOM_LENGTH / 5, -ROOM_LENGTH / 5, -ROOM_LENGTH / 2 - ROOM_LENGTH / 4);
	glRotatef(ROTATE_ANGLE, 0, -1, 0);
	glTranslatef(ROOM_LENGTH / 10, 0, 0);
	cuboid(ROOM_LENGTH / 5, ROOM_LENGTH * 3 / 5, 2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(ROOM_LENGTH / 5, -ROOM_LENGTH / 5, -ROOM_LENGTH / 2 - ROOM_LENGTH / 4);
	glRotatef(ROTATE_ANGLE, 0, 1, 0);
	glTranslatef(-ROOM_LENGTH / 10, 0, 0);
	cuboid(ROOM_LENGTH / 5, ROOM_LENGTH * 3 / 5, 2);
	glPopMatrix();
}

void teapot() {
	glPushMatrix();
	glTranslatef(5, 12.8, -35);
	glutSolidTeapot(3);
	glPopMatrix();
}

void almirahLeft()
{
	float almirahColor[4] = { 0.59, 0.59, 0.57, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, almirahColor);
	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	// Top
	glPushMatrix();
	glColor3f(almirahColor[0], almirahColor[1], almirahColor[2]);
	glTranslatef(-ROOM_LENGTH / 2 + ROOM_LENGTH / 10, ROOM_LENGTH / 5, -ROOM_LENGTH * (0.61));
	cuboid(ROOM_LENGTH / 5, 1, ROOM_LENGTH * 2 / 7);
	glPopMatrix();

	// Back
	glPushMatrix();
	glColor3f(almirahColor[0], almirahColor[1], almirahColor[2]);
	glTranslatef(-ROOM_LENGTH / 2 + 1, -5 * ROOM_LENGTH / 40, -ROOM_LENGTH * (0.61));
	cuboid(1, ROOM_LENGTH * 13 / 20, ROOM_LENGTH * 2 / 7);
	glPopMatrix();

	// Bottom
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH / 2 + ROOM_LENGTH / 10, -ROOM_LENGTH / 2 + ROOM_LENGTH / 20, -ROOM_LENGTH * (0.61));
	cuboid(ROOM_LENGTH / 5, 1, ROOM_LENGTH * 2 / 7);
	glPopMatrix();

	// Right Side
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH / 2 + ROOM_LENGTH / 10, -5 * ROOM_LENGTH / 40, -ROOM_LENGTH / 2 + 0.5 - ROOM_LENGTH / 4);
	cuboid(ROOM_LENGTH / 5, ROOM_LENGTH * 13 / 20, 1);
	glPopMatrix();

	// Left Side
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH / 2 + ROOM_LENGTH / 10, -5 * ROOM_LENGTH / 40, -ROOM_LENGTH * (0.475));
	cuboid(ROOM_LENGTH / 5, ROOM_LENGTH * 13 / 20, 1);
	glPopMatrix();

	// Legs
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH / 2 + ROOM_LENGTH / 10, -ROOM_LENGTH / 2 + ROOM_LENGTH / 40, -ROOM_LENGTH * (0.61) - ROOM_LENGTH / 10);
	cuboid(ROOM_LENGTH / 6, ROOM_LENGTH / 20, 3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-ROOM_LENGTH / 2 + ROOM_LENGTH / 10, -ROOM_LENGTH / 2 + ROOM_LENGTH / 40, -ROOM_LENGTH * (0.61) + ROOM_LENGTH / 10);
	cuboid(ROOM_LENGTH / 6, ROOM_LENGTH / 20, 3);
	glPopMatrix();




	// almirah door
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH / 2 + ROOM_LENGTH * 2 / 10, -5 * ROOM_LENGTH / 40, -ROOM_LENGTH * (0.6125));
	glTranslatef(0, 0, ROOM_LENGTH / 7);
	glRotatef(ROTATE_ANGLE_ALMIRAH, 0, -1, 0);
	glTranslatef(0, 0, -ROOM_LENGTH / 14);
	cuboid(1, ROOM_LENGTH * 13 / 20, ROOM_LENGTH / 7);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-ROOM_LENGTH / 2 + ROOM_LENGTH * 2 / 10, -5 * ROOM_LENGTH / 40, -ROOM_LENGTH * (0.6125));
	glTranslatef(0, 0, -ROOM_LENGTH / 7);
	glRotatef(ROTATE_ANGLE_ALMIRAH, 0, 1, 0);
	glTranslatef(0, 0, ROOM_LENGTH / 14);
	cuboid(1, ROOM_LENGTH * 13 / 20, ROOM_LENGTH / 7);
	glPopMatrix();

	glPopMatrix();
}
void almirahRight()
{
	glPushMatrix();
	glTranslatef(0, 0, -ROOM_LENGTH * (1.225) + 1);
	glRotatef(180, 0, 1, 0);
	almirahLeft();
	glPopMatrix();
}

void bedLeft()
{
	// main bed
	glColor3f(0.64, 0.2, 0.2);
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH * (0.33), -ROOM_LENGTH * (0.35), 0);
	cuboid(ROOM_LENGTH * 3 / 10, 1, ROOM_LENGTH * 5 / 7);
	glPopMatrix();

	// mattress
	float mattressColor[4] = { 0.07, 0.35, 0.48, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mattressColor);
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH * (0.33), -ROOM_LENGTH * (0.35) + 1, 0);
	cuboid(ROOM_LENGTH * 3 / 10, 1, ROOM_LENGTH * 5 / 7 - 3);
	glPopMatrix();

	// pillow
	float pillowColor[4] = { 0.6, 0.43, 0.13, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, pillowColor);
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH * (0.33)-7.5, -ROOM_LENGTH * (0.35) + 3, 30);
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(3, 15, 20, 20);
	glPopMatrix();

	// Leg tall right
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, almirahColor);
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH * (0.33) + ROOM_LENGTH * 3 / 20, -ROOM_LENGTH * (0.35) + ROOM_LENGTH / 10, ROOM_LENGTH * 5 / 14);
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(1, ROOM_LENGTH / 4, 10, 10);
	glPopMatrix();

	// Leg tall left
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH * (0.33) - ROOM_LENGTH * 3 / 20, -ROOM_LENGTH * (0.35) + ROOM_LENGTH / 10, ROOM_LENGTH * 5 / 14);
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(1, ROOM_LENGTH / 4, 10, 10);
	glPopMatrix();

	// Leg short right
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH * (0.33) + ROOM_LENGTH * 3 / 20, -ROOM_LENGTH * (0.34), -ROOM_LENGTH * 5 / 14);
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(1, ROOM_LENGTH / 6, 10, 10);
	glPopMatrix();

	// Leg short left
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH * (0.33) - ROOM_LENGTH * 3 / 20, -ROOM_LENGTH * (0.34), -ROOM_LENGTH * 5 / 14);
	glRotatef(90, 1, 0, 0);
	glutSolidCylinder(1, ROOM_LENGTH / 6, 10, 10);
	glPopMatrix();

	// bed support
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH * (0.33), -ROOM_LENGTH * (0.3), ROOM_LENGTH * 5 / 14);
	cuboid(ROOM_LENGTH * 3 / 10, ROOM_LENGTH / 10 - 0.2, 1);
	glPopMatrix();

}
void bedRight() {
	glColor3f(0.64, 0.2, 0.2);
	glPushMatrix();
	glTranslatef(ROOM_LENGTH * (0.66), 0, 0);
	bedLeft();
	glPopMatrix();
}

void tableLeft() {

	float tableColor[4] = { 0.59, 0.29, 0.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, tableColor);
	glPushMatrix();
	glTranslatef(-6, 0, 0);
	int TABLE_LEG_SHIFT = 3;
	
	// main table
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH * (0.33), -ROOM_LENGTH * (0.20), ROOM_LENGTH / 2 + ROOM_LENGTH / 20);
	cuboid(ROOM_LENGTH * 2 / 10, 1, ROOM_LENGTH * 2.5 / 7);
	glPopMatrix();

	// Leg front left
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH * (0.33) + ROOM_LENGTH / 10 - 0.5 - TABLE_LEG_SHIFT, -ROOM_LENGTH * (0.35), ROOM_LENGTH / 2 + ROOM_LENGTH / 20 + ROOM_LENGTH * 2.5 / 14 - 0.5 - TABLE_LEG_SHIFT);
	cuboid(1, ROOM_LENGTH * (0.3), 1);
	glPopMatrix();

	// Leg front right
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH * (0.33) + ROOM_LENGTH / 10 - 0.5 - TABLE_LEG_SHIFT, -ROOM_LENGTH * (0.35), ROOM_LENGTH / 2 + ROOM_LENGTH / 20 - ROOM_LENGTH * 2.5 / 14 + 0.5 + TABLE_LEG_SHIFT);
	cuboid(1, ROOM_LENGTH * (0.3), 1);
	glPopMatrix();

	// Leg back left
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH * (0.33) - ROOM_LENGTH / 10 + 0.5 + TABLE_LEG_SHIFT, -ROOM_LENGTH * (0.35), ROOM_LENGTH / 2 + ROOM_LENGTH / 20 + ROOM_LENGTH * 2.5 / 14 - 0.5 - TABLE_LEG_SHIFT);
	cuboid(1, ROOM_LENGTH * (0.3), 1);
	glPopMatrix();

	// Leg back right
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH * (0.33) - ROOM_LENGTH / 10 + 0.5 + TABLE_LEG_SHIFT, -ROOM_LENGTH * (0.35), ROOM_LENGTH / 2 + ROOM_LENGTH / 20 - ROOM_LENGTH * 2.5 / 14 + 0.5 + TABLE_LEG_SHIFT);
	cuboid(1, ROOM_LENGTH * (0.3), 1);
	glPopMatrix();

	glPopMatrix();
}
void tableRight() {
	int TABLE_LEG_SHIFT = 3;
	glPushMatrix();
	glScalef(-1, 1, 1);
	tableLeft();
	glPopMatrix();

	float bgcolor[4] = { 0.0, 0.7, 0.5, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, bgcolor);
	glPushMatrix();
	glTranslatef(35,-30, 80);
	teapot();
	glPopMatrix();
}

void lightLeft() {
	float lightMaterialLeft[4] = { 1, 1, 1, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, lightMaterialLeft);
	if (light)
	{
		float emission[4] = { 0.6, 0.6, 0.6, 1 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	}

	glPushMatrix();
	glTranslatef(-ROOM_LENGTH * (0.5) + 2, ROOM_LENGTH * (0.30), 0);
	glutSolidCylinder(2, 7, 3, 1);
	glPopMatrix();

	//Light Source
	float lightPos1[] = { -ROOM_LENGTH * (0.5) +2, ROOM_LENGTH * (0.30), 0, 1 };
	float led[4] = { 0.5 , 0.5, 0.5, 1 };
	glPushMatrix();
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, led);
	glPopMatrix();

	float zero[] = { 0, 0, 0, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, zero);

}
void lightRight() {

	float lightMaterialRight[4] = { 1, 1, 1, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, lightMaterialRight);
	if (light)
	{
		float emission[4] = { 0.6, 0.6, 0.6, 1 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	}


	glPushMatrix();
	glTranslatef(ROOM_LENGTH * (0.5) - 2, ROOM_LENGTH * (0.30), 0);
	glRotatef(180, 0, 0, 1);
	glutSolidCylinder(2, 7, 3, 1);
	glPopMatrix();

	//Light Source
	float lightPos1[] = { ROOM_LENGTH * (0.5) - 2, ROOM_LENGTH * (0.30), 0, 1 };
	float led[4] = { 0.5, 0.5, 0.5, 1 };
	glPushMatrix();
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, led);
	glPopMatrix();


	float zero[] = { 0, 0, 0, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, zero);
}

void timer()
{
	if (fanSwitch)
	{
		t += fanSpeed;
	}
	glutPostRedisplay();
}
void fan()
{
	float lightMaterialLef[4] = { 0,0,0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, lightMaterialLef);


	float temp = 10;
	int lx, ly, lz;
	lx = ROOM_LENGTH / 5;
	ly = 0.2;
	lz = 3;
	glPushMatrix();
	glRotatef(240 + t, 0, -1, 0);
	glTranslatef(lx / 2, ROOM_LENGTH / 2 - temp, 0);
	cuboid(lx, ly, lz);
	glPopMatrix();



	glPushMatrix();
	glRotatef(120 + t, 0, -1, 0);
	glTranslatef(lx / 2, ROOM_LENGTH / 2 - temp, 0);
	cuboid(lx, ly, lz);
	glPopMatrix();



	glPushMatrix();
	glRotatef(t, 0, -1, 0);
	glTranslatef(lx / 2, ROOM_LENGTH / 2 - temp, 0);
	cuboid(lx, ly, lz);
	glPopMatrix();

}
void fanSwitchfun()
{
	fan();
}

void cloth_left()
{
	int density = 5; int l = 5;
	float clothcolor[4] = { 0.61, 0.88, 0.96, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, clothcolor);

	for (float i = 0; i < l * density; i += 0.2)
	{
		glColor3f(0.0, 1.0, 0.0);
		glPushMatrix();
		glTranslatef(-10, -1.5, ROOM_LENGTH *3/ 4 - 6);

		glTranslatef(0, i * l / density, amplitude* (pow(2, -i * l / (l * density))) * sin(-0.005 * t - (2 * 3.14 / wavelength) * i * l / density));
		//glutSolidSphere(0.7, 5, 5);
		glRotatef(90, 0, 1, 0);
		glutSolidCylinder(0.25, 18, 10, 10);
		glPopMatrix();
	}

}
void cloth_right() {
	glPushMatrix();
	glTranslatef(0, 0, 2);
	cloth_left();
	glPopMatrix();
}


void corridorLight()
{
	float lightMaterialLeft[4] = { 1, 1, 1, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, lightMaterialLeft);


	//Light Source
	float lightPos1[] = { 0, 0, -100, 1 };
	float led[4] = { 0.6 , 0.6, 0.6, 1 };
	glPushMatrix();
	glLightfv(GL_LIGHT3, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, led);
	glPopMatrix();



}
// all_objects_fun() function contains all objects in a room
void all_objects_fun() {
	
	lightLeft();
	lightRight();
	corridorLight();
	drawRoom();


	
	main_door();
	tableLeft();
	tableRight();

	almirahLeft();
	almirahRight();
	cloth_left();
	cloth_right();
	timer();
	fanSwitchfun();
	bedLeft();
	bedRight();
	windows();
	lightLeft();
	lightRight();

	float bgcolor[4] = { 0.0, 0.7, 0.5, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, bgcolor);


}
void multiroom_left() {

	// partition 1
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(ROOM_LENGTH / 2 + 2, 0, 5);
	cuboid(4, ROOM_LENGTH, ROOM_LENGTH * 3 / 2 + 10);
	glPopMatrix();

	for (int rooms = 1; rooms <= 4; rooms++) {
		// room
		glPushMatrix();
		glTranslatef((-ROOM_LENGTH - 4) * (rooms - 1), 0, 0);
		all_objects_fun();
		glPopMatrix();

		//partition
		glPushMatrix();
		glTranslatef(-ROOM_LENGTH / 2 - 2 + (-ROOM_LENGTH - 4) * (rooms - 1), 0, 5);
		cuboid(4, ROOM_LENGTH, ROOM_LENGTH * 3 / 2 + 10);
		glPopMatrix();
	}

}
void multiroom_right() {
	glPushMatrix();
	glTranslatef(-ROOM_LENGTH * 3 - 12, 0, -ROOM_LENGTH * 2);
	glRotatef(180, 0, 1, 0);
	multiroom_left();

	glPopMatrix();
}


void draw_scene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 1.0);
	glLoadIdentity();


	if (rotate == 0) {
		gluLookAt(eye_x_init, eye_y_init, eye_z_init, centerX, centerY, centerZ, 0.0, 1.0, 0.0);
	}
	else if (rotate == 1) {
		gluLookAt(eye_x, eye_y, eye_z, centerX, centerY, centerZ, 0.0, 1.0, 0.0);
	}

	multiroom_left();
	corridor();
	multiroom_right();

	glPopMatrix();
	glFlush();

}

// Main routine.
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(750, 690);
	glutInitWindowPosition(200, 0);
	glutCreateWindow("Hostel Room of IIT Goa");
	glutDisplayFunc(draw_scene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	setup();

	glutMainLoop();
}
