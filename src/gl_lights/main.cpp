#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

float fRotate;

// Whether to display in perspective mode
bool bPersp = true;
// Whether to display animation
bool bAnim = true;
// Whether to display in wire mode
bool bWire = false;

// The current window size (GLOBAL)
int initHeight = 480;
int initWidth = 480;

/* The global variables of parallel light */
float lightColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
float lightDirection[] = { 1.0f, 0.0f, 1.0f, 1.0f };

/* Spot light class definition */
class Spotlight
{
public:
	Spotlight() : angle(20.0f)
	{ // Constructor
		color = new float[4];
		position = new float[4];
		direction = new float[3];
		color[0] = 1.0f; color[1] = 1.0f; color[2] = 1.0f; color[3] = 1.0f;
		position[0] = -2.0f; position[1] = -0.5f; position[2] = 2.0f; position[3] = 1.0f;
		direction[0] = 1.0f; direction[1] = 0.8f; direction[2] = -0.4f;
	}

	~Spotlight()
	{ // Destructor
		delete[] color;
		delete[] position;
		delete[] direction;
	}

	// The color of spotlight
	float* color;
	// The position of spotlight
	float* position;
	// The direction of spotlight
	float* direction;
	// The light angle of spotlight
	float angle;
};

// Add a spotlight to the scene
Spotlight spotlight;

// Eye position and the center of objects
float eye[] = { 0.0f, 0.5f, 3.0f };
float center[] = { 0.0f, 0.5f, -5.0f };

/* Default color using namespace */
namespace Color
{
	// Basic color defined by RGBA value
	float white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float pureGold[] = { 0.85f, 0.96f, 0.15f, 1.0f };
	float rostyBrown[] = { 0.75f, 0.56f, 0.56f, 1.0f };
	float darkGray[] = { 0.20f, 0.20f, 0.20f, 1.0f };
	float blueViolet[] = { 0.54f, 0.17f, 0.89f, 1.0f };
	float steelBlue[] = { 0.27f, 0.51f, 0.71f, 1.0f };
	float fireBrick[] = { 0.70f, 0.13f, 0.13f, 1.0f };
}

/* The function to draw a cuboid */
void drawCuboid(float* materialColor)
{
	glScalef(1.0f, 1.0f, 3.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

	// The specular color is BLACK! You can reset it.
	glMaterialfv(GL_FRONT, GL_SPECULAR, Color::black);
	glutSolidCube(1.0f);
}

void drawCuboid(float red, float green, float blue, float transparence)
{
	// Given RGBA color instead of an array
	float materialColor[4];
	materialColor[0] = red; materialColor[1] = green;
	materialColor[2] = blue; materialColor[3] = transparence;

	glScalef(1.0f, 1.0f, 3.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

	// The specular color is BLACK! You can reset it.
	glMaterialfv(GL_FRONT, GL_SPECULAR, Color::black);
	glutSolidCube(1.0f);
}

/* The function to draw objects */
void drawScene()
{
	// Draw a teapot
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 5.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Color::pureGold);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Color::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 55.0);
	glutSolidTeapot(1.0);
	glPopMatrix();

	// Draw the top of our table
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 3.5f);
	glScalef(5.0f, 4.0f, 1.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Color::rostyBrown);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Color::black);
	glutSolidCube(1.0);
	glPopMatrix();

	// Draw four table legs
	glPushMatrix();
	glTranslatef(1.5f, 1.0f, 1.5f);
	drawCuboid(Color::darkGray);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5f, 1.0f, 1.5f);
	drawCuboid(Color::blueViolet);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5f, -1.0f, 1.5f);
	drawCuboid(Color::steelBlue);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5f, -1.0f, 1.5f);
	drawCuboid(Color::fireBrick);
	glPopMatrix();
}

/* The function to update view */
void updateView(int width, int height)
{
	// Reset the current viewport
	glViewport(0.0f, 0.0f, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Perspective setting
	// If bPersp = false, then construct orthogonal projection
	if (bPersp) gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
	else glOrtho(-3.0f, 3.0f, -3.0f, 3.0f, -100.0f, 100.0f);

	// Select The Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
}

void reshape(int width, int height)
{
	// Height is not allowed to be zero
	if (height == 0) height = 1;

	// Call function to update view
	updateView(width, height);
}

void idle()
{
	glutPostRedisplay();
}

/**********************************************************************
* KEYBOARD FUNCTION:
* 	This function defines keyboard controller.
* 	Key function - EXPLANATION:
* 
* Fundamental cases:
*	@`x`: Quit this window.
* 	@`z`: Whether to change perspective mode.
*	@` `: Whether to do rotation animation.
* 	@`c`: Whether to show objects in wire mode.
*
* Eye and center controller
* 	@`a`, `d`, `w`, `s`: Malposition.
* 	@`q`: Walk closer to the objects, so that they look bigger.
* 	@`e`: Keep larger distance, so that the objects look smaller.
*
* Light position controller
* 	@`j`, `k`, `l`: Change the position of light
* 	Press the `CTRL` button to do operations reversely!
* 
* Spot light position controller
* 	@`u`, `i`, `o`: Change the position of the new added spotlight
* 	@`p`: Change the angle of the spotlight
* 	Press the `CTRL` button to do operations reversely!
*
* Light color controller
* 	@`r`, `g`, `b`: Change the rgba value of the light color
* 	Press the `CTRL` button to do operations reversely!
* 	Press the `CTRL` and `ALT` button at the same time to set the
* 	corresponding `rgba` value equaling to 1.
* 	
**********************************************************************/

/* Keyboard function */
void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	// Foundamental cases
	case 'x': { exit(0); break; }
	case 'z': { bPersp = !bPersp; break; }
	case ' ': { bAnim = !bAnim; break; }
	case 'c': { bWire = !bWire; break; }
	// Eye and center controller
	case 'a': { eye[0] += 0.05f; center[0] += 0.05f; break; }
	case 'd': { eye[0] -= 0.05f; center[0] -= 0.05f; break; }
	case 'w': { eye[1] -= 0.05f; center[1] -= 0.05f; break; }
	case 's': { eye[1] += 0.05f; center[1] += 0.05f; break; }
	case 'q': { eye[2] -= 0.05f; center[2] -= 0.05f; break; }
	case 'e': { eye[2] += 0.05f; center[2] += 0.05f; break; }
	// Light position controller
	case 'j': { lightDirection[0] += 0.05f; break; }
	case 'j'&0x1f: { lightDirection[0] -= 0.05f; break; }
	case 'k': { lightDirection[1] -= 0.05f; break; }
	case 'k'&0x1f: { lightDirection[1] += 0.05f; break; }
	case 'l': { lightDirection[2] -= 0.05f; break; }
	case 'l'&0x1f: { lightDirection[2] += 0.05f; break; }
	// Spot light direction controller
	case 'u': { spotlight.direction[0] += 0.05f; break; }
	case 'u'&0x1f: { spotlight.direction[0] -= 0.05f; break; }
	case 'i': { spotlight.direction[1] -= 0.05f; break; }
	case 'i'&0x1f: { spotlight.direction[1] += 0.05f; break; }
	case 'o': { spotlight.direction[2] -= 0.05f; break; }
	case 'o'&0x1f: { spotlight.direction[2] += 0.05f; break; }
	case 'p': { if (spotlight.angle >= 1) spotlight.angle -= 1; break; }
	case 'p'&0x1f: { if (spotlight.angle <= 179) spotlight.angle += 1; break; }
	// Light color controller
	case 'r': { if (lightColor[0] >= 0.05f) lightColor[0] -= 0.05f; break; }
	case 'g': { if (lightColor[1] >= 0.05f) lightColor[1] -= 0.05f; break; }
	case 'b': { if (lightColor[2] >= 0.05f) lightColor[2] -= 0.05f; break; }
	case 'r'&0x1f:
	{ // The `CTRL` key is down and set `r` value of light
		int mod = glutGetModifiers();
		if (mod == (GLUT_ACTIVE_CTRL | GLUT_ACTIVE_ALT)) { lightColor[0] = 1.0f; break; }
		else { if (lightColor[0] <= 0.95f) lightColor[0] += 0.05f; break; }
	}
	case 'g'&0x1f:
	{ // The `CTRL` key is down and set `g` value of light
		int mod = glutGetModifiers();
		if (mod == (GLUT_ACTIVE_CTRL | GLUT_ACTIVE_ALT)) { lightColor[1] = 1.0f; break; }
		else { if (lightColor[1] <= 0.95f) lightColor[1] += 0.05f; break; }
	}
	case 'b'&0x1f:
	{ // The `CTRL` key is down and set `b` value of light
		int mod = glutGetModifiers();
		if (mod == (GLUT_ACTIVE_CTRL | GLUT_ACTIVE_ALT)) { lightColor[2] = 1.0f; break; }
		else { if (lightColor[2] <= 0.95f) lightColor[2] += 0.05f; break; }
	}
	}
}

/* The callback function to draw scene */
void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// The position of person to look at objects we draw
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0.0f, 1.0f, 0.0f);

	// Whether the display mode of objects is `WIRE`
	if (bWire) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	
	// The parallel light settings
	glLightfv(GL_LIGHT0, GL_POSITION, lightDirection);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);

	// The spot light settings
	glLightfv(GL_LIGHT1, GL_DIFFUSE, spotlight.color);
	glLightfv(GL_LIGHT1, GL_POSITION, spotlight.position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlight.direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotlight.angle);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.5f);

	// Enable or disable light (spot light)
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// Rotate operation
	glRotatef(fRotate, 0.0f, 1.0f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glScalef(0.2f, 0.2f, 0.2f);
	// Draw the objects
	drawScene();

	// Do animation
	if (bAnim) fRotate += 0.5f;
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(initWidth, initHeight);
	glutCreateWindow("OpenGL - light");
	
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}