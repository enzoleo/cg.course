#include <stdlib.h>
#include <GL/glut.h>


float fTranslate;
float fRotate;
float fScale = 1.0f;

bool bPersp = false;
bool bAnim = false;
bool bWire = false;

int wHeight = 0;
int wWidth = 0;

float myteapot[] = { 0, 0, 0 };

void Draw_Leg()
{
    glScalef(1, 1, 3);
    glutSolidCube(1.0);
}

void Draw_Scene()
{
    glPushMatrix();
    glTranslatef(0, 0, 4 + 1);

    glRotatef(90, 1, 0, 0);
    glTranslatef(myteapot[0], 0, myteapot[1]);
    glRotatef(myteapot[2], 0, 1, 0);
    glutSolidTeapot(1);
    
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 3.5);
    glScalef(5, 4, 1);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5, 1, 1.5);
    Draw_Leg();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5, 1, 1.5);
    Draw_Leg();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5, -1, 1.5);
    Draw_Leg();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5, -1, 1.5);
    Draw_Leg();
    glPopMatrix();
}

void updateView(int width, int height)
{
	// Reset The Current Viewport
	glViewport(0, 0, width, height);

	// Select The Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (bPersp) gluPerspective(60, 1, 1, 100);
	else glOrtho(-2, 2, -2, 2, -100, 100);
	
	// Select The Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
}

void reshape(int width, int height)
{
    if (height == 0) height = 1;

    wHeight = height;
    wWidth = width;

    updateView(wHeight, wWidth);
}

void idle()
{
    glutPostRedisplay();
}

float eye[] = { 0, 0, 8 };
float center[] = { 0, 0, 0 };


void key(unsigned char k, int x, int y)
{
    switch (k)
    {
    case 27:
    case 'q': { exit(0); break; }
    case 'p': { bPersp = !bPersp; updateView(wHeight, wWidth); break; }
    case ' ': { bAnim = !bAnim; break; }
    case 'o': { bWire = !bWire; break; }
    case 'a': { eye[0] -= 1; break; }
    case 'd': { eye[0] += 1; break; }
    case 'w': { eye[1] += 1; break; }
    case 's': { eye[1] -= 1; break; }
    case 'z': { eye[2] += 1; break; }
    case 'c': { eye[2] -= 1; break; } 
    case 'l': { myteapot[0] += 0.2; if (myteapot[0] > 2.5) myteapot[0] = 2.5; break; }
    case 'j': { myteapot[0] -= 0.2; if (myteapot[0] < -2.5) myteapot[0] = -2.5; break; }
    case 'i': { myteapot[1] -= 0.2; if (myteapot[1] < -2) myteapot[1] = -2; break; }
    case 'k': { myteapot[1] += 0.2; if (myteapot[1] > 2) myteapot[1] = 2; break; }
    case 'e': { myteapot[2] += 5; break; }
    }
}


void redraw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset The Current Modelview Matrix
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2],
        center[0], center[1], center[2],
        0, 1, 0);

    if (bWire) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_pos[] = { 5,5,5,1 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, white);
    glEnable(GL_LIGHT0);

    //glTranslatef(0.0f, 0.0f,-6.0f);// Place the triangle at Center
    glRotatef(fRotate, 0, 1.0f, 0);
    glRotatef(-90, 1, 0, 0);
    glScalef(0.2, 0.2, 0.2);
    Draw_Scene();

    if (bAnim) fRotate += 0.5f;
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(480, 480);
    glutCreateWindow("Simple GLUT App");

    glutDisplayFunc(redraw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
