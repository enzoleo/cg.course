/// ////////////////////////////////////////////////////////////////////
/// EXPERIMENT 4
/// Author: Peiyu Liao
/// Date: 2016.11.24
///
/// File: main.cpp
/// This C++ source file aims to solve the problem 4.
///
/// ATTENTION:
/// The two files are needed in this poject:
/// 	stanford_bunny.cpp	stanford_bunny.h
/// Make sure you have these files. You can find them on the Internet.
/// ////////////////////////////////////////////////////////////////////  

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "GL/glut.h"

#include "stanford_bunny.h"

/// ////////////////////////////////////////////////////////////////////
/// GLOBAL VARIABLES
///
/// The following variables are all global variables which are used in
/// specific functions defined below.
///
/// @param fTranslate: The variable about translation.
/// @param fRotate: The variable about rotation.
/// @param fScale: The variable about stretching transformation.
/// @param fDistance: The variable about camera position.
/// --------------------------------------------------------------------
/// @param bPersp: The variable about perspective.
/// @param bAnim: The variable about animation.
/// @param bWire: The variable about the graphic structure.
/// --------------------------------------------------------------------
/// @param bTableList: It determines whether to draw a table.
/// @param bBunnyList: It determines whether to draw a bunny.
/// @param bTeapotList: It determines whether to draw a teapot.
/// --------------------------------------------------------------------
/// @param tableList: The variable to generate a GL-tablelist.
/// @param bunnyList: The variable to generate a GL-bunnylist.
/// @param teapotList: The variable to generate a GL-teapotlist.
/// ////////////////////////////////////////////////////////////////////

// The variables about transformation
float fTranslate;
float fRotate;
float fScale = 1.0f;
float fDistance = 0.2f;

// The variables about camera and animation
bool bPersp = false;
bool bAnim = false;
bool bWire = false;

// The variables determining whether to draw objects
bool bTable = true;
bool bBunny = true;
bool bTeapot = true;
bool bLists = true;

// The variables generating GL-lists
GLint tableList = 0;
GLint bunnyList = 0;
GLint teapotList = 0;

// Also global variables but only used in camera settings
float eye[] = {0, 0, 8};
float center[] = {0, 0, 0};

void drawFixedTable()
{
	// Draw a table board
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 3.5f);
	glScalef(5.0f, 4.0f, 1.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// Draw four legs
	glPushMatrix();
	glTranslatef(1.5f, 1.0f, 1.5f);
	glScalef(1.0f, 1.0f, 3.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5f, 1.0f, 1.5f);
	glScalef(1.0f, 1.0f, 3.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5f, -1.0f, 1.5f);
	glScalef(1.0f, 1.0f, 3.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5f, -1.0f, 1.5f);
	glScalef(1.0f, 1.0f, 3.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
}

void drawFixedBunny()
{
	glPushMatrix();

	// The size and position of bunny can be edited here
	glTranslatef(1.5f, 0.0f, 5.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glScalef(4.0f, 4.0f, 4.0f);
	glColor3f(0.5f, 0.5f, 0.5f);

	// This function is defined in stanford_bunny.h
	DrawBunny();
	glPopMatrix();
}

void drawFixedTeapot()
{
	glPushMatrix();

	// The size and position of teapot can be edited here
	glTranslatef(-1.5f, 0.0f, 5.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidTeapot(1.0f);
	glPopMatrix();
}

// Generate the table GL-list
GLint GenTableList()
{
	GLint lid = glGenLists(1);
	glNewList(lid, GL_COMPILE);
	drawFixedTable();
	glEndList();

	return lid;
}

// Generate the bunny2 GL-list
GLint GenBunnyList()
{
	GLint lid = glGenLists(1);
	glNewList(lid, GL_COMPILE);
	drawFixedBunny();
	glEndList();

	return lid;
}

// Generate the teapot GL-list
GLint GenTeapotList()
{
	GLint lid = glGenLists(1);
	glNewList(lid, GL_COMPILE);
	drawFixedTeapot();
	glEndList();

	return lid;
}

void drawTableList() { glCallList(tableList); }
void drawBunnyList() { glCallList(bunnyList); }
void drawTeapotList() { glCallList(teapotList); }

void drawScene()
{
	// This function draws the whole objects
	if (bBunny) drawFixedBunny();
	if (bTeapot) drawFixedTeapot();
	if (bTable) drawFixedTable();
}

void drawSceneLists()
{
	// This function draws the whole objects by calling lists
	if (bBunny) drawBunnyList();
	if (bTeapot) drawTeapotList();
	if (bTable) drawTableList();
}

void updateView(int width, int height)
{
	// Reset the current viewport
	glViewport(0, 0, width, height);

	// Select the projection matrix
	glMatrixMode(GL_PROJECTION);
	// Reset the projection matrix
	glLoadIdentity();

	if (bPersp == 1) gluPerspective(45.0f, 1.0f, 1.0f, 100.0f);
	else glOrtho(-3.0f, 3.0f, -3.0f, 3.0f, -100.0f, 100.0f);

	// Select the modelview matrix
	glMatrixMode(GL_MODELVIEW);
}

void reshape(int width, int height)
{
	// Prevent A divide by zero
	if (height == 0) height=1;
	updateView(height, width);
}

void idle()
{
	glutPostRedisplay();
}

void key(unsigned char k, int x, int y)
{
	switch(k)
	{
	case 27:
	case 'q': { exit(0); break; }
	case 'p': { bPersp = !bPersp; updateView(560, 560); break; }
	case ' ': { bAnim = !bAnim; break; }
	case 'o': { bWire = !bWire; break; }
	case 'a': { eye[0] = eye[0] + fDistance; center[0] = center[0] + fDistance; break; }
	case 'd': { eye[0] = eye[0] - fDistance; center[0] = center[0] - fDistance; break; }
	case 'w': { eye[1] = eye[1] - fDistance; center[1] = center[1] - fDistance; break; }
	case 's': { eye[1] = eye[1] + fDistance; center[1] = center[1] + fDistance; break; }
	case 'z': { eye[2] = eye[2] * 0.95; break; }
	case 'c': { eye[2] = eye[2] * 1.05; break; }
	case '1': { bTable = !bTable; break; }
	case '2': { bTeapot = !bTeapot; break; }
	case '3': { bBunny = !bBunny; break; }
	case 'l': { bLists = !bLists; break; }
	default: break;
	}
}

void getFPS()
{
	static int frame = 0, time, timebase = 0;
	static char buffer[256];

	// Mode display
	char mode[64];
	if (bLists) strcpy(mode, "display list");
	else strcpy(mode, "naive");

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000)
	{ // Calculate and print FPS data on the window screen
		sprintf(buffer,"FPS:%4.2f %s", frame * 1000.0 / (time - timebase), mode);
		timebase = time;
		frame = 0;
	}

	glDisable(GL_DEPTH_TEST);
	// Select the projection matrix
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, 480.0f, 0.0f, 480.0f, -1.0f, 1.0f);

	// Select the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2f(10, 10);

	for (char* c = buffer; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

	// Pop the projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// Pop the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
	glEnable(GL_DEPTH_TEST);
}

void redraw()
{
	// Clear color and depth buffer bit
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Set the camera position and the object position
	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);

	// Choose the showing structure
	if (bWire) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	// Lighting settings
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 5, 5, 5, 1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,white);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);

	glRotatef(fRotate, 0, 1.0f, 0);
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);

	// Draw the whole scene
	if (bLists) drawSceneLists();
	else drawScene();

	// Animation settings (rotate it if doing this)
	if (bAnim) fRotate += 0.5f;
	getFPS();

	glutSwapBuffers();
}

int main (int argc,  char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	// Create a window
	glutInitWindowSize(480,480);
	glutCreateWindow("Simple GLUT App");

	// Table lists valuation
	tableList = GenTableList();
	bunnyList = GenBunnyList();
	teapotList = GenTeapotList();

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);

	// Keyboard function
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}
